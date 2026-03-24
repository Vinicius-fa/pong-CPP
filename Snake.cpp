#include <iostream>
#include <deque>
#include <windows.h>
#include <conio.h>
#include <cstdlib>

using namespace std;

const int WIDTH = 20;
const int HEIGHT = 10;

int dirX = 1, dirY = 0;

bool gameRunning = true;

struct Point { int x, y; };

deque<Point> snake;
Point food;

int score = 0;

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

    cout << "Score: " << score << "\n";
}

void logic() {
    Point novasCabeca = { snake.front().x + dirX,
                          snake.front().y + dirY };

    // 1. bateu na borda?
    if (novasCabeca.x <= 0 || novasCabeca.x >= WIDTH - 1 ||
        novasCabeca.y <= 0 || novasCabeca.y >= HEIGHT - 1) {
        gameRunning = false;
        return;
    }

    // 2. bateu no próprio corpo?
    for (Point p : snake) {
        if (p.x == novasCabeca.x && p.y == novasCabeca.y) {
            gameRunning = false;
            return;
        }
    }

    // 3. move
    snake.push_front(novasCabeca);

    // 4. comeu a comida?
    if (novasCabeca.x == food.x && novasCabeca.y == food.y) {
        score++;
        food = { rand() % (WIDTH - 2) + 1,
                 rand() % (HEIGHT - 2) + 1 };
    } else {
        snake.pop_back();
    }
}

void input() {
    if (!_kbhit()) return;
    char ch = _getch();

    switch(ch) {
        case 'w': case 'W': if (dirY != 1) { dirX = 0; dirY = -1; } break;
        case 's': case 'S': if (dirY != -1) { dirX = 0; dirY = 1; } break;
        case 'a': case 'A': if (dirX != 1) { dirX = -1; dirY = 0; } break;
        case 'd': case 'D': if (dirX != -1) { dirX = 1; dirY = 0; } break;
        case 'x': case 'X': gameRunning = false; break;
    }
}

void setup() {
    snake.clear();
    snake.push_back({5, 3});
    snake.push_back({4, 3});
    snake.push_back({3, 3});

    food = { rand() % (WIDTH - 2) + 1,
         rand() % (HEIGHT - 2) + 1};

    dirX = 1;
    dirY = 0;
    score = 0;
    gameRunning = true;
}

int main () {
    hideCursor();
    system("cls");
    srand((unsigned)time(nullptr));
    
    setup();

    while (true) {
        while(gameRunning) {
            draw();
            input();
            logic();
            Sleep(150);
        }

        gotoxy(0, HEIGHT + 1);
        cout << "Game over! Score " << score << "      \n";
        cout << "Jogar novamente? (S/N): ";

        char ch = _getch();
        if (ch == 's' || ch == 'S') {
            system("cls");
            setup();
        } else {
            break;
        }
    }
    return 0;
}