#ifndef SHADOWINFO_H
#define SHADOWINFO_H

#include <glm.hpp>

class ShadowInfo
{
public:

	ShadowInfo(const glm::mat4& projection) : projection(projection) {}

	inline glm::mat4 GetProjection() { return projection; }

private:

	glm::mat4 projection;
};

#endif