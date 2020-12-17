#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>             // _getch()
#include <time.h>
#include <windows.h>       // SetConsoleCursorPosition(), GetStdHandll, Sleep()

#define col GetStdHandle(STD_OUTPUT_HANDLE)         // �ʼ� // �ܼ�â ��������
#define BLACK SetConsoleTextAttribute(col, 0x0000)      //������
#define DARK_BLUE SetConsoleTextAttribute(col, 0x0001 );      // ���Ķ�
#define GREEN SetConsoleTextAttribute(col, 0x0002 );      // �ʷϻ�
#define BLUE_GREEN SetConsoleTextAttribute(col, 0x0003 );      // û�ϻ�
#define BLOOD SetConsoleTextAttribute(col, 0x0004 );      // �˺�����
#define WINE SetConsoleTextAttribute(col, 0x0005);      // �����
#define GOLD SetConsoleTextAttribute(col, 0x0006);      // �ݻ�
#define ORIGINAL SetConsoleTextAttribute(col, 0x0007);      // ����ȸ��
#define GRAY SetConsoleTextAttribute(col, 0x0008);      // ȸ��
#define BLUE SetConsoleTextAttribute(col, 0x0009);      // �Ķ���
#define HIGH_GREEN SetConsoleTextAttribute(col, 0x000a);      // ���λ�
#define SKY_BLUE SetConsoleTextAttribute(col, 0x000b);      // �ϴû�
#define RED SetConsoleTextAttribute(col, 0x000c);      // ������
#define PLUM SetConsoleTextAttribute(col, 0x000d);      // ���ֻ�
#define YELLOW SetConsoleTextAttribute(col, 0x000e);      // �����
#define WHITE SetConsoleTextAttribute(col, 0x000f);      // �Ͼ��

#define height 20
#define width 80
static int i, j, q, bx, by, x, y, xy, array[height][width] ;


int H_rand(int h_rand_max , int re) {
    srand((unsigned int)time(NULL));   // time�� unsigned int ������ ����ȯ !
    int num = rand()+re;                  // ���� num�� rand() �� ������ ������ ���� �־���
    int randm = (int)num % 100;        // ���� rand�� %�� ����Ͽ� 100������ ���� �־���
    if (randm > h_rand_max - 1) {        // RAND_MAX �� �迭�� ���� ū �� (20-1) �� �־��ְ�,
        if (randm > 80)  randm -= 81;  // �� ������ ū ���� ������ -81 �� �ؼ� �迭�� ���ڰ� ������ ���� ��
        else if (randm > 70 && randm <= 80) randm -= 61;
        else if (randm > 60 && randm <= 70) randm -= 51;
        else if (randm > 50 && randm <= 60) randm -= 41;
        else if (randm > 40 && randm <= 50) randm -= 31;
        else if (randm > 30 && randm <= 40) randm -= 21;
        else if (randm > 20 && randm <= 30) randm -= 11;
    }
    if (randm == 0)     randm += 1;         // �׵θ��� �ִ� 0�� ���� �ʵ��� ����
    else if (randm == h_rand_max - 1)       randm -= 1;         // �׵θ��� �ִ� h_rand_max-1 �� ���� �ʵ��� ����
    return randm;
}
int W_rand(int w_rand_max, int re) {
    srand((unsigned int)time(NULL));  // time�� unsigned int ������ ����ȯ !
    int num = rand()+re;                 // ���� num�� rand() �� ������ ������ ���� �־���
    int randm = (int)num % 100;       // ���� rand�� %�� ����Ͽ� 100������ ���� �־���
    if (randm > w_rand_max) {      // RAND_MAX �� �迭�� ���� ū �� (80-1) �� �־��ְ�,
        randm -= 21;      // �� ������ ū ���� ������ -21 �� �ؼ� �迭�� ���ڰ� ������ ���� ��
    }
    if (randm == 0)     randm += 1;         // �׵θ��� �ִ� 0�� ���� �ʵ��� ����
    else if (randm == w_rand_max - 1)       randm -= 1;         // �׵θ��� �ִ� h_rand_max-1 �� ���� �ʵ��� ����
    return randm;
}

void gotoxy(int x, int y) {
    COORD pos = { x - 1, y - 1 };       // Prototype ����
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos) ;    // Prototype ����� ��ġ�̵�
}

int main()
{
    int score = 0;

    // �� Ʋ �����
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
    gotoxy(90, 2);      printf("����� Control �����");
    gotoxy(90, 3);      printf("W �� | S �� | A �� | F ��");
    gotoxy(90, 4);      printf("       Exit : ESC");
    gotoxy(90, 6);      printf("�� Score : %d", score);



    int h, w, sum = 0; // ���� �Ѹ��� �뵵 !
    // ���� �Ѹ���
    for (int i = 0; i < height; i++) {      // ��� �迭�� 0���� Ȯ��
        for (int j = 0; j < width; j++) {
            if (array[i][j] != 0) {
                sum += array[i][j];     // �迭�� 0�� �ƴѰ� �ִٸ� sum�� ����
            }
        }
    }
    if (sum == 0) {         // ����, ��� �迭�� 0 �̸� ���̻Ѹ���
        for (int i = 0; i < 30; i++) {
            if (i % 5==0) {
                h = H_rand(height, i);
                w = W_rand(width, i);
                array[h][w] = 1;        // @�� 1�� �ε�ġ�� ���� �÷����ؼ� !!
                gotoxy(w - 1, h - 1);       printf("*");        // �� ��ġ�� ���� �����ֱ� !!
            }
        }
        sum = 0;
    }

    // @ �����
    x = 2, y = 2;
    gotoxy(x, y);

    while (1) {
        Sleep(100);                                     // �ݺ� ��, 100ms ��� 
        bx = x;        by = y;                        // ���� ��ġ ����
        if (_kbhit()) {                                  // Ű���� �Է� �ִ��� Ȯ��
            xy = _getch();                            // �Է��� �ִٸ� xy�� ����
        }

        if (xy == 83 || xy == 115) {        // s ��
            if (y < height - 1)
                y += 1;
            else if (y == height - 1)
                y = 2;
            gotoxy(x, y);
            YELLOW;
            printf("@");
        }
        else if (xy == 78 || xy == 119) {       // w ��
            if (y > 2)
                y -= 1;
            else if (y == 2)
                y = height - 1;
            gotoxy(x, y);
            YELLOW;
            printf("@");
        }
        else if (xy == 65 || xy == 97) {        // a ��
            if (x > 2)
                x -= 1;
            else if (x == 2)
                x = width-1;
            gotoxy(x, y);
            YELLOW;
            printf("@");
        }
        else if (xy == 68 || xy == 100) {       // d ��
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
        else {  // �ٸ� Ű�� ������ ����.. ����?
            // xy = �������� �״�� ���� �ϱ� !!!
        }
        /*else {    // kbhit() �������� ��� ��µǴ� �� ���� ����..
            gotoxy(90,6);
            ORIGINAL;
            printf("Error : ���۹��� Ȯ�����ּ���.");
            Sleep(1000);
            gotoxy(90, 6);
            printf("                                                               ");
        }*/

        // @(�����)�� *(����) �� �ε�ġ�� ����10+ �迭0 �����
        if (array[y - 1][x - 1] == 1) {
            score += 10;
            array[y - 1][x - 1] = 0;
            gotoxy(90, 6);      printf("�� Score : %d", score);
        }

        // ������ġ (bx, by) �����
        gotoxy(bx, by);             
        printf(" ");
    }

    // ����
    system("cls");

    gotoxy(15, 14);
    GOLD;
    printf("�������������");
    gotoxy(15, 16);
    SKY_BLUE;
    printf(" ���α׷��� �����մϴ�.");
    gotoxy(15, 18);
    GOLD;
    printf("�������������");
    
    gotoxy(1, 30);
    ORIGINAL;
    
    return 0;
}
