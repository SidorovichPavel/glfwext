#include <stdexcept>

#include <GLFW/glfw3.h>
#include <glfwext/exception.hpp>
#include <glfwext/glfwext.hpp>

namespace glfwext {

void init() {
  if (glfwInit() == GLFW_FALSE) {
    const char* errctx;
    auto errc = glfwGetError(&errctx);
    throw glfw_exception(errc, errctx);
  }
}

}  // namespace glfwext