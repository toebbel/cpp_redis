#include <cpp_redis/cpp_redis>

#include <signal.h>
#include <iostream>

volatile std::atomic_bool should_exit(false);
asio::io_service io_service;
cpp_redis::redis_subscriber sub(io_service);

void
sigint_handler(int) {
    std::cout << "disconnected (sigint handler)" << std::endl;
    sub.disconnect();
}

int
main(void) {
    sub.set_disconnection_handler([] (cpp_redis::redis_subscriber&) {
        std::cout << "sub disconnected (disconnection handler)" << std::endl;
        should_exit = true;
    });

    sub.connect();

    sub.subscribe("some_chan", [] (const std::string& chan, const std::string& msg) {
        std::cout << "MESSAGE " << chan << ": " << msg << std::endl;
    });
    sub.psubscribe("*", [] (const std::string& chan, const std::string& msg) {
        std::cout << "PMESSAGE " << chan << ": " << msg << std::endl;
    });

    signal(SIGINT, &sigint_handler);
    while (not should_exit);

    return 0;
}
