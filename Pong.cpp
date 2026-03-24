#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

const int WIDTH  = 40;
const int HEIGHT = 20;

int ballX, ballY;
int ballDirX, ballDirY;
int paddleY;
int score;
int lives;
bool gameRunning;
bool started;

// ── helpers ─────────────────────────────────────────────────────────────────

void gotoxy(int x, int y) {
    COORD c = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void hideCursor() {
    CONSOLE_CURSOR_INFO ci = { 1, FALSE };
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ci);
}

// ── game logic ───────────────────────────────────────────────────────────────

void setup() {
    ballX    = WIDTH / 2;
    ballY    = HEIGHT / 2;
    ballDirX = 1;   // always moves right at start
    ballDirY = 1;
    paddleY  = HEIGHT / 2;
    score    = 0;
    lives    = 3;
    gameRunning = true;
    started     = false;
}

void resetBall() {
    ballX    = WIDTH / 2;
    ballY    = HEIGHT / 2;
    ballDirX = 1;
    ballDirY = (rand() % 2 == 0) ? 1 : -1;
    started  = false;
}

void draw() {
    gotoxy(0, 0);   // redraw in place – no flicker

    // top border
    for (int i = 0; i < WIDTH + 2; i++) cout << '#';
    cout << '\n';

    for (int row = 0; row < HEIGHT; row++) {
        cout << '#';                        // left wall

        for (int col = 0; col < WIDTH; col++) {
            bool drawn = false;

            // ball
            if (row == ballY && col == ballX) {
                cout << 'O'; drawn = true;
            }
            // paddle (column 1, 3 cells tall)
            else if (col == 1 &&
                     row >= paddleY - 1 &&
                     row <= paddleY + 1) {
                cout << '|'; drawn = true;
            }

            if (!drawn) cout << ' ';
        }

        cout << '#' << '\n';                // right wall
    }

    // bottom border
    for (int i = 0; i < WIDTH + 2; i++) cout << '#';
    cout << '\n';

    // HUD
    cout << "Score: " << score
         << "   Lives: " << lives
         << "          " << '\n';

    if (!started)
        cout << "SPACE = start  W/S = move  X = quit\n";
    else
        cout << "                                    \n"; // clear hint line
}

void input() {
    if (!_kbhit()) return;
    char ch = _getch();

    switch (ch) {
        case 'w': case 'W':
            if (paddleY > 1) paddleY--;
            break;
        case 's': case 'S':
            if (paddleY < HEIGHT - 2) paddleY++;
            break;
        case ' ':
            started = true;
            break;
        case 'x': case 'X':
            gameRunning = false;
            break;
    }
}

void logic() {
    if (!started) return;

    // ── move ball ──
    ballX += ballDirX;
    ballY += ballDirY;

    // top / bottom bounce
    if (ballY <= 0)          { ballY = 1;         ballDirY = 1;  }
    if (ballY >= HEIGHT - 1) { ballY = HEIGHT - 2; ballDirY = -1; }

    // ── paddle collision (column 2, after the '#' at col 0 + paddle at col 1) ──
    if (ballX == 2 &&
        ballY >= paddleY - 1 &&
        ballY <= paddleY + 1) {
        ballDirX = 1;   // bounce right
        score++;
    }

    // ── ball passed paddle ──
    if (ballX < 0) {
        lives--;
        if (lives <= 0) {
            gameRunning = false;
        } else {
            resetBall();
        }
    }

    // ── ball reaches right wall → bounce back ──
    if (ballX >= WIDTH - 1) {
        ballDirX = -1;
    }
}

// ── entry point ──────────────────────────────────────────────────────────────

int main() {
    srand((unsigned)time(nullptr));
    hideCursor();
    system("cls");

    setup();

    while (gameRunning) {
        draw();
        input();
        logic();
        Sleep(80);
    }

    gotoxy(0, HEIGHT + 4);
    cout << "\n=== GAME OVER ===  Score: " << score << "\n\n";
    return 0;
}