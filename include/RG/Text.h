#ifndef TEXT_H
#define TEXT_H

#include <RG/RenderSurface.h>
#include <RG/Font.h>

namespace rg
{
    class Text
    {
	Font m_font;
	RenderSurface m_ren_surf;
	std::string m_text;

    public:

	Text();
	Text(const std::string &txt);

	void setFont(const Font &f);
	Font getFont();
	void draw();

    };
}


#endif
