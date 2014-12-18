#include "TileSet.h"
#include "Dirt.h"
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */


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
	srand(time(NULL));

	/*int Map[10][10] = 
	
	{
		{ 0, 0, 0, 0, 1, 1, 0, 0, 0, 0 },
		{ 0, 0, 7, 7, 8, 1, 0, 0, 7, 7 },
		{ 3, 3, 3, 3, 1, 1, 3, 3, 3, 3 },
		{ 1, 8, 8, 1, 1, 8, 1, 8, 1, 1 }, 
		{ 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 },
		{ 2, 2, 2, 2, 2, 2, 9, 2, 9, 2},
		{ 9, 2, 9, 2, 2, 9, 2, 2, 2, 9},
		{ 9, 2, 2, 9, 2, 16, 16, 9, 9, 16},
		{ 9, 16, 9, 16, 16, 16, 9, 16, 9, 16 },
		{ 16, 16, 16, 9, 16, 9, 16, 16, 9, 9 }
	};*/

	for (int i = 0; i < MapSize.y; i++)
	{
		for (int j = 0; j < MapSize.x; j++)
		{
			Tiles.at(i).at(j)->TileID = rand() % 18;
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
			Tiles.at(i).at(j)->Sprite.setTextureRect(sf::IntRect(TileSize.x * (Tiles.at(i).at(j)->TileID % 6), TileSize.y * (Tiles.at(i).at(j)->TileID / 6), TileSize.x, TileSize.y));
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
	Tiles.resize(MapSize.y);

	for (int i = 0; i < MapSize.y; i++)
	{
		Tiles.at(i).resize(MapSize.x);
	}

	for (int i = 0; i < MapSize.y; i++)
	{
		for (int j = 0; j < MapSize.x; j++)
		{
			Tiles.at(i).at(j) = new Tile();
		}
	}
}

