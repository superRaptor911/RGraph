#include <RG/r_util.h>
#include <RG/Font.h>
#include <RG/File.h>
#include <RG/RGraph.h>
#include <ft2build.h>
#include <RG/Quad.h>
#include <RG/QuadDrawer.h>
#include <RG/RenderSurface.h>
#include FT_FREETYPE_H


using namespace rg;

Font::Font()
{
	// Start Reference counting
    startRefCounting();
}

Font::Font(const std::string &path)
{
    // Start Reference counting
    startRefCounting();	
	loadFont(path);	
}

Font::Font(Font &f)
{
    // Do ref counting
    attachRefCount(f);
    
    // get data from f
    m_characters = f.m_characters;
    m_size = f.m_size;
}

Font &Font::operator = (Font &f)
{
    // Decrement ref count and delete Texture if ref vount reaches 0
    m_decrementRefCount();
    // Do ref counting
    attachRefCount(f);

    // get data from f
    m_characters = f.m_characters;
    m_size = f.m_size;
    
	return *this;
}

bool Font::loadFont(const std::string &path)
{
	// Handle previously loaded font
	if (!m_characters.empty())
	{
		m_decrementRefCount();
		startRefCounting();
	}
	
	// Free Type resource
	FT_Library ft;
	FT_Face face;
		
	// Init FT
	if (FT_Init_FreeType(&ft))
	{
		R_CPRINT_ERR("Could not init FreeType Library");
		return false;
	}
	
	// Load Font
	if (FT_New_Face(ft, path.c_str(), 0, &face))
	{
		R_CPRINT_ERR("Failed to load font");
		FT_Done_Face(face);
		return false;
	}
	
	FT_Set_Pixel_Sizes(face, 0, 48);
	// Disable byte-alignment restriction
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	long f_offset = 0;
	  
	for (unsigned char c = 0; c < 128; c++)
	{
		// load character glyph 
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			R_CPRINT_WARN("Failed to load Glyph");
			continue;
		}
		
		// generate texture
		unsigned int texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			face->glyph->bitmap.buffer
		);
		// set texture options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// now store character for later use
		Character character = {
			texture, 
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			(face->glyph->advance.x >> 6),
			f_offset
		};
		f_offset += character.Advance;
		m_characters.insert(std::pair<char, Character>(c, character));
	}
	
	// Cleanup FT
	FT_Done_Face(face);
	FT_Done_FreeType(ft);

	rg::File vs, fs;
	vs.open("shaders/s1.vs");
	fs.open("shaders/s1.fs");
	
	shader = rg::Shader(vs.getFileContent(), fs.getFileContent());

	const float Vertex_data[8] = {
	// positions and texture coords
		0.f,   1.f,
		1.f,   1.f,
		1.f,   0.f,
		0.f,   0.f
	};

	const uint Indices[6] = {
		0, 1, 2, // first triangle
		2, 3, 0  // second triangle
	};

    // glEnable(GL_CULL_FACE);
    // glEnable(GL_BLEND);
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	int vertex_size = sizeof(float) * 2;
	
    // position attribute
	glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);
	
	glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, 4 * vertex_size, Vertex_data, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(uint), Indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, vertex_size, (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

	/////////////////////////////////////////////////////////////

	RenderSurface rs(800, 600);
	rs.activate();

	shader.setParam("textColor", glm::vec3(0.5f, 0.8f, 0.2f));
	shader.setParam("proj", rs.getOrthoProjection());
	shader.activate();

	Quad q;
	QuadDrawer qd;

	q.setPosition(glm::vec2(10,10));
	q.setSize(glm::vec2(100,100));
	q.setColor(Color::Blue);
	qd.drawQuad(q);
	glBindFramebuffer(GL_FRAMEBUFFER, 0); // back to default


	return true;

    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(m_VAO);

	Character chr = m_characters[uchar(65)];
	long index = chr.offset;
	for (uchar c = 65; c < 70; c++)
	{
        Character ch = m_characters[c];

        float xpos = ch.offset - index + ch.Bearing.x;
        float ypos = 40-ch.Bearing.y;
        float w = ch.Size.x;
        float h = ch.Size.y;

		printf("pos : (%f, %f) | sz : (%f, %f)\n", xpos, ypos, w, h);

		q.setPosition(glm::vec2(xpos,ypos));
		q.setSize(glm::vec2(w, h));
		//q.setScale(glm::vec2(1,-1));
		shader.setParam("model", q.getTransformMatrix());

        // render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);		
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0,0,1024,768);
	// tex = texColorBuffer;

	return true;
}


void Font::drawText(const std::string &str)
{
    float x=100, y=100;
	//glm::ortho(0.0f, 1024.f, 0.0f, 768.f);
	shader.setParam("textColor", glm::vec3(0.5f, 0.8f, 0.2f));
	shader.setParam("proj", RGraph::getInstancePtr()->getDefaultWindow()->getOrthoProjection());
	shader.activate();

    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(m_VAO);

	Quad q;
    // iterate through all characters
    std::string::const_iterator c;
    for (c = str.begin(); c != str.end(); c++) 
    {
        Character ch = m_characters[*c];

        float xpos = x + ch.Bearing.x;
        float ypos = y - ch.Bearing.y;
        float w = ch.Size.x;
        float h = ch.Size.y;

		q.setPosition(glm::vec2(xpos,ypos));
		q.setSize(glm::vec2(w, h));
		//q.setScale(glm::vec2(1,-1));
		shader.setParam("model", q.getTransformMatrix());

        // render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch.Advance >> 6); // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}


void Font::m_decrementRefCount()
{
    // Delete resource if value of ref count reaches 0
    if (dettachRefCount())
    {
        // Destroy glyphs
		if (!m_characters.empty())
		{
			// code to free glyphs
			m_freeGlyphs();
		}
    }
}

void Font::m_freeGlyphs()
{
	for (auto &i : m_characters)
	{
		glDeleteTextures(1, &i.second.TextureID);
	}

	m_characters.clear();
}
