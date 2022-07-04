#include <iostream>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define WIDTH 20
#define HEIGHT 20

using namespace std;

int x, y, fruitX, fruitY;
int tailX[324], tailY[324];
int nTail;

int score, difficulty;

bool gameOver;

string game = "t";
string dif;

enum eDirection{ STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

void Setup() {

    gameOver = false;
    dir = STOP;
    x = WIDTH / 2;
    y = HEIGHT / 2;
    fruitX = rand() % WIDTH;
    fruitY = rand() % HEIGHT;
    score = 0;
    nTail = 0;
}

void Menu() {

    system("cls");

    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~SNAKE~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
    cout << endl << "1. EASY (Przenikanie przez sciany wlaczone, zmniejszowa szybkosc rozgrywki) ... " << endl;
    cout << endl << "2. MEDIUM (Przenikanie przez sciany wylaczone, normalna szybkosc rozgrywki) ... " << endl;
    cout << endl << "3. HARD (Przenikanie przez sciany wylaczone, maksymalna szybkosc rozgrywki) ... " << endl << endl;

    cout << "Wpisz numer poziomu trudnosci ..." << endl;
    cin >> difficulty;

    system("cls");
}
/*
    Draws the current frame on screen
*/
void Draw() {

    system("cls");

    //  Difficulty selection
    switch (difficulty) {

    case 1:
        dif = "EASY";
        break;
    case 2:
        dif = "MEDIUM";
        break;
    case 3:
        dif = "HARD";
        break;
    default:
        break;
    }

    cout << "~~~~~~SNAKE " << dif << "~~~~~~" << endl << endl;

    //  Upper border
    for (int i = 0; i < WIDTH + 2; i++)
        cout << "#";
    cout << endl;

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {

            //  Left border
            if (j == 0)
                cout << "#";

            if (i == y && j == x)   //  Snake position
                cout << "O";
            else if (i == fruitY && j == fruitX)    //  Fruit position
                cout << "F";
            else {
                bool print = false;
                for (int k = 0; k < nTail; k++) {

                    //  Printing tail
                    if (tailX[k] == j && tailY[k] == i) {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print)
                    cout << " ";
            }
            
            //  Right border
            if (j == WIDTH - 1)
                cout << "#";
        }
        cout << endl;
    }

    //  Bottom border
    for (int i = 0; i < WIDTH + 2; i++)
        cout << "#";
    cout << endl;
    
    cout << "Score : " << score << endl;
}

/*
    Getting input from keyboard
*/
void Input()
{
    if (_kbhit()) {

        switch (_getch()) {

        case 'a':
            dir = LEFT;
            break;

        case 'd':
            dir = RIGHT;
            break;

        case 's':
             dir = UP;
            break;

        case 'w':
            dir = DOWN;
            break;

        //  Quick exit
        case 'x':
            gameOver = true;
            break;

        //  Hidden bonus ¯\_(ツ)_/¯
        case 'p':
            nTail++;
            score += 10;
            break;
        
        default:
            break;
        }
    }
}
/*
    Clipping through walls enabled
*/
void LogicEasy() {

    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < nTail; i++) {

        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    //  Moving the snake
    switch (dir){

    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y++;
        break;
    case DOWN:
        y--;
        break;
    default:
        break;
    }

    if (x >= WIDTH)
        x = 0;
    else if (x < 0)
        x = WIDTH - 1;
    if (y >= HEIGHT)
        y = 0;
    else if (y < 0)
        y = HEIGHT - 1;

    //  Snakehit == gameover
    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;

    //  Eating fruit
    if (x == fruitX && y == fruitY) {

        nTail++;
        score += 10;
        fruitX = rand() % WIDTH;
        fruitY = rand() % HEIGHT;
    }
}

/*
    Clipping through walls disabled
*/
void Logic() {

    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < nTail; i++) {

        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    //  Moving the snake
    switch (dir) {

    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y++;
        break;
    case DOWN:
        y--;
        break;
    default:
        break;
    }

    //  Wallhit == gameover
    if (x > WIDTH || x < 0 || y > HEIGHT || y < 0)
        gameOver = true;

    //  Snakehit == gameover
    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;

    //  Eating fruit
    if (x == fruitX && y == fruitY) {

        nTail++;
        score += 10;
        fruitX = rand() % WIDTH;
        fruitY = rand() % HEIGHT;
    }
}

int main() {

    srand(time(NULL));

    while (game != "n") {
        Setup();
        Menu();

        switch (difficulty) {

        case 1:
            while (!gameOver)
            {
                Draw();
                Input();
                LogicEasy();
                Sleep(30);
            }
            break;

        case 2:
            while (!gameOver)
            {
                Draw();
                Input();
                Logic();
                Sleep(15);
            }
            break;

        case 3:
            while (!gameOver)
            {
                Draw();
                Input();
                Logic();
            }
            break;

        default:
            cout << "Wybrano nieprawidlowy tryb!!" << endl << endl;
            break;
        }

        cout << endl << "Udalo ci sie zdobyc " << score << " punktow." << endl;
        cout << "Chcesz zagrac ponownie? 't/n' ..." << endl;
        cin >> game;

    }

    system("cls");

    cout << "Dziekujemy za rozgrywke :)" << endl;
    Sleep(1000);

    system("exit");
}