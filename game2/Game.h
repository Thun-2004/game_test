#pragma once
#include <map>
#include <string>
#include <sstream>
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"

class Game{
    private: 
        sf::RenderWindow* window; 

        //Resources
        std::map<std::string, sf::Texture*> textures; 
        std::vector<Bullet*> bullets; 

        //PLayer
        Player* player; 
        unsigned points; 
        sf::Font font; 
        sf::Text pointText; 
        void initWindow();
        void initTextures();
        void initPlayer(); 
        void initEnemies();
        void initWorld(); 
        void initSystem(); 
        

        //Enenmies
        float spawnTimer; 
        float spawnTimerMax;
        std::vector<Enemy*>enemies; 
        // Enemy* enemy; //save memory than storing the whole enemy class

        sf::Texture bgTexture; 
        sf::Sprite bg; 

    public: 
        Game(); 
        virtual ~Game();

        void updatePollEvents(); 
        void updateInput();
        void updateBullet(); 
        void updateEnemies();
        void updateCombat();
        void updateWorld(); 
        void updateCollision();
        void updateGUI(); 
        
        void run(); 
        void update(); 
        void renderWorld(); 
        void render(); 
      
};
