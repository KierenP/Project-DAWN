#include <SFML/Graphics.hpp>
#include "Character.h"
#include "TileSet.h"

TileSet MyTileset;
Character MyCharacter;

int main()
{
	MyTileset.MapSize = sf::Vector2f(100, 100);
	MyTileset.TileSize = sf::Vector2f(32, 32);

	MyTileset.TextureMap.loadFromFile("Tileset.png");

	MyTileset.GenerateTiles();
	MyTileset.LoadFromFile();
	MyTileset.UpdateTiles();
	MyTileset.GenerateSprites();
}