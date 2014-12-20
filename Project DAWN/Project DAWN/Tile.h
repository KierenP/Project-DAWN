#pragma once
#include "SFML header.h"

class Tile
{
public:
	Tile();
	~Tile();

	int TileID;
	sf::Sprite Sprite;
	bool IsVisible;
	bool IsSolid;
	float SpeedVar;
};

