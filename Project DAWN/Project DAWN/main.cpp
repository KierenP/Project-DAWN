#include <SFML/Graphics.hpp>
#include "Character.h"
#include "TileSet.h"

TileSet MyTileset; 
Character MyCharacter;
sf::Texture CharacterText; 

sf::RenderWindow window(sf::VideoMode(1920, 1080), "DAWN");

sf::Clock GameGlock;
float Delta;

bool LeftPressed; //is the left button pressed? if so, this will be true. if not it will be false
bool RightPressed;
bool UpPressed;
bool DownPressed;

bool LGlide; //the character will glide till it locks to the tile. If this is true, the charecter is "gliding" till it snaps to the tile
bool RGlide; //right
bool UGlide;
bool DGlide;

float Xstop; //the co-ordinate that the character will stop at
float Ystop;

void PollEvent(); //check window events (close)
void Update();    //game logic
void Render();    //rendering to the window
void KeyCheck();  //

int main()
{
	//window.setFramerateLimit(60);

	MyTileset.MapSize = sf::Vector2f(64, 64); //hard coding
	MyTileset.TileSize = sf::Vector2f(32, 32);

	MyTileset.TextureMap.loadFromFile("Tileset.png");

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

        Delta = GameGlock.getElapsedTime().asSeconds(); //Delta is the time from the last frame
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
		if (LeftPressed == true) //if true, then we begin to "glide" till we snap to the tile grid (32x32)
		{
			LeftPressed = false; 
			LGlide = true;
			Xstop = int(MyCharacter.Position.x / 32) * 32; //the X co-ordinate that the character will stop at
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
            //pixles from edge - Character position + (1/2 window width) - (1/2 character width)         
		}
	}

	if (UpPressed || UGlide)
	{
		MyCharacter.Position.y -= 192 * Delta * MyTileset.Tiles[int((MyCharacter.Position.y + CharacterText.getSize().y / 2) / 32)][int((MyCharacter.Position.x + CharacterText.getSize().x / 2) / 32)]->SpeedVar; //192 pixles per second * Tile since last frame * tile speed
	}
	if (DownPressed || DGlide)
	{
		MyCharacter.Position.y += 192 * Delta * MyTileset.Tiles[int((MyCharacter.Position.y + CharacterText.getSize().y / 2) / 32)][int((MyCharacter.Position.x + CharacterText.getSize().x / 2) / 32)]->SpeedVar;
	}
	if (LeftPressed || LGlide)
	{
		MyCharacter.Position.x -= 192 * Delta * MyTileset.Tiles[int((MyCharacter.Position.y + CharacterText.getSize().y / 2) / 32)][int((MyCharacter.Position.x + CharacterText.getSize().x / 2) / 32)]->SpeedVar;
	}
	if (RightPressed || RGlide)
	{
		MyCharacter.Position.x += 192 * Delta * MyTileset.Tiles[int((MyCharacter.Position.y + CharacterText.getSize().y / 2) / 32)][int((MyCharacter.Position.x + CharacterText.getSize().x / 2) / 32)]->SpeedVar;
	}

	if (MyCharacter.Position.y < 0) //Has it gone of the tileset?
	{
		MyCharacter.Position.y = 0; //move it back
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

	if (MyCharacter.Position.x <= Xstop && LGlide) //has it reached the glide stop position?
	{
		LGlide = false;
		MyCharacter.Position.x = Xstop;            //then stop the character
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

void Render()
{
	window.clear();

	for (int i = 0; i < MyTileset.MapSize.y; i++)
	{
		for (int j = 0; j < MyTileset.MapSize.x; j++)
		{
			window.draw(MyTileset.Tiles.at(i).at(j)->Sprite); //draw all the tiles
		}
	}

	window.draw(MyCharacter.Sprite); //draw the sprite

	window.display();
}
