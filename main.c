#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <termios.h>
#include <unistd.h>
int t()
{
       struct timeval t;
       gettimeofday(&t, 0);
       return t.tv_usec / 1000 + t.tv_sec * 1000;
}

#define g(x, y, u, v, s)                                                                  \
       for (int j = 0, X = x, Y = y; j < v && Y + j < h - X / w && Y >= 0 && X >= 0; ++j) \
       memcpy(&f[Y + j][X], &s[j * u], u)
#define l(x, y, w, h, a, b, c, d) \
       !((x - a > c && x >= a) || (a - x > w && a >= x) || (y - b > d && y >= b) || (b - y > h && b >= y))
#define f(x, y, z)   \
       y += z * d;   \
       strcpy(b, x); \
       break

int main()
{
       struct termios z, o;
       tcgetattr(0, &z);
       o = z;
       z.c_lflag &= ~ICANON & ~ECHO;
       z.c_cc[VMIN] = 0;
       tcsetattr(0, TCSANOW, &z);
       struct winsize v;
       ioctl(STDOUT_FILENO, TIOCGWINSZ, &v);
       int h = v.ws_row, w = v.ws_col, A = w * h / 100, l = t(), g = 1, i, c = 0, L;
       struct V
       {
              float x, y;
       } p = {w / 2, h / 2}, a[A], m[A];
       char u = 0, f[h + 1][w], b[13] = " /\\ /  \\ vv ";
       while (1)
       {
              float d = (t() - l) * .001;
              read(0, &u, 1);
              l = t();
              c += 15;
              i = h * w - 1;
       K:
              L = c * d;
              L = abs(((i / w) - L) * (i % w) + h * w);
              (*f)[i] = L % 3 + L % 5 + L % 7 + L % 11 + L % 13 + L % 17 + L % 19 > 14 ? 32 : 46;
              if (i--)
                     goto K;
              switch (u) // could be minified...
              {
              case 65:
                     f(" /\\ /  \\ vv ", p.y, -20);
              case 66:
                     f(" ^^ \\  / \\/ ", p.y, 20);
              case 67:
                     f("<\\  <  ></  ", p.x, 40);
              case 68:
                     f("  /><  >  \\>", p.x, -40);
              }
              p.x = p.x < 4 ? 4 : p.x >= w - 4 ? w - 4
                                               : p.x;
              p.y = p.y < 1 ? 1 : p.y >= h - 3 ? h - 3
                                               : p.y;
              i = A - 1;
       L:
              *(f[h]) = 0;
              struct V *e = &a[i], *z = &m[i];
              e->x += d * z->x;
              e->y += d * z->y;
              e->x < 0 - 3 || e->x >= w + 3 || e->y >= h + 2 || g ? e->y = -rand() % h * (1 + g),
                                                                    e->x = rand() % w,
                                                                    z->x = -8 + rand() % 15,
                                                                    z->y = 10 + rand() % 5 : 0;
              if (l(p.x, p.y, 4, 3, e->x, e->y, 3, 2))
              {
                     tcsetattr(0, TCSADRAIN, &o);
                     exit(0);
              };
              g(e->x, e->y, 3, 2, "OOOOOO");
              if (i--)
                     goto L;
              g(p.x, p.y, 4, 3, b);
              printf("\33[0;4H%s", &f[0][4]);
              while (t() - l < 9)
                     ;
              g = 0;
       }
}
