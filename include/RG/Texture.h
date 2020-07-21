#ifndef TEXTURE_H
#define TEXTURE_H

#include <glm/glm.hpp>
#include <string>
#include <RG/Global_Def.h>


namespace rg
{
    class Texture
    {
    private:
        uint _texture = RG_INVALID_ID;
        glm::ivec2 _size;
        int _channels;

        int *ref_count = nullptr;

    private:

        inline void _decrementRefCount();

    public:
        
        Texture();

        // cpy constructor
        Texture(const Texture &T);
        // cpy operator
        Texture &operator = (const Texture &T);
        // Load texture from file
        Texture(const std::string &path);
        
        // Load from a file
        bool loadTexture(const std::string &path);
        
        // Get size of image
        glm::ivec2 getSize() const;
        
        // Generate mimap
        void genMipmap();

        // set as current texture for draw call
        void setAsActive(int id = 0);


        ~Texture();
    };    
}



#endif
