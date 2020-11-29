#ifndef TEXT_H
#define TEXT_H

#include <RG/Font.h>

namespace rg
{
	class Text
	{
		Font m_font;
		std::string m_text;
		
		uint m_VAO, m_VBO;
		
	
	public:
		
		Text();
		Text(const std::string &txt);
		
		void setFont(const Font &f);
				
		
	};
}


#endif
