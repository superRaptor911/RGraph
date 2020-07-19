#ifndef COLOR_H
#define COLOR_H

namespace rg
{    
    struct Color
    {
        float r,g,b;
        float a;

        Color()
        {
            r = g =  b = 0.f;
            a = 1.f;
        }

        Color(float red, float green, float blue, float alpha = 1.f)
        {
            r = red; g = green; b = blue;
            a = alpha;
        }

        Color(int red, int green, int blue, int alpha = 255)
        {
            r = red / 255.f;
            g = green / 255.f;
            b = blue / 255.f;
            a = alpha;
        }

        static Color Red;
        static Color Blue;
        static Color Green;
        static Color Black;

    };
    
    
}

#endif
