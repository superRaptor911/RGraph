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
    attachToRefCount(image);
    // Set data
    _data = image._data;
    _img_info = image._img_info;
}

Image::Image(uchar *data, const glm::ivec2 &size, int channels)
{
    startRefCounting();
    // Set data
    _data = data;
    _img_info.size = size;
    _img_info.channels = channels;
}

Image &Image::operator = (const Image &image)
{
    _decrementRefCount();
    attachToRefCount(image);
    _data = image._data;
    _img_info = image._img_info;
    return *this;
}

bool Image::operator == (const Image &image)
{
    return (_data == image._data);
}

bool Image::loadImage(const std::string &filepath)
{
    // Load image form file
    stbi_set_flip_vertically_on_load(true); 
    uchar *data = stbi_load(filepath.c_str(), &_img_info.size.x, &_img_info.size.y, &_img_info.channels, 0);

    // If has data detach from it
    if (_data)
        _decrementRefCount();
    
    _data = nullptr;

    if (data)
        _data = data;
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
    auto extension = getExtension(filepath);

    if (extension == "jpg")
        stbi_write_jpg(filepath.c_str(), _img_info.size.x, _img_info.size.y, _img_info.channels, _data, 100);
    
    else if (extension == "png")
        stbi_write_png(filepath.c_str(), _img_info.size.x, _img_info.size.y, _img_info.channels, _data, _img_info.size.x * _img_info.channels);
    
    else
    {
        stbi_write_png((filepath + ".png").c_str(), _img_info.size.x, _img_info.size.y, _img_info.channels, _data, _img_info.size.x * _img_info.channels);
    }
}


void Image::_decrementRefCount()
{
    // Delete resource if value of ref count reaches 0
    if (dettachRefCount())
    {
        // If resource free
        if (_data)
        {
            free(_data);
            _data = nullptr;
        }        
    }
}