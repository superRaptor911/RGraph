#ifndef TEXTURE_H
#define TEXTURE_H

#include "glm/fwd.hpp"
#include <glm/glm.hpp>
#include <string>
#include <RG/Ref_Base.h>
#include <RG/Image.h>

namespace rg
{
    class Texture : public Ref_Base
    {     
    private:
	
	struct Data
	{
	    // Handle to texture
	    uint m_texture_id = RG_INVALID_ID;
	    // Texture size 
	    glm::ivec2 m_size = glm::ivec2(0, 0);
	    // channels, 4 for rgba
	    int m_channels = RG_INVALID_ID;
	};

	Data m_data;

    private:

        inline void m_detachRef();

    public:
        
        Texture();

        // cpy constructor
        Texture(const Texture &T);
        // cpy operator
        Texture &operator = (const Texture &T);
        // Load texture from file
        Texture(const std::string &path);
        // Load from gl
        Texture(uint gl_Texture, const glm::vec2 &sz, int channels = 4);
        
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
        uint getTextureID() { return m_data.m_texture_id;}

	int getChannels() { return m_data.m_channels; }

        Image getImage();

        // Destroy texture, will not affect other sharing Textures
        void destroy();

        ~Texture();
    };    
}



#endif
