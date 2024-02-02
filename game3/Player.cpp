#include "./Header/stdafx.h"
#include "./Header/Player.h"
#include "Player.h"

Player::Player()
{
    this->initVariables();
    this->initTexture();
    this->initSprite();
    this->initAnimation();
}

Player::~Player()
{
}

// private
void Player::initVariables()
{
    this->animaState = PLAYER_ANIMATION_STATES::IDLE;
    this->moving = false;
}

void Player::initSprite()
{
    this->sprite.setTexture(this->textureSheet);
    this->currentFrame = sf::IntRect(0, 0, 132, 139);
    this->sprite.setTextureRect(this->currentFrame); // display only partial of picture
    this->sprite.setScale(1.5f, 1.5f);
}

void Player::initTexture()
{
    if (!this->textureSheet.loadFromFile("./Textures/player.png"))
    {
        std::cout << "ERROR::PLAYER::INITTEXTURE::Could not load player file."
                  << "\n";
    }
}

void Player::initAnimation()
{
    this->animationTimer.restart();
}
// public
void Player::updateMovement()
{

    this->animState = PLAYER_ANIMATION_STATES::IDLE;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    { // left
        this->sprite.move(-1.f, 0.f);
        this->animState = PLAYER_ANIMATION_STATES::MOVING_LEFT;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    { // right
        this->sprite.move(1.f, 0.f);
        this->animState = PLAYER_ANIMATION_STATES::MOVING_RIGHT;
    }

    // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
    // { // top
    //     this->sprite.move(0.f, -1.f);
    //     this->moving = true;
    // }
    // else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
    // { // down
    //     this->sprite.move(0.f, 1.f);
    //     this->moving = true;
    // }
}

void Player::updateAnimation()
{
    if (this->animState == PLAYER_ANIMATION_STATES::IDLE)
    {
        if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f)
        {   
            this->currentFrame.top = 0.f; 
            this->currentFrame.left += 20.f;
            if (this->currentFrame.left >= 264.f)
            {
                this->currentFrame.left = 0;
            }
            this->animationTimer.restart(); 
            this->sprite.setTextureRect(this->currentFrame);

        }
    }else if (this->animState == PLAYER_ANIMATION_STATES::MOVING_RIGHT)
    {
        if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f)
        {
            this->currentFrame.top = 20.f; 
            this->currentFrame.left += 20.f;
            if (this->currentFrame.left >= 264.f)
            {
                this->currentFrame.left = 0;
            }
            this->animationTimer.restart(); 
            this->sprite.setTextureRect(this->currentFrame);

        }
    }else{
        this->animationTimer.restart(); 
    }
}

void Player::updatePhysics()
{
    
}


void Player::update()
{
    this->updateMovement();
    this->updateAnimation();
}

void Player::render(sf::RenderTarget &target)
{
    target.draw(this->sprite);
}
