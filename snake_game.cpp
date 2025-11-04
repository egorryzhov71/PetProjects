#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>


bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitx, fruity, score;
int tailx[100], taily[100];
int nTail;
enum eDirection{STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;


void clearScreen(){
    std::cout << "\033[2J\033[1;1H";
}

bool kbhit() {
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF) {
        ungetc(ch, stdin);
        return true;
    }

    return false;
}

char getch() {
    char buf = 0;
    struct termios old = {0};
    
    if (tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    
    if (tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    
    if (read(0, &buf, 1) < 0)
        perror("read()");
    
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    
    if (tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
    
    return buf;
}

void Setup(){
    gameOver = false;
    dir = STOP;
    x = width / 2 - 1 ;
    y = height / 2 - 1;
    fruitx = rand() % width;
    fruity = rand() % height;
    score = 0;
}

void Draw(){
    system("clear");
    for (int i  = 0; i < width + 1; i++)
        std::cout << "#";
    std::cout << std::endl;
    
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            if (j == 0 || j == width- 1)
                std::cout << "#";
            if (i == y && j == x)
                std::cout << "@";
            else if (i == fruity && j == fruitx)
                std::cout << "F";
            else {
                bool print = false;
                for (int k = 0; k < nTail; k++){
                    if (tailx[k] == j && taily[k] == i){
                        print = true;
                        std::cout << "0";
                    }
                }
                if (!print)
                std::cout << " ";
           }
        }
    std::cout << std::endl;
}
    for (int i  = 0; i < width + 1; i++)
        std::cout << "#";
    std::cout << std::endl;
    std::cout << "Счет: " << score << std::endl;
    
}

void Input(){
    if (kbhit()){
        switch (getch()){
            case 'a':
                dir = LEFT;
                break;
            case 'd':
                dir = RIGHT;
                break;
            case 'w':
                dir = UP;
                break;
            case 's':
                dir = DOWN;
                break;
            case 'x':
                gameOver = true;
                break;
        }
    }

    if (x > width || x < 0 || y > height || y < 0){
        gameOver = true;
    }
    
    for (int i = 0; i < nTail; i++){
        if (tailx[i] == x && taily[i] == y){
            gameOver = true;
            std::cout << "Игра окончена." << std::endl;
        }
    }
    
    if (x == fruitx && y == fruity){
        score += 1;
        fruitx = rand() % width;
        fruity = rand() % height;
        nTail += 1;
    }
}
            

void Logic(){
    int prevx = tailx[0];
    int prevy = taily[0];
    int prev2x, prev2y;
    tailx[0] = x;
    taily[0] = y;
    for (int i = 1; i < nTail; i++){
        prev2x = tailx[i];
        prev2y = taily[i];
        tailx[i] = prevx;
        taily[i] = prevy;
        prevx = prev2x;
        prevy = prev2y;
    }
    switch(dir){
        case LEFT:
            x --;
            break;
        case RIGHT:
            x ++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y ++;
            break;
    }
}


int main(){
    Setup();
    while (!gameOver){
        Draw();
        Input();
        Logic();
        usleep(200000);
    }

    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag |= (ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &term);

    std::cout << "==============================" << std::endl;
    std::cout << "       Игра закончилась!" << std::endl;
    std::cout << "       Финальный счет: " << score << std::endl;
    std::cout << "==============================" << std::endl;

}