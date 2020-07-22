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
	f.open("../res/default.vs",rg::File::READ);
	std::string v = f.getFileContent();
	f.open("../res/default.fs",rg::File::READ);
	std::string fr = f.getFileContent();
	
	const char *src = fr.c_str();
    GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
    //glShaderSource(vertex, 1, &src, NULL);
    glCompileShader(vertex);

	return 0;

	//rg::Shader s(v.c_str(), fr.c_str());


	
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