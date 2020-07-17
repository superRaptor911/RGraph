#include <RG/Texture.h>
#include <RG/RGraph.h>
#include <SDL2/SDL_image.h>

using namespace rg;

Texture::Texture()
{
    // Start Reference counting
    ref_count = new int;
    *ref_count = 1;
}

Texture::Texture(const std::string &path)
{
    // Start Reference counting
    ref_count = new int;
    *ref_count = 1;

    loadTexture(path);
}

Texture::Texture(const Texture &T)
{
    // Do ref counting
    ref_count = T.ref_count;
    *ref_count += 1;

    _texture = T._texture;
    _size = T._size;
}

Texture &Texture::operator = (const Texture &T)
{
    // Reduce ref by 1
    *ref_count -= 1;

    // Delete resource 
    if (ref_count == 0)
    {
        delete ref_count;

        // Destroy Texture if exists
        if (_texture)
            SDL_DestroyTexture(_texture);
    }

    ref_count = T.ref_count;
    *ref_count += 1;

    _texture = T._texture;
    _size = T._size;

    return *this;
}

bool Texture::loadTexture(const std::string &path)
{
    _texture = IMG_LoadTexture(RGraph::getRenderer(), path.c_str());

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

void Texture::draw(glm::vec2 pos)
{
	SDL_Rect dst;
	dst.x = pos.x;
	dst.y = pos.y;
	dst.w = _size.x;
	dst.h = _size.y;
	SDL_RenderCopy(RGraph::getRenderer(), _texture, NULL, &dst);
}

Texture::~Texture()
{
    // Reduce ref by 1
    *ref_count -= 1;

    // Delete resource 
    if (ref_count == 0)
    {
        delete ref_count;

        // Destroy Texture if exists
        if (_texture)
            SDL_DestroyTexture(_texture);
    }
}