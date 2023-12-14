#ifndef GAME_HPP
#define GAME_HPP
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <ctime>
#include <iostream>
#include <sstream>
#include <vector>

//cmd + . to define new definitio in new file 
class Game{
    private: 
        //variables
        sf::RenderWindow* window; 
        sf::VideoMode videoMode; 
        sf::Event ev;
        
        //Mouse position
        sf::Font font;

        //Text
        sf::Text uiText; 

        //game logic
        bool endGame;
        unsigned points = 0; 
        float enemySpawnTimer; 
        float enemySpawnTimerMax;
        int maxEnemies;
        int health; 
        bool mouseHeld; 

        //game obj
        std::vector<sf::RectangleShape> enemies; 
        sf::RectangleShape enemy; 
        sf::Vector2i mousePosWindow; //only relative to window
        sf::Vector2f mousePosView;

        //function
        void initVariables();
        void initWindow();
        void initFonts(); 
        void initText(); 
        void initEnemies(); 
    
    public: 
        Game(); 
        virtual ~Game(); //destructor : cleanup code when an object goes out of scope or is explicitly deleted , prevnet memory leak
        const bool running() const; 
        const bool getEndGame() const;
        void update(); 
        void updateText();
        void updateMousePositons(); 
        void spawnEnemy(); 
        void updateEnemies();
        void renderEnemies(sf::RenderTarget& target);
        void pollEvents();
        void render();
        void renderText(sf::RenderTarget& target);  
};

#endif //GAME_HPP