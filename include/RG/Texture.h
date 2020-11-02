#ifndef TEXTURE_H
#define TEXTURE_H

#include <glm/glm.hpp>
#include <string>
#include <RG/Ref_Base.h>
#include <RG/Image.h>

namespace rg
{
    class Texture : public Ref_Base
    {     
    private:
        uint m_texture_id = RG_INVALID_ID;
        glm::ivec2 m_size;
        int m_channels;

    private:

        inline void m_decrementRefCount();

    public:
        
        Texture();

        // cpy constructor
        Texture(const Texture &T);
        // cpy operator
        Texture &operator = (const Texture &T);
        // Load texture from file
        Texture(const std::string &path);
        
        bool operator == (const Texture &T);

        // Load from a file
        bool loadTexture(const std::string &path);
        
        // Get size of image
        glm::ivec2 getSize() const;
        
        // Generate mimap
        void genMipmap();

        // set as current texture for draw call
        void activate(int id = 0);
        
        // Get opengl texture id
        uint getTextureID() { return m_texture_id;}

        Image getImage();

        ~Texture();
    };    
}



#endif
