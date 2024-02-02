#include "Player.h"

//private


//public
Player::Player(){
    // this->movementSpeed = 10.f;
    this->initVariables();
    this->initTexture(); 
    this->initSprite();
}

Player::~Player(){

}

void Player::initVariables(){
    this->movementSpeed = 1.f; 
    this->attackCooldownMax = 10.f; 
    this->attackCooldown = this->attackCooldownMax; 
}

void Player::initTexture(){
    if(!this->texture.loadFromFile("./resources/spacecraft.png")){ //if not load texture
        std::cout<<"ERROR::PLAYER::INITTEXTURE::Could not load texture file."<<std::endl;
    }

}

void Player::initSprite(){
    this->sprite.setTexture(this->texture);
    //Resize
    this->sprite.scale(0.5f, 0.5f); //set image sizze
}

const sf::Vector2f& Player::getPos() const{
    return this->sprite.getPosition(); 
}

const sf::FloatRect Player::getBounds() const
{
    return this->sprite.getGlobalBounds();
}

const bool Player::canAttack(){
    if(this->attackCooldown >= this->attackCooldownMax){
        this->attackCooldown = 0.f; 
        return true; 
    }
    return false; 
}

void Player::setPos(const sf::Vector2f pos)
{
    this->sprite.setPosition(pos); 
}
void Player::setPosition(const float x, const float y)
{
    this->sprite.setPosition(x ,y); 
}

void Player::updateAttack()
{
    if(this->attackCooldown < this->attackCooldownMax){
        this->attackCooldown += 0.5f; 
    }
}

void Player::update(){
    this->updateAttack(); 
}

void Player::move(const float dirx, const float diry){
    this->sprite.move(this->movementSpeed * dirx, this->movementSpeed * diry);
}

void Player::render(sf::RenderTarget& target){
    target.draw(this->sprite); 
}

   