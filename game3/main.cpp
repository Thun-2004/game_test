#include "./Header/Game.h"
int main()
{
    // srand(time(static_cast<unsigned>(0))); 
    srand(time(NULL));
    Game game; 
    while(game.getWindow().isOpen()){
        game.update(); 
        game.render(); 
    }

    return 0;
}