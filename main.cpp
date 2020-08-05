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
#include <vector>

using namespace rg;

int main()
{
	
	RGraph::init("Haha", glm::ivec2(1280,720));
	auto tex = Texture("../res/rinc.png");
	auto tex2 = Texture("../res/rinc2.png");

	std::vector<Sprite> sprites;
	for (size_t i = 0; i < 8; i++)
	{

		Sprite s(tex);

		s.setPosition(glm::vec2(rand() % 1280, rand() % 720));

		sprites.push_back(s);
	}
	
	RGraph::setClearColor(Color::Blue);

	float t = glfwGetTime();
	int frames = 0;


	while (RGraph::windowOpen())
	{
		frames += 1;
		if (glfwGetTime() - 2 > t )
		{
			t = glfwGetTime();
			std::cout << "FPS "<<frames / 2 << " Time(us) : " << (1.f / frames ) * 2.f * 1000 << "\n";
			frames = 0;
		}
		
		RGraph::clearScreen();

		for (auto &i : sprites)
		{
			i.rotate(-0.08);
			i.draw();
		}

		RGraph::updateScreen();
		RGraph::pollEvents();
	}
	
	return 0;
}