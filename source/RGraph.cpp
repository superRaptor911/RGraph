#include <RG/RGraph.h>
#include <RG/r_util.h>

using namespace rg;

RGraph RGraph::_Rgraph_instance;

bool RGraph::init(std::string win_name, glm::ivec2 win_size)
{
    auto &instance = _Rgraph_instance;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif
    
    instance._win_size = win_size;
    instance._win_name = win_name;
    instance._window = glfwCreateWindow(win_size.x, win_size.y, win_name.c_str(), nullptr, nullptr);

    // Check window 
    if (instance._window == nullptr)
    {
        printf("Failed to create GLFW window\n");
        glfwTerminate();
        return false;
    }

    // Set at current context
    glfwMakeContextCurrent(instance._window);
    // Handle Window resize
    glfwSetFramebufferSizeCallback(instance._window, handleWindowResize);

    // Load all opengl function pointer
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("Failed to initialize GLAD\n");
        return false;
    }

    return true;
}

void RGraph::handleWindowResize(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);

    // Change size
    _Rgraph_instance._win_size = glm::ivec2(width, height);
}

void RGraph::setClearColor(const Color &c_color)
{ 
    _Rgraph_instance._clear_color = c_color;

    glClearColor(c_color.r, c_color.g, c_color.b, c_color.a);
}


void RGraph::clearScreen()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void RGraph::updateScreen()
{
    glfwSwapBuffers(_Rgraph_instance._window);
}

RGraph::~RGraph()
{
 glfwTerminate();
}