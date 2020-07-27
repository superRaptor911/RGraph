#include <RG/Sprite.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <RG/r_util.h>
#include <RG/RGraph.h>
#include <RG/SpriteBatcher.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



using namespace rg;

Sprite::Sprite()
{
    // Start ref counting
    startRefCounting();
}

Sprite::Sprite(const Texture &T)
{
    // Start ref counting
    startRefCounting();
    // Set Texture
    _texture = T;
    _origin = glm::vec2(T.getSize()) / 2.f;
}

Sprite::Sprite(const Sprite &S)
{
    // Attach to S
    attachToRefCount(S);
    // Cpy Texture
    _texture = S._texture;

    _rotation = S._rotation;
    _position = S._position;
    _origin = S._origin;
    _scale = S._scale;
}

Sprite &Sprite::operator = (const Sprite &S)
{ 
    _decrementRefCount();

    // Increment ref count of S
    attachToRefCount(S);
    // Cpy Texture
    _texture = S._texture;

    _rotation = S._rotation;
    _position = S._position;
    _origin = S._origin;
    _scale = S._scale;

    return *this;
}


void Sprite::_decrementRefCount()
{
    // Free resource if ref count reaches 0
    if (dettachRefCount())
    {
        DEBUG_PRINT("Deleting Sprite");
    }    
}

void Sprite::draw()
{ 
    SpriteBatcher::addSprite(*this);
}


Sprite::~Sprite()
{
    _decrementRefCount();
}