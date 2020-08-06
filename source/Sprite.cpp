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
    startRefCounting();
}

Sprite::Sprite(const Texture &T)
{
    startRefCounting();

    _attribute.texture = T;
    _attribute.origin = glm::vec2(T.getSize()) / 2.f;
}

Sprite::Sprite(const Sprite &S)
{
    attachToRefCount(S);

    _attribute = S._attribute;
}

Sprite &Sprite::operator = (const Sprite &S)
{ 
    _decrementRefCount();
    attachToRefCount(S);

    _attribute = S._attribute;
    return *this;
}

glm::mat4 Sprite::getTransformMatrix()
{
    glm::mat4 model = glm::mat4(1.0f);

    model = glm::translate(model, glm::vec3(_attribute.origin * _attribute.scale + _attribute.position, 0.0f)); 
    model = glm::rotate(model, _attribute.rotation, glm::vec3(0.0f, 0.0f, 1.0f)); 
    model = glm::translate(model, glm::vec3(-_attribute.origin * _attribute.scale, 0.0f));
    model = glm::scale(model, glm::vec3(glm::vec2(_attribute.texture.getSize()) * _attribute.scale, 1.0f));

    return model;
}

void Sprite::draw()
{ 
    if (_attribute.is_visible) 
        SpriteBatcher::addSprite(*this);
}


void Sprite::_decrementRefCount()
{
    // Free resource if ref count reaches 0
    if (dettachRefCount())
    {
        DEBUG_PRINT("Deleting Sprite");
    }    
}

Sprite::~Sprite()
{
    _decrementRefCount();
}