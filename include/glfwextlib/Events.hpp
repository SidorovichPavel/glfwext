#pragma once

#include <functional>
#include <vector>
#include <concepts>
#include <stdexcept>
#include <exception>

namespace glfwext {

    template <class... ArgTypes>
    class Event {
    public:
        using callable_type = std::function<void(ArgTypes...)>;
        using exception_info = std::tuple<typename std::vector<callable_type>::iterator, std::exception_ptr>;

        Event() {}

        template <std::invocable<ArgTypes...> Callable>
        void attach(Callable&& callback) {
            storage_.emplace_back(std::forward<Callable>(callback));
        }

        template <std::invocable<ArgTypes...> Callable>
        Event& operator+=(Callable&& callback) {
            storage_.emplace_back(std::forward<Callable>(callback));
            return *this;
        }

        void detach_all() {
            storage_.clear();
        }

        Event(const Event& other) {
            storage_ = other.storage_;
        }

        Event& operator=(const Event& other) {
            if (this != &other) {
                storage_.clear();
                storage_ = other.storage_;
            }
            return *this;
        }

        Event(Event&& other) noexcept {
            storage_ = std::move(other.storage_);
        }

        Event& operator=(Event&& other) noexcept {
            if (this != &other) {
                storage_.clear();
                storage_ = std::move(other.storage_);
            }
            return *this;
        }

        std::vector<exception_info> operator()(ArgTypes... Args) {
            std::vector<exception_info> exceptions;

            for (auto callback_it = storage_.begin(); callback_it != storage_.end(); ++callback_it) {
                try {
                    (*callback_it)(Args...);
                } catch (const std::exception& e) {
                    exceptions.push_back(std::make_tuple(callback_it, std::current_exception()));
                }
            }

            return exceptions;
        }

    private:
        std::vector<callable_type> storage_;
    };
}
