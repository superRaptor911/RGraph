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
#include <RG/RGraph.h>
#include <RG/Sprite.h>
#include <RG/File.h>
#include <RG/r_util.h>
#include <RG/Keyboard.h>

using namespace rg;

int main()
{
	
	RGraph::init();
	Sprite sprite(Texture("../res/rinc.png"));	
	RGraph::setClearColor(Color::Blue);

	while (RGraph::windowOpen())
	{
		RGraph::clearScreen();
		sprite.draw();

		if (Keyboard::isKeyPressed("c"))
		{
			std::cout<< "Whooo\n";
		}
		

		RGraph::updateScreen();
		RGraph::pollEvents();
	}
	
	return 0;
}