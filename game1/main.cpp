#include "Game.hpp"
using namespace std;

int main()
{
    std::srand(static_cast<unsigned>(time(NULL)));
    //Init game engine
    Game game; 
    while(game.running() && !game.getEndGame()){
        game.update(); 
        game.render();
    }


    //Render

    //draw your game
    return 0; 
}

