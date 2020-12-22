#include <glm/fwd.hpp>
#include <RG/Text.h>
#include <string>
#include <vector>
#include <RG/QuadBatcher.h>
#include <RG/SpriteDrawer.h>
#include <RG/r_util.h>

using namespace rg;

void Text::setFont(Font &f)
{
    m_font = f;
}


void Text::setText(const std::string &txt)
{
    if (m_text == txt)
	return;
    m_text = txt;
    
    // Reference to Font char map
    auto &char_map = m_font.m_characters;
    // Bounding rectangle size
    glm::ivec2 rect_size = glm::ivec2(0, m_font.getSize());
    // Pen Position
    glm::vec2 pos = glm::vec2(0, 0);
    // length of all the characters in a line in pixels.
    int x_len = 0;

    std::vector<Quad> quads;

    for(auto &i : txt)
    {
	auto ch = char_map.find(i);
	if(ch == char_map.end())
	{
	    ch = char_map.begin();
	    R_CPRINT_WARN("Character not found.");
	}

	auto &ch_info = ch->second;

	x_len += ch_info.Size.x;

	// Handle new line
	if(i == '\n')
	{
	    rect_size.x = std::max(rect_size.x, x_len);
	    x_len = 0;
	    pos.x = 0;
	    pos.y += m_vertical_seperation + m_font.getSize();
	    rect_size.y += m_vertical_seperation + m_font.getSize();
	    continue;
	}

	Quad q;
	q.setColor(Color::Green);
	q.setPosition(pos.x, pos.y + m_font.getMaxBearingY() - ch_info.Bearing.y);
	q.setSize(ch_info.Size);
	quads.push_back(q);

	pos.x += ch_info.Advance;
    }

    m_ren_surf.setSize(rect_size);
    m_ren_surf.generate();
    m_ren_surf.activate();
    QuadBatcher qb;
    qb.draw(quads, m_ren_surf.getOrthoProjection());
    m_ren_surf.deactivate();
}


void Text::draw(const glm::vec2 &pos)
{
    static SpriteDrawer spr_dr;
    Sprite spr;
    spr.setPosition(pos);
    spr.setTexture(m_ren_surf.getTexture());
    spr_dr.drawSprite(spr);
}
