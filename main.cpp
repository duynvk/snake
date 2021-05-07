#include <iostream>
#include "snake.h"
#include <conio.h>

int main(){
    snake Game;
    Game.load();
    Game.menu();
    Game.drawBorder();
    while (1){
        Game.drawSnake();
        Game.drawApple();
        Game.control();
        Game.eatedTest();
        Game.lostTest();
    }
}
