#include <GLFW/glfw3.h>
#include <glfwext/Events.hpp>
#include <glfwext/Window.hpp>
#include <glfwext/exception.hpp>

#include <algorithm>
#include <ranges>
#include <stdexcept>

namespace glfwext {
Window::Window(std::string_view title, int width, int height)
    : title_(title), width_(width), height_(height) {
  window_ = glfwCreateWindow(width_, height_, title_.c_str(), nullptr, nullptr);
  if (!window_) {
    const char* errctx;
    auto errc = glfwGetError(&errctx);
    throw glfw_exception(errc, errctx);
  }

  glfwSetWindowUserPointer(window_, this);

  glfwSetWindowSizeCallback(window_, static_window_size_callback);
  glfwSetFramebufferSizeCallback(window_, static_framebuffer_size_callback);
  glfwSetKeyCallback(window_, static_key_callback);
  glfwSetCursorPosCallback(window_, static_cursor_pos_callback);
  glfwSetMouseButtonCallback(window_, static_mouse_button_callback);
  glfwSetScrollCallback(window_, static_scroll_callback);

  std::ranges::fill(keys_, false);
}

Window::~Window() {}

void Window::make_current() const noexcept { glfwMakeContextCurrent(window_); }

bool Window::should_close() const noexcept {
  return glfwWindowShouldClose(window_);
}

void Window::swap_buffers() const noexcept { glfwSwapBuffers(window_); }

void Window::destroy() const noexcept { glfwDestroyWindow(window_); }

void Window::set_input_mode(int mode, int value) {
  glfwSetInputMode(window_, mode, value);
}

void Window::set_should_close(bool value) {
  glfwSetWindowShouldClose(window_, value);
}

std::tuple<float, float> Window::cursor_pos() {
  double xpos, ypos;
  glfwGetCursorPos(window_, &xpos, &ypos);
  return std::tuple<float, float>(static_cast<float>(xpos),
                                  static_cast<float>(ypos));
}

std::tuple<int, int> Window::framebuffer_size() {
  int fbwidth, fbheight;
  glfwGetFramebufferSize(window_, &fbwidth, &fbheight);

  return std::make_tuple(fbwidth, fbheight);
}

float Window::ratio() const noexcept {
  return static_cast<float>(width_) / static_cast<float>(height_);
}

const std::array<bool, 1024>& Window::keys_state() const noexcept {
  return keys_;
}

std::pair<int, int> Window::size() const noexcept {
  return std::make_pair(width_, height_);
}

/*--------------------------------------------------------------------------------------------------------------------*/
/* STATIC MEMBERS */
/*--------------------------------------------------------------------------------------------------------------------*/

void Window::static_window_size_callback(handle_type window, int width,
                                         int height) {
  auto obj_ptr = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
  if (obj_ptr) obj_ptr->window_size_callback(width, height);
}

void Window::static_framebuffer_size_callback(handle_type window, int width,
                                              int height)

{
  auto obj_ptr = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
  if (obj_ptr) obj_ptr->framebuffer_size_callback(width, height);
}

void Window::static_key_callback(handle_type window, int key, int scancode,
                                 int action, int mode) {
  auto obj_ptr = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
  if (obj_ptr) obj_ptr->key_callback(key, scancode, action, mode);
}

void Window::static_cursor_pos_callback(handle_type window, double xpos,
                                        double ypos) {
  auto obj_ptr = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
  if (obj_ptr)
    obj_ptr->cursor_pos_callback(static_cast<float>(xpos),
                                 static_cast<float>(ypos));
}

void Window::static_mouse_button_callback(handle_type window, int button,
                                          int action, int mode) {
  auto obj_ptr = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
  if (obj_ptr) obj_ptr->mouse_button_callback(button, action, mode);
}

void Window::static_scroll_callback(handle_type window, double xoffset,
                                    double yoffset) {
  auto obj_ptr = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
  if (obj_ptr)
    obj_ptr->scroll_callback(static_cast<float>(xoffset),
                             static_cast<float>(yoffset));
}

/*--------------------------------------------------------------------------------------------------------------------*/
/* STATIC MEMBERS END */
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
/* PRIVATE MEMBERS */
/*--------------------------------------------------------------------------------------------------------------------*/

void Window::window_size_callback(int width, int height) {
  width_ = width;
  height_ = height;

  on_window_resize(width_, height_);
  resize(this, width_, height_);
}

void Window::framebuffer_size_callback(int width, int height) {
  on_framebuffer_resize(width, height);
  framebuffer_resize(this, width, height);
}

void Window::key_callback(int key, int scancode, int action, int mode) {
  switch (action) {
    case GLFW_PRESS:
      keys_[key] = true;
      on_key_press(key, scancode, mode);
      key_press(this, key, scancode, mode);
      break;
    case GLFW_RELEASE:
      keys_[key] = false;
      on_key_release(key, scancode, mode);
      key_release(this, key, scancode, mode);
      break;
  }
}

void Window::cursor_pos_callback(float xpos, float ypos) {
  on_cursor_move(xpos, ypos);
  cursor_move(this, xpos, ypos);
}

void Window::mouse_button_callback(int button, int action, int mode) {
  switch (action) {
    case GLFW_PRESS:
      on_mouse_button_press(button, mode);
      mbutton_press(this, button, mode);
      break;
    case GLFW_RELEASE:
      on_mouse_button_release(button, mode);
      mbutton_release(this, button, mode);
      break;
  }
}

void Window::scroll_callback(float xoffset, float yoffset) {
  on_scroll(xoffset, yoffset);
  scroll(this, xoffset, yoffset);
}

/*--------------------------------------------------------------------------------------------------------------------*/
/* PRIVATE MEMBERS END */
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
/* PROTECTED MEMBERS */
/*--------------------------------------------------------------------------------------------------------------------*/

void Window::on_window_resize(int width, int height) {}

void Window::on_framebuffer_resize(int width, int height) {}

void Window::on_key_press(int key, int scancode, int mode) {}

void Window::on_key_release(int key, int scancode, int mode) {}

void Window::on_cursor_move(float xpos, float ypos) {}

void Window::on_mouse_button_press(int button, int mode) {}

void Window::on_mouse_button_release(int button, int mode) {}

void Window::on_scroll(float xoffset, float yoffset) {}

/*--------------------------------------------------------------------------------------------------------------------*/
/* PROTECTED MEMBERS END */
/*--------------------------------------------------------------------------------------------------------------------*/

}  // namespace glfwext