#ifndef SNAKE_H_INCLUDED
#define SNAKE_H_INCLUDED

#include <windows.h>
#include <vector>

#pragma once

#define HEIGHT 20
#define WIDTH 40
#define X0 18
#define Y0 10
#define CHAR 219

struct coordinate{
    int x0,y0,x,y;
};

struct simpleCoordinate{
    int x,y;
};

enum STYLE{LEFT = 0, RIGHT, UP, DOWN};

class snake
{
private:
    coordinate head;
    std::vector<coordinate> tail;
    bool gameOver;
    int prev;
    int unsigned score;
    coordinate apple;
    int lengthSnake;
    int speed=300;
    int cutRate=7;
    int highScore[5]={0,0,0,0,0};
    char type='1';
    int wall[50][70];
public:
    snake();
    void drawBorder();
    void drawSnake();
    void drawApple();
    void drawScore();
    void control();
    void deletePoint(int x,int y);
    void lostTest();
    void eatedTest();
    void initPrev(coordinate& coord);
    void menu();
    void reset();
    void load();
};

#endif // SNAKE_H_INCLUDED
