#include <stdio.h>
#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#define UP 72
#define DOWN 80
#define RIGHT 77
#define LEFT 75
#define Read(u) u = kbhit() ? getch() : u
#define tcsetattr(a, b, c)
#define SetupConsole() \
    SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), ENABLE_PROCESSED_OUTPUT | ENABLE_WRAP_AT_EOL_OUTPUT | ENABLE_VIRTUAL_TERMINAL_PROCESSING)
void getSize(int *x, int *y) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    *x = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    *y = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}
#else
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>
#define UP 65
#define DOWN 66
#define RIGHT 67
#define LEFT 68
#define Read(u) read(0, &u, 1)
#define SetupConsole() \
    struct termios z, o; \
    tcgetattr(0, &z); \
    o = z; \
    z.c_lflag &= ~ICANON; \
    z.c_cc[VMIN] = 0; \
    tcsetattr(0, TCSANOW, &z);
int GetTickCount() {
    struct timespec t;
    timespec_get(&t, TIME_UTC);
    return t.tv_sec * 1000 + t.tv_nsec / 1000000;
}
void getSize(int *x, int *y) {
    struct winsize w;
    ioctl(0, TIOCGWINSZ, &w);
    *x = w.ws_col;
    *y = w.ws_row;
}
#endif
#define g(x, y, u, v, s) for (int j = 0, X = x, Y = y; j < v && Y + j < h - X / w && Y >= 0 && X >= 0; ++j) memcpy(&f[Y + j][X], &s[j * u], u)
#define l(x, y, w, h, a, b, c, d) !((x - a > c && x >= a) || (a - x > w && a >= x) || (y - b > d && y >= b) || (b - y > h && b >= y))
#define f(x, y, z) p.y += z * d; strcpy(b, x); break
int main() {
    SetupConsole();
    printf("\x1b[?25l"); // hide cursor
    int w, W, h, H;
    getSize(&w, &h);
    int A = w * h / 100, l = GetTickCount(), g = 1, start = l;
    struct V {
        float x, y;
    } p = {w / 2, h / 2}, a[A], m[A];
    char u = 0, f[h + 1][w], b[13] = " /\\ /  \\ vv ";
    while (1) {
        float d = (GetTickCount() - l) * .001;
        Read(u); // read input
        l = GetTickCount();
        memset(f, ' ', h * w); // clear the screen
        switch (u) {           // could be minified...
        case UP:
            f(" /\\ /  \\ vv ", y, -20);
        case DOWN:
            f(" ^^ \\  / \\/ ", y, 20);
        case RIGHT:
            f("<\\  <  ></  ", x, 40);
        case LEFT:
            f("  /><  >  \\>", x, -40);
        }
        p.x = p.x < 4 ? 4 : p.x >= w - 4 ? w - 4 : p.x; // make sure the player is in the screen (horizontally)
        p.y = p.y < 2 ? 2 : p.y >= h - 3 ? h - 3 : p.y; // make sure the player is in the screen (vertically)
        for (int i = A - 1; i--;) {
            *f[h] = 0;
            struct V *e = &a[i], *z = &m[i];
            e->x += d * z->x; // move the asteroid in the x direction
            e->y += d * z->y; // move the asteroid in the y direction
            e->x < 0 - 3 || e->x >= w + 3 || e->y >= h + 2 || g ? e->y = -rand() % h * (1 + g), e->x = rand() % w, z->x = -8 + rand() % 15, z->y = 10 + rand() % 5 : 0;
            if (l(p.x, p.y, 4, 3, e->x, e->y, 3, 2)) { // if player hit an asteroid
                tcsetattr(0, TCSADRAIN, &o);           // restore the terminal
                exit(0);                               // exit the program
            };
            g(e->x, e->y, 3, 2, "OOOOOO"); // draw the asteroid
        }
        g(p.x, p.y, 4, 3, b);                                                                                                               // draw the player
        for (int i = -2, j = 1e7, k, K = 0; i <= 2; i++, j /= 10, k = (l - start) / j % 10, K = k | K) f[1][w / 2 + i] = K ? '0' + k : ' '; // draw the score
        getSize(&W, &H);                                                                                                                    // get the new screen size
        if (W != w || H < h) exit(printf("\033[0;31m\nPlease don't resize the screen, it will break the program\033[0m\n"));                // make sure the screen is not resized besides getting higher
        else printf("\033[0;4H%s", &f[0][4]);                                                                                               // print the screen
        while (GetTickCount() - l < 10);                                                                                                    // wait for a bit
        g = 0;
    }
}