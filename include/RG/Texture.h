#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <glm/glm.hpp>
#include <string>


namespace rg
{
    class Texture
    {
    private:

        glm::ivec2 _size;

        SDL_Texture *_texture = nullptr;

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

        ~Texture();
    };    
}



#endif
