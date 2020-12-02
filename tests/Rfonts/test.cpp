#include <RG/RGraph.h>
#include <RG/Font.h>
#include <RG/Drawer.h>

#include <RG/Shader.h>
#include <RG/File.h>

int main()
{	
	rg::RGraph rgraph;
	rgraph.InitRgraph();
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	
	rg::Font f;
	f.loadFont("fonts/arial.ttf");

	rg::Texture t(f.tex, glm::vec2(800.f, 600.f), 4);

	rg::Sprite q;
	q.setPosition(glm::vec2(100,100));
	q.setTexture(t);


	auto win = rgraph.getDefaultWindow();
	rg::Drawer dr;
	win->setClearColor(rg::Color::Blue);


    while (win->windowOpen())
    {
        win->clearScreen();
		//f.drawText("abcggggg");
		dr.draw(q);
        win->updateScreen();
    }
	
	int i;
	scanf("%d", &i);
	return 0;
}
