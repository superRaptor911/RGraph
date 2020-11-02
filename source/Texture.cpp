#include <RG/Texture.h>
#include <RG/RGraph.h>
#include <RG/DirMan.h>
#include <RG/r_util.h>

#define STB_IMAGE_IMPLEMENTATION
#include <RG/deps/stb_image.h>

using namespace rg;

Texture::Texture()
{
    // Start Reference counting
    startRefCounting();
}

Texture::Texture(const std::string &path)
{
    // Start Reference counting
    startRefCounting();
    loadTexture(path);
}

Texture::Texture(const Texture &T)
{
    // Do ref counting
    attachRefCount(T);
    // copy Texture id
    m_texture_id = T.m_texture_id;
    //Copy size
    m_size = T.m_size;
}

Texture &Texture::operator = (const Texture &T)
{
    // Decrement ref count and delete Texture if ref vount reaches 0
    m_decrementRefCount();
    // Do ref counting
    attachRefCount(T);

    // copy Texture id
    m_texture_id = T.m_texture_id;
    //Copy size
    m_size = T.m_size;

    return *this;
}

bool Texture::operator == (const Texture &T)
{
    return (m_texture_id == T.m_texture_id);
}

bool Texture::loadTexture(const std::string &path)
{
    stbi_set_flip_vertically_on_load(true); 
    uchar *data = stbi_load(path.c_str(), &m_size.x, &m_size.y, &m_channels, 0);

    // Texture was used before
    if (m_texture_id != RG_INVALID_ID)
        m_decrementRefCount();

    glGenTextures(1, &m_texture_id);
    
    // Set as nth Texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_texture_id);
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
        if (m_channels == 4)
            clr_format = GL_RGBA;
        
        glTexImage2D(GL_TEXTURE_2D, 0, clr_format, m_size.x, m_size.y, 0, clr_format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        printf("Error::Failed to load texture %s\n", path.c_str());
        stbi_image_free(data);
        return false;
    }

    //stbi_image_free(data);   
    return true;
}

glm::ivec2 Texture::getSize() const
{
    return m_size;
}

void Texture::activate(int id)
{
    glActiveTexture(GL_TEXTURE0 + id);
    glBindTexture(GL_TEXTURE_2D, m_texture_id);
}

void Texture::m_decrementRefCount()
{
    // Delete resource if value of ref count reaches 0
    if (dettachRefCount())
    {
        // Destroy Texture if exists
        if (m_texture_id != RG_INVALID_ID)
            glDeleteTextures(1, &m_texture_id);

    }
}

Image Texture::getImage()
{
    if (m_texture_id == RG_INVALID_ID)
        return Image();
    
    uchar* data = new uchar[m_size.x * m_size.y * m_channels];

    if (m_channels == 4)
        glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    else
        glGetTexImage(GL_TEXTURE_2D, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    
    return Image(data, m_size, m_channels);      
}

Texture::~Texture()
{
    m_decrementRefCount();
}