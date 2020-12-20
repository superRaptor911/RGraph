#include <RG/r_util.h>
#include <RG/Font.h>
#include <RG/RGraph.h>
#include <RG/QuadDrawer.h>
#include <RG/RenderSurface.h>
#include <ft2build.h>
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
    m_detachRef();
    // Do ref counting
    attachRefCount(f);

    // get data from f
    m_characters = f.m_characters;
    m_size = f.m_size;

    return *this;
}

bool Font::loadFont(const std::string &path, uint font_size)
{
    // set Size
    m_size = font_size;
    // Handle previously loaded font
    if (!m_characters.empty())
    {
	destroy();
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

    // Set Size
    FT_Set_Pixel_Sizes(face, 0, m_size);
    // Load glyphs
    long f_offset = 0;	// Offset of character in texture
    int max_bearing = 0;
    for (unsigned char c = 0; c < 128; c++)
    {
	// load character glyph 
	if (FT_Load_Char(face, c, FT_LOAD_RENDER))
	{
	    R_CPRINT_WARN("Failed to load Glyph ");
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

	if (max_bearing < face->glyph->bitmap_top)
	{
	    max_bearing = face->glyph->bitmap_top;
	}
    }

    // Cleanup FT
    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    if (m_characters.empty())
    {
	R_CPRINT_ERR("Unable to generate any glyps for Font.");
	return false;
    }

    // Shader source
    const char *vs_src ="#version 330 core \n"
	"layout (location = 0) in vec2 vertex;\n"
	"out vec2 TexCoords;\n"
	"uniform mat4 proj;\n"
	"uniform mat4 model;\n"
	"void main()\n"
	"{\n"
	"gl_Position = proj * model * vec4(vertex.xy, 0.0, 1.0);\n"
	"TexCoords = vertex.xy;\n"
	"}\n";

    const char *fs_src = "#version 330 core \n in vec2 TexCoords;" 
	"out vec4 color;" 
	"uniform sampler2D text;" 
	"uniform vec3 textColor;" 
	"void main()"
	"{"
	"vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);" 
	"color = vec4(textColor, 1.0) * sampled;" 
	"}";

    // Create Shader
    shader = rg::Shader(vs_src, fs_src);

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

    // Create Surface
    auto last_ch = (--m_characters.end())->second;
    RenderSurface rs(last_ch.offset + last_ch.Bearing.x, m_size);
    rs.activate();
    rs.setClearColor(Color(0.0f,0.0f,0.0f,0.0f));
    rs.clear();
    shader.setParam("textColor", glm::vec3(0.0f, 0.0f, 0.0f));
    shader.setParam("proj", rs.getOrthoProjection());
    shader.activate();	

    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(m_VAO);

    for (uchar c = 0; c < 128; c++)
    {
	Character ch = m_characters[c];

	float xpos = ch.offset + ch.Bearing.x;
	float ypos = max_bearing - ch.Bearing.y;
	float w = ch.Size.x;
	float h = ch.Size.y;

	Quad q;
	q.setPosition(glm::vec2(xpos,ypos));
	q.setSize(glm::vec2(w, h));
	shader.setParam("model", q.getTransformMatrix());

	// render glyph texture over quad
	glBindTexture(GL_TEXTURE_2D, ch.TextureID);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);	
    }

    // Cleanup
    glBindVertexArray(0);
    glDeleteBuffers(1, &m_VBO);
    glDeleteBuffers(1, &m_EBO);
    glDeleteVertexArrays(1, &m_VAO);

    for (auto &i : m_characters)
    {
	glDeleteTextures(1, &i.second.TextureID);
    }

    rs.deactivate();
    m_texture = rs.getTexture();
    return true;
}


void Font::m_detachRef()
{
    // Delete resource if value of ref count reaches 0
    if (dettachRefCount())
    {
	// Destroy glyphs
	if (!m_characters.empty())
	{
	    m_characters.clear();
	    m_texture.destroy();
	}
    }
}


void Font::destroy()
{
    m_detachRef();
    startRefCounting();
}
