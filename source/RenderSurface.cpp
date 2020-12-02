#include <RG/RenderSurface.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <RG/r_util.h>

using namespace rg;

RenderSurface::RenderSurface()
{
    // Start Reference counting
    startRefCounting();
}

RenderSurface::RenderSurface(const glm::ivec2 &size)
{
    // Start Reference counting
    startRefCounting();
    m_size = size;
    generate();
}

RenderSurface::RenderSurface(uint x_sz, uint y_sz)
{
    // Start Reference counting
    startRefCounting();
    m_size = glm::ivec2(x_sz, y_sz);
    generate();
}

RenderSurface::RenderSurface(RenderSurface &rs)
{
    if (rs.m_framebuffer != RG_INVALID_ID)
    {
        // Do ref counting
        attachRefCount(rs);
        // cpy data
        m_texture = rs.m_texture;
        m_size = rs.m_size;
        m_framebuffer = rs.m_framebuffer;
    }
    else
        R_CPRINT_WARN("Render Surface : incomplete surface provided");
}

RenderSurface &RenderSurface::operator = (const RenderSurface &rs)
{    
    if (rs.m_framebuffer != RG_INVALID_ID)
    {
        m_detachRef();
        // Do ref counting
        attachRefCount(rs);
        // cpy data
        m_texture = rs.m_texture;
        m_size = rs.m_size;
        m_framebuffer = rs.m_framebuffer;
    }
    else
        R_CPRINT_WARN("Render Surface : incomplete surface provided");
    
    return *this;
}

bool RenderSurface::generate()
{
    if (m_framebuffer != RG_INVALID_ID)
        destroy();
    
    glGenFramebuffers(1, &m_framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);

    // generate texture
    unsigned int texColorBuffer;
    glGenTextures(1, &texColorBuffer);
    glBindTexture(GL_TEXTURE_2D, texColorBuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_size.x, m_size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    m_texture = Texture(texColorBuffer, m_size);

    // attach it to currently bound framebuffer object
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texColorBuffer, 0);
    
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        R_CPRINT_WARN("RenderSurface : Failed to generate framebuffer");
        return false;
    }

    glClear(GL_COLOR_BUFFER_BIT);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    return true;
}

bool RenderSurface::activate()
{
    if (m_framebuffer == RG_INVALID_ID)
        return false;
    
    glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);
    return true;    
}

void RenderSurface::deactivate()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void RenderSurface::clear()
{
    glClearColor(m_clear_color.r, m_clear_color.g, m_clear_color.b, m_clear_color.a);
    glClear(GL_COLOR_BUFFER_BIT);
}

void RenderSurface::setSize(const glm::ivec2 &surf_size)
{
    if (m_framebuffer == RG_INVALID_ID)
    {
        m_size = surf_size;
    }
    else
        R_CPRINT_WARN("Render Surface : Cannot resize while in use.");
}

void RenderSurface::m_detachRef()
{
    // Delete resource if value of ref count reaches 0
    if (dettachRefCount())
    {
        // Destroy Texture if exists
        if (m_framebuffer != RG_INVALID_ID)
            glDeleteFramebuffers(1, &m_framebuffer);
    }

    m_texture.destroy();
    m_framebuffer = RG_INVALID_ID;
}


void RenderSurface::destroy()
{
    m_detachRef();
    startRefCounting();
}

RenderSurface::~RenderSurface()
{
    m_detachRef();
}