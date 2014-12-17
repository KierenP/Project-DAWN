#pragma once
#include "Tile.h"

using namespace::std;

class TileSet

{
public:
	TileSet();
	~TileSet();
	void LoadFromFile();
	void GenerateSprites();
	void GenerateTiles();
	void UpdateTiles();

	vector<vector<Tile*>> Tiles;
	sf::Vector2f MapSize;            //In tiles not pixles
	sf::Vector2f TileSize;           //In pixles
	sf::Texture TextureMap;
};

