#ifndef ROOM_H
#define ROOM_H
#include "GameObject.h"
#include "Model.h"
class Room : public GameObject
{
public:
	Room();
	~Room();

public:

	void Create() override;
	void Draw() override;

private:

	Model m_airCon;
	Model m_speakers;
	Model m_door;
	Model m_nintendoWii;
	Model m_pc;
	Model m_pouffes;
	Model m_ps3;
	Model m_ps4;
	Model m_sofa;
	Model m_sonyAmp;
	Model m_speakerStand;
	Model m_switches;
	Model m_table;
	Model m_tv;
	Model m_walls;
	Model m_yamahaSub;
	Model m_ceiling;
};

#endif