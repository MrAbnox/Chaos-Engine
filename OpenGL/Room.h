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
	void Update() override;
	void Draw() override;
	void Destroy() override;

private:

	Model m_pouffe;
	Model m_pouffe2;
	Model m_pouffe3;
	Model m_pouffe4;
	Model m_pouffe5;

private:

	Model m_walls;
	Model m_tv;
	Model m_table;
	Model m_PS3;
	Model m_PS4;
	Model m_Wii;
	Model m_computer;
	Model m_amp;
	Model m_couch;

};
#endif
