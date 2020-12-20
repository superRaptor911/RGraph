#include <RG/RGraph.h>
#include <RG/r_util.h>
#include <RG/QuadDrawer.h>
#include <RG/File.h>

int main()
{
    rg::RGraph RG;
    RG.InitRgraph();
    
    rg::Quad quad;
    quad.setSize(glm::vec2(100, 100));
    quad.setPosition(glm::vec2(300,300));
    quad.setColor(rg::Color::Green);
 
    rg::Window *w = RG.getDefaultWindow();
    w->setClearColor(rg::Color::Blue);
    rg::QuadDrawer drawer;

    while (w->windowOpen())
    {
        w->clearScreen();       
        drawer.drawQuad(quad);
        w->updateScreen();
    }
    
    return 0;
}
