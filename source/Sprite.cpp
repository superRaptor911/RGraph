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

                "out vec2 uv;\n"
                "uniform mat4 proj;"

                "void main()\n"
                "{\n"
                " gl_Position = proj * vec4(vpos, 0.0, 1.0);\n"
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

        glBindVertexArray(_VAO);

        glBindBuffer(GL_ARRAY_BUFFER, _VBO);
        glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(vertex) * 10000, nullptr, GL_DYNAMIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(uint) * 10000, nullptr, GL_DYNAMIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, pos));
        glEnableVertexAttribArray(0);

        // texture coord attribute
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, uv));
        glEnableVertexAttribArray(1);

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

    if (!_is_initiated)
    {
        _default_shader = Shader(
                "#version 330 core\n"
                "layout (location = 0) in vec2 vpos;\n"
                "layout (location = 1) in vec2 texCoord;\n"

                "out vec2 uv;\n"
                "uniform mat4 proj;"

                "void main()\n"
                "{\n"
                " gl_Position = proj * vec4(vpos, 0.0, 1.0);\n"
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

        glBindVertexArray(_VAO);

        glBindBuffer(GL_ARRAY_BUFFER, _VBO);
        glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(vertex) * 10000, nullptr, GL_DYNAMIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(uint) * 10000, nullptr, GL_DYNAMIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, pos));
        glEnableVertexAttribArray(0);

        // texture coord attribute
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)(8));
        glEnableVertexAttribArray(1);

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
    float data[ 4 * sizeof(vertex) * 10000];
    long int index = 0;

    for (auto &it : _draw_queue)
    {
        glm::mat4 model = glm::mat4(1.0f);

       // model = glm::translate(model, glm::vec3(it._position , 0.0f));
        model = glm::translate(model, glm::vec3(it._origin + it._position, 0.0f)); 
        model = glm::rotate(model, it._rotation, glm::vec3(0.0f, 0.0f, 1.0f)); 
        model = glm::translate(model, glm::vec3(-it._origin, 0.0f));
        model = glm::scale(model, glm::vec3(glm::vec2(it._texture.getSize()) * it._scale, 1.0f));

        glm::vec4 coord[4];
        coord[0] = model * glm::vec4(1.f, 1.f, 0.f, 1.f);
        coord[0].z = 1.f; coord[0].w = 1.f; 
        coord[1] = model * glm::vec4(1.f, 0.f, 0.f, 1.f);
        coord[1].z = 1.f; coord[1].w = 0.f;
        coord[2] = model * glm::vec4(0.f, 0.f, 0.f, 1.f);
        coord[2].z = 0.f; coord[2].w = 0.f;
        coord[3] = model * glm::vec4(0.f, 1.f, 0.f, 1.f);
        coord[3].z = 0.f; coord[3].w = 1.f;

        memcpy(&data[index], &coord, sizeof(coord));
        index += 16; // 4 * 4
        //it._texture.activate();
    }

    int quad_count = _draw_queue.size();
    uint indices[ 6 * 10000];
    for (int i = 0; i < quad_count; i++)
    {
        indices[i * 6] = 0 + 4 * i;
        indices[i * 6 + 1] = 1 + 4 * i;
        indices[i * 6 + 2] = 3 + 4 * i;
        indices[i * 6 + 3] = 1 + 4 * i;
        indices[i * 6 + 4] = 2 + 4 * i;
        indices[i * 6 + 5] = 3 + 4 * i;
    }

    
    _default_shader.activate();
    _default_shader.setParam("proj", proj);
    glBindVertexArray(_VAO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, 16 * quad_count * sizeof(float), &data);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, 6 * quad_count * sizeof(uint), &indices);    
    glDrawElements(GL_TRIANGLES, 6 * quad_count, GL_UNSIGNED_INT, 0);

    _draw_queue.clear();

}

Sprite::~Sprite()
{
    _decrementRefCount();
}