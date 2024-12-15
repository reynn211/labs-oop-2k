#pragma once
#include <coroutine>
#include <exception>
#include <concepts>

template<typename T>
class Generator {
public:
    struct promise_type {
        T value;
        Generator get_return_object() { 
            return Generator{std::coroutine_handle<promise_type>::from_promise(*this)}; 
        }
        std::suspend_always initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        std::suspend_always yield_value(T v) {
            value = v;
            return {};
        }
        void return_void() {}
        void unhandled_exception() {
            std::terminate();
        }
    };

    Generator(std::coroutine_handle<promise_type> h) : handle(h) {}
    ~Generator() {
        if (handle) handle.destroy();
    }

    T value() const { return handle.promise().value; }
    bool next() {
        handle.resume();
        return !handle.done();
    }

private:
    std::coroutine_handle<promise_type> handle;
}; 