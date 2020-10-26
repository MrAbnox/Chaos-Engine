#include "Ray.h"
#include "TheInput.h"
#include "TheScreen.h"

Ray::Ray(const glm::vec3& originRef, const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix)
{
	// Stores origin of the ray.
	origin = originRef;

	glm::vec2 mousePosition;
	mousePosition.x = TheInput::Instance()->GetMousePositionX();
	mousePosition.y = TheInput::Instance()->GetMousePositionY();
	float width = TheScreen::Instance()->GetScreenSize().x;
	float height = TheScreen::Instance()->GetScreenSize().y;

	// Normalized Ray
	glm::vec3 ray;
	ray.x = (2.0f * mousePosition.x) / width - 1.0f;
	ray.y = 1.0f - (2.0f * mousePosition.y) / height;
	ray.z = 1.0f;

	// Convert into clip spaces
	glm::vec4 rayClipCoords = glm::vec4(ray.x, ray.y, -1.0f, 1.0f);

	// Inverse Projection Matrix
	glm::mat4 invertedProjectionMatrix = glm::inverse(projectionMatrix);

	// Convert it to eye Space
	glm::vec4 rayEyeCoords = invertedProjectionMatrix * rayClipCoords;
	rayEyeCoords.z = -1.0f;
	rayEyeCoords.w = 0.0f;

	// Inverse Projection Matrix
	glm::mat4 invertedViewMatrix = glm::inverse(viewMatrix);

	// Convert to world coords (ray direction)
	direction = invertedViewMatrix * rayEyeCoords;

	// Normalize / Ray Direction
	direction = glm::normalize(direction);
}

Ray::~Ray()
{
}

glm::vec3 Ray::GetDirection()
{
	return glm::vec3();
}
