#include <RG/Keyboard.h>
#include <RG/r_util.h>
#include <RG/RGraph.h>

using namespace rg;

bool Keyboard::isKeyPressed(const std::string &key)
{
    auto it = _key_bindings.find(toUpper(key));
    if (it == _key_bindings.end())
        return false;
    
    return (glfwGetKey(RGraph::getWindow(),it->second) == GLFW_PRESS);
}

bool Keyboard::isKeyPressed(const int key_id)
{
    return (glfwGetKey(RGraph::getWindow(), key_id) == GLFW_PRESS);
}


bool Keyboard::isKeyReleased(const std::string &key)
{
    auto it = _key_bindings.find(toUpper(key));
    if (it == _key_bindings.end())
        return false;
    
    return (glfwGetKey(RGraph::getWindow(),it->second) == GLFW_RELEASE);
}

bool Keyboard::isKeyReleased(const int key_id)
{
    return (glfwGetKey(RGraph::getWindow(), key_id) == GLFW_RELEASE);
}

