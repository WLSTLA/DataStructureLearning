#include <stdio.h>
#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>
using namespace std;

int len;
struct Dot {
    int x;
    int y;
    char c;
}a[10000000];
int vis[10000000];
char c[5] = { 35, 36, 37, 38, 79 };
string s = "/\\";
int n;
string me = "Merry Christmas!";
string fm = "To My Angle LinJuanAn!";

void getcur(short int x, short int y)//移动光标函数 
{
    COORD pos = { x,y };//定义一个屏幕上的座标 
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(handle, pos);;
}

void goprint(int x, int y, char c) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), rand() % 16);
    getcur(x, y); printf("%c", c); //getcur(0,row);//消除光标影响 
}



void del(int x, int y)
{
    getcur(x, y); printf(" ");
}


int main() {
    system("color 3F");
    cout << "请输入你喜欢的一个数字（10 - 17），并将窗口最大化：";
    cin >> n;
    cout << endl;
    system("CLS");
    int Layer = 2 * n - 1;
    int Space = 2 * n - 2;
    for (int i = 1; i <= Layer; ++i) {
        if (i & 1) {
            for (int j = 0; j < 2 * i; j += 2) {
                a[len].x = j + Space + 30, a[len].y = i + 5, a[len++].c = c[rand() % 5];
            }
            Space -= 2;
        }
        else {
            int r = 0;
            for (int j = 0; j < 2 * i; j += 2) {
                a[len].x = j + Space + 31, a[len].y = i + 5, a[len++].c = s[r];
                r = (r + 1) % 2;
            }
        }
    }
    for (int i = 0; i < Layer / 3 + 1; ++i) {
        a[len].x = Layer + 29, a[len].y = i + 6 + Layer, a[len++].c = '|';
        a[len].x = Layer + 30, a[len].y = i + 6 + Layer, a[len++].c = '|';
    }
    for (int i = 0; i < me.length(); ++i) {
        a[len].x = Layer - 1 + i + 30;
        a[len].y = Layer / 3 + 10 + Layer;
        a[len++].c = me[i];
    }
    for (int i = 0; i < fm.length(); ++i) {
        a[len].x = Layer - 1 + i + 30;
        a[len].y = Layer / 3 + 11 + Layer;
        a[len++].c = fm[i];
    }
    while (1) {
        int i = rand() % len;
        if ((a[i].c == '\\' || a[i].c == '/') && vis[i]) {
            continue;
        }
        goprint(a[i].x, a[i].y, a[i].c);
        vis[i] = 1;
    }
}
