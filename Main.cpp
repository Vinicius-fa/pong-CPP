#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

const int width = 20;
const int height = 10;
int ballX, ballY, paddleY;
int score;

enum Direction { STOP = 0, LEFT, RIGHT };
Direction dir;

void setup() {
    ballX = width /2;
    ballY = height /2;
    paddleY = height /2;
    score = 0;
    dir = STOP; 
}

void draw() {
    system ("cls");
    for (int i = 0; i < width + 2; i++) {
        cout << "#";
    }

    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0) {
                cout << "#";
            }

            if (i == ballY && j == ballX) {
                cout << "O";
            } else if ( j == 1 && i >= paddleY - 1 && i <= paddleY + 1) {
                cout << "#";
            } else {
                cout << " ";
            }

            if (j == width - 1) {
                cout << "#";
            }
            cout << endl;
        }

        for (int i = 0; i < width + 2; i++) {
            cout << "#";
        }

        cout << endl;

        cout << "Score: " << score << endl;
    }
}

void logic() {
    if (dir == STOP){
      return;  
    } 

    ballX ++;
    if(ballX >= width) {
        ballX = 0;
        score++;
    }

    // colisão da bola com o paddle
    if(ballX == 1 && ballY >= paddleY -1 && ballY <= paddleY + 1) {
        ballX ++;
    }
}

void input() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'w':
                if (paddleY > 1) paddleY--;
                break;
            case 's':
                if (paddleY < height - 2) paddleY++;
                break;
            case 'x':
                dir = STOP;
                break;
        }
    }
}

void gameOver() {
    cout << "Game Over! Final Score: " << score << endl;
    exit(0);
}

int main() {
    setup();
    while (true) {
        draw();
        input();
        logic();
        Sleep(100);
    }
    return 0;
}