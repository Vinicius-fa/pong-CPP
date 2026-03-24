#include <iostream>
#include <deque>
#include <windows.h>

using namespace std;

const int WIDTH = 20;
const int HEIGHT = 10;

int dirX = 1, dirY = 0;

bool gameRunning = true;

struct Point { int x, y; };

deque<Point> snake;
Point food;

void gotoxy(int x, int y) {
    COORD c = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void hideCursor() {
    CONSOLE_CURSOR_INFO ci = {1, FALSE};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ci);
}

void draw() {

    gotoxy(0, 0);

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {

            if (x == 0 || x == WIDTH -1 || y == 0 || y == HEIGHT -1) {
                cout << "#";
            } else {

                bool ehCobra = false;
                for (Point p : snake) {
                    if (p.x == x && p.y == y) {
                        ehCobra = true;
                    }
                }
                if (ehCobra) cout << "0";
                else if (food.x == x && food.y == y) cout << "*";
                else         cout << " ";  
            }
        }
        cout << "\n";
    }

    cout << "Score: 0\n";
}

void logic() {
    Point novasCabeca = { snake.front().x + dirX,
                          snake.front().y + dirY};

    snake.push_front(novasCabeca);
    snake.pop_back();
}

int main () {
    hideCursor();
    system("cls");
    
    snake.push_back({5,3});
    snake.push_back({4,3});
    snake.push_back({3,3});

    food = {10, 5};

    while(true) {
        draw();
        logic();
        Sleep(200);
    }
    
    return 0;
}