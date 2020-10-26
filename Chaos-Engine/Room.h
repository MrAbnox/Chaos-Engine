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

	Model airCon;
	Model speakers;
	Model door;
	Model nintendoWii;
	Model pc;
	Model pouffes;
	Model ps3;
	Model ps4;
	Model sofa;
	Model sonyAmp;
	Model speakerStand;
	Model switches;
	Model table;
	Model tv;
	Model walls;
	Model yamahaSub;
	Model ceiling;
};

#endif