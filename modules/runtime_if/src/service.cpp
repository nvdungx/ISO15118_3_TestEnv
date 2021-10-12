#include <spdlog/spdlog.h>
#include <spdlog/fmt/fmt.h>
#include <ostream>
#include "service.hpp"

#define SLOGW(msg) spdlog::warn("{0} {1}: {2}", __FILE__, __LINE__, msg)
#define SLOGI(msg) spdlog::info("{0} {1}: {2}", __FILE__, __LINE__, msg)
#define SLOGE(msg) spdlog::error("{0} {1}: {2}", __FILE__, __LINE__, msg)
#define SLOGD(msg) spdlog::debug("{0} {1}: {2}", __FILE__, __LINE__, msg)

namespace TestLib
{

  Service::Service(size_t threads, bool pool)
      : _io_service_index(0), _started(false), _pool_used(pool)
  {
    if (0 == threads)
    {
      // only 1 main thread
      _service_list.emplace_back(std::make_shared<boost::asio::io_service>());
      _pool_used = false;
    }
    else
    {
      // use single io_service with threadpool
      if (_pool_used)
      {
        // create 1 io_service
        _service_list.emplace_back(std::make_shared<boost::asio::io_service>());
        for (size_t i = 0; i < threads; i++)
        {
          _thread_list.emplace_back(std::thread());
        }
        // explicit strand is an instance of strand<> or io_context::strand
        _strand = std::make_shared<boost::asio::io_service::strand>(*_service_list[0]);
      }
      // io_service per thread design
      else
      {
        for (size_t i = 0; i < threads; i++)
        {
          // io_context::run() from only one thread means all event handlers execute in an implicit strand,
          // due to the io_context's guarantee that handlers are only invoked from inside run().
          _service_list.emplace_back(std::make_shared<boost::asio::io_service>());
          _thread_list.emplace_back(std::thread());
        }
      }
    }
  }

  bool Service::start(void)
  {
    bool ret_status = false;
    if (!is_started())
    {
      _io_service_index = 0;
      auto self(this->shared_from_this());
      // self shared_ptr to make sure obj exit until object handler completed.
      auto start_handler = [this, self]()
      {
        if (!is_started())
        {
          _started = true;
          on_started();
        }
        else
        {
          return;
        }
      };
      // post start_handler to notify service started
      if (_pool_used)
      {
        boost::asio::post(*_strand, start_handler);
      }
      else
      {
        boost::asio::post(*_service_list[0], start_handler);
      }
      // start service in working threads
      for (size_t i = 0; i < _thread_list.size(); i++)
      {
        // incase of pool > n threads & 1 io_service > _service_list[0]
        // else n threads & n io_services > _service_list[0:n-1]
        _thread_list[i] = std::thread(
            [this, self, i]()
            {
              service_thread(self, _service_list[i % _service_list.size()]);
            });
      }
      // wait for service run
      while (!is_started())
      {
        std::this_thread::yield();
      }
      ret_status = true;
    }
    else
    {
      // do nothing
    }
    return ret_status;
  }

  bool Service::stop(void)
  {
    bool ret_status = false;
    if (is_started())
    {
      auto self(this->shared_from_this());
      // stop operation
      auto stop_handler = [this, self]()
      {
        if (is_started())
        {
          for (auto &service : _service_list)
          {
            service->stop();
          }
          _started = false;
          on_stopped();
        }
        else
        {
          return;
        }
      };
      // post stop_handler
      if (_pool_used)
      {
        boost::asio::post(*_strand, stop_handler);
      }
      else
      {
        boost::asio::post(*_service_list[0], stop_handler);
      }
      // join all thread
      for (auto &&thread : _thread_list)
      {
        thread.join();
      }
      // wait for service stop
      while (is_started())
      {
        std::this_thread::yield();
      }
      ret_status = true;
    }
    else
    {
      // do nothing
    }
    return ret_status;
  }

  bool Service::restart(void)
  {
    bool ret_status = false;
    if (stop())
    {
      // init new asio service
      for (size_t i = 0; i < _service_list.size(); i++)
      {
        _service_list[i]->restart();
      }
      ret_status = start();
    }
    else
    {
      // do nothing
    }
    return ret_status;
  }

  void Service::service_thread(const std::shared_ptr<Service> &service, const std::shared_ptr<boost::asio::io_service> &io_service)
  {
    service->on_thread_initialized();
    try
    {
      // create work to keep io_service run
      boost::asio::executor_work_guard work(io_service->get_executor());
      do
      {
        try
        {
          io_service->run();
          break;
        }
        catch (const boost::system::error_code &ex)
        {
          if (boost::asio::error::not_connected == ex.value())
          {
            continue;
          }
          else
          {
            throw ex;
          }
        }
      } while (service->is_started());
    }
    catch (const boost::system::error_code &ex)
    {
      //
    }
    catch (const std::exception &ex)
    {
      //
    }
    catch (...)
    {
      SLOGE("Asio service thread terminated!");
    }
    service->on_thread_cleanup();
  }

  void Service::on_thread_initialized(void)
  {
    std::stringstream thread_id;
    thread_id << std::this_thread::get_id();
    SLOGD(fmt::format("Service thread {} stated", thread_id.str()));
  }

  void Service::on_thread_cleanup(void)
  {
    std::stringstream thread_id;
    thread_id << std::this_thread::get_id();
    SLOGD(fmt::format("Service thread {} stopped", thread_id.str()));
  }

  void Service::on_started(void)
  {
    SLOGD("Service started");
  }

  void Service::on_stopped(void)
  {
    SLOGD("Service stopped");
  }
} // namespace TestLib