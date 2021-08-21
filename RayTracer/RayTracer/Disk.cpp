#include "Disk.h"

#define PI 3.14159265

using namespace Primitive;

Disk::Disk()
    : m_center(0,0,0)
    , m_normal(0,0,1)
    , m_radius(1)
    , m_material()
{}

Disk::Disk(
    const Vector3& center,
    const Vector3& normal,
    float radius,
    bool isBackFaceCulling)

    : m_center(center)
    , m_normal(normal.unit_vector())
    , m_radius(radius)
    , m_isBackFaceCulling(isBackFaceCulling)
    , m_material()
{}

Disk::Disk(
    const Vector3& center,
    const Vector3& normal,
    float radius, 
    bool isBackFaceCulling,
    const Material& material)

    : m_center(center)
    , m_normal(normal.unit_vector())
    , m_radius(radius)
    , m_isBackFaceCulling(isBackFaceCulling)
    , m_material(material)
{}

bool Disk::intersect_first_image(const Ray& ray) const 
{
    float s = Vector3::dot(ray.direction, m_normal);
    
    if (!m_isBackFaceCulling) {
        if (acos(s) * 180.0 / PI < 90.0) {
            return false;
        }
    }

    if (s < 1e-6 && s >= -1e-6) {
        // Perpendicular to each other
        return false;
    }
    float x = Vector3::dot((m_center - ray.origin), m_normal) / s;
    if (x < 0) {
        // if the hit point is behind the origin point
        return false;
    }
        
    // True if the hit point is on the disk, otherwise false
    return (ray.at(x) - m_center).length() <= m_radius;
}

Hit Disk::intersect(const Ray& ray) const 
{
    // Same operations in the function above
    float s = Vector3::dot(ray.direction, m_normal);
    float x = Vector3::dot((m_center - ray.origin), m_normal) / s;

    if (!m_isBackFaceCulling) {
        if (acos(s) * 180.0 / PI < 90.0) {
            return Hit();
        }
    }

    if (x < 0 || (s < 1e-6 && s >= -1e-6)) {
        // if the hit point is behind the origin point
        // or vectors are perpendicular to each other
        return Hit();
    }

    // Solve the ray's equation with the given ratio to find the hit point
    Vector3 hitPoint = ray.at(x);
    // Check if x is in front of ray's origin and the hit point is on the disk 
    bool isValid = x >= 0 && (hitPoint - m_center).length() <= m_radius;

    // Return hit informations
    return Hit{
        isValid,
        hitPoint,
        m_normal,
        m_material,
        (hitPoint-ray.origin).length()
    };
}