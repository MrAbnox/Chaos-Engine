#include "Physics.h"
#include <glm.hpp>
#include <gtx/intersect.hpp>

Physics::Physics()
{
}

//-------------------------------------------------------------------------------
//Ray Collision with Box
//-------------------------------------------------------------------------------
bool Physics::RayABB(glm::vec3 dir, glm::vec3 pos, AABB aabb)
{
    glm::vec3 tempDir;
    // r.dir is unit direction vector of ray
    tempDir.x = 1.0f / dir.x;
    tempDir.y = 1.0f / dir.y;
    tempDir.z = 1.0f / dir.z;
    // lb is the corner of AABB with minimal coordinates - left bottom, rt is maximal corner
    // r.org is origin of ray
    float t1 = (aabb.GetMin().x - pos.x) * tempDir.x;
    float t2 = (aabb.GetMax().x - pos.x) * tempDir.x;
    float t3 = (aabb.GetMin().y - pos.y) * tempDir.y;
    float t4 = (aabb.GetMax().y - pos.y) * tempDir.y;
    float t5 = (aabb.GetMin().z - pos.z) * tempDir.z;
    float t6 = (aabb.GetMax().z - pos.z) * tempDir.z;
    
    float tmin = glm::max(glm::max(glm::min(t1, t2), glm::min(t3, t4)), glm::min(t5, t6));
    float tmax = glm::min(glm::min(glm::max(t1, t2), glm::max(t3, t4)), glm::max(t5, t6));
    
    // if tmax < 0, ray (line) is intersecting AABB, but the whole AABB is behind us
    if (tmax < 0)
    {
        return false;
    }
    
    // if tmin > tmax, ray doesn't intersect AABB
    if (tmin > tmax)
    {
        return false;
    }
    
    return true;
}
