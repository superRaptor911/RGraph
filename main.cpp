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

		if (Keyboard::isKeyPressed("w"))
			sprite.move(glm::vec2(0,-1) * 5.f);
		
		if (Keyboard::isKeyPressed("s"))
			sprite.move(glm::vec2(0,1) * 5.f);

		if (Keyboard::isKeyPressed("a"))
			sprite.move(glm::vec2(-1,0) * 5.f);

		if (Keyboard::isKeyPressed("d"))
			sprite.move(glm::vec2(1,0) * 5.f);

		if (Keyboard::isKeyPressed("x"))
			sprite.rotate(0.02);

		if (Keyboard::isKeyPressed("z"))
			sprite.rotate(-0.02);

		if (Keyboard::isKeyPressed("p"))
			std::cout<< sprite.getOrigin().x << "," << sprite.getPosition().y << "\n";

		RGraph::updateScreen();
		RGraph::pollEvents();
	}
	
	return 0;
}