#ifndef DRAW_H
#define DRAW_H

#include <3ds.h>
#include <stdbool.h>

u16 getScreenWidth(u8* fb);
bool isInBounds(u8* fb, s16 x, s16 y);
void drawPixel(u8* fb, s16 x, s16 y, u8 r, u8 g, u8 b, u8 a);
void drawLine(u8* fb, s16 x1, s16 y1, s16 x2, s16 y2, u8 r, u8 g, u8 b);
void drawHLine(u8* fb, s16 row, s16 x1, s16 x2, u8 r, u8 g, u8 b, u8 a);
void drawVLine(u8* fb, s16 col, s16 y1, s16 y2, u8 r, u8 g, u8 b, u8 a);

#endif