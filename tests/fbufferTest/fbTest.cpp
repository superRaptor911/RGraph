#include <RG/RGraph.h>
#include <RG/SpriteDrawer.h>
#include <RG/QuadDrawer.h>
#include <RG/RenderSurface.h>

int main()
{
    rg::RGraph Rg;
    Rg.InitRgraph();

    rg::Texture tex;
    tex.loadTexture("m1.png");

    rg::Sprite spr;
    spr.setPosition(300,100);
    spr.setTexture(tex);
    rg::SpriteDrawer spr_dr;

    rg::Quad quad;
    quad.setPosition(100, 100);
    quad.setSize(400,300);
    quad.setColor(rg::Color::Red);
    rg::QuadDrawer q_dr;

    auto win = Rg.getDefaultWindow();

    rg::RenderSurface rs;
    rs.generate();
    rs.setClearColor(rg::Color::Blue);
    rs.activate();
    rs.clear();

    q_dr.drawQuad(quad, rs);
    quad.rotate(1.0);
    quad.setColor(rg::Color::White);
    q_dr.drawQuad(quad);
    quad.setPosition(300,300);
    q_dr.drawQuad(quad);
    spr.setTexture(rs.getTexture());
    
    rs.deactivate();
    while (win->windowOpen())
    {
        win->clearScreen();
        spr_dr.drawSprite(spr);
      //  q_dr.drawQuad(quad);
        win->updateScreen();
    }   

    return 0;
}