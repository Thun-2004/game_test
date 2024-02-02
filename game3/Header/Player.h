#pragma once

enum PLAYER_ANIMATION_STATES{IDLE = 0, MOVING_LEFT, MOVING_RIGHT, JUMPING, FALLING};

class Player{
    private: 
        sf::Sprite sprite; 
        sf::Texture textureSheet;
        bool moving; 
        //Animation 
        short animState; 
        sf::IntRect currentFrame; 
        sf::Clock animationTimer; 

        //Physic Movement 
        sf::Vector2f velocity; 
        float acceleration; 
        float deceleration;

        //Core
        void initVariables(); 
        void initSprite(); 
        void initTexture();
        void initAnimation();

    public: 
        Player();
        virtual ~Player();

        //fn
        void updatePhysics(); 
        void updateMovement(); 
        void updateAnimation(); 
        void update(); 
        void render(sf::RenderTarget& target);
};