#ifndef Font_H
#define Font_H

#include <map>
#include <ft2build.h>
#include FT_FREETYPE_H

namespace rg
{
	class Font
	{
	    struct Character 
	    {
		uint TextureID;  		// ID handle of the glyph texture
		glm::ivec2   Size;		// Size of glyph
		glm::ivec2   Bearing;	// Offset from baseline to left/top of glyph
	    	uint Advance;    		// Offset to advance to next glyph
	    };

	    std::map<char, Character> m_characters;
	    FT_Library m_ft;
	    FT_Library m_face;
		
	    int m_size = 12;
		
	    public:
		
	    Font();
	    Font(const std::string &path);
	    bool loadFont(const std::string &path);
		
	};
}

#endif
