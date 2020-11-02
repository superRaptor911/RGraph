#include <RG/Window.h>
#include <RG/RGraph.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace rg;

bool Window::createWindow(const glm::ivec2 &window_size, const std::string &title)
{
    if (m_window)
    {
        printf("Error : This window is already created.\n");
        return false;
    }

    m_window = glfwCreateWindow(window_size.x, window_size.y, title.c_str(), nullptr, nullptr);

    // Check window status
    if (m_window == nullptr)
    {
        printf("Error : Failed to create GLFW window\n");
        return false;
    }

    // Set at current context
    glfwMakeContextCurrent(m_window);
    //glfwSetFramebufferSizeCallback(m_window, _handleWindowResize);
    //glfwSetWindowCloseCallback(m_window, _handleCloseButtonPressed);
    glEnable(GL_DEPTH_TEST);

    m_size = window_size;
    m_ortho_projection = glm::ortho(0.0f, float(m_size.x), float(m_size.y), 0.0f, -1.0f, 1.0f);
    return true;
}


void Window::setClearColor(const Color &c)
{
    m_clear_color = c;
    glClearColor(m_clear_color.r, m_clear_color.g, m_clear_color.b, m_clear_color.a);
}


Color Window::getClearColor() const
{
    return m_clear_color;
}


void Window::clearScreen()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::updateScreen()
{
    glfwSwapBuffers(m_window);
    // Compute frame Time and Fps
    m_frame_times[0] = m_frame_times[1];
    m_frame_times[1] = glfwGetTime();

    
    if (m_frame_times[1] - m_time_stamp >= 1.f)
    {
        m_time_stamp = m_frame_times[1];
        m_FPS = m_frame_count;
        m_frame_count = 0;

        printf("FPS : %d\n", m_FPS);
    }

    m_frame_count += 1;
}

GLFWwindow *Window::getGLFWWindow()
{
    return m_window;
}


void Window::destroyWindow()
{
    if (m_window)
    {
        glfwDestroyWindow(m_window);
        m_window = nullptr;
    }
}


int Window::getFPS()
{
    return m_FPS;
}


float Window::getFrameTime()
{
    return m_frame_times[1] - m_frame_times[0];
}


bool Window::windowOpen() 
{
    glfwPollEvents();
    return !glfwWindowShouldClose(m_window);
}


Window::~Window()
{
    destroyWindow();
}