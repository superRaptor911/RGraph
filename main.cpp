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

using namespace rg;

int main()
{
	
	RGraph::init();
	rg::Sprite sprite(Texture("../res/rinc.png"));	
	RGraph::setClearColor(Color::Blue);

	RGraph::clearScreen();
	sprite.draw();
	RGraph::updateScreen();
	
	std::cin.get();
	return 0;
}