#include "Room.h"

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
	m_airCon.Create("NormalMapping");
	m_airCon.LoadNormalMap("./Textures/Models/GR_AirCon/GR_AirCon_Normal.png");
	m_airCon.LoadHeightMap("./Textures/Models/GR_AirCon/GR_AirCon_Height.jpg");
	m_airCon.LoadObj("./Models/GR_AirCon.obj");
	m_airCon.Scale(glm::vec3(0.01f));
	m_airCon.LoadTexture("./Textures/Models/GR_AirCon/GR_AirCon_Diffuse.png", "AirCon");


	m_speakers.Create("NormalMapping");
	m_speakers.LoadNormalMap("./Textures/Models/GR_BlueSky_Speaker/GR_BluseSky_Speaker_Normal.png");
	m_speakers.LoadHeightMap("./Textures/Models/GR_BlueSky_Speaker/GR_BluseSky_Speaker_Height.jpg");
	m_speakers.LoadObj("./Models/GR_BlueSky_Speakers.obj");
	m_speakers.Scale(glm::vec3(0.01f));
	m_speakers.LoadTexture("./Textures/Models/GR_BlueSky_Speaker/GR_BluseSky_Speaker_Diffuse.png", "Speakers");


	m_ceiling.Create("ShadowMapping");
	m_ceiling.LoadObj("./Models/GR_Ceiling.obj");
	m_ceiling.Scale(glm::vec3(0.01f));
	m_ceiling.LoadTexture("./Textures/Models/GR_Walls/GR_Walls_Diffuse.png", "Walls");


	m_door.Create("NormalMapping");
	m_door.LoadNormalMap("./Textures/Models/GR_Door/GR_Door_Normal.png");
	m_door.LoadHeightMap("./Textures/Models/GR_Door/GR_Door_Height.jpg");
	m_door.LoadObj("./Models/GR_Door.obj");
	m_door.Scale(glm::vec3(0.01f));
	m_door.LoadTexture("./Textures/Models/GR_Door/GR_Door_Diffuse.png", "Door");

	m_nintendoWii.Create("NormalMapping");
	m_nintendoWii.LoadNormalMap("./Textures/Models/GR_NintendoWii/GR_NintendoWii_Normal.png");
	m_nintendoWii.LoadHeightMap("./Textures/Models/GR_NintendoWii/GR_NintendoWii_Height.jpg");
	m_nintendoWii.LoadObj("./Models/GR_NintendoWii.obj");
	m_nintendoWii.Scale(glm::vec3(0.01f));
	m_nintendoWii.LoadTexture("./Textures/Models/GR_NintendoWii/GR_NintendoWii_Diffuse.png", "Wii");

	m_pc.Create("NormalMapping");
	m_pc.LoadNormalMap("./Textures/Models/GR_PC/GR_PC_Normal.png");
	m_pc.LoadHeightMap("./Textures/Models/GR_PC/GR_PC_Height.jpg");
	m_pc.LoadObj("./Models/GR_PC.obj");
	m_pc.Scale(glm::vec3(0.01f));
	m_pc.LoadTexture("./Textures/Models/GR_PC/GR_PC_Diffuse.png", "PC");

	m_pouffes.Create("NormalMapping");
	m_pouffes.LoadNormalMap("./Textures/Models/GR_Pouffe/GR_Pouffe_Normal.png");
	m_pouffes.LoadHeightMap("./Textures/Models/GR_Pouffe/GR_Pouffe_Height.jpg");
	m_pouffes.LoadObj("./Models/GR_Pouffes.obj");
	m_pouffes.Scale(glm::vec3(0.01f));
	m_pouffes.LoadTexture("./Textures/Models/GR_Pouffe/GR_Pouffe_Diffuse.png", "Poufe");

	m_ps3.Create("NormalMapping");
	m_ps3.LoadNormalMap("./Textures/Models/GR_PS3/GR_PS3_Normal.png");
	m_ps3.LoadHeightMap("./Textures/Models/GR_PS3/GR_PS3_Height.jpg");
	m_ps3.LoadObj("./Models/GR_PS3.obj");
	m_ps3.Scale(glm::vec3(0.01f));
	m_ps3.LoadTexture("./Textures/Models/GR_PS3/GR_PS3_Diffuse.png", "PS3");

	m_ps4.Create("NormalMapping");
	m_ps4.LoadNormalMap("./Textures/Models/GR_PS4/GR_PS4_Normal.png");
	m_ps4.LoadHeightMap("./Textures/Models/GR_PS4/GR_PS4_Height.jpg");
	m_ps4.LoadObj("./Models/GR_PS4.obj");
	m_ps4.Scale(glm::vec3(0.01f));
	m_ps4.LoadTexture("./Textures/Models/GR_PS4/GR_PS4_Diffuse.png", "PS4");

	m_sofa.Create("NormalMapping");
	m_sofa.LoadNormalMap("./Textures/Models/GR_Sofa/GR_Sofa_Normal.png");
	m_sofa.LoadHeightMap("./Textures/Models/GR_Sofa/GR_Sofa_Height.jpg");
	m_sofa.LoadObj("./Models/GR_Sofa.obj");
	m_sofa.Scale(glm::vec3(0.01f));
	m_sofa.LoadTexture("./Textures/Models/GR_Sofa/GR_Sofa_Diffuse.png", "Sofa");

	sonyAmp.Create("NormalMapping");
	sonyAmp.LoadNormalMap("./Textures/Models/GR_SonyAmp/GR_SonyAmp_Normal.png");
	sonyAmp.LoadHeightMap("./Textures/Models/GR_SonyAmp/GR_SonyAmp_Height.jpg");
	sonyAmp.LoadObj("./Models/GR_SonyAmp.obj");
	sonyAmp.Scale(glm::vec3(0.01f));
	sonyAmp.LoadTexture("./Textures/Models/GR_SonyAmp/GR_SonyAmp_Diffuse.png", "SonyAmp");

	m_speakerStand.Create("NormalMapping");
	m_speakerStand.LoadNormalMap("./Textures/Models/GR_SpeakerStand/GR_SpeakerStand_Normal.png");
	m_speakerStand.LoadHeightMap("./Textures/Models/GR_SpeakerStand/GR_SpeakerStand_Height.jpg");
	m_speakerStand.LoadObj("./Models/GR_SpeakerStands.obj");
	m_speakerStand.Scale(glm::vec3(0.01f));
	m_speakerStand.LoadTexture("./Textures/Models/GR_SpeakerStand/GR_SpeakerStand_Diffuse.png", "SpeakerStand");

	m_switches.Create("NormalMapping");
	m_switches.LoadNormalMap("./Textures/Models/GR_Switches/GR_Switches_Normal.png");
	m_switches.LoadHeightMap("./Textures/Models/GR_Switches/GR_Switches_Height.jpg");
	m_switches.LoadObj("./Models/GR_Switches.obj");
	m_switches.Scale(glm::vec3(0.01f));
	m_switches.LoadTexture("./Textures/Models/GR_Switches/GR_Switches_Diffuse.png", "GR_Switches_Diffuse");

	m_table.Create("NormalMapping");
	m_table.LoadNormalMap("./Textures/Models/GR_Table/GR_Table_Normal.png");
	m_table.LoadHeightMap("./Textures/Models/GR_Table/GR_Table_Height.jpg");
	m_table.LoadObj("./Models/GR_Table.obj");
	m_table.Scale(glm::vec3(0.01f));
	m_table.LoadTexture("./Textures/Models/GR_Table/GR_Table_Diffuse.png", "Table");

	m_tv.Create("NormalMapping");
	m_tv.LoadNormalMap("./Textures/Models/GR_TV/GR_TV_Normal.png");
	m_tv.LoadHeightMap("./Textures/Models/GR_TV/GR_TV_Height.jpg");
	m_tv.LoadObj("./Models/GR_TV.obj");
	m_tv.Scale(glm::vec3(0.01f));
	m_tv.LoadTexture("./Textures/Models/GR_TV/GR_TV_Diffuse.png", "GR_TV");

	m_walls.Create("NormalMapping");
	m_walls.LoadNormalMap("./Textures/Models/GR_Walls/GR_Walls_Normal.png");
	m_walls.LoadHeightMap("./Textures/Models/GR_Walls/GR_Walls_Height.jpg");
	m_walls.LoadObj("./Models/GR_Walls.obj");
	m_walls.Scale(glm::vec3(0.01f));
	m_walls.LoadTexture("./Textures/Models/GR_Walls/GR_Walls_Diffuse.png", "Walls");

	m_yamahaSub.Create("NormalMapping");
	m_yamahaSub.LoadNormalMap("./Textures/Models/GR_YamahaSub/GR_YamahaSub_Normal.png");
	m_yamahaSub.LoadHeightMap("./Textures/Models/GR_YamahaSub/GR_YamahaSub_Height.jpg");
	m_yamahaSub.LoadObj("./Models/GR_YamahaSub.obj");
	m_yamahaSub.Scale(glm::vec3(0.01f));
	m_yamahaSub.LoadTexture("./Textures/Models/GR_YamahaSub/GR_YamahaSub_Diffuse.png", "YamahaSub");

}

//-------------------------------------------------------------------------------
//Draw
//-------------------------------------------------------------------------------
void Room::Draw()
{
	m_airCon.Draw();
	m_speakers.Draw();
	m_ceiling.Draw();
	m_door.Draw();
	m_nintendoWii.Draw();
	m_pc.Draw();
	m_pouffes.Draw();
	m_ps3.Draw();
	m_ps4.Draw();
	m_sofa.Draw();
	sonyAmp.Draw();
	m_speakerStand.Draw();
	m_switches.Draw();
	m_table.Draw();
	m_tv.Draw();
	m_walls.Draw();
	m_yamahaSub.Draw();
}
