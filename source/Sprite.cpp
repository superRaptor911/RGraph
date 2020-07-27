#include <RG/Sprite.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <RG/r_util.h>
#include <RG/RGraph.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


using namespace rg;

Sprite::Sprite()
{
    // Start ref counting
    startRefCounting();

    // _is_initiated is static
    if (!_is_initiated)
    {
        _default_shader = Shader(
                "#version 330 core\n"
                "layout (location = 0) in vec2 vpos;\n"
                "layout (location = 1) in vec2 texCoord;\n"
                "layout (location = 3) in mat4 instanceMatrix;\n"

                "out vec2 uv;\n"
                "uniform mat4 proj;"

                "void main()\n"
                "{\n"
                " gl_Position = proj * instanceMatrix * vec4(vpos, 0.0, 1.0);\n"
                " uv = texCoord;\n"
                "}\n",

                "#version 330 core\n"
                "out vec4 FragColor;\n"

                "in vec2 uv;\n"

                "uniform sampler2D texture1;\n"

                "void main()\n"
                "{\n"
                "	FragColor = texture(texture1, uv);\n"
                "}\n"
                );

        glGenVertexArrays(1, &_VAO);
        glGenBuffers(1, &_VBO);
        glGenBuffers(1, &_EBO);
        glGenBuffers(1, &_trans_buffer);

        glBindVertexArray(_VAO);

        glBindBuffer(GL_ARRAY_BUFFER, _VBO);
        glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(vertex), _vertex_data, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(uint), _indices, GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, pos));
        glEnableVertexAttribArray(0);

        // texture coord attribute
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, uv));
        glEnableVertexAttribArray(1);

        // Trans buffer
        glBindBuffer(GL_ARRAY_BUFFER, _trans_buffer);
        glBufferData(GL_ARRAY_BUFFER, 10000 * sizeof(glm::mat4), nullptr, GL_DYNAMIC_DRAW);

        std::size_t vec4Size = sizeof(glm::vec4);
        glEnableVertexAttribArray(3); 
        glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)0);
        glEnableVertexAttribArray(4); 
        glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(1 * vec4Size));
        glEnableVertexAttribArray(5); 
        glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(2 * vec4Size));
        glEnableVertexAttribArray(6); 
        glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(3 * vec4Size));

        glVertexAttribDivisor(3, 1);
        glVertexAttribDivisor(4, 1);
        glVertexAttribDivisor(5, 1);
        glVertexAttribDivisor(6, 1);

        RGraph::addCallback_onReadyToDraw(_drawAllSprites);
        _is_initiated = true;
    }
}

Sprite::Sprite(const Texture &T)
{
    // Start ref counting
    startRefCounting();
    // Set Texture
    _texture = T;
    _origin = glm::vec2(T.getSize()) / 2.f;

    // _is_initiated is static
    if (!_is_initiated)
    {
        _default_shader = Shader(
                "#version 330 core\n"
                "layout (location = 0) in vec2 vpos;\n"
                "layout (location = 1) in vec2 texCoord;\n"
                "layout (location = 3) in mat4 instanceMatrix;\n"

                "out vec2 uv;\n"
                "uniform mat4 proj;"

                "void main()\n"
                "{\n"
                " gl_Position = proj * instanceMatrix * vec4(vpos, 0.0, 1.0);\n"
                " uv = texCoord;\n"
                "}\n",

                "#version 330 core\n"
                "out vec4 FragColor;\n"

                "in vec2 uv;\n"

                "uniform sampler2D texture1;\n"

                "void main()\n"
                "{\n"
                "	FragColor = texture(texture1, uv);\n"
                "}\n"
                );

        glGenVertexArrays(1, &_VAO);
        glGenBuffers(1, &_VBO);
        glGenBuffers(1, &_EBO);
        glGenBuffers(1, &_trans_buffer);

        glBindVertexArray(_VAO);

        glBindBuffer(GL_ARRAY_BUFFER, _VBO);
        glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(vertex), _vertex_data, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(uint), _indices, GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, pos));
        glEnableVertexAttribArray(0);

        // texture coord attribute
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, uv));
        glEnableVertexAttribArray(1);

        // Trans buffer
        glBindBuffer(GL_ARRAY_BUFFER, _trans_buffer);
        glBufferData(GL_ARRAY_BUFFER, 10000 * sizeof(glm::mat4), nullptr, GL_DYNAMIC_DRAW);

        std::size_t vec4Size = sizeof(glm::vec4);
        glEnableVertexAttribArray(3); 
        glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)0);
        glEnableVertexAttribArray(4); 
        glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(1 * vec4Size));
        glEnableVertexAttribArray(5); 
        glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(2 * vec4Size));
        glEnableVertexAttribArray(6); 
        glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(3 * vec4Size));

        glVertexAttribDivisor(3, 1);
        glVertexAttribDivisor(4, 1);
        glVertexAttribDivisor(5, 1);
        glVertexAttribDivisor(6, 1);

        RGraph::addCallback_onReadyToDraw(_drawAllSprites);
        _is_initiated = true;
    }
}

Sprite::Sprite(const Sprite &S)
{
    // Attach to S
    attachToRefCount(S);
    // Cpy Texture
    _texture = S._texture;

    _rotation = S._rotation;
    _position = S._position;
    _origin = S._origin;
    _scale = S._scale;
}

Sprite &Sprite::operator = (const Sprite &S)
{ 
    _decrementRefCount();

    // Increment ref count of S
    attachToRefCount(S);
    // Cpy Texture
    _texture = S._texture;

    _rotation = S._rotation;
    _position = S._position;
    _origin = S._origin;
    _scale = S._scale;

    return *this;
}


void Sprite::_decrementRefCount()
{
    // Free resource if ref count reaches 0
    if (dettachRefCount())
    {
        /*      
        glDeleteVertexArrays(1, &_VAO);
        glDeleteBuffers(1, &_VBO);
        glDeleteBuffers(1, &_EBO);*/

        DEBUG_PRINT("Deleting Sprite");
    }    
}

void Sprite::draw()
{ 
    _draw_queue.push_back(*this);
}

void Sprite::_drawAllSprites()
{
    glm::mat4 proj = RGraph::getOrthoProgection();
    int quad_count = _draw_queue.size();
    glm::mat4 *trans_buffer = new glm::mat4[ quad_count];
    int index = 0;

    for (auto &it : _draw_queue)
    {
        glm::mat4 model = glm::mat4(1.0f);
       // model = glm::translate(model, glm::vec3(it._position , 0.0f));
        model = glm::translate(model, glm::vec3(it._origin + it._position, 0.0f)); 
        model = glm::rotate(model, it._rotation, glm::vec3(0.0f, 0.0f, 1.0f)); 
        model = glm::translate(model, glm::vec3(-it._origin, 0.0f));
        model = glm::scale(model, glm::vec3(glm::vec2(it._texture.getSize()) * it._scale, 1.0f));

        trans_buffer[index] = model;
        index += 1;
    }

    
    _default_shader.activate();
    _default_shader.setParam("proj", proj);
    glBindVertexArray(_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, _trans_buffer);
    glBufferSubData(GL_ARRAY_BUFFER, 0, quad_count * sizeof(glm::mat4), trans_buffer);
    glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, quad_count);

    _draw_queue.clear();
    delete[] trans_buffer;
}

Sprite::~Sprite()
{
    _decrementRefCount();
}