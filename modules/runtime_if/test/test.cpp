#include "service.hpp"
#include "spdlog/spdlog.h"
#include "datatype.hpp"
#include <boost/asio/deadline_timer.hpp>
#include <boost/asio/steady_timer.hpp>

using namespace TestLib;
void print(const boost::system::error_code& /*e*/)
{
  spdlog::info("call timeout");
}
int main(int argc, char **argv)
{
  (void)argc;
  (void)argv;
  spdlog::set_level(spdlog::level::level_enum::debug);
  auto temp = std::make_shared<Service>(2, true);
  temp->start();
  boost::asio::steady_timer timer1(*temp->get_asio_service(),std::chrono::seconds(2));
  boost::asio::steady_timer timer2(*temp->get_asio_service(),std::chrono::seconds(4));
  spdlog::info("befor wait");
  timer1.wait();
  spdlog::info("wait 2s");
  timer1.async_wait([](const boost::system::error_code&){
    std::stringstream thread_id;
    thread_id << std::this_thread::get_id();
    spdlog::debug("timer1 timeout! {}", thread_id.str());
  });
  timer2.async_wait([](const boost::system::error_code&){
    std::stringstream thread_id;
    thread_id << std::this_thread::get_id();
    spdlog::debug("timer2 timeout! {}", thread_id.str());
  });
  std::cin.get();
  temp->stop();
  return 0;
}