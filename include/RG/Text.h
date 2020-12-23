#ifndef TEXT_H
#define TEXT_H

#include "glm/fwd.hpp"
#include <RG/RenderSurface.h>
#include <RG/Font.h>
#include <string>

namespace rg
{
    class Text
    {
	Font m_font;
	RenderSurface m_ren_surf;
	std::string m_text;
	int m_vertical_seperation = 4;
	Color m_color;
	Shader m_shader;

    public:

	Text();
	
	// Set Text, ASCII only
	void setText(const std::string &txt);
	// Set Font to render
	void setFont(Font &f);
	// Get currently used font
	Font getFont();

	void setVSeperation(int v_sep);
	// Draw Text
	void draw(const glm::vec2 &pos);

    };
}


#endif
