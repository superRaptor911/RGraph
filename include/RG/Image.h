#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <RG/Ref_Base.h>
#include <glm/glm.hpp>

namespace rg
{
    class Image : public Ref_Base
    {
        struct ImageInfo
        {
            glm::ivec2 size = glm::ivec2(0,0);
            int channels = 0;            
        };

    private:

        uchar *m_data = nullptr;

        ImageInfo m_img_info;

    private:

        inline void m_decrementRefCount();

    public:
    
        Image();
        Image(const std::string &filepath);
        Image(const Image &image);
        Image(uchar *data, const glm::ivec2 &size, int channels);
        Image &operator = (const Image &image);

        bool operator == (const Image &image);
        
        bool loadImage(const std::string &filepath);
        void saveToFile(const std::string &filepath);

        ~Image();
    };  
    
}

#endif
