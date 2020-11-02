#ifndef DRAWER_H
#define DRAWER_H

#include <RG/Quad.h>
#include <RG/Sprite.h>
#include <vector>

namespace rg
{
    class SpriteDrawer;
    class QuadDrawer;
    class Window;
    class QuadBatcher;
    
    class  Drawer
    {

        SpriteDrawer *m_sprite_drawer = nullptr;
        QuadDrawer *m_quad_drawer = nullptr;
        QuadBatcher *m_quad_batcher;
        Window *m_window;

        std::vector<Quad> m_quad_draw_queue;
        std::vector<Sprite> m_sprite_draw_queue;

    private:

        void m_initBatcher();

    public:

        Drawer(Window *window = nullptr);

        void draw(Quad &quad);
        void draw(Sprite &sprite);

        void addToBatch(Quad &quad);
        void addToBatch(Sprite &sprite);

        void drawBatch();
        ~Drawer();
    };
    
}

#endif
