#include "Game.h"
#include <iostream>

//Private fn
void Game::initWindow(){
    this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "Game 2", sf::Style::Close | sf::Style::Titlebar);
    this->window->setFramerateLimit(144); //higher the number, faster/smoother the game
    this->window->setVerticalSyncEnabled(false); //synchronize the framerate of the game with the refresh rate of the monitor.
}

void Game::initTextures(){
    this->textures["BULLET"] = new sf::Texture(); 
    this->textures["BULLET"]->loadFromFile("./resources/bullet.png");
}

void Game::initPlayer(){
    this->player = new Player(); 
}

void Game::initEnemies(){
    this->spawnTimerMax = 50.f; 
    this->spawnTimer = this->spawnTimerMax;
}

void Game::initWorld(){
    if(!this->bgTexture.loadFromFile("./resources/space.png")){
        std::cout << "ERROR::GAME::INITWORLD::FAILED TO LOAD BG TEXTURE" << std::endl;
    }
    this->bgTexture.loadFromFile("./resources/space.png");
    std::cout << "working fine"<<std::endl; 
    this->bg.setTexture(this->bgTexture); 
}

void Game::initSystem()
{
    this->points = 0; 
}


Game::Game(){
    this->initWindow(); 
    this->initTextures(); 
    this->initWorld();
    this->initSystem();
    this->initPlayer();
    this->initEnemies();
}

Game::~Game(){
    delete this->window; 
    delete this->player;

    for(auto &i : this->textures){
        delete i.second; 
    }
    for(auto *i : this->bullets){ //use with dynamically allocated memmory cis bullet is vector 
        delete i; 
    }

    for(auto *i : this->enemies){
        delete i; 
    }
}

void Game::updateCollision()
{
    //out of left screen
    if(this->player->getBounds().left < 0.f){
        this->player->setPosition(0.f, this->player->getBounds().top);
    }
  
    if(this->player->getBounds().left + this->player->getBounds().width > this->window ->getSize().x){
        this->player->setPosition(this->window->getSize().x - this->player->getBounds().width, this->player->getBounds().top);
    }
}

void Game::updateWorld(){
}

void Game::updateGUI(){
    if(!this->font.loadFromFile("./resources/Dosis-Light.ttf")){
        std::cout<<"ERROR::GAME::UPDATEGUI::COULD NOT LOAD FONT"<<std::endl;
    }
    std::stringstream ss; 
    ss  << "Points : "<< this->points; 
    this->pointText.setString(ss.str()); 
    this->pointText.setFont(this->font);
    this->pointText.setPosition(20.f, 20.f); 
    this->pointText.setCharacterSize(25); 
    this->pointText.setFillColor(sf::Color::White);
}

// Public fn
void Game::run(){
    while(this->window->isOpen()){
        sf::Event event; 
        while(this->window->pollEvent(event)){
            if(event.type == sf::Event::Closed){
                this->window->close(); 
            }
        }
        this->update(); 
        this->render(); 
    }
}

void Game::updatePollEvents(){
    sf::Event e; 
    while(this->window->pollEvent(e)){
        if(e.Event::type == sf::Event::Closed){
            this->window->close(); 
        }
        if(e.Event::KeyPressed && e.Event::key.code == sf::Keyboard::Escape){
            this->window->close(); 
        }
    }

}

void Game::updateInput(){
    //move player
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        this->player->move(-1.f, 0.f); 
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        this->player->move(0.f, -1.f); 
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        this->player->move(1.f, 0.f); 
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        this->player->move(0.f, 1.f); 
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && this->player->canAttack()){
        this->bullets.push_back( 

            new Bullet(this->textures["BULLET"], 
            this->player->getPos().x + this->player->getBounds().width/2.f - 13, 
            this->player->getPos().y,
            0.f,
            -1.f,
            5.f));
    }
}

void Game::updateBullet(){
    unsigned count = 0;
    for(auto *bullet : this->bullets){
        bullet->update(); 
        if (bullet->getBounds().top + bullet->getBounds().height < 0.f){
            delete this->bullets.at(count); 
            this->bullets.erase(this->bullets.begin() + count); 
            --count; 
            std::cout<<"shooted"<<std::endl; //this is not working
            // std::cout <<this->bullets.size()<<std::endl;
        }
        ++count; 
    }
}

void Game::updateEnemies(){
    //spawn enemies
    this->spawnTimer += 0.5f; 
    if(this->spawnTimer >= this->spawnTimerMax){
        this->enemies.push_back(new Enemy(rand() % this->window->getSize().x - 20.f, -100.f));
        this->spawnTimer = 0.f;
    }

    //update enemies
    unsigned count = 0;
    for(auto *enemy : this->enemies){
        enemy->update(); 
        if (enemy->getBounds().top  > this->window->getSize().y){
            delete this->enemies.at(count); 
            this->enemies.erase(this->enemies.begin() + count); 
            --count; 
            std::cout<<"enemy one"<<std::endl; //this is not working
            // std::cout <<this->enemies.size()<<std::endl;
        }
        ++count; 
    }
}

void Game::updateCombat(){
    //delete when out of scene
    for(int i = 0; i < this->enemies.size(); ++i){
        bool enemy_deleted = false; 
        for(size_t k = 0; k < this->bullets.size() && enemy_deleted == false; k++){
            //in case 
            if(this->enemies[i] -> getBounds().intersects(this->bullets[k]->getBounds())){
                delete this->enemies[i]; 
                this->enemies.erase(this->enemies.begin() + i); 
                delete this->bullets[k]; 
                this->bullets.erase(this->bullets.begin() + k); 

                enemy_deleted = true; 
            }
        }
    }
}

void Game::update(){
    this->updateGUI(); 
    this->updatePollEvents(); 
    this->updateWorld();
    this->updateCollision(); 
    this->updateInput();
    this->player->update(); 
    this->updateBullet();
    this->updateEnemies();
    this->updateCombat();
}

void Game::renderWorld(){
    this->window->draw(this->bg); 
}

void Game::render(){
    this->window->clear();
    //draw bg 

    this->renderWorld();
    this->window->draw(this->pointText); 
    //draw all stuff
    this->player->render(*this -> window); //derenference window since it is a pointer
    for(auto *i : this->bullets){
        i->render(this->window); //render to window 
    }
    for(auto *i : this->enemies){
        i->render(this->window); 
    }
    this->window->display();
}

