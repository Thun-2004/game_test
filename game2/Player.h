#pragma once
#include <iostream>
#include<SFML/System.hpp>
#include<SFML/Graphics.hpp>

class Player{
    private: 
        sf::Sprite sprite;
        sf::Texture texture; 
        float movementSpeed;
        float attackCooldown; 
        float attackCooldownMax; 

        //fn 
        void initVariables(); //set variables
        void initTexture(); //load texture
        void initSprite(); //set sprite

    public: 
        Player(); 
        virtual ~Player();
        void move(const float dirx, const float diry); 

        //Accesstor
        const sf::Vector2f& getPos() const; 
        const sf::FloatRect getBounds() const; 

        //Modifier
        void setPos(const sf::Vector2f pos);
        void setPosition(const float x, const float y); 

        //Function
        void updateAttack();
        const bool canAttack();
        void update(); 
        void render(sf::RenderTarget& target); 
};