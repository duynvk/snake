#include <iostream>
#include <conio.h>
#include <time.h>
#include "snake.h"

snake::snake()
{
    srand(time(NULL));
    head.x = X0 + WIDTH / 2;
    head.y = Y0 + HEIGHT / 2;

    int x1,y1;
    do {
        x1 = X0 + rand() % (WIDTH + 1);
        y1 = Y0 + rand() % (HEIGHT + 1);
    } while (wall[y1][x1] == 1);
    apple.x = x1;
    apple.y = y1;

    prev = RIGHT;
    gameOver = false;
    score = 0;
    lengthSnake = 1;

    tail.push_back(head);
}
void snake::reset()
{
    head.x = X0 + WIDTH / 2;
    head.y = Y0 + HEIGHT / 2;

    int x1,y1;
    do {
        x1 = X0 + rand() % (WIDTH + 1);
        y1 = Y0 + rand() % (HEIGHT + 1);
    } while (wall[y1][x1] == 1);
    apple.x = x1;
    apple.y = y1;

    prev = RIGHT;
    gameOver = false;
    score = 0;
    lengthSnake = 1;
    speed=300;
    cutRate=7;

    tail.clear();
    tail.push_back(head);
}
void resizeConsole(int width, int height)
{
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);
    MoveWindow(console, r.left, r.top, width, height, TRUE);
}

void textColor(int x)
{
    HANDLE color;
    color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(color, x);
}

void goToXY(int x, int y)
{
    HANDLE hConsoleOutput;
    COORD Cursor_an_Pos = { x - 1, y - 1 };
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}

void snake::initPrev(coordinate& coord)
{
    coord.x0 = coord.x;
    coord.y0 = coord.y;
}

void snake::drawSnake()
{
    textColor(14);
    for (int i = 0; i < tail.size(); i++)
    {
        if (i == 0){
            goToXY(tail[i].x,tail[i].y);
            std::cout<<"O";
        } else {
            initPrev(tail[i]);
            goToXY(tail[i].x,tail[i].y);
            std::cout<<" ";
            tail[i].x = tail[i - 1].x0;
            tail[i].y = tail[i - 1].y0;
            goToXY(tail[i].x, tail[i].y); std::cout << "o";
        }
    }
}

void snake::drawApple()
{
    textColor(12);
    goToXY(apple.x,apple.y);
    std::cout<<"0";
}

void snake::drawScore()
{
    textColor(12);
    goToXY(WIDTH / 2, Y0 - 3);
    std::cout << "SCORE : " << score;
}

void snake::deletePoint(int x,int y)
{
    goToXY(x,y);
    std::cout<<" ";
}

void snake::drawBorder()
{
    system("cls");
    resizeConsole(675,600);
    SetConsoleTitle("Game:Snake - Nguyen Van Khanh Duy - 20020041");
    goToXY(1,1);
    std::cout << "\n  SPACE : TAM DUNG          UP : DI LEN         RIGHT : RE PHAI";
    std::cout << "\n  ESC   : QUAY LAI MENU     DOWN : DI XUONG     LEFT  : RE TRAI";
    textColor(8);
    for (int i = 18; i < 45; i++)
        for (int j = 10; j < 65; j++)   wall[i][j]=0;
    if (type == '1'){
        for (int i = Y0; i <= Y0 + HEIGHT; i++){
            goToXY(X0, i);
            wall[i][X0] = 1;    wall[i][X0 + 1] = 1;
            std::cout << char(CHAR) << char(CHAR);
            goToXY(X0 + WIDTH - 1, i);
            wall[i][X0 + WIDTH - 1] = 1;    wall[i][X0 + WIDTH] = 1;
            std::cout << char(CHAR) << char(CHAR);
        }
        for (int i = X0; i <= X0 + WIDTH; i++){
            goToXY(i, Y0);              wall[Y0][i] = 1;
            std::cout << char(CHAR);
            goToXY(i, Y0 + HEIGHT);     wall[Y0 + HEIGHT][i] = 1;
            std::cout << char(CHAR);
        }
    }
    if (type == '3'){
        for (int i = Y0; i < Y0 + 5; i++){
            goToXY(X0, i);
            wall[i][X0] = 1;    wall[i][X0 + 1] = 1;
            std::cout << char(CHAR) << char(CHAR);
            goToXY(X0 + WIDTH - 1, i);
            wall[i][X0 + WIDTH - 1] = 1;    wall[i][X0 + WIDTH] = 1;
            std::cout << char(CHAR) << char(CHAR);
        }
        for (int i = Y0 + 5; i < Y0 + HEIGHT - 5; i++){
            goToXY(X0 + 11, i);
            wall[i][X0 + 11] = 1;   wall[i][X0 + 12] = 1;
            std::cout << char(CHAR) << char(CHAR);
            goToXY(X0 + WIDTH - 12, i);
            wall[i][X0 + WIDTH - 12] = 1;   wall[i][X0 + WIDTH - 11] = 1;
            std::cout << char(CHAR) << char(CHAR);
        }
        for (int i = Y0 + HEIGHT - 4; i <= Y0 + HEIGHT; i++){
            goToXY(X0, i);
            wall[i][X0] = 1;    wall[i][X0 + 1] = 1;
            std::cout << char(CHAR) << char(CHAR);
            goToXY(X0 + WIDTH - 1, i);
            wall[i][X0 + WIDTH - 1] = 1;    wall[i][X0 + WIDTH] = 1;
            std::cout << char(CHAR) << char(CHAR);
        }
        for (int i = X0; i < X0 + 10; i++){
            goToXY(i, Y0);              wall[Y0][i] = 1;
            std::cout << char(CHAR);
            goToXY(i, Y0 + HEIGHT);     wall[Y0 + HEIGHT][i] = 1;
            std::cout << char(CHAR);
        }
        for (int i = X0 + WIDTH - 9; i <= X0 + WIDTH; i++){
            goToXY(i, Y0);              wall[Y0][i] = 1;
            std::cout << char(CHAR);
            goToXY(i, Y0 + HEIGHT);     wall[Y0 + HEIGHT][i] = 1;
            std::cout << char(CHAR);
        }
    }
    if (type == '4'){
        for (int i = Y0; i < Y0 + 7; i++){
            goToXY(X0 + 4, i);
            wall[i][X0 + 4] = 1;    wall[i][X0 + 5] = 1;
            std::cout << char(CHAR) << char(CHAR);
        }
        for (int i = Y0 + HEIGHT - 6; i <= Y0 + HEIGHT; i++){
            goToXY(X0 + WIDTH - 5, i);
            wall[i][X0 + WIDTH - 5] = 1;    wall[i][X0 + WIDTH - 4] = 1;
            std::cout << char(CHAR) << char(CHAR);
        }
        for (int i = X0 + 10; i <= X0 + WIDTH; i++){
            goToXY(i, Y0 + 6);          wall[Y0 + 6][i] = 1;
            std::cout << char(CHAR);
        }
        for (int i = X0; i <= X0 + WIDTH - 10; i++){
            goToXY(i, Y0 + HEIGHT - 6); wall[Y0 + HEIGHT - 6][i] = 1;
            std::cout << char(CHAR);
        }
    }
    if (type == '5'){
        for (int i = Y0; i <= Y0 + HEIGHT; i++){
            goToXY(X0, i);
            wall[i][X0] = 1;    wall[i][X0 + 1] = 1;
            std::cout << char(CHAR) << char(CHAR);
            goToXY(X0 + WIDTH - 1, i);
            wall[i][X0 + WIDTH - 1] = 1;    wall[i][X0 + WIDTH] = 1;
            std::cout << char(CHAR) << char(CHAR);
        }
        for (int i = Y0 + 5; i < Y0 + HEIGHT - 5; i++){
            goToXY(X0 + 11, i);
            wall[i][X0 + 11] = 1;   wall[i][X0 + 12] = 1;
            std::cout << char(CHAR) << char(CHAR);
            goToXY(X0 + WIDTH - 12, i);
            wall[i][X0 + WIDTH - 12] = 1;   wall[i][X0 + WIDTH - 11] = 1;
            std::cout << char(CHAR) << char(CHAR);
        }
        for (int i = X0; i < X0 + 10; i++){
            goToXY(i, Y0);              wall[Y0][i] = 1;
            std::cout << char(CHAR);
            goToXY(i, Y0 + HEIGHT);     wall[Y0 + HEIGHT][i] = 1;
            std::cout << char(CHAR);
        }
        for (int i = X0 + WIDTH - 9; i <= X0 + WIDTH; i++){
            goToXY(i, Y0);              wall[Y0][i] = 1;
            std::cout << char(CHAR);
            goToXY(i, Y0 + HEIGHT);     wall[Y0 + HEIGHT][i] = 1;
            std::cout << char(CHAR);
        }
    }
    if (type == '6'){
        for (int i = Y0; i < Y0 + 5; i++){
            goToXY(X0 + WIDTH - 1, i);
            wall[i][X0 + WIDTH - 1] = 1;    wall[i][X0 + WIDTH] = 1;
            std::cout << char(CHAR) << char(CHAR);
        }
        for (int i = Y0; i <= Y0 + HEIGHT; i++){
            goToXY(X0 + 10, i);
            wall[i][X0 + 10] = 1;    wall[i][X0 + 11] = 1;
            std::cout << char(CHAR) << char(CHAR);
        }
        for (int i = Y0 + 8; i <= Y0 + HEIGHT - 4; i++){
            goToXY(X0 + WIDTH -1, i);
            wall[i][X0 + WIDTH -1] = 1;    wall[i][X0 + WIDTH] = 1;
            std::cout << char(CHAR) << char(CHAR);
        }
        for (int i = Y0; i <= Y0 + 9; i++){
            goToXY(X0 + 23, i);
            wall[i][X0 + 23] = 1;    wall[i][X0 + 24] = 1;
            std::cout << char(CHAR) << char(CHAR);
        }
        for (int i = Y0 + 13; i <= Y0 + HEIGHT; i++){
            goToXY(X0 + 23, i);
            wall[i][X0 + 23] = 1;    wall[i][X0 + 24] = 1;
            std::cout << char(CHAR) << char(CHAR);
        }
        for (int i = X0 + WIDTH - 9; i <= X0 + WIDTH; i++){
            goToXY(i, Y0);          wall[Y0][i] = 1;
            std::cout << char(CHAR);
        }
        for (int i = X0; i < X0 + 10; i++){
            goToXY(i, Y0 + 13);     wall[Y0 + 13][i] = 1;
            std::cout << char(CHAR);
        }
        for (int i = X0 + 25; i <= X0 + WIDTH; i++){
            goToXY(i, Y0 + 9);     wall[Y0 + 9][i] = 1;
            std::cout << char(CHAR);
        }
    }
    textColor(15);
    for (int i = (X0-1); i <= (X0 + WIDTH + 1); i++){
        goToXY(i, Y0-1);
        std::cout << char(CHAR);

        goToXY(i, Y0 + HEIGHT+1);
        std::cout << char(CHAR);

    }
    for (int i = Y0 - 1; i <= Y0 + HEIGHT + 1; i++){
        goToXY(X0 - 2, i);
        std::cout << char(CHAR) << char(CHAR);

        goToXY(X0 + WIDTH + 1, i);
        std::cout << char(CHAR) << char(CHAR);
    }
    int x1,y1;
    do {
        x1 = X0 + rand() % (WIDTH + 1);
        y1 = Y0 + rand() % (HEIGHT + 1);
    } while (wall[y1][x1] == 1);
    apple.x = x1;
    apple.y = y1;
    drawApple();
    drawScore();
    drawSnake();
}

void snake::control()
{
    Sleep(speed);
    initPrev(tail[0]);
    deletePoint(head.x,head.y);
    if (GetAsyncKeyState(VK_LEFT) && prev != RIGHT){
        head.x--;
        prev = LEFT;
    }
    else if (GetAsyncKeyState(VK_RIGHT) && prev != LEFT){
        head.x++;
        prev = RIGHT;
    }
    else if (GetAsyncKeyState(VK_UP) && prev != DOWN){
        head.y--;
        prev = UP;
    }
    else if (GetAsyncKeyState(VK_DOWN) && prev != UP){
        head.y++;
        prev = DOWN;
    }
    else if (GetAsyncKeyState(32)){
        goToXY(3, 4);
        system("pause");
        goToXY(3, 4);
        std::cout << "                                                                      ";
    }
    else if (GetAsyncKeyState(27)){
        reset();
            menu();
            system("cls");
            drawBorder();
            while (1){
                drawSnake();
                drawApple();
                control();
                eatedTest();
                lostTest();
            }
    }
    else{
        switch (prev){
            case LEFT:
                head.x--;
                break;
            case RIGHT:
                head.x++;
                break;
            case UP:
                head.y--;
                break;
            case DOWN:
                head.y++;
                break;
        }
    }
    if (head.x < X0) head.x = X0 + WIDTH;
    if (head.x > X0 + WIDTH) head.x = X0;
    if (head.y < Y0) head.y = Y0 + HEIGHT;
    if (head.y > Y0 + HEIGHT) head.y = Y0;
    tail[0].x = head.x;
    tail[0].y = head.y;
}

void snake::lostTest()
{
    if (wall[tail[0].y][tail[0].x] == 1) gameOver = true;
    for (int i = 1; i < lengthSnake; i++)
        if (tail[0].x == tail[i].x && tail[0].y == tail[i].y) gameOver = true;


    if (gameOver){
        if (score>highScore[4]) highScore[4]=score;
        for (int i = 0; i < 4; i++)
            for (int j = i + 1; j < 5; j++)
                if (highScore[i] < highScore[j]) {
                    int hScore = highScore[i];
                    highScore[i] = highScore[j];
                    highScore[j] = hScore;
                }
        system("cls");
        textColor(12);
        std::cout << "\n                         >> GAME OVER ! <<\n\n";
        textColor(15);
        std::cout << "                             SCORE: " << score;
        textColor(15);
        std::cout << "\n\n             Bam 1 de choi lai va 2 de ket thuc tro choi.";
        char select;
        while (1){
            select=getch();
            if (select == '1') {
                reset();
                menu();
                system("cls");
                drawBorder();
                while (1){
                    drawSnake();
                    drawApple();
                    control();
                    eatedTest();
                    lostTest();
                }
            }
            if (select == '2') {
                system("cls");
                textColor(14);
                goToXY(X0 + WIDTH / 2 - 6, Y0 + HEIGHT / 2 - 10);
                std::cout<<"GAME-ENDING...\n\n\n\n\n\n\n\n\n\n";
                textColor(15);
                Sleep(3000);
                exit(1);
            }
        }
    }
}

void snake::eatedTest()
{
    if (head.x == apple.x && head.y == apple.y){
        score += 10;
        lengthSnake++;

        coordinate coord;
        tail.push_back(coord);
        drawScore();
        goToXY(apple.x, apple.y);
        std::cout << " ";
        srand(time(NULL));
        int x1,y1;
        do {
            x1 = X0 + rand() % (WIDTH + 1);
            y1 = Y0 + rand() % (HEIGHT + 1);
        } while (wall[y1][x1] == 1);
        apple.x = x1;
        apple.y = y1;
        drawApple();
        if (speed>75) speed-=cutRate;
    }
}

void snake::menu()
{
    resizeConsole(675,600);
    SetConsoleTitle("Game:Snake - Nguyen Van Khanh Duy - 20020041");
    system("cls");
    textColor(12);
    std::cout<<"\n                       >> GAME : SNAKE <<\n\n";
    textColor(14);
    std::cout<<"                         1 . CHOI LUON\n";
    std::cout<<"                         2 . CHON MUC DO\n";
    std::cout<<"                         3 . CHON LOAI DIA HINH\n";
    std::cout<<"                         4 . DIEM CAO\n";
    std::cout<<"                         5 . HUONG DAN\n";
    std::cout<<"                         6 . THOAT TRO CHOI\n\n";
    textColor(15);
    std::cout<<"                      ( Bam 1 2 3 4 5 6 de chon )";

    char select=48;
    while (1)
        if (kbhit())
        {
            select=getch();
            if (select>48 && select<55) break;
        }
    if (select == '1') return;
    if (select == '2'){
        system("cls");
        textColor(12);
        std::cout<<"\n                       >> CHON MUC DO <<\n\n";
        textColor(14);
        std::cout<<"                         1 . De\n";
        std::cout<<"                         2 . Trung binh\n";
        std::cout<<"                         3 . Kho\n\n";
        textColor(15);
        std::cout<<"                      ( Bam 1 2 3 de chon muc )\n\n";
        char select2;
        while (1)
            if (kbhit())
            {
                select2=getch();
                if (select2>48 && select2<52) break;
            }
        if (select2 == '1'){
            speed = 500;
            cutRate = 15;
            std::cout<<"Ban da chon muc do De\n";
        }
        if (select2 == '2'){
            speed = 300;
            cutRate = 7;
            std::cout<<"Ban da chon muc do Trung binh\n";
        }
        if (select2 == '3'){
            speed = 100;
            cutRate = 1;
            std::cout<<"Ban da chon muc do Kho\n";
        }
        textColor(15);
        std::cout<<"\n\n( Bam 1 de choi va ESC de quay lai menu )";
        char select3;
        while (1)
            if (kbhit())
            {
                select3=getch();
                if (select3 == 49) return;
                if (select3 == 27) break;
            }
        menu();
    }
    if (select == '3'){
        system("cls");
        textColor(12);
        std::cout<<"\n                       >> CHON DIA HINH <<\n\n";
        textColor(14);
        std::cout<<"                         1 . Cai hop\n";
        std::cout<<"                         2 . Khong me cung\n";
        std::cout<<"                         3 . Duong ham\n";
        std::cout<<"                         4 . Coi xay\n";
        std::cout<<"                         5 . Duong ray\n";
        std::cout<<"                         6 . Can ho\n\n";
        textColor(15);
        std::cout<<"                    ( Bam 1 2 3 4 5 6 de chon muc )\n\n";
        char select2;
        while (1)
            if (kbhit())
            {
                select2=getch();
                if (select2>48 && select2<55) break;
            }
        type = select2;
        if ( select2 == '1') std::cout<<"Ban da chon dia hinh Cai hop\n";
        if ( select2 == '2') std::cout<<"Ban da chon dia hinh Khong me cung\n";
        if ( select2 == '3') std::cout<<"Ban da chon dia hinh Duong ham\n";
        if ( select2 == '4') std::cout<<"Ban da chon dia hinh Coi xay\n";
        if ( select2 == '5') std::cout<<"Ban da chon dia hinh Duong ray\n";
        if ( select2 == '6') std::cout<<"Ban da chon dia hinh Can ho\n";
        textColor(15);
        std::cout<<"\n\n( Bam 1 de choi va ESC de quay lai menu )";
        char select3;
        while (1)
            if (kbhit())
            {
                select3=getch();
                if (select3 == 49) return;
                if (select3 == 27) break;
            }
        menu();
    }
    if (select == '4'){
        system("cls");
        textColor(12);
        std::cout<<"\n                        >> DIEM CAO <<\n\n";
        textColor(14);
        std::cout<<"                           1 . "<<highScore[0];
        std::cout<<"\n                           2 . "<<highScore[1];
        std::cout<<"\n                           3 . "<<highScore[2];
        std::cout<<"\n                           4 . "<<highScore[3];
        std::cout<<"\n                           5 . "<<highScore[4];
        textColor(15);
        std::cout<<"\n\n                     Bam ESC de quay lai menu";
        char select2;
        while (1)
            if (kbhit())
            {
                select2=getch();
                if (select2 == 27) break;
            }
        menu();
    }
    if (select == '5'){
        system("cls");
        std::cout<<"Su dung 4 phim: UP, DOWN, RIGHT, LEFT de dieu khien con ran toi an qua tao.\n";
        std::cout<<"Bam phim SPACE de tam dung tro choi.\n";
        std::cout<<"Moi khi an 1 qua tao thi ban se nhan them 10 diem va toc do con ran se tang len.\n";
        std::cout<<"Khi con ran dam dau vao tuong hay chinh con ran tro choi se ket thuc.\n\n";
        std::cout<<"( Bam ESC de quay lai menu )";
        char select2;
        while (1)
            if (kbhit())
            {
                select2=getch();
                if (select2 == 27) break;
            }
        menu();
    }
    if (select == '6'){
        system("cls");
        textColor(14);
        goToXY(X0 + WIDTH / 2 - 6, Y0 + HEIGHT / 2 - 10);
        std::cout<<"GAME-ENDING...\n\n\n\n\n\n\n\n\n\n";
        textColor(15);
        Sleep(3000);
        exit(1);
    }
}
void snake::load()
{
    resizeConsole(675,600);
    SetConsoleTitle("Game:Snake - Nguyen Van Khanh Duy - 20020041");
    textColor(14);
    goToXY(X0 + WIDTH / 2 - 6, Y0 + HEIGHT / 2 - 10);
    std::cout<<"GAME-BEGINING...";
    Sleep(3000);
    for (int i = 18; i < 45; i++)
        for (int j = 10; j < 65; j++)   wall[i][j]=0;
}
