#include <iostream>
#include<Windows.h>
using namespace std;

void goToXY(int x, int y) {
    COORD pos = { x, y };
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(output, pos);
}

const int width = 17;
const int height = 10;
const int maxLenghtSnake = (width - 3) * (height - 2);

const int _up = 0;
const int _down = 1;
const int _left = 2;
const int _right = 3;

int snakeDir = _up;

bool isRunning = true;

char map[] =
"################\n"
"#              #\n"
"#              #\n"
"#              #\n"
"#              #\n"
"#              #\n"
"#              #\n"
"#              #\n"
"#              #\n"
"################\n";

char snake = 'O';
int snakeX[maxLenghtSnake] = { 0 };
int snakeY[maxLenghtSnake] = { 0 };
int snakeLenght = 1;

int foodX = 1 + (rand() % (width - 3));
int foodY = 1 + (rand() % (height - 2));
char food = '*';

int main() {
    snakeX[0] = width / 2;
    snakeY[0] = height / 2;
    int time = clock();

    while (isRunning) {
        if (GetKeyState('W') & 0x8000) {
            if (snakeDir != _down) {
                snakeDir = _up;
            }
        }

        if (GetKeyState('A') & 0x8000) {
            if (snakeDir != _right) {
                snakeDir = _left;
            }
        }

        if (GetKeyState('S') & 0x8000) {
            if (snakeDir != _up) {
                snakeDir = _down;
            }
        }

        if (GetKeyState('D') & 0x8000) {
            if (snakeDir != _left) {
                snakeDir = _right;
            }
        }

        if ((clock() - time) / CLOCKS_PER_SEC >= 0.5) {
            time = clock();

            if (snakeX[0] == foodX && snakeY[0] == foodY) {
                ++snakeLenght;
                foodX = 1 + (rand() % (width - 3));
                foodY = 1 + (rand() % (height - 2));
            }

            for (int i = snakeLenght - 2; i >= 0; --i) {
                snakeX[i + 1] = snakeX[i];
                snakeY[i + 1] = snakeY[i];
            }

            if (snakeDir == _up) {
                --snakeY[0];
            }

            if (snakeDir == _down) {
                ++snakeY[0];
            }

            if (snakeDir == _right) {
                ++snakeX[0];
            }
            
            if (snakeDir == _left) {
                --snakeX[0];
            }
            
            if (snakeX[0] == 0 || snakeY[0] == 0 || snakeX[0] == width - 2 || snakeY[0] == height - 1) {
                isRunning = false;
            }
            for (int i = 1; i < snakeLenght; ++i) {
                if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i]) {
                    isRunning = false;
                    i = snakeLenght;
                }
            }

            goToXY(0, 0);
            cout << "Lenght: " << snakeLenght << endl;
            map[foodY * width + foodX] = food;
            for (int i = 0; i < snakeLenght; ++i) {
                map[snakeY[i] * width + snakeX[i]] = snake;
            }
            cout << map;
            for (int i = 0; i < snakeLenght; ++i) {
                map[snakeY[i] * width + snakeX[i]] = ' ';
            }
        }
    }
    goToXY(1, height / 2);
    cout << "You score = " << snakeLenght;
    goToXY(width, height);
}