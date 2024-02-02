#include "Game.hpp"
#include <iostream> 
#include "Game.h"
//private function
void Game::initVariables()
{
    this->window = nullptr; 

    //game logic
    int points; 
    float enemySpawnTimer; 
    float enemySpawnTimerMax;
    int maxEnemies;
    this->endGame = false;
    this->points = 0;
    this->health = 10;
    this->enemySpawnTimerMax = 60.f;

    this->enemySpawnTimer = this->enemySpawnTimerMax;
    this->maxEnemies = 15; //5
    this->mouseHeld = false; 
}

void Game::initWindow()
{
    this->videoMode.height = 600;
    this->videoMode.width = 800;
    this->window = new sf::RenderWindow(this->videoMode, "My window", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(144); 
}


void Game::initEnemies()
{
    this->enemy.setPosition(10.f, 10.f); 
    this->enemy.setSize(sf::Vector2f(100.f, 100.f)); 
    this->enemy.setScale(sf::Vector2f(0.5f, 0.5f));
    this->enemy.setFillColor(sf::Color::Cyan);
    this->enemy.setOutlineColor(sf::Color::Green);
    this->enemy.setOutlineThickness(1.f); //1 as float
} 

//constructor
Game::Game()
{
    this->initVariables(); 
    this->initWindow();
    this->initFonts(); 
    this->initText(); 
    this->initEnemies();
}

Game::~Game()
{
    delete this->window; 
}

void Game::initFonts()
{
    if(!(this->font.loadFromFile("../Fonts/Dosis-Light.ttf"))){
        std::cout <<"ERROR::GAME::INITFONTS::Failed to load font!\n";
    };
}

//public
//accessor
const bool Game::running() const
{
    return this->window->isOpen();
}

void Game::pollEvents()
{
    while(this->window->pollEvent(this->ev)){
        switch(this->ev.type){
            case sf::Event::Closed:
                this->window->close(); //-> cuz window is a pointer
               break; 
            case sf::Event::KeyPressed: 
                if(ev.key.code == sf::Keyboard::Escape){
                    this->window->close(); 
                }
                break; 
        }   
    }
}

void Game::update()
{
    this->pollEvents();
    if(this->endGame == false){
        this->updateMousePositons(); 
        this->updateText();
        this->updateEnemies();
    }

    if (this->health <= 0){
        this->endGame = true;
    }
    
    //relative to screen 
    // std::cout <<"Mouse position: " << sf::Mouse::getPosition().x << " " << sf::Mouse::getPosition().y << std::endl; 
    //relative to window 
    // std::cout <<"Mouse position: " << sf::Mouse::getPosition(*this->window).x << " " << sf::Mouse::getPosition(*this->window).y << std::endl;
}

void Game::updateMousePositons()
{
    this->mousePosWindow = sf::Mouse::getPosition(*this->window); 
    this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}


void Game::spawnEnemy()
{
    sf::RectangleShape enemy; // Create a new RectangleShape for each enemy
    enemy.setSize(sf::Vector2f(100.f, 100.f));
    enemy.setScale(sf::Vector2f(0.5f, 0.5f));
    enemy.setFillColor(sf::Color::Blue);

    enemy.setPosition(
        static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - enemy.getSize().x)),
        0.f
    );
    int type = rand() % 5; //random enemy type(0,5)
    std::cout<<type<<std::endl;
    switch(type){
        case 0:
            enemy.setSize(sf::Vector2f(10.f, 10.f)); 
            enemy.setFillColor(sf::Color::Magenta); 
            break;  //break out of switch otherwise it will run code of other cases
        case 1:
            enemy.setSize(sf::Vector2f(30.f, 30.f)); 
            enemy.setFillColor(sf::Color::Blue); 
            break; 
        case 2:
            enemy.setSize(sf::Vector2f(50.f, 50.f)); 
            enemy.setFillColor(sf::Color::Cyan);
            break;  
        case 3:
            enemy.setSize(sf::Vector2f(70.f, 70.f)); 
            enemy.setFillColor(sf::Color::Red); 
            break; 
        case 4:
            enemy.setSize(sf::Vector2f(100.f, 100.f)); 
            enemy.setFillColor(sf::Color::Green); 
            break; 
        default: //if not 0-4
            enemy.setSize(sf::Vector2f(100.f, 100.f)); 
            enemy.setFillColor(sf::Color::Yellow); 
            break; 
    }
    this->enemies.push_back(enemy);
}

const bool Game::getEndGame() const
{
    return this->endGame; 
}

void Game::updateEnemies()
{
    //spawning
    if(this->enemies.size() < this->maxEnemies){ //if num of enemies is less than max enemies
        if(this->enemySpawnTimer >= this -> enemySpawnTimerMax){
            this->spawnEnemy();
            this->enemySpawnTimer = 0.f;
        }else{
            this->enemySpawnTimer += 1.f; 
        }
    }

    //updating
    

}

void Game::updateCombat()
{
    //move and update enemies
    for(int i = 0; i < this->enemies.size(); i++){
        bool deleted = false; 
        this->enemies[i].move(0.f, 1.f);
        if(this->enemies[i].getPosition().y > this->window->getSize().y){
            this->enemies.erase(this->enemies.begin() + i); 
            this->health -=1; 
            std::cout <<"Health: " << this->health << std::endl;

        }
    }

    //check if clicked upon
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        if (this->mouseHeld == false){
            this->mouseHeld = true;
            bool deleted = false;
            for(size_t i = 0; i < this->enemies.size() && deleted == false; i++){
                if(this->enemies[i].getGlobalBounds().contains(this->mousePosView)){
                    deleted = true; 
                    this->points += 10;
                    std::cout <<"Points: " << this->points << std::endl;
                    this->enemies.erase(this->enemies.begin() + i); 
                }
            }
            std::cout<<mouseHeld<<std::endl;

        }
    }else{
        this->mouseHeld = false; 
    }
}

void Game::initText()
{
    this->uiText.setFont(this->font);
    this->uiText.setCharacterSize(12); 
    this->uiText.setFillColor(sf::Color::White); 
    this->uiText.setPosition(10.f, 10.f);
    this->uiText.setString("NONE"); 
}

void Game::renderEnemies(sf::RenderTarget& target)
{
    for(auto &e : this->enemies){
        // this->window->draw(e);
        target.draw(e); 
    }
}

void Game::render()
{
    //clear old frame, render obj, display frame in window
    this->window->clear();
    this->renderEnemies(*this->window);
    this->renderText(*this->window);
    //draw game 
    this->window->display(); 

}

void Game::updateText()
{
    std::stringstream ss; 
    ss << "Points: " << this->points << "\n" << "Health: " << this->health << "\n"; //create string that's combination of string and int
    this->uiText.setString(ss.str()); 
}

void Game::renderText(sf::RenderTarget& target)
{
    target.draw(this->uiText);  
}
