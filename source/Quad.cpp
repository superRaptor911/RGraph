#include <RG/Quad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <RG/QuadDrawer.h>

using namespace rg;


void Quad::m_getTransformMatrix()
{
    glm::mat4 model = glm::mat4(1.0f);

    model = glm::translate(model, glm::vec3(m_position, 0.0f)); 
    model = glm::rotate(model, m_rotation, glm::vec3(0.0f, 0.0f, 1.0f)); 
    model = glm::translate(model, glm::vec3(-m_origin * m_scale, 0.0f));
    model = glm::scale(model, glm::vec3(m_size  * m_scale, 1.0f));

    m_model = model;
}


glm::mat4 Quad::getTransformMatrix()
{
    if (m_transformation_changed)
    {
        m_getTransformMatrix();
    }

    return m_model;    
}
