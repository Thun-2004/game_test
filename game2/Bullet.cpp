#include "Bullet.h"

Bullet::Bullet(sf::Texture* texture, float pos_x, float pos_y , float dirx, float diry, float movement_speed){
    this->shape.setTexture(*texture); 
    this->shape.setPosition(pos_x, pos_y);
    this->shape.scale(0.1f, 0.1f);
    this->direction.x = dirx;
    this->direction.y = diry;
    this->movementSpeed = movement_speed;
}

Bullet::~Bullet(){
   
}

const sf::FloatRect Bullet::getBounds() const{
    return this->shape.getGlobalBounds(); 
}

void Bullet::update(){
    this->shape.move(this->movementSpeed * this->direction); 
}

void Bullet::render(sf::RenderTarget* target){ //optionla param can be nullptr
    target->draw(this->shape); 
}