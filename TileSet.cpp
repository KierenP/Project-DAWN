#include "TileSet.h"
#include "Dirt.h"


TileSet::TileSet()
{
}


TileSet::~TileSet()
{
	for (int i = 0; i < MapSize.y; i++)
	{
		for (int j = 0; j < MapSize.x; j++)
		{
			delete Tiles.at(i).at(j);
		}
	}
}


void TileSet::LoadFromFile()
{
	for (int i = 0; i < MapSize.y; i++)
	{
		for (int j = 0; j < MapSize.x; j++)
		{
			Tiles.at(i).at(j)->TileID = 0;
		}
	}
}

void TileSet::GenerateSprites()
{
	for (int i = 0; i < MapSize.y; i++)
	{
		for (int j = 0; j < MapSize.x; j++)
		{
			Tiles.at(i).at(j)->Sprite.setTexture(TextureMap);
			Tiles.at(i).at(j)->Sprite.setTextureRect(sf::IntRect(TileSize.x * j, TileSize.y * i, TileSize.x, TileSize.y));
		}
	}
}

void TileSet::UpdateTiles()
{
	for (int i = 0; i < MapSize.y; i++)
	{
		for (int j = 0; j < MapSize.x; j++)
		{
			switch (Tiles.at(i).at(j)->TileID)
			{
			case 0:
				Tiles.at(i).at(j) = new Dirt();
			default:
				break;
			}
			
		}
	}
}

void TileSet::GenerateTiles()
{
	Tiles.resize = MapSize.y;

	for (int i = 0; i < MapSize.y; i++)
	{
		Tiles.at(i).resize = MapSize.x;
	}

	for (int i = 0; i < MapSize.y; i++)
	{
		for (int j = 0; j < MapSize.x; j++)
		{
			Tiles.at(i).at(j) = new Tile();
		}
	}
}

