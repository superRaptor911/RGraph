#ifndef RGRAPH_H
#define RGRAPH_H

#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <string>

namespace rg
{
	class RGraph
	{
	private:

		glm::ivec2 _win_size;
		SDL_Window *_window = nullptr;
		SDL_Renderer *_renderer = nullptr;

		std::string _win_name;
		bool _is_initiated = false;

		static RGraph _Rgraph_instance;

	private:

		RGraph() {}
		
	public:
		
		static bool init(std::string win_name = "NO NAME", glm::ivec2 win_size = glm::ivec2(640, 480));
		static RGraph &Instance() {return _Rgraph_instance;}

		static SDL_Renderer *getRenderer() {return _Rgraph_instance._renderer;}

		static SDL_Window *getWindow() {return _Rgraph_instance._window;}

		static void clearScreen();

		static void updateScreen();

		~RGraph();
	};
	
	
}

#endif
