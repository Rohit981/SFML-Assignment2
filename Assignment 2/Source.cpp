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
#include <fstream>



//Namespace
using namespace std;
using namespace sf;

//Global Variables
Texture tileTexture[20];
const int Row = 10;
const int WORLD_SIZE = 10;
int coordinateWorld[WORLD_SIZE][WORLD_SIZE];
Sprite SpritePosition[WORLD_SIZE][WORLD_SIZE];
// loading info
Sprite tileSprite[200];
int TextureValue = 0;
int CurrentTextureValue = 0;
int CurrentSpriteValue = 0;
bool isLeftMouseClicked = false;
bool isLevelLoaded = false;
bool isLevelSaved = false;




//Starter Function
void Setup();
void handleInput(RenderWindow& window, Event e);
void Update(RenderWindow& window);
void Render(RenderWindow& window);
void ChangeTile(int ComparisonValue, int Value);
void OnLeftMouseClick(RenderWindow& window);
bool LoadLevel();
bool SaveLevel();



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
        tileSprite[CurrentSpriteValue].setPosition(Mouse::getPosition(window).x - (int)((Mouse::getPosition(window).x % 70)), Mouse::getPosition(window).y - (int)(Mouse::getPosition(window).y % 70));
        SpritePosition[Mouse::getPosition(window).x][Mouse::getPosition(window).y];


        isLeftMouseClicked = true;

        CurrentSpriteValue += 1;

        int spriteXIndex = Mouse::getPosition(window).x / 70;
        int spriteYIndex = Mouse::getPosition(window).y / 70;

        coordinateWorld[spriteXIndex][spriteYIndex] = CurrentSpriteValue;

        //cout << "Tile X Position:" << Mouse::getPosition(window).x - ((Mouse::getPosition(window).x % 70)) << endl;

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

    else if (Keyboard::isKeyPressed(Keyboard::L))
    {
        isLevelLoaded = LoadLevel();
            if (!isLevelLoaded) {
                cout << "ERROR: failed to load. Level.txt does not exist." << endl;
            }
    }else if (Keyboard::isKeyPressed(Keyboard::S)) 
    {
         isLevelSaved = SaveLevel();
        if (!isLevelSaved) {
            cout << "failed to save" << endl;
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

//Loading of Level
bool LoadLevel()
{
    const char* fileName = "level.txt";
    ifstream inFile(fileName);
    if (inFile.good()) 
    {
        int data[WORLD_SIZE * WORLD_SIZE] = { 0 };
        int number = 0;

        int index = 0;
        for (int i = 0; i < WORLD_SIZE * WORLD_SIZE; i++) 
        {
            inFile >> number;
            cout << number << ", ";
            data[index] = number;

            index++;
        }

        index = 0;
        for (int i = 0; i < WORLD_SIZE; i++) 
        {
            for (int j = 0; j < WORLD_SIZE; j++) 
            {
                int textureValue = data[index];

                cout << "loading data:" << textureValue << " | index:" << index << endl;
                coordinateWorld[i][j] = textureValue;

                if (textureValue != -1) 
                {
                    Sprite dataSprite = Sprite();
                    dataSprite.setTexture(tileTexture[textureValue]);
                    dataSprite.setPosition(i * 70.f, j * 70.f);

                    tileSprite[i] = dataSprite;
                }

                index++;
            }
        }
        cout << endl;
        inFile.close();
        isLevelLoaded = true;
    }

    return isLevelLoaded;
}

//Saving the level
bool SaveLevel()
{
    int levelData[WORLD_SIZE * WORLD_SIZE];
    int indexer = 0;
    for (int i = 0; i < WORLD_SIZE; i++) 
    {
        for (int j = 0; j < WORLD_SIZE; j++) 
        {
            levelData[indexer] = coordinateWorld[i][j];
            indexer++;
            cout << "writing char:" << indexer << endl;
        }
    }

    const int size = WORLD_SIZE * WORLD_SIZE;
    ofstream myfile("level.txt");
    if (myfile.is_open())
    {
        for (int count = 0; count < size; count++) 
        {
            myfile << levelData[count] << " ";
        }
        myfile.close();
        isLevelSaved = true;
    }
    else 
    {
        cout << "Unable to open file";
    }
    return isLevelSaved;
    return false;
}
