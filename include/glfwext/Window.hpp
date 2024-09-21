#pragma once

#include <array>
#include <string>
#include <string_view>

#include <glfwext/Events.hpp>

struct GLFWwindow;

namespace glfwext {

class Window {
 public:
  using handle_type = GLFWwindow*;

  Window(std::string_view title, int width, int height);
  virtual ~Window();

  void make_current() const noexcept;
  bool should_close() const noexcept;
  void swap_buffers() const noexcept;
  void destroy() const noexcept;

  void set_input_mode(int mode, int value);
  void set_should_close(bool value);
  std::tuple<float, float> cursor_pos();
  std::tuple<int, int> framebuffer_size();

  float ratio() const noexcept;
  const std::array<bool, 1024>& keys_state() const noexcept;
  std::pair<int, int> size() const noexcept;

  Event<Window*, int, int> resize;
  Event<Window*, int, int> framebuffer_resize;
  Event<Window*, int, int, int> key_press;
  Event<Window*, int, int, int> key_release;
  Event<Window*, float, float> cursor_move;
  Event<Window*, int, int> mbutton_press;
  Event<Window*, int, int> mbutton_release;
  Event<Window*, float, float> scroll;

 private:
  static void static_window_size_callback(handle_type window, int width,
                                          int height);
  static void static_framebuffer_size_callback(handle_type window, int width,
                                               int height);
  static void static_key_callback(handle_type window, int key, int scancode,
                                  int action, int mode);
  static void static_cursor_pos_callback(handle_type window, double xpos,
                                         double ypos);
  static void static_mouse_button_callback(handle_type window, int button,
                                           int action, int mode);
  static void static_scroll_callback(handle_type window, double xoffset,
                                     double yoffset);

  void window_size_callback(int width, int height);
  void framebuffer_size_callback(int width, int height);
  void key_callback(int key, int scancode, int action, int mode);
  void cursor_pos_callback(float xpos, float ypos);
  void mouse_button_callback(int button, int action, int mode);
  void scroll_callback(float xoffset, float yoffset);

 protected:
  virtual void on_window_resize(int width, int height);
  virtual void on_framebuffer_resize(int width, int height);
  virtual void on_key_press(int key, int scancode, int mode);
  virtual void on_key_release(int key, int scancode, int mode);
  virtual void on_cursor_move(float xpos, float ypos);
  virtual void on_mouse_button_press(int button, int mode);
  virtual void on_mouse_button_release(int button, int mode);
  virtual void on_scroll(float xoffset, float yoffset);

 private:
  handle_type window_;
  int width_, height_;
  std::string title_;
  std::array<bool, 1024> keys_;
};

}  // namespace glfwext