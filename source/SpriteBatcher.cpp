#include <RG/SpriteBatcher.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <RG/RGraph.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace rg;

SpriteBatcher SpriteBatcher::_SBinstance;

SpriteBatcher::SpriteBatcher()
{
    RGraph::addCallback_RGInitiated(_initBatcher);
}

void SpriteBatcher::_initBatcher()
{
    const char *vertex_source = "#version 330 core\n"
        "layout (location = 0) in vec2 vpos;\n"
        "layout (location = 1) in vec2 texCoord;\n"
        "layout (location = 3) in mat4 instanceMatrix;\n"

        "out vec2 uv;\n"
        "uniform mat4 proj;"

        "void main()\n"
        "{\n"
        " gl_Position = proj * instanceMatrix * vec4(vpos, 0.0, 1.0);\n"
        " uv = texCoord;\n"
        "}\n";
    
    const char *frag_source = "#version 330 core\n"
        "out vec4 FragColor;\n"

        "in vec2 uv;\n"

        "uniform sampler2D texture1;\n"

        "void main()\n"
        "{\n"
        "	FragColor = texture(texture1, uv);\n"
        "}\n";

    

    _SBinstance._default_shader = Shader(
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

    int size_of_vertex = sizeof(float) * (2 + 2); // 2 floats for pos and 2 for uv

    glGenVertexArrays(1, &_SBinstance._VAO);
    glGenBuffers(1, &_SBinstance._VBO);
    glGenBuffers(1, &_SBinstance._EBO);
    glGenBuffers(1, &_SBinstance._trans_buffer);

    glBindVertexArray(_SBinstance._VAO);

    glBindBuffer(GL_ARRAY_BUFFER, _SBinstance._VBO);
    glBufferData(GL_ARRAY_BUFFER, 4 * size_of_vertex, _SBinstance._vertex_data, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _SBinstance._EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(uint), _SBinstance._indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, size_of_vertex, (void*)0);
    glEnableVertexAttribArray(0);

    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, size_of_vertex, (void*)(sizeof(float) * 2));
    glEnableVertexAttribArray(1);

    // Trans buffer
    glBindBuffer(GL_ARRAY_BUFFER, _SBinstance._trans_buffer);
    glBufferData(GL_ARRAY_BUFFER, _SBinstance._max_sprites_per_batch * sizeof(glm::mat4), nullptr, GL_DYNAMIC_DRAW);

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
}

void SpriteBatcher::_drawAllSprites()
{
    glm::mat4 proj = RGraph::getOrthoProgection();
    int quad_count = _SBinstance._draw_queue.size();
    glm::mat4 *trans_buffer = new glm::mat4[ quad_count];
    int index = 0;

    for (auto &it : _SBinstance._draw_queue)
    {
        glm::mat4 model = glm::mat4(1.0f);
       // model = glm::translate(model, glm::vec3(it._position , 0.0f));
        model = glm::translate(model, glm::vec3(it._origin * it._scale + it._position, 0.0f)); 
        model = glm::rotate(model, it._rotation, glm::vec3(0.0f, 0.0f, 1.0f)); 
        model = glm::translate(model, glm::vec3(-it._origin * it._scale, 0.0f));
        model = glm::scale(model, glm::vec3(glm::vec2(it._texture.getSize()) * it._scale, 1.0f));

        trans_buffer[index] = model;
        index += 1;
    }

    _SBinstance._default_shader.activate();
    _SBinstance._default_shader.setParam("proj", proj);
    glBindVertexArray(_SBinstance._VAO);
    glBindBuffer(GL_ARRAY_BUFFER, _SBinstance._trans_buffer);
    glBufferSubData(GL_ARRAY_BUFFER, 0, quad_count * sizeof(glm::mat4), trans_buffer);
    glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, quad_count);

    _SBinstance._draw_queue.clear();
    delete[] trans_buffer;
}