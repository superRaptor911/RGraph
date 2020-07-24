#include <RG/Sprite.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <RG/r_util.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


using namespace rg;

Sprite::Sprite()
{
    // Start ref counting
    startRefCounting();

    glGenVertexArrays(1, &_VAO);
    glGenBuffers(1, &_VBO);
    glGenBuffers(1, &_EBO);

    glBindVertexArray(_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(_vertex_data), _vertex_data, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_indices), _indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

Sprite::Sprite(const Texture &T)
{
    // Start ref counting
    startRefCounting();
    // Set Texture
    _texture = T;
    _origin = glm::vec2(T.getSize()) / 2.f;

    glGenVertexArrays(1, &_VAO);
    glGenBuffers(1, &_VBO);
    glGenBuffers(1, &_EBO);

    glBindVertexArray(_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(_vertex_data), _vertex_data, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_indices), _indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

Sprite::Sprite(const Sprite &S)
{
    // Attach to S
    attachToRefCount(S);
    // Cpy Texture
    _texture = S._texture;

    //cpy buffer handles
    _VAO = S._VAO;
    _VBO = S._VBO;
    _EBO = S._EBO;
}

Sprite &Sprite::operator = (const Sprite &S)
{ 
    _decrementRefCount();

    // Increment ref count of S
    attachToRefCount(S);
    // Cpy Texture
    _texture = S._texture;

    return *this;
}


void Sprite::_decrementRefCount()
{
    // Free resource if ref count reaches 0
    if (dettachRefCount())
    {
        glDeleteVertexArrays(1, &_VAO);
        glDeleteBuffers(1, &_VBO);
        glDeleteBuffers(1, &_EBO);

        DEBUG_PRINT("Deleting Sprite");
    }    
}

void Sprite::draw()
{
    static Shader _default_shader = Shader(
        "#version 330 core\n"
        "layout (location = 0) in vec2 aPos;\n"
        "layout (location = 1) in vec2 aTexCoord;\n"

        "out vec2 TexCoord;\n"
        "uniform mat4 model;\n"
        "uniform mat4 proj;\n"

        "void main()\n"
        "{\n"
        " gl_Position = proj * model * vec4(aPos, 0.0, 1.0);\n"
        " TexCoord = aTexCoord;\n"
        "}\n",

        "#version 330 core\n"
        "out vec4 FragColor;\n"

        "in vec2 TexCoord;\n"

        "uniform sampler2D texture1;\n"

        "void main()\n"
        "{\n"
        "	FragColor = texture(texture1, TexCoord);\n"
        "}\n"
        );

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(_position , 0.0f));

    model = glm::translate(model, glm::vec3(_origin, 0.0f)); 
    model = glm::rotate(model, _rotation, glm::vec3(0.0f, 0.0f, 1.0f)); 
    model = glm::translate(model, glm::vec3(-_origin, 0.0f));

    model = glm::scale(model, glm::vec3(glm::vec2(_texture.getSize()) * _scale, 1.0f)); 
    
    _default_shader.setParam("proj", glm::ortho(0.0f, 640.0f, 480.0f, 0.0f, -1.0f, 1.0f));

    _default_shader.setParam("model", model);
    
    if (_custom_shader.isReady())
        _custom_shader.activate();
    else
        _default_shader.activate();
    
    _texture.activate();
    glBindVertexArray(_VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

Sprite::~Sprite()
{
    _decrementRefCount();
}