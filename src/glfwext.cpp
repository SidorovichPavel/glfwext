#include <stdexcept>

#include <glfwext/glfwext.hpp>
#include <glfwext/exception.hpp>
#include <GLFW/glfw3.h>

namespace glfwext {

    void init() {
        if (glfwInit() == GLFW_FALSE) {
            const char* errctx;
            auto errc = glfwGetError(&errctx);
            throw glfw_exception(errc, errctx);
        }
    }
    
}