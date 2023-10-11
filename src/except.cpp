#include <glfwextlib/except.hpp>

namespace glfwext
{
    const char* Exception::what() const noexcept {
        return message_.c_str();
    }
}