#include <RG/Texture.h>
#include <RG/RGraph.h>
#include <RG/DirMan.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

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
    // copy Texture id
    _texture = T._texture;
    //Copy size
    _size = T._size;
}

Texture &Texture::operator = (const Texture &T)
{
    // Decrement ref count and delete Texture if ref vount reaches 0
    _decrementRefCount();
    // Do ref counting
    ref_count = T.ref_count;
    *ref_count += 1;

    // copy Texture id
    _texture = T._texture;
    //Copy size
    _size = T._size;

    return *this;
}

bool Texture::loadTexture(const std::string &path)
{
    stbi_set_flip_vertically_on_load(true); 
    uchar *data = stbi_load(DirMan::getAliasPath(path).c_str(), &_size.x, &_size.y, &_channels, 0);

    // Texture was used before
    if (_texture != RG_INVALID_ID)
        _decrementRefCount();

    glGenTextures(1, &_texture);
    
    // Set as nth Texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _texture);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Linear Filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    if (data)
    {
        // Color format (Default RGB)
        auto clr_format = GL_RGB;
        // Channel 4 = RGBA
        if (_channels == 4)
            clr_format = GL_RGBA;
        
        glTexImage2D(GL_TEXTURE_2D, 0, clr_format, _size.x, _size.y, 0, clr_format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        printf("Error::Failed to load texture %s\n", DirMan::getAliasPath(path).c_str());
        stbi_image_free(data);
        return false;
    }

    stbi_image_free(data);   
    return true;
}

glm::ivec2 Texture::getSize() const
{
    return _size;
}


void Texture::_decrementRefCount()
{
    // Reduce ref by 1
    *ref_count -= 1;

    // Delete resource if ref count reaches 0
    if (ref_count == 0)
    {
        delete ref_count;

        // Destroy Texture if exists
        if (_texture != RG_INVALID_ID)
            glDeleteTextures(1, &_texture);
    }
}

Texture::~Texture()
{
    _decrementRefCount();
}