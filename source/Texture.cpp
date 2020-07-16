#include <RG/Texture.h>
#include <RG/RGraph.h>
#include <SDL2/SDL_image.h>

using namespace rg;

Texture::Texture(const std::string &path)
{
    loadTexture(path);
}

bool Texture::loadTexture(const std::string &path)
{
    _texture = IMG_LoadTexture(RGraph::Instance().getRenderer(), path.c_str());

    if (_texture == nullptr)
    {
        printf( "Failed to Load texture: %s\n", SDL_GetError() );
        return false;
    }

    SDL_QueryTexture(_texture, NULL, NULL, &_size.x, &_size.y);
    
    return true;
}

glm::ivec2 Texture::getSize() const
{
    return _size;
}

Texture::~Texture()
{
    if (_texture)
        SDL_DestroyTexture(_texture);
}