#ifndef _ANSI_H_
#define _ANSI_H_

void clrscr();

void clreol();

void gotoxy(int x, int y);

void underline(int enable);

void blink(int enable);

void inverse(int enable);

void hide_cursor();
void home_cursor();
int set_colors(char fg, char gb);
int set_color(char color);

#endif /* _ANSI_H_ */
