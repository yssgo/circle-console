///////////////////////
// circle-console.cpp
//
#include <windows.h>
#include <conio.h>
#include <iostream>
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "user32.lib")

int main();
BOOL hello_my_console(FILE** fpIn, FILE** fpOut);
void bybye_my_console(FILE* fpIn, FILE* fpOut);
int getkey();
void gotoxy(int x, int y);

class MY_CIRCLE
{
public:
    int left, top, right, bottom; //좌우상하 좌표
    MY_CIRCLE(int l, int t, int r, int b) : left(l), top(t), right(r), bottom(b) {
        ;
    }
    void do_draw()
    {
        HWND win = ::GetForegroundWindow();
        HDC hdc = ::GetWindowDC(win);
        ::Ellipse(hdc, left, top, right, bottom);
        ::ReleaseDC(win, hdc);
    }
    MY_CIRCLE Clone()
    {
        return *this;
    }
    MY_CIRCLE &CloneR()
    {
        return *this;
    }
    MY_CIRCLE* CloneP()
    {
        return this;
    }
}; // class

int main()
{
    /////////////
    FILE* fpIn, * fpOut;
    hello_my_console(&fpIn, &fpOut);
    /////////////

    MY_CIRCLE c1(100, 100, 180, 180);
    MY_CIRCLE c2(200, 200, 300, 300);
    c1.do_draw();
    c2.do_draw();

    gotoxy(10, 25);
    std::cout << "Press any key to QUIT ... ";
    getkey();

    /////////////
    bybye_my_console(fpIn, fpOut);
    /////////////

    return 0;
}

BOOL hello_my_console(FILE** fpIn, FILE** fpOut)
{
    if (!FreeConsole()) {
        std::perror("(hello_my_console, FreeConsole)");
        return FALSE;
    }
    if (!AllocConsole()) {
        std::perror("(hello_my_console, AllocConsole)");
        return FALSE;
    }

    *fpIn = nullptr;
    *fpOut = nullptr;
    ::freopen_s(&*fpIn, "CONIN$", "r", stdin);
    ::freopen_s(&*fpOut, "CONOUT$", "w", stdout);
    _ASSERT(*fpIn == stdin);
    _ASSERT(*fpOut == stdout);
    //[출처] Windows / C++ - AllocConsole로 할당한 콘솔과 CRT 함수 연동|작성자 techshare
    //  https://blog.naver.com/techshare/223578470671?trackingCode=rss

    return TRUE;
}

void bybye_my_console(FILE* fpIn, FILE* fpOut)
{
    if (fpIn) {
        std::fclose(fpIn);
    }
    if (fpOut) {
        std::fclose(fpOut);
    }
}

int getkey()
{
    int key;
    key = _getch();
    if (key == 0xe0 || key == 0x00) {
        key = _getch() + 256;
    }
    return key;
}

void gotoxy(int x, int y)
{
    COORD xy;
    xy.X = (SHORT)x;
    xy.Y = (SHORT)y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), xy);
}
