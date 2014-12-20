#include "TileSet.h"
#include "Grass.h"
#include "Coast.h"
#include "Ocean.h"
#include "RedFlower.h"
#include "Sand.h"
#include "Stone.h"
#include "Tree.h"
#include "YellowFlower.h"
#include "Snow.h"
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "PerlinNoise.h"


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
	/*srand(time(NULL));

	int Map[10][10] = 
	
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
	};

	for (int i = 0; i < MapSize.y; i++)
	{
		for (int j = 0; j < MapSize.x; j++)
		{
			Tiles.at(i).at(j)->TileID = rand() % 18; //choose from the 18 tiles in our current tileset at random
		}
	}*/

    /*vector<vector<float>> Map1;
    vector<vector<float>> Map2;

    Map1.resize(MapSize.y);
    Map2.resize(MapSize.y);

    for (int i = 0; i < MapSize.y; i++)
    {
        Map1[i].resize(MapSize.x);
        Map2[i].resize(MapSize.x);
    }

    // creating random noise

    for (int i = 0; i < MapSize.y; i++)
    {
        for (int j = 0; j < MapSize.x; j++)
        {
            Map1[i][j] = float(rand() % 6);
            Map2[i][j] = Map1[i][j];
        }
    }

    //sofening the map

	int Sofeningfactor = 4;
	int Sofeningrate = 1;

	for (int x = 0; x < 2; x++)
	{
		for (int i = 0; i < MapSize.y; i += Sofeningfactor)
		{
			for (int j = 0; j < MapSize.x; j += Sofeningfactor)
			{
				float Averageheight = 0;

				for (int k = 0; k < Sofeningfactor * Sofeningfactor; k++)
				{
					Averageheight += Map2[i + (k % Sofeningfactor)][j + (k / Sofeningfactor)];
				}

				Averageheight = Averageheight / (Sofeningfactor * Sofeningfactor);

				for (int k = 0; k < Sofeningfactor * Sofeningfactor; k++)
				{
					Sofeningrate = rand() % 4 + 1;
					Map2[i + (k % Sofeningfactor)][j + (k / Sofeningfactor)] = ((Map2[i + (k % Sofeningfactor)][j + (k / Sofeningfactor)] * Sofeningrate) + Averageheight) / (1 + Sofeningrate);
				}
			}
		}

		Sofeningfactor = Sofeningfactor * 2;
	}

	for (int i = 0; i < MapSize.y; i++)
	{
		for (int j = 0; j < MapSize.x; j++)
		{
				Tiles[i][j]->TileID = Map2[i][j];
		}
	}*/

	/*vector<vector<float>> Noise;
	vector<vector<float>> Total;

	Total.resize(MapSize.x);

	for (int i = 0; i < MapSize.x; i++)
	{
		Total[i].resize(MapSize.x);
	}
	

	for (int x = 0; x < 5; x++)
	{
		int frequency = pow(2, x);
		int amplitude = pow(1 / 2, x);

		Noise.resize(frequency);

		for (int i = 0; i < MapSize.y; i++)
		{
			Noise
		}
	}*/

    Perlin Noise(4, 4, 4, rand() % 100);

	for (int i = 0; i < MapSize.y; i++)
	{
		for (int j = 0; j < MapSize.x; j++)
		{
			Tiles[i][j]->TileID = (Noise.Get(float(i) / 64, float(j) / 64) + 3);

			if (Tiles[i][j]->TileID == 2)
			{
				int random = rand() % 16;

				if (random == 0)
					Tiles[i][j]->TileID = 7;
				if (random == 1)
					Tiles[i][j]->TileID = 8;
				if (random > 12)
					Tiles[i][j]->TileID = 6;
			}
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
			Tiles.at(i).at(j)->Sprite.setTextureRect(sf::IntRect(TileSize.x * (Tiles.at(i).at(j)->TileID % 3), TileSize.y * (Tiles.at(i).at(j)->TileID / 3), TileSize.x, TileSize.y));
		}
	}
}

void TileSet::UpdateTiles() //Create tiles based on the TileID of the particular tile
{
	for (int i = 0; i < MapSize.y; i++)
	{
		for (int j = 0; j < MapSize.x; j++)
		{
			switch (Tiles.at(i).at(j)->TileID)
			{
			case 0:
				Tiles.at(i).at(j) = new Snow(); 
				break;
			case 1:
				Tiles.at(i).at(j) = new Stone();
				break;
			case 2:
				Tiles.at(i).at(j) = new Grass();
				break;
			case 3:
				Tiles.at(i).at(j) = new Sand();
				break;
			case 4:
				Tiles.at(i).at(j) = new Coast();
				break;
			case 5:
				Tiles.at(i).at(j) = new Ocean();
				break;
			case 6:
				Tiles.at(i).at(j) = new Tree();
				break;
			case 7:
				Tiles.at(i).at(j) = new RedFlower();
				break;
			case 8:
				Tiles.at(i).at(j) = new YellowFlower();
				break;
			default:
				break;
			}
			
		}
	}
}

void TileSet::GenerateTiles() //Populate the vector
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

