#include <RG/RGraph.h>
#include <RG/r_util.h>
#include <RG/Global_Def.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace rg;

RGraph RGraph::_Rgraph_instance;


bool RGraph::init(std::string win_name, glm::ivec2 win_size)
{
    auto &instance = _Rgraph_instance;

    glfwInit();
    _Rgraph_instance._getGL_version();

    if (_Rgraph_instance._gl_version >= 4.2f)
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        printf("Open GL version : 4.2\n");
    }
    else if (_Rgraph_instance._gl_version >= 3.3f)
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        printf("Open GL version : 3.3\n");
    }
    else
    {
        printf("Hardware is not supported. Open GL 3.3 level GPU required.\n");
        return false;
    }
    
    
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
    glfwSetFramebufferSizeCallback(instance._window, _handleWindowResize);
    glfwSetWindowCloseCallback(instance._window, _handleCloseButtonPressed);

    // Load all opengl function pointer
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("Failed to initialize GLAD\n");
        glfwTerminate();
        return false;
    }

    glEnable(GL_DEPTH_TEST);

    instance._resolution = instance._win_size;
    instance._ortho_proj = glm::ortho(0.0f, instance._resolution.x, instance._resolution.y, 0.0f, -1.0f, 1.0f);

    for (auto &it : _Rgraph_instance._RGInitiated_callbacks)
        it();

    return true;
}


void RGraph::_getGL_version()
{
    _gl_version = -1.f;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif
    
    // Create test window
   GLFWwindow* window = glfwCreateWindow(640, 480, "Test", nullptr, nullptr);

    // Check window 
    if (window == nullptr)
    {
        printf("Failed to create GLFW window\n");
        printf("Minimum Open GL version supported is 3.3\n");
        glfwTerminate();
        return;
    }

    // Set at current context
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("Failed to initialize GLAD\n");
        glfwTerminate();
        return;
    }
    
    auto strings = splitStr((char *)glGetString(GL_VERSION), " ");
    glfwDestroyWindow(window);
    // Set gl version
    _gl_version = std::stof(strings[0]);
}


void RGraph::_handleWindowResize(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    // Change size
    _Rgraph_instance._win_size = glm::ivec2(width, height);

    for (auto &it : _Rgraph_instance._win_resized_callbacks)
        it();
}


void RGraph::_handleCloseButtonPressed(GLFWwindow * window)
{
    exit(0);
}


void RGraph::setClearColor(const Color &c_color)
{ 
    _Rgraph_instance._clear_color = c_color;
    glClearColor(c_color.r, c_color.g, c_color.b, c_color.a);
}


void RGraph::clearScreen()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Ready to Draw callbacks
    for (auto &it : _Rgraph_instance._ready2draw_callbacks)
        it();
}

void RGraph::updateScreen()
{
    glfwSwapBuffers(_Rgraph_instance._window);
    _Rgraph_instance._frame_times[0] = _Rgraph_instance._frame_times[1];
    _Rgraph_instance._frame_times[1] = glfwGetTime();
}

bool RGraph::windowOpen() 
{
    return !glfwWindowShouldClose(_Rgraph_instance._window);
}

RGraph::~RGraph()
{
    DEBUG_PRINT("RGraph shutdown");
    //glfwTerminate();
}