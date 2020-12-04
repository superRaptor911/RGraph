#include <RG/RGraph.h>
#include <RG/SpriteDrawer.h>
#include <RG/QuadDrawer.h>
#include <RG/RenderSurface.h>

int main()
{
    rg::RGraph Rg;
    Rg.InitRgraph();
    rg::RenderSurface rs(300,300);

    rg::Sprite spr;
    rg::SpriteDrawer spr_dr;
    rg::Quad quad;
    rg::QuadDrawer q_dr;

    quad.setPosition(0, 0);
    quad.setSize(300,150);
    quad.setColor(rg::Color::Green);
	rs.setClearColor(rg::Color::Black);
	rs.clear();
    q_dr.drawQuad(quad, rs);
	spr.setPosition(100, 200);
    spr.setTexture(rs.getTexture());
	rs.deactivate();

    auto win = Rg.getDefaultWindow();
	win->setClearColor(rg::Color::Blue);
    while (win->windowOpen())
    {
      win->clearScreen();
      spr_dr.drawSprite(spr);
      win->updateScreen();
    }   

    return 0;
}