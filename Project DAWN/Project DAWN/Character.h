#pragma once
#include "SFML header.h"

class Character
{
public:
	Character();
	~Character();

	sf::Vector2f Position;
	int Direction;              //0 up, 1 down, 2 left, 3 right
};

