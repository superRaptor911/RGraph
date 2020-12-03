#include <RG/Texture.h>
#include <RG/RGraph.h>
#include <RG/DirMan.h>
#include <RG/r_util.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

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

Texture::Texture(uint gl_Texture, const glm::vec2 &sz,int channels)
{
    // Start Reference counting
    startRefCounting();
    m_texture_id = gl_Texture;
    m_channels = channels;
    m_size = sz;
}

Texture &Texture::operator = (const Texture &T)
{
    // Decrement ref count and delete Texture if ref vount reaches 0
    m_detachRef();
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

    // Destroy active Texture active
    if (m_texture_id != RG_INVALID_ID)
    {
        destroy();
	}

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
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
        auto clr_format = GL_RGBA;
        switch (m_channels)
        {
        case 3:
            clr_format = GL_RGB;
            break;
        case 1:
            clr_format = GL_RED;
            break;
        default:
            break;
        }
                
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

void Texture::m_detachRef()
{
    // Delete resource if value of ref count reaches 0
    if (dettachRefCount())
    {
        // Destroy Texture if exists
        if (m_texture_id != RG_INVALID_ID)
            glDeleteTextures(1, &m_texture_id);
    }

    m_texture_id = RG_INVALID_ID;
}

Image Texture::getImage()
{
    if (m_texture_id == RG_INVALID_ID)
        return Image();
    
    uchar* data = new uchar[m_size.x * m_size.y * m_channels];

    auto clr_format = GL_RGBA;
    switch (m_channels)
    {
    case 3:
        clr_format = GL_RGB;
        break;
    case 1:
        clr_format = GL_RED;
        break;
    default:
        break;
    }

    glGetTexImage(GL_TEXTURE_2D, 0, clr_format, GL_UNSIGNED_BYTE, data);
    return Image(data, m_size, m_channels);
}

// Detach previous ref and create new
void Texture::destroy()
{
    m_detachRef();
    startRefCounting();
}

Texture::~Texture()
{
    m_detachRef();
}
