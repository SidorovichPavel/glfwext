#include <glfwextlib/Window.hpp>
#include <glfwextlib/Events.hpp>
#include <glfwextlib/except.hpp>

#include <stdexcept>
#include <algorithm>
#include <ranges>

namespace glfwext
{
    Window::Window(const std::string& title, int width, int height) noexcept
        :
        title_(title),
        width_(width),
        height_(height)
    {
        window_ = glfwCreateWindow(width_, height_, title_.c_str(), nullptr, nullptr);
        if (!window_)
        {
            const char* desc;
            glfwGetError(&desc);
            throw Exception(desc);
        }

        glfwSetWindowUserPointer(window_, this);

        glfwSetFramebufferSizeCallback(window_, static_framebuffer_size_callback);
        glfwSetKeyCallback(window_, static_key_callback);
        glfwSetCursorPosCallback(window_, static_cursor_pos_callback);

        std::ranges::fill(keys_, false);

        lastX = 400;
        lastY = 300;

        pitch = 0.0f;
        yaw = -90.0f;
    }

    Window::~Window()
    {
    }

    void Window::make_current() const noexcept
    {
        glfwMakeContextCurrent(window_);
    }

    bool Window::should_close() const noexcept
    {
        return glfwWindowShouldClose(window_);
    }

    void Window::swap_buffers() const noexcept
    {
        glfwSwapBuffers(window_);
    }


    void Window::set_input_mode(int mode, int value)
    {
        glfwSetInputMode(window_, mode, value);
    }

    float Window::ratio() const noexcept
    {
        return static_cast<float>(width_) / static_cast<float>(height_);
    }

    const std::array<bool, 1024>& Window::keys_state() const noexcept
    {
        return keys_;
    }

    std::pair<int, int> Window::size() const noexcept
    {
        return std::make_pair(width_, height_);
    }

    std::pair<float, float> Window::angles() const noexcept
    {
        return std::pair<float, float>(yaw, pitch);
    }

    /*--------------------------------------------------------------------------------------------------------------------*/
    /* STATIC MEMBERS */
    /*--------------------------------------------------------------------------------------------------------------------*/

    void Window::static_key_callback(handle_type window, int key, int scancode, int action, int mode)
    {
        auto obj_ptr = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
        if (obj_ptr)
            obj_ptr->key_callback(key, scancode, action, mode);
    }

    void Window::static_framebuffer_size_callback(handle_type window, int width, int height)
    {
        auto obj_ptr = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
        if (obj_ptr)
            obj_ptr->framebuffer_size_callback(width, height);
    }

    void Window::static_cursor_pos_callback(handle_type window, double xpos, double ypos)
    {
        auto obj_ptr = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
        if (obj_ptr)
            obj_ptr->cursor_pos_callback(static_cast<float>(xpos), static_cast<float>(ypos));
    }

    /*--------------------------------------------------------------------------------------------------------------------*/
    /* STATIC MEMBERS END*/
    /*--------------------------------------------------------------------------------------------------------------------*/

    /*--------------------------------------------------------------------------------------------------------------------*/
    /* PRIVATE MEMBERS*/
    /*--------------------------------------------------------------------------------------------------------------------*/

    void Window::framebuffer_size_callback(int width, int height)
    {
        on_framebuffer_resize(width, height);
        framebuffer_resize(this, width, height);
    }

    void Window::key_callback(int key, int scancode, int action, int mode)
    {
        switch (action)
        {
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

        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
            glfwSetWindowShouldClose(window_, GL_TRUE);
    }

    /*--------------------------------------------------------------------------------------------------------------------*/
    /* PRIVATE MEMBERS END*/
    /*--------------------------------------------------------------------------------------------------------------------*/

    /*--------------------------------------------------------------------------------------------------------------------*/
    /* PROTECTED MEMBERS*/
    /*--------------------------------------------------------------------------------------------------------------------*/

    void Window::on_framebuffer_resize(int width, int height)
    {    }

    void Window::on_key_press(int key, int scancode, int mode)
    {    }

    void Window::on_key_release(int key, int scancode, int mode)
    {    }

    void Window::on_cursor_move(float xpos, float ypos)
    {    }

    void Window::cursor_pos_callback(float xpos, float ypos)
    {
        float xoffset = xpos - lastX;
        float yoffset = ypos - lastY; // Обратный порядок вычитания потому что оконные Y-координаты возрастают с верху вниз
        lastX = xpos;
        lastY = ypos;

        float sensitivity = 0.05f;
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        yaw -= xoffset;
        pitch += yoffset;

        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;
    }

    /*--------------------------------------------------------------------------------------------------------------------*/
    /* PROTECTED MEMBERS END*/
    /*--------------------------------------------------------------------------------------------------------------------*/





}