#ifndef RENDERSURFACE_H
#define RENDERSURFACE_H

#include <RG/Ref_Base.h>
#include <RG/Texture.h>
#include <RG/Color.h>

namespace rg
{
    class RenderSurface : public Ref_Base
    {

    private:

        uint m_framebuffer  = RG_INVALID_ID;
        Texture m_texture;

        glm::ivec2 m_size   = glm::ivec2(800,600);
        glm::mat4 m_ortho_proj;

        Color m_clear_color;
            
    public:

        struct Config
        {
            // here
        };

    private:

        inline void m_detachRef();
    
    public:

        RenderSurface();
        RenderSurface(const glm::ivec2 &size);
        RenderSurface(uint x_sz, uint y_sz);

        // Cpy constructor
        RenderSurface(RenderSurface &rs);
        // Assignment
        RenderSurface &operator = (const RenderSurface &rs);

        // create Render Surface
        bool generate();
        // Clear Surface
        void clear();
        // Set as current surface
        bool activate();
        // Switch to default surface, (screen)
        void deactivate();
        // Set clear color
        void setClearColor(const Color &clr) {m_clear_color = clr;}
        // Get Clear color
        Color getClearColor() const { return m_clear_color;}
        // Get texture
        Texture getTexture() { return m_texture;}

        void setSize(const glm::ivec2 &surf_size);
        glm::ivec2 getSize() const {return m_size;}

        glm::mat4 getOrthoProjection() const {return m_ortho_proj;}

        // Destroy Surface
        void destroy();

        ~RenderSurface();
    };   
}

#endif
