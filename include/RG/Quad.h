#ifndef QUAD_H
#define QUAD_H

#include <glm/glm.hpp>
#include <RG/Color.h>


namespace rg
{
    class QuadDrawer;
    class Quad
    {
    protected:
        glm::vec2 m_position = glm::vec2(0,0);
        glm::vec2 m_size = glm::vec2(0,0);

        glm::vec2 m_scale = glm::vec2(1,1);
        glm::vec2 m_origin  = glm::vec2(0,0);
        float m_rotation = 0.f;

        bool m_is_visible = true;
        bool m_transformation_changed = true;
        int m_z_index = 0;

        glm::mat4 m_model;
        Color m_color;

        friend QuadDrawer;

    private:
        
        void m_getTransformMatrix();

    public:

        glm::vec2 getPosition() const {return m_position;}

        void setPosition(const glm::vec2 &pos) {m_position = pos; m_transformation_changed = true; }

        void move(const glm::vec2 &delta) { m_position += delta; m_transformation_changed = true;}

        glm::vec2 getOrigin() const {return m_origin;}
        
        void setOrigin(const glm::vec2 &origin) {m_origin = origin; m_transformation_changed = true;}

        glm::vec2 getScale() { return m_scale;}

        void setScale(const glm::vec2 &scale) { m_scale = scale; m_transformation_changed = true;}

        float getRotaion() { return m_rotation;}

        void setRotation(float rot) { m_rotation = rot; m_transformation_changed = true;}

        void rotate(float angle) { m_rotation += angle; m_transformation_changed = true;}

        void setColor(const Color &clr) { m_color = clr;}

        Color getColor() { return m_color;}

        void setSize(const glm::vec2 &sz) { m_size = sz; m_origin = sz / 2.f; m_transformation_changed = true;}

        glm::mat4 getTransformMatrix();

    };

    
} // namespace rg


#endif
