#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>             // _getch()
#include <time.h>
#include <windows.h>       // SetConsoleCursorPosition(), GetStdHandll, Sleep()

#define col GetStdHandle(STD_OUTPUT_HANDLE)         // 필수 // 콘솔창 색입히기
#define BLACK SetConsoleTextAttribute(col, 0x0000)      //검정색
#define DARK_BLUE SetConsoleTextAttribute(col, 0x0001 );      // 검파랑
#define GREEN SetConsoleTextAttribute(col, 0x0002 );      // 초록색
#define BLUE_GREEN SetConsoleTextAttribute(col, 0x0003 );      // 청록색
#define BLOOD SetConsoleTextAttribute(col, 0x0004 );      // 검붉은색
#define WINE SetConsoleTextAttribute(col, 0x0005);      // 보라색
#define GOLD SetConsoleTextAttribute(col, 0x0006);      // 금색
#define ORIGINAL SetConsoleTextAttribute(col, 0x0007);      // 밝은회색
#define GRAY SetConsoleTextAttribute(col, 0x0008);      // 회색
#define BLUE SetConsoleTextAttribute(col, 0x0009);      // 파란색
#define HIGH_GREEN SetConsoleTextAttribute(col, 0x000a);      // 연두색
#define SKY_BLUE SetConsoleTextAttribute(col, 0x000b);      // 하늘색
#define RED SetConsoleTextAttribute(col, 0x000c);      // 빨강색
#define PLUM SetConsoleTextAttribute(col, 0x000d);      // 자주색
#define YELLOW SetConsoleTextAttribute(col, 0x000e);      // 노랑색
#define WHITE SetConsoleTextAttribute(col, 0x000f);      // 하양색

#define height 20
#define width 80
static int i, j, q, bx, by, x, y, xy, array[height][width] ;


int H_rand(int h_rand_max , int re) {
    srand((unsigned int)time(NULL));   // time을 unsigned int 형으로 형변환 !
    int num = rand()+re;                  // 변수 num에 rand() 로 완전한 랜덤한 수를 넣어줌
    int randm = (int)num % 100;        // 변수 rand에 %를 사용하여 100이하의 수를 넣어줌
    if (randm > h_rand_max - 1) {        // RAND_MAX 에 배열의 제일 큰 수 (20-1) 를 넣어주고,
        if (randm > 80)  randm -= 81;  // 그 수보다 큰 수가 나오면 -81 을 해서 배열내 숫자가 들어가도록 맞춰 줌
        else if (randm > 70 && randm <= 80) randm -= 61;
        else if (randm > 60 && randm <= 70) randm -= 51;
        else if (randm > 50 && randm <= 60) randm -= 41;
        else if (randm > 40 && randm <= 50) randm -= 31;
        else if (randm > 30 && randm <= 40) randm -= 21;
        else if (randm > 20 && randm <= 30) randm -= 11;
    }
    if (randm == 0)     randm += 1;         // 테두리가 있는 0에 가지 않도록 설정
    else if (randm == h_rand_max - 1)       randm -= 1;         // 테두리가 있는 h_rand_max-1 에 가지 않도록 설정
    return randm;
}
int W_rand(int w_rand_max, int re) {
    srand((unsigned int)time(NULL));  // time을 unsigned int 형으로 형변환 !
    int num = rand()+re;                 // 변수 num에 rand() 로 완전한 랜덤한 수를 넣어줌
    int randm = (int)num % 100;       // 변수 rand에 %를 사용하여 100이하의 수를 넣어줌
    if (randm > w_rand_max) {      // RAND_MAX 에 배열의 제일 큰 수 (80-1) 를 넣어주고,
        randm -= 21;      // 그 수보다 큰 수가 나오면 -21 을 해서 배열내 숫자가 들어가도록 맞춰 줌
    }
    if (randm == 0)     randm += 1;         // 테두리가 있는 0에 가지 않도록 설정
    else if (randm == w_rand_max - 1)       randm -= 1;         // 테두리가 있는 h_rand_max-1 에 가지 않도록 설정
    return randm;
}

void gotoxy(int x, int y) {
    COORD pos = { x - 1, y - 1 };       // Prototype 선언
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos) ;    // Prototype 값대로 위치이동
}

int main()
{
    int score = 0;

    // ㅁ 틀 만들기
    for (i = 0; i < height; i++) {
        if (i > 0 && i < height - 1) {
            for (j = 0; j < width; j++) {
                if (j > 0 && j < width - 1) {
                    printf(" ");
                }
                else {
                    RED;
                    printf("+");
                }
            }
        }
        else {
            for (j = 0; j < width; j++) {
                BLUE;
                printf("+");
            }
        }
        printf("\n");
    }

    // message
    ORIGINAL;
    gotoxy(90, 2);      printf("■■■■ Control ■■■■");
    gotoxy(90, 3);      printf("W ↑ | S ↓ | A ← | F →");
    gotoxy(90, 4);      printf("       Exit : ESC");
    gotoxy(90, 6);      printf("■ Score : %d", score);



    int h, w, sum = 0; // 먹이 뿌리기 용도 !
    // 먹이 뿌리기
    for (int i = 0; i < height; i++) {      // 모든 배열이 0인지 확인
        for (int j = 0; j < width; j++) {
            if (array[i][j] != 0) {
                sum += array[i][j];     // 배열이 0이 아닌게 있다면 sum에 누적
            }
        }
    }
    if (sum == 0) {         // 만약, 모든 배열이 0 이면 먹이뿌리기
        for (int i = 0; i < 30; i++) {
            if (i % 5==0) {
                h = H_rand(height, i);
                w = W_rand(width, i);
                array[h][w] = 1;        // @와 1이 부딪치면 점수 올려야해서 !!
                gotoxy(w - 1, h - 1);       printf("*");        // 저 위치에 먹이 보여주기 !!
            }
        }
        sum = 0;
    }

    // @ 만들기
    x = 2, y = 2;
    gotoxy(x, y);

    while (1) {
        Sleep(100);                                     // 반복 시, 100ms 대기 
        bx = x;        by = y;                        // 이전 위치 저장
        if (_kbhit()) {                                  // 키보드 입력 있는지 확인
            xy = _getch();                            // 입력이 있다면 xy에 저장
        }

        if (xy == 83 || xy == 115) {        // s ↓
            if (y < height - 1)
                y += 1;
            else if (y == height - 1)
                y = 2;
            gotoxy(x, y);
            YELLOW;
            printf("@");
        }
        else if (xy == 78 || xy == 119) {       // w ↑
            if (y > 2)
                y -= 1;
            else if (y == 2)
                y = height - 1;
            gotoxy(x, y);
            YELLOW;
            printf("@");
        }
        else if (xy == 65 || xy == 97) {        // a ←
            if (x > 2)
                x -= 1;
            else if (x == 2)
                x = width-1;
            gotoxy(x, y);
            YELLOW;
            printf("@");
        }
        else if (xy == 68 || xy == 100) {       // d →
            if (x < width - 1)
                x += 1;
            else if (x == width - 1)
                x = 2;
            gotoxy(x, y);
            YELLOW;
            printf("@");
        }
        else if (xy == 27) {        // Esc
            break;
        }
        else {  // 다른 키를 누르면 멈춰.. 왜지?
            // xy = 가던방향 그대로 가게 하기 !!!
        }
        /*else {    // kbhit() 때문인지 계속 출력되는 것 으로 나옴..
            gotoxy(90,6);
            ORIGINAL;
            printf("Error : 조작법을 확인해주세요.");
            Sleep(1000);
            gotoxy(90, 6);
            printf("                                                               ");
        }*/

        // @(사용자)가 *(먹이) 와 부딪치면 점수10+ 배열0 만들기
        if (array[y - 1][x - 1] == 1) {
            score += 10;
            array[y - 1][x - 1] = 0;
            gotoxy(90, 6);      printf("■ Score : %d", score);
        }

        // 이전위치 (bx, by) 지우기
        gotoxy(bx, by);             
        printf(" ");
    }

    // 종료
    system("cls");

    gotoxy(15, 14);
    GOLD;
    printf("■■■■■■■■■■■■");
    gotoxy(15, 16);
    SKY_BLUE;
    printf(" 프로그램을 종료합니다.");
    gotoxy(15, 18);
    GOLD;
    printf("■■■■■■■■■■■■");
    
    gotoxy(1, 30);
    ORIGINAL;
    
    return 0;
}
