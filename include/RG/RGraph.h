#ifndef RGRAPH_H
#define RGRAPH_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>
#include <RG/Color.h>

namespace rg
{
	class RGraph
	{
	private:

		glm::ivec2 _win_size;

		GLFWwindow* _window;

		std::string _win_name;
		bool _is_initiated = false;

		static RGraph _Rgraph_instance;

		Color _clear_color;

	private:

		RGraph() {}

		static void handleWindowResize(GLFWwindow* window, int width, int height);
		
	public:
		
		static bool init(std::string win_name = "NO NAME", glm::ivec2 win_size = glm::ivec2(640, 480));
		static RGraph &Instance() {return _Rgraph_instance;}

		static void setClearColor(const Color &c_color);
		static Color getClearColor() { return _Rgraph_instance._clear_color;}


		static void clearScreen();

		static void updateScreen();

		~RGraph();
	};
	
	
}

#endif
