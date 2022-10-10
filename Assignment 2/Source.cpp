#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include <iostream>
#include <array>
#include <string>


//Namespace
using namespace std;
using namespace sf;

//Global Variables
Texture tileTexture[20];
const int Row = 10;
const int column = 10;
int SpritePosition[Row][column];
Sprite tileSprite[200];
int TextureValue = 0;
int CurrentTextureValue = 0;
int CurrentSpriteValue = 0;
bool isLeftMouseClicked = false;


//Starter Function
void Setup();
void handleInput(RenderWindow& window, Event e);
void Update(RenderWindow& window);
void Render(RenderWindow& window);
void ChangeTile(int ComparisonValue, int Value);
void OnLeftMouseClick(RenderWindow& window);





int main()
{
    RenderWindow window(VideoMode(700, 700), "SFML works!");

    Setup();

    
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            handleInput(window, event);
   
        }

        Update(window);
        Render(window);

        
    }
    return 0;
}

void Setup()
{

//Initialzing the Sprites
#pragma region Load Sprite
    for (int ImageNo = 0; ImageNo < 21; ImageNo++)
    {
        string Image = "Assets/Tileset/Platformer-" + to_string(ImageNo) + ".png";
        if (!tileTexture[ImageNo].loadFromFile(Image))
        {
            cout << "Error loading the sprite" << endl;
        }
        else
        {
            cout << "Loaded TileSet/Platformer-" << to_string(ImageNo) << endl;

        }


    }

    tileSprite[CurrentSpriteValue].setTexture(tileTexture[TextureValue]);
    

    cout << "Current Tile Select TileSet/Platformer-" << CurrentTextureValue << endl;

#pragma endregion

    
   
}

//Function to handle all the player Inputs
void handleInput(RenderWindow& window, Event e)
{
    if (e.type == Event::Closed)
        window.close();
    if (Keyboard::isKeyPressed(Keyboard::Up))
    {
        CurrentTextureValue = TextureValue + 1;

        ChangeTile(21, 0);
        
    }
    else if (Keyboard::isKeyPressed(Keyboard::Down))
    {
        CurrentTextureValue = TextureValue - 1;

        ChangeTile(-1, 20);

    }
    else if (Mouse::isButtonPressed(Mouse::Left))
    {
        tileSprite[CurrentSpriteValue].setPosition(Mouse::getPosition(window).x, Mouse::getPosition(window).y);
        SpritePosition[Mouse::getPosition(window).x][Mouse::getPosition(window).y];

        isLeftMouseClicked = true;

        CurrentSpriteValue += 1;

    }
    else if (e.key.code == sf::Keyboard::Space) 
    {
        sf::Texture texture;
        texture.create(window.getSize().x, window.getSize().y);
        texture.update(window);
        if (texture.copyToImage().saveToFile("Homework 2 Screenshot.png"))
        {
            std::cout << "Screenshot saved to Homework 2 Screenshot.png" << std::endl;
        }
    }
}

//Function that updates every frame
void Update(RenderWindow& window)
{
    
    OnLeftMouseClick(window);

}

//Draw all the sprites on the screen
void Render(RenderWindow& window)
{
    window.clear();
    
    for (int i = 0; i < 200; i++)
    {
        
         window.draw(tileSprite[i]);
    
        

    }

 
    window.display();
}

//Function to cycle between the sprites
void ChangeTile(int ComparisonValue, int Value)
{
    
    if (CurrentTextureValue == ComparisonValue)
    {
        CurrentTextureValue = Value;
    }
    tileSprite[CurrentSpriteValue].setTexture(tileTexture[CurrentTextureValue]);
    

    TextureValue = CurrentTextureValue;

    cout << "Current Tile Select TileSet/Platformer-" << CurrentTextureValue << endl;



}

//Function that positions the srite on mouse click position
void OnLeftMouseClick(RenderWindow& window)
{
    if (isLeftMouseClicked == false)
    {
        tileSprite[CurrentSpriteValue].setPosition(Mouse::getPosition(window).x, Mouse::getPosition(window).y);




    }
    else
    {
        tileSprite[CurrentSpriteValue].setTexture(tileTexture[TextureValue]);
        tileSprite[CurrentSpriteValue].setPosition(Mouse::getPosition(window).x, Mouse::getPosition(window).y);

    }

}
