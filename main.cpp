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
	
	RGraph::init("RGraph", glm::ivec2(1280,720));

	auto tex = Texture("../res/rinc.png");
	auto tex2 = Texture("../res/rinc2.png");

	std::vector<Sprite> sprites;
	for (size_t i = 0; i < 20000; i++)
	{
		Sprite s(tex);
		s.setPosition(glm::vec2(rand() % 1280, rand() % 720));
		sprites.push_back(s);
	}
	
	RGraph::setClearColor(Color::Blue);


	float old_time = RGraph::getTime();
	int frames = 0;
	float frame_time = 0.f;

	while (RGraph::windowOpen())
	{		
		RGraph::clearScreen();

		for (auto &i : sprites)
		{
			i.rotate(-0.08);
			i.draw();
		}

		RGraph::updateScreen();
		RGraph::pollEvents();

		float new_time = RGraph::getTime();
		frame_time += RGraph::getFrameTime();
		frames += 1;

		if (new_time - old_time > 2)
		{
			old_time = new_time;
			printf("FPS %d Frame time (us) : %f\n ",  frames / 2, (frame_time / frames) * 1000.f);
			frames = 0;
			frame_time = 0.f;
		}
		
	}
	
	return 0;
}