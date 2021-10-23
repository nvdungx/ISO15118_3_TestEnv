#ifndef __PLATFORM_ADAPTER_H__
#define __PLATFORM_ADAPTER_H__

#include <cstdint>
#include <vector>
#include <thread>
#include <unordered_map>
#include <memory>
#include "service.hpp"

namespace TestLib
{
  /* provide general timer operation */
  class PlatformAdapter
  {
  private:
    /* data */
  public:
    PlatformAdapter(/* args */) {}
    ~PlatformAdapter() {}
  };

  uint32_t get_crc32(const std::vector<uint8_t> &dataArr);
  uint32_t get_crc32_tb(const std::vector<uint8_t> &dataArr);

  class Timer
  {
  private:
    // Asio IO service
    std::shared_ptr<boost::asio::io_service> _io_service;
    // Asio service strand for serialized handler execution
    boost::asio::io_service::strand _strand;
    bool _strand_required;

    std::string id;
    float timeout_value;
    // timeout flag
    std::atomic_bool _timeout;
  public:
    Timer(const std::shared_ptr<Service> &service, const std::string &timer_id, float timeout_val=0)
      : _io_service(service->get_asio_service()), _strand(*_io_service),
        _strand_required(service->is_strand_required()),
        id(std::move(timer_id)), timeout_value(timeout_val)
    {
    }
    ~Timer() {}
    bool start(void);
    bool start(float val);
    bool stop(void);
    float read(void);
    bool running(void);
    bool timeout(void);
  };

  class TimerFactory
  {
  private:
    static std::shared_ptr<Service> _service;
    static std::unordered_map<std::string, std::shared_ptr<Timer>> _timer_list;

  public:
    ~TimerFactory() {
      _timer_list.clear();
      _service.reset();
    }
    TimerFactory() = delete;
    TimerFactory(TimerFactory &) = delete;
    TimerFactory &operator=(const TimerFactory &) = delete;
    static void start(const std::shared_ptr<Service> &service) {
        _service = service;
    }
    static std::shared_ptr<Timer> &create_timer(const std::string &timer_id, float timeout_val=0) {
      if (_timer_list.find(timer_id) == _timer_list.end())
        _timer_list[timer_id] = std::make_shared<Timer>(_service, timer_id, timeout_val);
      return _timer_list[timer_id];
    }
    static bool remove_timer(const std::string &timer_id) {
      return (1 == _timer_list.erase(timer_id));
    }
    static void remove_all(void) {
      _timer_list.clear();
    }
    void stop_all(void) {
      for (auto &&timer : _timer_list)
      {
        timer.second->stop();
      }
    }
  };

} // namespace TestLib
#endif // __PLATFORM_ADAPTER_H__