#include <RG/Drawer.h>
#include <RG/SpriteDrawer.h>
#include <RG/QuadDrawer.h>
#include <RG/QuadBatcher.h>
#include <RG/RGraph.h>


using namespace rg;


Drawer::Drawer()
{
    m_sprite_drawer = new SpriteDrawer;
    m_quad_drawer = new QuadDrawer;
    m_quad_batcher = new QuadBatcher;
}


void Drawer::m_initBatcher()
{

}



void Drawer::draw(Quad &quad)
{
    m_quad_drawer->drawQuad(quad);
}


void Drawer::draw(Sprite &sprite)
{
    m_sprite_drawer->drawSprite(sprite);
}


void Drawer::addToBatch(Quad &quad)
{
    m_quad_draw_queue.push_back(quad);
}


void Drawer::addToBatch(Sprite &sprite)
{
    m_sprite_draw_queue.push_back(sprite);
}

void Drawer::drawBatch()
{
    m_quad_batcher->draw(m_quad_draw_queue);
}

Drawer::~Drawer()
{
    delete m_sprite_drawer;
    delete m_quad_drawer;
    delete m_quad_batcher;
}
