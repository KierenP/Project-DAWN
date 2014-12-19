#include <SFML/Graphics.hpp>
#include "Character.h"
#include "TileSet.h"

TileSet MyTileset;
Character MyCharacter;
sf::Texture CharacterText;

sf::RenderWindow window(sf::VideoMode(1920, 1080), "DAWN");

sf::Clock GameGlock;
float Delta;

bool LeftPressed;
bool RightPressed;
bool UpPressed;
bool DownPressed;

bool LGlide;
bool RGlide;
bool UGlide;
bool DGlide;

float Xstop;
float Ystop;

void PollEvent();
void Update();
void Render();
void KeyCheck();

int main()
{
	//window.setFramerateLimit(60);

	MyTileset.MapSize = sf::Vector2f(50, 50);
	MyTileset.TileSize = sf::Vector2f(32, 32);

	MyTileset.TextureMap.loadFromFile("Tileset2.png");

	MyTileset.GenerateTiles();
	MyTileset.LoadFromFile();
	MyTileset.UpdateTiles();
	MyTileset.GenerateSprites();

	MyCharacter.Position = sf::Vector2f(0, 0);

	CharacterText.loadFromFile("Character.png");

	MyCharacter.Sprite.setTexture(CharacterText);

	while (window.isOpen())
	{
		KeyCheck();
		PollEvent();
		Update();
		Render();

		Delta = GameGlock.getElapsedTime().asSeconds();
		GameGlock.restart();
	}
}

void KeyCheck()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		LeftPressed = true;
	}
	else
	{
		if (LeftPressed == true)
		{
			LeftPressed = false;
			LGlide = true;
			Xstop = int(MyCharacter.Position.x / 32) * 32;
		}
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		RightPressed = true;
	}
	else
	{
		if (RightPressed == true)
		{
			RightPressed = false;
			RGlide = true;
			Xstop = int(MyCharacter.Position.x / 32 + 1) * 32;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		UpPressed = true;
	}
	else
	{
		if (UpPressed == true)
		{
			UpPressed = false;
			UGlide = true;
			Ystop = int(MyCharacter.Position.y / 32) * 32;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		DownPressed = true;
	}
	else
	{
		if (DownPressed == true)
		{
			DownPressed = false;
			DGlide = true;
			Ystop = int(MyCharacter.Position.y / 32 + 1) * 32;
		}
	}

	if (MyCharacter.Position.x <= Xstop && LGlide)
	{
		LGlide = false;
		MyCharacter.Position.x = Xstop;
	}
	if (MyCharacter.Position.x >= Xstop && RGlide)
	{
		RGlide = false;
		MyCharacter.Position.x = Xstop;
	}
	if (MyCharacter.Position.y <= Ystop && UGlide)
	{
		UGlide = false;
		MyCharacter.Position.y = Ystop;
	}
	if (MyCharacter.Position.y >= Ystop && DGlide)
	{
		DGlide = false;
		MyCharacter.Position.y = Ystop;
	}
		
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
			MyTileset.Tiles.at(i).at(j)->Sprite.setPosition(sf::Vector2f(j * MyTileset.TileSize.x - int(MyCharacter.Position.x) + (window.getSize().x / 2) - (CharacterText.getSize().x / 2), i * MyTileset.TileSize.y - int(MyCharacter.Position.y) + (window.getSize().y / 2) - (CharacterText.getSize().y / 2)));
		}
	}

	if (UpPressed || UGlide)
	{
		MyCharacter.Position.y -= 192 * Delta;
	}
	if (DownPressed || DGlide)
	{
		MyCharacter.Position.y += 192 * Delta;
	}
	if (LeftPressed || LGlide)
	{
		MyCharacter.Position.x -= 192 * Delta;
	}
	if (RightPressed || RGlide)
	{
		MyCharacter.Position.x += 192 * Delta;
	}

	if (MyCharacter.Position.y < 0)
	{
		MyCharacter.Position.y = 0;
		UpPressed = false;
	}

	if (MyCharacter.Position.x < 0)
	{
		MyCharacter.Position.x = 0;
		LeftPressed = false;
	}

	if (MyCharacter.Position.y > ((MyTileset.MapSize.y - 1) * MyTileset.TileSize.y))
	{
		MyCharacter.Position.y = ((MyTileset.MapSize.y - 1) * MyTileset.TileSize.y);
		DownPressed = false;
	}

	if (MyCharacter.Position.x > ((MyTileset.MapSize.x - 1) * MyTileset.TileSize.x))
	{
		MyCharacter.Position.x = ((MyTileset.MapSize.x - 1) * MyTileset.TileSize.x);
		RightPressed = false;
	}


	MyCharacter.Sprite.setPosition(sf::Vector2f(window.getSize().x / 2 - (CharacterText.getSize().x / 2), window.getSize().y / 2 - (CharacterText.getSize().y / 2)));
	//MyCharacter.Sprite.setPosition(sf::Vector2f(0, 0));
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

	window.draw(MyCharacter.Sprite);

	window.display();
}
