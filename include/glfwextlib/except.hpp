#pragma once

#include <stdexcept>

namespace glfwext
{

    class Exception : public std::exception {
    public:
        Exception(const std::string& message) : message_(message) {}

        const char* what() const noexcept override {
            return message_.c_str();
        }

    private:
        std::string message_;
    };

}