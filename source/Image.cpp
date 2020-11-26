#include <RG/Image.h>
#include <RG/r_util.h>

#include <stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

using namespace rg;

Image::Image()
{
    startRefCounting();
}

Image::Image(const std::string &filepath)
{
    startRefCounting();
    loadImage(filepath);
}

Image::Image(const Image &image)
{
    attachRefCount(image);
    // Set data
    m_data = image.m_data;
    m_img_info = image.m_img_info;
}

Image::Image(uchar *data, const glm::ivec2 &size, int channels)
{
    startRefCounting();
    // Set data
    m_data = data;
    m_img_info.size = size;
    m_img_info.channels = channels;
}

Image &Image::operator = (const Image &image)
{
    m_decrementRefCount();
    attachRefCount(image);
    m_data = image.m_data;
    m_img_info = image.m_img_info;
    return *this;
}

bool Image::operator == (const Image &image)
{
    return (m_data == image.m_data);
}

bool Image::loadImage(const std::string &filepath)
{
    // Load image form file
    stbi_set_flip_vertically_on_load(true); 
    uchar *data = stbi_load(filepath.c_str(), &m_img_info.size.x, &m_img_info.size.y, &m_img_info.channels, 0);

    // If has data detach from it
    if (m_data)
        m_decrementRefCount();
    
    m_data = nullptr;

    if (data)
        m_data = data;
    else
    {    
        printf("Error::Image-> Failed to load image from %s.\n", filepath.c_str());
        stbi_image_free(data);
        return false;
    }

    return true;
}


void Image::saveToFile(const std::string &filepath)
{
    if (!m_data)
        return;

    auto extension = getExtension(filepath);

    if (extension == "jpg")
        stbi_write_jpg(filepath.c_str(), m_img_info.size.x, m_img_info.size.y, m_img_info.channels, m_data, 100);
    
    else if (extension == "png")
        stbi_write_png(filepath.c_str(), m_img_info.size.x, m_img_info.size.y, m_img_info.channels, m_data, m_img_info.size.x * m_img_info.channels);
    
    else
        stbi_write_png((filepath + ".png").c_str(), m_img_info.size.x, m_img_info.size.y, m_img_info.channels, m_data, m_img_info.size.x * m_img_info.channels);
}


void Image::m_decrementRefCount()
{
    // Delete resource if value of ref count reaches 0
    if (dettachRefCount())
    {
        // If resource free
        if (m_data)
        {
            free(m_data);
            m_data = nullptr;
        }        
    }
}

Image::~Image()
{
    m_decrementRefCount();
}
