#include <glfwextlib/except.hpp>

namespace glfwext
{
    Exception::Exception(const std::string& message)
        :
        message_(message)
    {   }

    const char* Exception::what() const noexcept {
        return message_.c_str();
    }
}