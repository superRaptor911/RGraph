#include <RG/RGraph.h>
#include <RG/r_util.h>
#include <RG/Drawer.h>
#include <RG/File.h>

int main()
{
    rg::RGraph RG;
    RG.InitRgraph();
    
    rg::Quad quad[10000];
 
    rg::Window *w = RG.getDefaultWindow();
    w->setClearColor(rg::Color::Blue);
    rg::Drawer drawer(w);

    for (int i = 0; i < 9999; i++)
    {
        quad[i].setSize(glm::vec2(50,50));
        quad[i].setPosition(glm::vec2(rand() % 1024, rand() % 768));
        quad[i].setColor(rg::Color::Green);
        quad[i].rotate(3.14 * (rand() % 100) / 100);
        drawer.addToBatch(quad[i]);
    }   

    while (w->windowOpen())
    {
        w->clearScreen();
        // for (int i = 0; i < 9999; i++)
        // {
        //     drawer.draw(quad[i]);
        // }
        
        drawer.drawBatch();
        w->updateScreen();
    }

    return 0;
}
