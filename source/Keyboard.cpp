#include <RG/Keyboard.h>
#include <RG/r_util.h>
#include <RG/RGraph.h>

using namespace rg;

Keyboard::Keyboard(Window *window)
{
    m_window = window;
}

bool Keyboard::isKeyPressed(const std::string &key)
{
    if (!m_window->getGLFWWindow())
        return false;

    auto it = _key_bindings.find(toUpper(key));
    if (it == _key_bindings.end())
        return false;
    
    return (glfwGetKey(m_window->getGLFWWindow(),it->second) == GLFW_PRESS);
}

bool Keyboard::isKeyPressed(const int key_id)
{
    if (!m_window->getGLFWWindow())
        return false;
    
    return (glfwGetKey(m_window->getGLFWWindow(), key_id) == GLFW_PRESS);
}


bool Keyboard::isKeyReleased(const std::string &key)
{
    if (!m_window->getGLFWWindow())
        return false;
        
    auto it = _key_bindings.find(toUpper(key));
    if (it == _key_bindings.end())
        return false;
    
    return (glfwGetKey(m_window->getGLFWWindow(), it->second) == GLFW_RELEASE);
}

bool Keyboard::isKeyReleased(const int key_id)
{
    if (!m_window->getGLFWWindow())
        return false;

    return (glfwGetKey(m_window->getGLFWWindow(), key_id) == GLFW_RELEASE);
}

