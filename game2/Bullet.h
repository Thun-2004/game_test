#pragma once
#include <iostream>
#include<SFML/System.hpp>
#include<SFML/Graphics.hpp>

class Bullet{
    private: 
        sf::Sprite shape;
        sf::Texture* texture;  

        sf::Vector2f direction; 
        float movementSpeed; 
    public: 
        Bullet(sf::Texture* texture, float pos_x, float pos_y, float dirx, float diry, float movement_speed);
        virtual ~Bullet();

        //Accessor
        const sf::FloatRect getBounds() const; 

        void update(); 
        void render(sf::RenderTarget* target);
};