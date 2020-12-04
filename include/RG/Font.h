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
			uint TextureID;  		// ID handle of the glyph texture
			glm::ivec2   Size;		// Size of glyph
			glm::ivec2   Bearing;	// Offset from baseline to left/top of glyph
			long Advance;    		// Offset to advance to next glyph
			long offset = 0;
		};

		int m_size = 24;
		std::map<char, Character> m_characters;

		Shader shader;
		uint m_VAO, m_VBO, m_EBO;
		
	public:

		Texture m_texture;

	private:
			 
		inline void m_detachRef();
		// Free Glyphs
		void m_freeGlyphs();
		
	public:
		
		Font();
		Font(const std::string &path);
		
		Font(Font &f);
		Font &operator = (Font &f);
		
		bool loadFont(const std::string &path);
		
        // Destroy Font
        void destroy();
	};
}

#endif
