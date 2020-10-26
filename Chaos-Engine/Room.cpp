#include "Room.h"
#include "Game.h"

//-------------------------------------------------------------------------------
//Constructor
//-------------------------------------------------------------------------------
Room::Room()
{

}

//-------------------------------------------------------------------------------
//Destructor
//-------------------------------------------------------------------------------
Room::~Room()
{
}

//-------------------------------------------------------------------------------
//Create 
//-------------------------------------------------------------------------------
void Room::Create()
{
	ceiling.Create("NormalMapping");
	ceiling.LoadNormalMap("./Textures/Models/GR_Ceiling/GR_Ceiling_Normal.png");
	ceiling.LoadHeightMap("./Textures/Models/GR_Ceiling/GR_Ceiling_Height.jpg");
	ceiling.LoadObj("./Models/GR_Ceiling.obj");
	ceiling.Scale(glm::vec3(0.01f));
	ceiling.LoadTexture("./Textures/Models/GR_Ceiling/GR_Ceiling_diffuse.png", "Ceiling");
	ceiling.SetName("Ceiling");

	airCon.Create("NormalMapping");
	airCon.LoadNormalMap("./Textures/Models/GR_AirCon/GR_AirCon_Normal.png");
	airCon.LoadHeightMap("./Textures/Models/GR_AirCon/GR_AirCon_Height.jpg");
	airCon.LoadObj("./Models/GR_AirCon.obj");
	airCon.Scale(glm::vec3(0.01f));
	airCon.LoadTexture("./Textures/Models/GR_AirCon/GR_AirCon_Diffuse.png", "AirCon");
	airCon.SetName("AirCon");
	
	speakers.Create("NormalMapping");
	speakers.LoadNormalMap("./Textures/Models/GR_BlueSky_Speaker/GR_BluseSky_Speaker_Normal.png");
	speakers.LoadHeightMap("./Textures/Models/GR_BlueSky_Speaker/GR_BluseSky_Speaker_Height.jpg");
	speakers.LoadObj("./Models/GR_BlueSky_Speakers.obj");
	speakers.Scale(glm::vec3(0.01f));
	speakers.SetName("Speakers");
	speakers.LoadTexture("./Textures/Models/GR_BlueSky_Speaker/GR_BluseSky_Speaker_Diffuse.png", "Speakers");

	door.Create("NormalMapping");
	door.LoadNormalMap("./Textures/Models/GR_Door/GR_Door_Normal.png");
	door.LoadHeightMap("./Textures/Models/GR_Door/GR_Door_Height.jpg");
	door.LoadObj("./Models/GR_Door.obj");
	door.Scale(glm::vec3(0.01f));
	door.SetName("Door");
	door.LoadTexture("./Textures/Models/GR_Door/GR_Door_Diffuse.png", "Door");

	nintendoWii.Create("NormalMapping");
	nintendoWii.LoadNormalMap("./Textures/Models/GR_NintendoWii/GR_NintendoWii_Normal.png");
	nintendoWii.LoadHeightMap("./Textures/Models/GR_NintendoWii/GR_NintendoWii_Height.jpg");
	nintendoWii.LoadObj("./Models/GR_NintendoWii.obj");
	nintendoWii.Scale(glm::vec3(0.01f));
	nintendoWii.SetName("NintendoWii");
	nintendoWii.LoadTexture("./Textures/Models/GR_NintendoWii/GR_NintendoWii_Diffuse.png", "Wii");

	pc.Create("NormalMapping");
	pc.LoadNormalMap("./Textures/Models/GR_PC/GR_PC_Normal.png");
	pc.LoadHeightMap("./Textures/Models/GR_PC/GR_PC_Height.jpg");
	pc.LoadObj("./Models/GR_PC.obj");
	pc.Scale(glm::vec3(0.01f));
	pc.SetName("PC");
	pc.LoadTexture("./Textures/Models/GR_PC/GR_PC_Diffuse.png", "PC");

	pouffes.Create("NormalMapping");
	pouffes.LoadNormalMap("./Textures/Models/GR_Pouffe/GR_Pouffe_Normal.png");
	pouffes.LoadHeightMap("./Textures/Models/GR_Pouffe/GR_Pouffe_Height.jpg");
	pouffes.LoadObj("./Models/GR_Pouffes.obj");
	pouffes.Scale(glm::vec3(0.01f));
	pouffes.SetName("Pouffes");
	pouffes.LoadTexture("./Textures/Models/GR_Pouffe/GR_Pouffe_Diffuse.png", "Poufe");

	ps3.Create("NormalMapping");
	ps3.LoadNormalMap("./Textures/Models/GR_PS3/GR_PS3_Normal.png");
	ps3.LoadHeightMap("./Textures/Models/GR_PS3/GR_PS3_Height.jpg");
	ps3.LoadObj("./Models/GR_PS3.obj");
	ps3.Scale(glm::vec3(0.01f));
	ps3.SetName("PS3");
	ps3.LoadTexture("./Textures/Models/GR_PS3/GR_PS3_Diffuse.png", "PS3");

	ps4.Create("NormalMapping");
	ps4.LoadNormalMap("./Textures/Models/GR_PS4/GR_PS4_Normal.png");
	ps4.LoadHeightMap("./Textures/Models/GR_PS4/GR_PS4_Height.jpg");
	ps4.LoadObj("./Models/GR_PS4.obj");
	ps4.Scale(glm::vec3(0.01f));
	ps4.SetName("PS4");
	ps4.LoadTexture("./Textures/Models/GR_PS4/GR_PS4_Diffuse.png", "PS4");

	sofa.Create("NormalMapping");
	sofa.LoadNormalMap("./Textures/Models/GR_Sofa/GR_Sofa_Normal.png");
	sofa.LoadHeightMap("./Textures/Models/GR_Sofa/GR_Sofa_Height.jpg");
	sofa.LoadObj("./Models/GR_Sofa.obj");
	sofa.Scale(glm::vec3(0.01f));
	sofa.SetName("Sofa");
	sofa.LoadTexture("./Textures/Models/GR_Sofa/GR_Sofa_Diffuse.png", "Sofa");

	sonyAmp.Create("NormalMapping");
	sonyAmp.LoadNormalMap("./Textures/Models/GR_SonyAmp/GR_SonyAmp_Normal.png");
	sonyAmp.LoadHeightMap("./Textures/Models/GR_SonyAmp/GR_SonyAmp_Height.jpg");
	sonyAmp.LoadObj("./Models/GR_SonyAmp.obj");
	sonyAmp.Scale(glm::vec3(0.01f));
	sonyAmp.SetName("SonyAmp");
	sonyAmp.LoadTexture("./Textures/Models/GR_SonyAmp/GR_SonyAmp_Diffuse.png", "SonyAmp");

	speakerStand.Create("NormalMapping");
	speakerStand.LoadNormalMap("./Textures/Models/GR_SpeakerStand/GR_SpeakerStand_Normal.png");
	speakerStand.LoadHeightMap("./Textures/Models/GR_SpeakerStand/GR_SpeakerStand_Height.jpg");
	speakerStand.LoadObj("./Models/GR_SpeakerStands.obj");
	speakerStand.Scale(glm::vec3(0.01f));
	speakerStand.SetName("SpeakerStand");
	speakerStand.LoadTexture("./Textures/Models/GR_SpeakerStand/GR_SpeakerStand_Diffuse.png", "SpeakerStand");

	switches.Create("NormalMapping");
	switches.LoadNormalMap("./Textures/Models/GR_Switches/GR_Switches_Normal.png");
	switches.LoadHeightMap("./Textures/Models/GR_Switches/GR_Switches_Height.jpg");
	switches.LoadObj("./Models/GR_Switches.obj");
	switches.Scale(glm::vec3(0.01f));
	switches.SetName("Switches");
	switches.LoadTexture("./Textures/Models/GR_Switches/GR_Switches_Diffuse.png", "GR_Switches_Diffuse");

	table.Create("NormalMapping");
	table.LoadNormalMap("./Textures/Models/GR_Table/GR_Table_Normal.png");
	table.LoadHeightMap("./Textures/Models/GR_Table/GR_Table_Height.jpg");
	table.LoadObj("./Models/GR_Table.obj");
	table.Scale(glm::vec3(0.01f));
	table.SetName("Table");
	table.LoadTexture("./Textures/Models/GR_Table/GR_Table_Diffuse.png", "Table");

	tv.Create("NormalMapping");
	tv.LoadNormalMap("./Textures/Models/GR_TV/GR_TV_Normal.png");
	tv.LoadHeightMap("./Textures/Models/GR_TV/GR_TV_Height.jpg");
	tv.LoadObj("./Models/GR_TV.obj");
	tv.Scale(glm::vec3(0.01f));
	tv.SetName("TV");
	tv.LoadTexture("./Textures/Models/GR_TV/GR_TV_Diffuse.png", "GR_TV");

	//Keep walls using normalMapping shader
	walls.Create("NormalMapping");
	walls.LoadNormalMap("./Textures/Models/GR_Walls/GR_Walls_Normal.png");
	walls.LoadHeightMap("./Textures/Models/GR_Walls/GR_Walls_Height.jpg");
	walls.LoadObj("./Models/GR_Walls.obj");
	walls.Scale(glm::vec3(0.01f));
	walls.SetName("Walls");
	walls.LoadTexture("./Textures/Models/GR_Walls/GR_Walls_Diffuse.png", "Walls");

	yamahaSub.Create("NormalMapping");
	yamahaSub.LoadNormalMap("./Textures/Models/GR_YamahaSub/GR_YamahaSub_Normal.png");
	yamahaSub.LoadHeightMap("./Textures/Models/GR_YamahaSub/GR_YamahaSub_Height.jpg");
	yamahaSub.LoadObj("./Models/GR_YamahaSub.obj");
	yamahaSub.Scale(glm::vec3(0.01f));
	yamahaSub.SetName("YamahaSub");
	yamahaSub.LoadTexture("./Textures/Models/GR_YamahaSub/GR_YamahaSub_Diffuse.png", "YamahaSub");

	Game::Instance()->GetCurrentScene()->AddExistingObject(&airCon);
	Game::Instance()->GetCurrentScene()->AddExistingObject(&speakers);
	Game::Instance()->GetCurrentScene()->AddExistingObject(&door);
	Game::Instance()->GetCurrentScene()->AddExistingObject(&nintendoWii);
	Game::Instance()->GetCurrentScene()->AddExistingObject(&pc);
	Game::Instance()->GetCurrentScene()->AddExistingObject(&pouffes);
	Game::Instance()->GetCurrentScene()->AddExistingObject(&ps3);
	Game::Instance()->GetCurrentScene()->AddExistingObject(&ps4);
	Game::Instance()->GetCurrentScene()->AddExistingObject(&sofa);
	Game::Instance()->GetCurrentScene()->AddExistingObject(&sonyAmp);
	Game::Instance()->GetCurrentScene()->AddExistingObject(&speakerStand);
	Game::Instance()->GetCurrentScene()->AddExistingObject(&switches);
	Game::Instance()->GetCurrentScene()->AddExistingObject(&table);
	Game::Instance()->GetCurrentScene()->AddExistingObject(&tv);
	Game::Instance()->GetCurrentScene()->AddExistingObject(&walls);
	Game::Instance()->GetCurrentScene()->AddExistingObject(&yamahaSub);
	Game::Instance()->GetCurrentScene()->AddExistingObject(&ceiling);
}

//-------------------------------------------------------------------------------
//Draw
//-------------------------------------------------------------------------------
void Room::Draw()
{
}
