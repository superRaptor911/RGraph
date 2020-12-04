#include <RG/RGraph.h>
#include <RG/Font.h>
#include <RG/Drawer.h>
#include <RG/QuadDrawer.h>

#include <RG/Shader.h>
#include <RG/File.h>

int main()
{	
	rg::RGraph rgraph;
	rgraph.InitRgraph();
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	
	rg::Font f;
	f.loadFont("fonts/arial.ttf");

	rg::Quad q;
	rg::QuadDrawer qd;

	rg::Sprite s;
	s.setPosition(glm::vec2(0,100));
	s.setTexture(f.m_texture);

	auto win = rgraph.getDefaultWindow();
	rg::Drawer dr;
	win->setClearColor(rg::Color::Blue);
    while (win->windowOpen())
    {
        win->clearScreen();
		dr.draw(s);
        win->updateScreen();
    }
	
	return 0;
}
