#include "MousePicker.h"
#include "TheInput.h"
#include "TheScreen.h"
//-------------------------------------------------------------------------------
//Destructor
//-------------------------------------------------------------------------------
MousePicker::~MousePicker()
{
	delete camera;
}

//-------------------------------------------------------------------------------
//Constructor
//-------------------------------------------------------------------------------
MousePicker::MousePicker(Camera cam, glm::mat4 projection)
{
	camera = &cam;
	projection = projection;
	view = camera->GetView();
}

//-------------------------------------------------------------------------------
//Get Current Ray
//-------------------------------------------------------------------------------
glm::vec3 MousePicker::GetCurrentRay() const
{
	return currentRay;
}

//-------------------------------------------------------------------------------
//Update
//-------------------------------------------------------------------------------
void MousePicker::Update()
{
	view = camera->GetView();
	currentRay = CalculateMouseRay();
}

//-------------------------------------------------------------------------------
//Calculate Ray
//-------------------------------------------------------------------------------
glm::vec3 MousePicker::CalculateMouseRay()
{
	float mouseX = TheInput::Instance()->GetMousePositionX();
	float mouseY = TheInput::Instance()->GetMousePositionY();

	glm::mat4 invVP = glm::inverse(camera->GetProjection() * camera->GetView());
	float x = (2.0f * mouseX) / TheScreen::Instance()->GetScreenSize().x - 1.0f;
	float y = (2.0f * mouseX) / TheScreen::Instance()->GetScreenSize().y - 1.0f;

	glm::vec4 clipCoords = glm::vec4(x, -y, 1.0f, 1.0f);
	glm::vec4 worldPos = invVP * clipCoords;

	glm::vec3 dir = glm::normalize(worldPos);

	return dir;
}
