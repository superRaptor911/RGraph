/**
 * @file main.cpp
 * @author Raptor (Aditya Aravind) (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2020-06-10
 * 
 * @copyright Copyright (c) 2020
 * 
 */


#include <iostream>
#include <RG/cleanup.h>
#include <RG/r_util.h>
#include <RG/File.h>
#include <RG/DirMan.h>
#include <RG/RGraph.h>
#include <RG/Texture.h>
#include <RG/Shader.h>




int main()
{
	typedef rg::RGraph Graph;
	Graph::init();
	rg::Texture s,s2;
	s = s2;
	for (size_t i = 0; i < 5; i++)
	{
		rg::Texture ss;
		s2 = ss;
		rg::Texture sss=s;
	}
	
	Graph::setClearColor(rg::Color::Blue);
	Graph::clearScreen();
	Graph::updateScreen();
	rg::sleep(2000);

	std::cout << "Done\n";

	/**rg::RGraph::init();
	rg::Texture T;

	T.loadTexture("../res/rinc.png");
	std::cout << "Started\n";
	for (size_t i = 0; i < 3; i++)
	{
		rg::RGraph::clearScreen();
		T.draw(glm::vec2(100,100) * float(i));
		rg::RGraph::updateScreen();
		SDL_Delay(1000);
	}*/

	return 0;
}