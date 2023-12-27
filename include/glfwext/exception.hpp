#pragma once

#include <stdexcept>
#include <exception>

namespace glfwext
{

    class glfw_exception : public std::exception {
    public:
        glfw_exception(const int code, const char* message);

        const char* what() const noexcept override;

    private:
        std::string message_;
    };

}