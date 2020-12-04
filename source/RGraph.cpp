#include <RG/RGraph.h>
#include <RG/r_util.h>

using namespace rg;

RGraph::RGraph()
{
    if (!m_instance_ptr)
    {
        m_instance_ptr = this;
    }
    else
    {
        R_CPRINT_WARN("Only 1 instance of RGraph should be used at a time");
    }
    
}


bool RGraph::InitRgraph()
{
    if (!glfwInit())
    {
        printf("Fatal Error : Failed to initiate GLFW.");
        return false;
    }

    m_getGLVersion();


    // Use Opengl version 4.2
    if (m_max_GL_version >= 4.2f)
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        m_GL_version = 4.2f;
        printf("Using Open GL version : 4.2\n");
    }
    // Use Opengl version 3.3
    else if (m_max_GL_version >= 3.3f)
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        m_GL_version = 3.3f;
        printf("Using Open GL version : 3.3\n");
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

    glfwSetErrorCallback(m_error_callback);
    m_default_window.createWindow(glm::ivec2(1024, 768), "Rgraph");
    m_current_window = &m_default_window;
    RGraph_initiated_signal.emit();
    m_is_initiated = true;

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);

    return true;
}

void RGraph::m_getGLVersion()
{
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
    
    printf("%s\n", (char *)glGetString(GL_VERSION));
    auto strings = splitStr((char *)glGetString(GL_VERSION), " ");
    glfwDestroyWindow(window);
    // Set gl version
    m_max_GL_version = std::stof(strings[0]);
}


Window *RGraph::getDefaultWindow()
{
    return m_current_window;
}


void RGraph::m_error_callback(int error, const char* description)
{
    printf("Error : %s.\n", description);
}



void RGraph::TerminateRgraph()
{
    if (m_is_initiated)
    {
        glfwTerminate();
        m_default_window.destroyWindow();
        m_is_initiated = false;
    }
    
}


RGraph::~RGraph()
{
    TerminateRgraph();
}