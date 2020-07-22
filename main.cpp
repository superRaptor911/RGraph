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
#include <RG/Sprite.h>



int main()
{
	typedef rg::RGraph Graph;
	Graph::init();
	rg::File f;
	rg::Sprite s;
	rg::Texture t("../res/rinc.png");
	s.setTexture(t);
	Graph::setClearColor(rg::Color::Blue);
	Graph::clearScreen();
	s.draw();
	Graph::updateScreen();
	rg::sleep(2000);

	std::cout << "Done\n";

	return 0;
}