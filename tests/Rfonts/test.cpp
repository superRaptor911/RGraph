#include "glm/fwd.hpp"
#include <RG/RGraph.h>
#include <RG/Drawer.h>
#include <RG/QuadDrawer.h>
#include <RG/Text.h>

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

    rg::Text text;
    text.setFont(f);
    text.setText("This____\n\n_lThis_\n___Thast");

    auto win = rgraph.getDefaultWindow();
    rg::Drawer dr;
    win->setClearColor(rg::Color::Blue);
    while (win->windowOpen())
    {
	win->clearScreen();
	dr.draw(s);
	text.draw(glm::vec2(100,300));
	win->updateScreen();
    }

    return 0;
}
