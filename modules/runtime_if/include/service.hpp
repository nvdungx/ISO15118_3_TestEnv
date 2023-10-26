/** @file service.hpp
 *  @brief Function prototypes for the service module.
 *
 *  This contains the prototypes for the service module
 *  and eventually any macros, constants, or needed global variables.
 *
 *  @author DungNV (Jun)
 *  @bug TBD.
 */

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
    /** @brief Constructor
     *
     *  To create a instance for runtime environment of the test system. Only 1 instance per test system.
     *
     *  @param threads Number of threads to be used for the test runtime environment.
     *  @param pool True = use thread pool(i.e. 1 io_service per thread pool), False = per thread design (1 io_service per thread).
     *  @return Void.
     */
    Service(size_t threads = 1, bool pool = false);

    /** @brief Copy constructor
     *
     *  Deleted.
     *
     *  @return Void.
     */
    Service(const Service &) = delete;

    /** @brief Move constructor
     *
     *  Deleted.
     *
     *  @return Void.
     */
    Service(Service &&) = delete;

    /** @brief Destructor
     *
     *  Default.
     *
     *  @return Void.
     */
    ~Service() = default;

    /** @brief Copy operator
     *
     *  Deleted.
     *
     *  @return Service&
     */
    Service &operator=(const Service &) = delete;

    /** @brief Move operator
     *
     *  Deleted.
     *
     *  @return Service&&
     */
    Service &operator=(Service &&) = delete;

    /** @brief Return number of threads used by runtime environment.
     *
     *  @return size_t: number of threads
     */
    size_t threads(void) const noexcept { return _thread_list.size(); }

    /** @brief Execution status of runtime environment
     *
     *  @return bool: true = runtime environment is started, false = otherwise
     */
    bool is_started(void) const noexcept { return _started; }

    /** @brief thread pool usage status.
     *
     *  @return bool: true = a single context and thread pool, false = io_context per thread
     */
    bool is_strand_required(void) const noexcept { return _pool_used; }

    /** @brief Start execution of runtime environment. This should be call once per program execution.
     *
     *  @return bool: true = success, false = fail
     */
    bool start(void);

    /** @brief Stop execution of runtime environment.
     *
     *  @return bool: true = success, false = fail
     */
    bool stop(void);

    /** @brief Restart execution of runtime environment.
     *
     *  @return bool: true = success, false = fail
     */
    bool restart(void);

    /** @brief Return the next underlying asio::io_service instance in Service list.
     *
     *  @return std::shared_ptr<boost::asio::io_service>&: ref pointer to asio::io_service
     */
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