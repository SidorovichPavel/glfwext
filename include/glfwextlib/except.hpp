#pragma once

#include <stdexcept>
#include <exception>

namespace glfwext
{

    class Exception : public std::exception {
    public:
        Exception(const std::string& message);

        const char* what() const noexcept override;

    private:
        std::string message_;
    };

}