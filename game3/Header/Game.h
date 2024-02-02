#pragma once
#include "stdafx.h"
#include "Player.h"

class Game{
    private: 
        sf::RenderWindow window; 
        sf::Event ev; 
        Player* player; 

        //fn
        void initWindow(); 
        void initPlayer(); 
    public: 
        Game();
        virtual ~Game();

        //fn
        void updatePlayer();
        void update(); 
        void render(); 
        void renderPlayer(); 
        const sf::RenderWindow& getWindow() const; 
};