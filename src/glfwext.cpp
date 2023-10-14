#include <stdexcept>

#include <glfwextlib/glfwext.hpp>

namespace glfwext
{
    void init()
    {
        if (!glfwInit())
            throw std::runtime_error("glfwextlib::GLFW3 init failed");
    }
}