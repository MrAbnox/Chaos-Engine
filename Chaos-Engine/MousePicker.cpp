#include "MousePicker.h"
#include "TheInput.h"
#include "TheScreen.h"

MousePicker::MousePicker(Camera cam, glm::mat4 projection)
{
	m_camera = &cam;
	m_projection = projection;
	m_view = m_camera->GetView();
}

glm::vec3 MousePicker::GetCurrentRay() const
{
	return m_currentRay;
}

void MousePicker::Update()
{
	m_view = m_camera->GetView();
	m_currentRay = CalculateMouseRay();
}

glm::vec3 MousePicker::CalculateMouseRay()
{
	float mouseX = TheInput::Instance()->GetMousePositionX();
	float mouseY = TheInput::Instance()->GetMousePositionY();

	glm::mat4 invVP = glm::inverse(m_camera->GetProjection() * m_camera->GetView());
	float x = (2.0f * mouseX) / TheScreen::Instance()->GetScreenSize().x - 1.0f;
	float y = (2.0f * mouseX) / TheScreen::Instance()->GetScreenSize().y - 1.0f;

	glm::vec4 clipCoords = glm::vec4(x, -y, 1.0f, 1.0f);
	glm::vec4 worldPos = invVP * clipCoords;

	glm::vec3 dir = glm::normalize(worldPos);

	return dir;
}
