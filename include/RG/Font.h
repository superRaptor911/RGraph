#ifndef FONT_H
#define FONT_H

#include <map>
#include <RG/Ref_Base.h>
#include <glm/glm.hpp>
#include <RG/Shader.h>
#include <RG/Texture.h>

namespace rg
{
    class Font : public Ref_Base
    {
	// Struct
	struct Character 
	{
	    Texture texture;  		// Texture of character
	    glm::ivec2   Size;		// Size of glyph
	    glm::ivec2   Bearing;	// Offset from baseline to left/top of glyph
	    long Advance;    		// Offset to advance to next glyph
	};

	uint m_size = 10;
	int m_max_bearing = 0;

	Shader shader;
	uint m_VAO, m_VBO, m_EBO;

    public:

	std::map<char, Character> m_characters;

    private:

	inline void m_detachRef();
	// Free Glyphs
	void m_freeGlyphs();

    public:

	Font();
	Font(const std::string &path);

	Font(Font &f);
	Font &operator = (Font &f);

	bool loadFont(const std::string &path, uint font_size = 14);
	uint getSize() { return m_size; }
	int getMaxBearingY() { return m_max_bearing; }

	// Destroy Font
	void destroy();
    };
}

#endif
