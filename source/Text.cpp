#include <glm/fwd.hpp>
#include <RG/Text.h>
#include <string>
#include <vector>
#include <RG/QuadBatcher.h>
#include <RG/SpriteDrawer.h>
#include <RG/r_util.h>

using namespace rg;

Text::Text()
{

    static const std::string vertex_source = "#version 330 core\n"
                                "layout (location = 0) in vec2 vpos;\n"
                                "layout (location = 1) in vec2 UVs;\n"
                                "out vec2 uv;\n"

                                "uniform mat4 proj;\n"
                                "uniform mat4 model;\n"

                                "void main()\n"
                                "{\n"
                                    " gl_Position = proj * model * vec4(vpos.xy, 0.0, 1.0);\n"
                                    " uv = UVs;\n"
                                "}\n";

    static const std::string frag_source = "#version 330 core\n"
                            "out vec4 FragColor;\n"
                            "in vec2 uv;\n"

                            "uniform vec4 color;\n"
                            "uniform sampler2D tex;\n"

                            "void main()\n"
                            "{\n"
			    "vec2 u = vec2(uv.x,1- uv.y);\n"
			    "vec4 sampled = vec4(1.0, 1.0, 1.0, texture(tex, u).r);" 
                            "FragColor = sampled * color;\n"
                            "}\n";


    static const Shader shader(vertex_source, frag_source);
    m_shader = shader;
}

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

    std::vector<Sprite> sprites;

    for(auto &i : txt)
    {
	// Handle new line
	if(i == '\n')
	{
	    rect_size.x = std::max(rect_size.x, (int)pos.x);
	    x_len = 0;
	    pos.x = 0;
	    pos.y += m_vertical_seperation + m_font.getSize();
	    rect_size.y += m_vertical_seperation + m_font.getSize();
	    continue;
	}

	auto ch = char_map.find(i);
	if(ch == char_map.end())
	{
	    ch = char_map.begin();
	    R_CPRINT_WARN("Character not found.");
	}

	auto &ch_info = ch->second;
	x_len += ch_info.Size.x;

	Sprite spr;
	spr.setPosition(pos.x, pos.y + m_font.getMaxBearingY() - ch_info.Bearing.y);
	spr.setTexture(ch_info.texture);
	sprites.push_back(spr);

	pos.x += ch_info.Advance;
    }
    
    rect_size.x = std::max(rect_size.x, (int)pos.x);

    m_ren_surf.setSize(rect_size);
    m_ren_surf.generate();
    m_ren_surf.activate();
    m_ren_surf.setClearColor(Color(0,0,0,0));
    m_ren_surf.clear();

    static SpriteDrawer spr_dr;
    m_shader.activate();
    m_shader.setParam("proj", m_ren_surf.getOrthoProjection());
    m_shader.setParam("color", m_color);
    
    for (auto &i : sprites)
    {
	m_shader.setParam("model", i.getTransformMatrix());
	spr_dr.drawSprite(i, m_shader);
    }
   
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
