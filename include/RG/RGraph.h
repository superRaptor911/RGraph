#ifndef RGRAPH_H
#define RGRAPH_H

#include <glm/glm.hpp>
#include <string>

namespace rg
{
	class RGraph
	{
	private:

		glm::ivec2 _win_size;


		std::string _win_name;
		bool _is_initiated = false;

		static RGraph _Rgraph_instance;

	private:

		RGraph() {}
		
	public:
		
		static bool init(std::string win_name = "NO NAME", glm::ivec2 win_size = glm::ivec2(640, 480));
		static RGraph &Instance() {return _Rgraph_instance;}



		static void clearScreen();

		static void updateScreen();

		~RGraph();
	};
	
	
}

#endif
