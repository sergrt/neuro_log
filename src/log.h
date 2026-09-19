#pragma once

#include <chrono>
#include <format>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>

namespace neuro_trace {

class Log final {
private:
    Log() = default;
    Log(const Log&) = delete;
    Log(Log&&) = delete;
    Log& operator=(const Log&) = delete;
    Log& operator=(Log&&) = delete;

    template<typename T>
    static auto ToPrintable(const T& val) requires std::is_enum_v<T> {
        return static_cast<std::underlying_type_t<T>>(val);
    }

    template<typename T>
    static const T& ToPrintable(const T& val) requires (!std::is_enum_v<T>) {
        return val;
    }

public:
    static Log& Instance() {
        static Log log{};
        return log;
    }

    void Info(const std::string& message, const auto&... values) {
        std::cout
            << Timestamp() << " "
            << "[" << std::this_thread::get_id() << "] "
            << message;
        ((std::cout << " " << ToPrintable(values)), ...); 

        std::cout << "\n";
    }

private:
    std::string Timestamp() const {
        auto now = std::chrono::system_clock::now();
        auto now_seconds = std::chrono::floor<std::chrono::seconds>(now);
        std::string timestamp = std::format("{:%Y%m%dT%H%M%S}", now_seconds);
        return timestamp;
    }
    std::mutex mutex_;
};

#define LOG_INFO(...) Log::Instance().Info(__VA_ARGS__)

}  // namespace neuro_trace
