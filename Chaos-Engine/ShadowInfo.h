#ifndef SHADOWINFO_H
#define SHADOWINFO_H

#include <glm.hpp>

class ShadowInfo
{
public:

	ShadowInfo(const glm::mat4& projection) : m_projection(projection) {}

	inline glm::mat4 GetProjection() { return m_projection; }

private:

	glm::mat4 m_projection;
};

#endif