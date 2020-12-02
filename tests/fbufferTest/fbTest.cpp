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
    rg::SpriteDrawer spr_dr(Rg.getDefaultWindow());

    rg::Quad quad;
    quad.setPosition(100, 100);
    quad.setSize(400,300);
    quad.setColor(rg::Color::Red);
    rg::QuadDrawer q_dr(Rg.getDefaultWindow());

    auto win = Rg.getDefaultWindow();

    rg::RenderSurface rs;
    rs.generate();
    rs.setClearColor(rg::Color::Blue);
    

    // uint framebuffer;
    // glGenFramebuffers(1, &framebuffer);
    // glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);  

    // // generate texture
    // unsigned int texColorBuffer;
    // glGenTextures(1, &texColorBuffer);
    // glBindTexture(GL_TEXTURE_2D, texColorBuffer);
    // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 800, 600, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // glBindTexture(GL_TEXTURE_2D, 0);

    // // attach it to currently bound framebuffer object
    // glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texColorBuffer, 0);
    // if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    //     printf("Errorrrrr\n");
    // glClear(GL_COLOR_BUFFER_BIT);
    // spr_dr.drawSprite(spr);
    // q_dr.drawQuad(quad);
    // glBindFramebuffer(GL_FRAMEBUFFER, 0);  

    rs.activate();
    rs.clear();
    q_dr.drawQuad(quad);
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