#pragma once

#include <thread>
#include <asio.hpp>

namespace cpp_redis {

namespace network {

//! asio io service wrapper
class io_service {
public:
    //! ctor & dtor
    io_service(void);
    ~io_service(void);

    //! copy ctor & assignment operator
    io_service(const io_service&) = delete;
    io_service& operator=(const io_service&) = delete;

public:
    //! methods
    void run(void);
    void post(const std::function<void()>& fct);

    //! getters
    asio::io_service& get(void);

private:
    asio::io_service m_io_service;
    asio::io_service::work m_work;
    std::thread m_io_service_thread;
};

} //! network

} //! cpp_redis
