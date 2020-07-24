#ifndef RGRAPH_H
#define RGRAPH_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>
#include <RG/Color.h>
#include <RG/Shader.h>

namespace rg
{
	class RGraph
	{
	private:
		// Window size
		glm::ivec2 _win_size;
		// Screen resolution
		glm::vec2 _resolution;

		GLFWwindow* _window;

		std::string _win_name;
		bool _is_initiated = false;

		static RGraph _Rgraph_instance;

		Color _clear_color;

		typedef void (*RgCloseFunc);

		RgCloseFunc _close_callback_func = nullptr;

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

		static GLFWwindow* getWindow() {return _Rgraph_instance._window;}

		static void clearScreen();

		static void updateScreen();

		static bool windowOpen();

		static void pollEvents() { glfwPollEvents();}

		static void setCloseCallback(RgCloseFunc func);

		~RGraph();
	};
	
	
}

#endif
