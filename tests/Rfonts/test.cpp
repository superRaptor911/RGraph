#include "RG/Sprite.h"
#include "RG/Texture.h"
#include "glm/fwd.hpp"
#include <RG/RGraph.h>
#include <RG/Drawer.h>
#include <RG/SpriteDrawer.h>
#include <RG/Text.h>

int main()
{	
    rg::RGraph rgraph;
    rgraph.InitRgraph();
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    rg::Font f;
    f.loadFont("fonts/arial.ttf", 24);

    rg::Texture texture("textures/m1.png");
    rg::Sprite spr;
    spr.setTexture(texture);
    rg::SpriteDrawer spr_dr;

    rg::Text text;
    text.setFont(f);
    text.setText("This is great?.\n Haha Jett is the best");

    auto win = rgraph.getDefaultWindow();
    rg::Drawer dr;
    win->setClearColor(rg::Color::Blue);
    while (win->windowOpen())
    {
	win->clearScreen();
	text.draw(glm::vec2(100,300));
//	spr_dr.drawSprite(spr);
	win->updateScreen();
    }

    return 0;
}
