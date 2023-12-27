#include <format>

#include <glfwext/exception.hpp>

namespace glfwext
{
    glfw_exception::glfw_exception(const int code, const char* message)
        :
        message_(std::format("[glfwext]::[exeption]::[error code: {}]::{}", code, message))
    {   }

    const char* glfw_exception::what() const noexcept {
        return message_.c_str();
    }
}