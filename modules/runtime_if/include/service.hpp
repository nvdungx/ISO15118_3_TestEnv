#ifndef __SERVICE_H__
#define __SERVICE_H__

#include <boost/asio.hpp>
#include <thread>
#include <atomic>
#include "datatype.hpp"

namespace TestLib
{

  /* io_service per thread to run asynchronous operation */
  /* io_service bound to thread-pool, required strand to serialize operation */
  class Service : public std::enable_shared_from_this<Service>
  {
  private:
    // threads used for io_service
    std::vector<std::thread> _thread_list;
    // list of io_service (1 if use threadpool, = number of thread when using per-thread)
    std::vector<std::shared_ptr<boost::asio::io_service>> _service_list;
    // strand, require for sequence execution if using threadpool
    std::shared_ptr<boost::asio::io_service::strand> _strand;
    // return a io_service_index
    std::atomic<size_t> _io_service_index;
    // state of Service
    std::atomic_bool _started;
    // true use pool or false use per-thread
    std::atomic_bool _pool_used;

  public:
    Service(size_t threads = 1, bool pool = false);
    Service(const Service &) = delete;
    Service(Service &&) = delete;
    ~Service() = default;

    Service &operator=(const Service &) = delete;
    Service &operator=(Service &&) = delete;

    // return number of threads
    size_t threads(void) const noexcept { return _thread_list.size(); }
    bool is_started(void) const noexcept { return _started; }
    bool is_strand_required(void) const noexcept { return _pool_used; }
    bool start(void);
    bool stop(void);
    bool restart(void);
    std::shared_ptr<boost::asio::io_service> &get_asio_service(void) noexcept {
      return _service_list[++_io_service_index % _service_list.size()];
    }
    template <typename CompletionHandler>
    BOOST_ASIO_INITFN_RESULT_TYPE(CompletionHandler, void()) dispatch(BOOST_ASIO_MOVE_ARG(CompletionHandler) handler)
    {
      if (_pool_used)
      {
        return boost::asio::dispatch(*_strand, handler);
      }
      else
      {
        return boost::asio::dispatch(*get_asio_service(), handler);
      }
    }
    template <typename CompletionHandler>
    BOOST_ASIO_INITFN_RESULT_TYPE(CompletionHandler, void()) post(BOOST_ASIO_MOVE_ARG(CompletionHandler) handler)
    {
      if (_pool_used)
      {
        return boost::asio::post(*_strand, handler);
      }
      else
      {
        return boost::asio::post(*get_asio_service(), handler);
      }
    }
  protected:
    virtual void on_started(void);
    virtual void on_stopped(void);
    virtual void on_thread_initialized(void);
    virtual void on_thread_cleanup(void);

  private:
    static void service_thread(const std::shared_ptr<Service> &service, const std::shared_ptr<boost::asio::io_service> &io_service);
  };

} // namespace TestLib
#endif // __SERVICE_H__