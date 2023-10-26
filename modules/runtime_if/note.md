# this module handle io_context for asynchronous operation

using asio, program has to make sure object life-time when waiting for completion handler to finish.

- runtime_if::service provide a wrapper/management over the boost.asio, which shall be input to other component constructor as reference to runtime environment execution context
- any asynchronous execution jobs(testing action, network communication, hardware I/O control, etc.) of test module can be pushed to io_context and be processed by runtime environment.
- runtime_if::service shall provide a single execution context (io_context) for whole testing environment and a thread pool(provide parallel processing capability)

