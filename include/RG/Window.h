#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <RG/Color.h>
#include <RG/Signal.h>
#include <string>

namespace rg
{
    class Window
    {
    private:

        GLFWwindow* m_window = nullptr;
        glm::ivec2 m_size;
        std::string m_window_title;
        
        Color m_clear_color;
        glm::mat4 m_ortho_projection;

		float m_frame_times[2] = {0.f, 0.f};
		int m_frame_count = 0;
        float m_time_stamp = 0.f;
        int m_FPS = 0;
    
    public:

        Signal<> window_closed_signal;
        Signal<glm::ivec2> window_resized_signal;
        
        
    public:
        Window() {};
        bool createWindow(const glm::ivec2 &window_size, const std::string &title);
        void setAsCurrent();
        
        void setClearColor(const Color &c);
        Color getClearColor() const;
        void clearScreen();
        void updateScreen();
        bool windowOpen();

        glm::ivec2 getSize() { return m_size;}

        glm::mat4 getOrthoProjection() { return m_ortho_projection;}
        GLFWwindow *getGLFWWindow();

        int getFPS();
        float getFrameTime();

        void destroyWindow();
        ~Window();
    };
}

#endif
