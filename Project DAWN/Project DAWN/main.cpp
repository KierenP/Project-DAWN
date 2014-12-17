#include <SFML/Graphics.hpp>
#include "Character.h"
#include "TileSet.h"

TileSet MyTileset;
Character MyCharacter;

sf::RenderWindow window(sf::VideoMode(1920, 1080), "DAWN");

bool LeftPressed;
bool RightPressed;
bool UpPressed;
bool DownPressed;

void PollEvent();
void Update();
void Render();
void KeyCheck();

int main()
{
	MyTileset.MapSize = sf::Vector2f(10, 10);
	MyTileset.TileSize = sf::Vector2f(32, 32);

	MyTileset.TextureMap.loadFromFile("Tileset.png");

	MyTileset.GenerateTiles();
	MyTileset.LoadFromFile();
	MyTileset.UpdateTiles();
	MyTileset.GenerateSprites();

	MyCharacter.Position = sf::Vector2f(0, 0);

	while (window.isOpen())
	{
		KeyCheck();
		PollEvent();
		Update();
		Render();
	}
}

void KeyCheck()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		LeftPressed = true;
	}
	else
		LeftPressed = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		RightPressed = true;
	}
	else
		RightPressed = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		UpPressed = true;
	}
	else
		UpPressed = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		DownPressed = true;
	}
	else
		DownPressed = false;

}

void PollEvent()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
	}
}

void Update()
{
	for (int i = 0; i < MyTileset.MapSize.y; i++)
	{
		for (int j = 0; j < MyTileset.MapSize.x; j++)
		{
			MyTileset.Tiles.at(i).at(j)->Sprite.setPosition(sf::Vector2f(j * MyTileset.TileSize.x - MyCharacter.Position.x + (window.getSize().x / 2), i * MyTileset.TileSize.y - MyCharacter.Position.y + (window.getSize().y / 2)));
		}
	}

	if (UpPressed)
	{
		MyCharacter.Position.y -= 0.5;
	}
	if (DownPressed)
	{
		MyCharacter.Position.y += 0.5;
	}
	if (LeftPressed)
	{
		MyCharacter.Position.x -= 0.5;
	}
	if (RightPressed)
	{
		MyCharacter.Position.x += 0.5;
	}
}

void Render()
{
	window.clear();

	for (int i = 0; i < MyTileset.MapSize.y; i++)
	{
		for (int j = 0; j < MyTileset.MapSize.x; j++)
		{
			window.draw(MyTileset.Tiles.at(i).at(j)->Sprite);
		}
	}

	window.display();
}
