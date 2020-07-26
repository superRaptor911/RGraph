#ifndef RGRAPH_H
#define RGRAPH_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>
#include <RG/Color.h>
#include <RG/Shader.h>
#include <vector>

namespace rg
{
	class RGraph
	{
	private:
		// Window size
		glm::ivec2 _win_size;
		// Screen resolution
		glm::vec2 _resolution;
		// Window
		GLFWwindow* _window;
		// Name of window
		std::string _win_name;
		// counter
		bool _is_initiated = false;
		// instance of RGraph
		static RGraph _Rgraph_instance;
		// Clear color
		Color _clear_color;

		glm::mat4 _ortho_proj;

		// Call backs
		typedef void (*Void_function) ();
		typedef void (*Void_function) ();
		
		std::vector<Void_function> _win_close_callbacks;
		std::vector<Void_function> _ready2draw_callbacks;
		
	private:

		RGraph() {}

		static void _handleWindowResize(GLFWwindow* window, int width, int height);

		static void _handleCloseButtonPressed(GLFWwindow * window);


	public:

		
	public:
		
		static bool init(std::string win_name = "NO NAME", glm::ivec2 win_size = glm::ivec2(640, 480));
		static RGraph &Instance() {return _Rgraph_instance;}

		static void setClearColor(const Color &c_color);
		static Color getClearColor() { return _Rgraph_instance._clear_color;}

		static void setResolution(const glm::vec2 &res) { _Rgraph_instance._resolution = res;}
		static glm::vec2 getResolution() {return _Rgraph_instance._resolution;}

		static glm::mat4 getOrthoProgection() { return _Rgraph_instance._ortho_proj;}

		static GLFWwindow* getWindow() {return _Rgraph_instance._window;}

		static void clearScreen();

		static void updateScreen();

		static bool windowOpen();

		static void pollEvents() { glfwPollEvents();}

		static void addCallback_onWindowClose(Void_function func);

		static void addCallback_onReadyToDraw(Void_function func) { _Rgraph_instance._ready2draw_callbacks.push_back(func);}

		~RGraph();
	};
	
	
}

#endif
