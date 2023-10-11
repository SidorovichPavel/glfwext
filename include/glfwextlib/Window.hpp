#pragma once

#include <GLFW/glfw3.h>

#include <string>
#include <array>

#include <glfwextlib/Events/Events.hpp>

namespace glfwext
{

    class Window
    {
    public:
        using handle_type = GLFWwindow*;

        Window(const std::string& title, int width, int height) noexcept;
        virtual ~Window();


        void make_current() const noexcept;
        bool should_close() const noexcept;
        void swap_buffers() const noexcept;

        float ratio() const noexcept;
        const std::array<bool, 1024>& keys_state() const noexcept;
        std::pair<float, float> angles() const noexcept;
        std::pair<int, int> size() const noexcept;

        Event<Window*, int, int> framebuffer_resize;
        Event<Window*, int, int, int> key_press;
        Event<Window*, int, int, int> key_release;
        Event<Window*, float, float> cursor_move;

    private:
        static void static_window_size_callback(handle_type window, int width, int height);
        static void static_framebuffer_size_callback(handle_type window, int width, int height);
        static void static_key_callback(handle_type window, int key, int scancode, int action, int mode);
        static void static_cursor_pos_callback(handle_type window, double xpos, double ypos);
        
        void framebuffer_size_callback(int width, int height);
        void key_callback(int key, int scancode, int action, int mode);
        void cursor_pos_callback(float xpos, float ypos);
    
    protected:
        virtual void on_framebuffer_resize(int width, int height);
        virtual void on_key_press(int key, int scancode, int mode);
        virtual void on_key_release(int key, int scancode, int mode);
        virtual void on_cursor_move(float xpos, float ypos);

    private:


        handle_type window_;
        int width_, height_;
        std::string title_;
        std::array<bool, 1024> keys_;

        float lastX, lastY;
        float pitch;
        float yaw;
    };
    
}