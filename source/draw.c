#include <math.h>
#include <stdbool.h>
#include "draw.h"
#include "minlib.h"

u16 getScreenWidth(u8* fb) {
	if (fb == gfxGetFramebuffer(GFX_BOTTOM, 0, NULL, NULL)) {
		return 320;
	} else {
		return 400;
	}
}

bool isInBounds(u8* fb, s16 x, s16 y) {
	if (x < 0) return false;
	if (y < 0) return false;
	if (x >= getScreenWidth(fb)) return false;
	if (y > 239) return false;
	return true;
}

void drawPixel(u8* fb, s16 x, s16 y, u8 r, u8 g, u8 b, u8 a) {
	if (!isInBounds(fb, x, y)) return;
	
	//Transparent pixel
	if (a == 0) return;
	
	u32 index = 3 * ((x + 1) * 240 - y - 1); //Get the address of the pixel
	if (a == 255) { //Solid pixel
		fb[index] = b;
		fb[index + 1] = g;
		fb[index + 2] = r;
	} else { //Alpha blending
		float alpha_ratio = a/255.0f;
		fb[index] = fb[index] * (1 - alpha_ratio) + b * alpha_ratio;
		fb[index + 1] = fb[index + 1] * (1 - alpha_ratio) + g * alpha_ratio;
		fb[index + 2] = fb[index + 2] * (1 - alpha_ratio) + r * alpha_ratio;
	}
}

//Wu's Line Algorithm
//Optimized with integer endpoints
void drawLine(u8* fb, s16 x1, s16 y1, s16 x2, s16 y2, u8 r, u8 g, u8 b) {
	bool steep = absVal(y2 - y1) > absVal(x2 - x1);
	if (steep) {
		swap(&x1, &y1);
		swap(&x2, &y2);
	}
	if (x1 > x2) {
		swap(&x1, &x2);
		swap(&y1, &y2);
	}
	
	s16 dx = x2 - x1;
	s16 dy = y2 - y1;
	float m = (float)dy / (float)dx;
	
	int i;
	float fPart, inter = y1;
	for (i = x1; i < x2; i++) {
		fPart = inter - (int)inter;
		if (steep) {
			drawPixel(fb, inter, i, r, g, b, (1 - fPart)*255.0f);
			drawPixel(fb, inter+1, i, r, g, b, fPart*255.0f);
		} else {
			drawPixel(fb, i, inter, r, g, b, (1 - fPart)*255.0f);
			drawPixel(fb, i, inter+1, r, g, b, fPart*255.0f);
		}
		inter += m;
	}
}

void drawHLine(u8* fb, s16 row, s16 x1, s16 x2, u8 r, u8 g, u8 b, u8 a) {
	if (x1 > x2) swap(&x1, &x2);
	
	int i;
	for (i = x1; i <= x2; i++) drawPixel(fb, i, row, r, g, b, a);
}

void drawVLine(u8* fb, s16 col, s16 y1, s16 y2, u8 r, u8 g, u8 b, u8 a) {
	if (y1 > y2) swap(&y1, &y2);
	
	int i;
	for (i = y1; i <= y2; i++) drawPixel(fb, col, i, r, g, b, a);
}