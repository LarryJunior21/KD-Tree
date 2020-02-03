#ifndef TAJ_H_INCLUDED
#define TAJ_H_INCLUDED

#include <conio.h>
#include <stdarg.h>
#include <windef.h>
#include <winbase.h>
#include <wincon.h>
#include <string.h>
#include <stdlib.h>

//---------------------------MYCONIO---------------------------------
void gotoxy(int x, int y)
{
  COORD c ;
  c.X = x - 1;
  c.Y = y - 1;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void textattr(int _attr)
{
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), _attr);
}

void textbackground(int _color)
{
  CONSOLE_SCREEN_BUFFER_INFO Info ;
  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
  textattr((Info.wAttributes & 0x0F) | (_color<<4));
}

void textcolor(int _color) {
  CONSOLE_SCREEN_BUFFER_INFO Info ;
  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
  textattr((Info.wAttributes & 0xF0) | _color);
}

int wherex() // retorna coordenada x do cursor
{
  CONSOLE_SCREEN_BUFFER_INFO Info;
  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
  return Info.dwCursorPosition.X + 1;
}

int wherey() // retorna coordenada y do cursor
{
  CONSOLE_SCREEN_BUFFER_INFO Info;
  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
  return Info.dwCursorPosition.Y + 1;
}

void clrscr(void)
{
  COORD coord = { 0, 0 };
  DWORD dwWritten, dwSize;
  HANDLE hScreen=GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_SCREEN_BUFFER_INFO Info;

  if(GetConsoleScreenBufferInfo(hScreen, &Info))
  {
      dwSize = Info.dwSize.X * Info.dwSize.Y;
      FillConsoleOutputCharacter (hScreen, ' ', dwSize, coord, &dwWritten);
      FillConsoleOutputAttribute (hScreen, Info.wAttributes, dwSize, coord, &dwWritten);
      gotoxy (1, 1);
  }
}
//------------------------------FIM MYCONIO-------------------------------------
/*
void lerString(char string[], int tamAtual, int tamMax)
{
    char c;
    int i, j, x, y;
    i = j = tamAtual;
    c = getch();
                          // enter
    while(c != 13 && c != 27)
    {
        if(c == -32 || c == 0) //teclas especiais
        {
            c = getch();
            switch(c)
            {
                case 77: // seta para direita
                    break;
                case 75: // seta para esquerda
                    break;
            }
        }
        else
        {
            if(c == 8) // backspace
            {
                x = wherex();
                if(x > 1)
                {
                    y = wherey();
                    gotoxy(x-1, y);
                    printf(" ");
                    gotoxy(x-1, y);
                    if(i > 0)
                        i--;
                }
            }
            else if(i < tamMax-1)
            {
                string[i++] = c;
                printf("%c",c);
            }
            else
                c = 13;
        }
        c = getch();
    }
    string[i] = '\0';
    printf("\n");
}
*/
#endif // TAJ_H_INCLUDED
