#include "./Header/Game.h"



void Game::initWindow()
{
    this->window.create(sf::VideoMode(800, 600), "Game 3", sf::Style::Close | sf::Style::Titlebar, sf::ContextSettings()); 
    this->window.setFramerateLimit(144);  //set framerate for game movemetn 
}

void Game::initPlayer()
{
    this->player = new Player(); 
}   

Game::Game()
{
    this->initWindow(); 
    this->initPlayer();
}

Game::~Game(){
    delete this->player; 
}

void Game::updatePlayer(){
    this->player->update();
}

void Game::update(){
    //polling whindow events
    while(this->window.pollEvent(this->ev)){
        if(this->ev.type == sf::Event::Closed){
            this->window.close();
        }else if(this->ev.type == sf::Event::KeyPressed && this->ev.key.code == sf::Keyboard::Escape){
            this->window.close(); 
        }
    }
    this->updatePlayer();
}

void Game::renderPlayer(){
    this->player->render(this->window);
}

void Game::render(){
    this->window.clear(); 

    //draw game objects
    this->renderPlayer(); 

    this->window.display(); //display this frame
}
const sf::RenderWindow& Game::getWindow() const{
    return this->window; 
}