#include "Transform.h"



const glm::mat4& Transform::getMatrix() const
{
    return m_matrix;
}

Transform& Transform::operator=(const Transform& other)
{
    if (this != &other)
    {
        m_matrix = other.m_matrix;
    }
    return *this;
}


Transform::Transform(float a00, float a01, float a02,
    float a10, float a11, float a12,
    float a20, float a21, float a22)
{
    m_matrix = glm::mat4(1.0f);
    // rotation + scale
    m_matrix[0][0] = a00;
    m_matrix[0][1] = a01;
    m_matrix[1][0] = a10;
    m_matrix[1][1] = a11;

    // translation
    m_matrix[3][0] = a02;
    m_matrix[3][1] = a12;

    // z-axis and bottom row
    m_matrix[2][2] = 1.0f;
    m_matrix[3][3] = 1.0f;
}

FloatRect Transform::transform_rect(const FloatRect& rectangle) const
{
    glm::vec2 p0 = rectangle.position;
    glm::vec2 p2 = rectangle.position + glm::vec2(rectangle.size.x, 0.0f);
    glm::vec2 p3 = rectangle.position + rectangle.size;
    glm::vec2 p1 = rectangle.position + glm::vec2(0.0f, rectangle.size.y);

    auto transformPoint = [&](const glm::vec2& p) {
        glm::vec4 r = m_matrix * glm::vec4(p, 0.0f, 1.0f);
        return glm::vec2(r.x, r.y);
        };

    glm::vec2 t0 = transformPoint(p0);
    glm::vec2 t1 = transformPoint(p1);
    glm::vec2 t2 = transformPoint(p2);
    glm::vec2 t3 = transformPoint(p3);

    const std::array points = { t0, t1, t2, t3 };
    // Compute the bounding rectangle of the transformed points
    glm::vec2 pmin = points[0];
    glm::vec2 pmax = points[0];

    for (std::size_t i = 1; i < points.size(); ++i)
    {
        // clang-format off
        if (points[i].x < pmin.x) pmin.x = points[i].x;
        else if (points[i].x > pmax.x) pmax.x = points[i].x;

        if (points[i].y < pmin.y) pmin.y = points[i].y;
        else if (points[i].y > pmax.y) pmax.y = points[i].y;
        // clang-format on
    }

    return { pmin, pmax - pmin };
}

Transform& Transform::combine(const Transform& transform)
{
    m_matrix = m_matrix * transform.m_matrix;
    return *this;
}

Transform& Transform::translate(glm::vec2 offset)
{
    m_matrix = glm::translate(m_matrix, glm::vec3(offset, 0.0f));
    return *this;
}

Transform& Transform::scale(glm::vec2 factor)
{
    m_matrix = glm::scale(m_matrix, glm::vec3(factor, 1.0f));
    return *this;
}

Transform& Transform::rotate(float angle)
{
    float angle_in_radians = glm::radians(angle);
    m_matrix = glm::rotate(m_matrix, angle_in_radians, glm::vec3(0, 0, 1));
    return *this;
}

