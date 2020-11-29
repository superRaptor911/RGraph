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
	rg::Texture t;
	t.loadTexture("textures/m1.png");

	rg::Sprite q;
	q.setPosition(glm::vec2(500,400));
	
	q.setTexture(t);
	q.setSize(glm::vec2(200,200));


	rg::Font f;
	f.loadFont("fonts/arial.ttf");
	
	auto win = rgraph.getDefaultWindow();
	rg::Drawer dr;
	win->setClearColor(rg::Color::Blue);


    while (win->windowOpen())
    {
        win->clearScreen();
		f.drawText("abcggggg");
		dr.draw(q);
        win->updateScreen();
    }
	
	int i;
	scanf("%d", &i);
	return 0;
}
