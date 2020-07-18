#ifndef TEXTURE_H
#define TEXTURE_H

#include <glm/glm.hpp>
#include <string>


namespace rg
{
    class Texture
    {
    private:

        glm::ivec2 _size;


        int *ref_count = nullptr;


    public:
        
        Texture();

        // cpy constructor
        Texture(const Texture &T);
        // cpy operator
        Texture &operator = (const Texture &T);

        Texture(const std::string &path);
        bool loadTexture(const std::string &path);

        glm::ivec2 getSize() const;

        void draw(glm::vec2 pos = glm::vec2(0,0));

        ~Texture();
    };    
}



#endif
