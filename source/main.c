#define PI 3.14159265

#include <3ds.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> //memset

#include "costable.h"
#include "draw.h"
#include "minlib.h"
#include "timing.h"

typedef u8 angle_t;

int main(int argc, char **argv)
{
	int i; //Generic iterator

	//Initialize services
	srvInit();
	aptInit();
	hidInit(NULL);
	gfxInitDefault();
	
	consoleInit(GFX_BOTTOM, NULL); //Show a console on the bottom screen
	
	srand(getSystemTick()); //Seed rand with the time
	
	u8 *fbTop, *fbBot; //Framebuffers
	
	// Main loop
	angle_t angle = 0;
	angle_t tmpAngle = angle;
	u8 regions = 6;
	s8 speed = 1;
	while (aptMainLoop())
	{
		//Scan all the inputs. This should be done once for each frame
		hidScanInput();

		//hidKeysDown returns information about which buttons have been just pressed (and they weren't in the previous frame)
		u32 kDown = hidKeysDown();

		if (kDown & KEY_START) break; // break in order to return to hbmenu
		
		//Clear screens
		fbTop = gfxGetFramebuffer(GFX_TOP, GFX_LEFT, NULL, NULL);
		memset(fbTop, 0, 240 * 400 * 3);
		//fbBot = gfxGetFramebuffer(GFX_BOTTOM, 0, NULL, NULL);
		//memset(fbBot, 0, 240 * 320 * 3);
		
		printf("\x1b[0;10H%s", "Press Start to exit.");
		printf("\x1b[1;1H%s", "Remove region <");
		printf("\x1b[2;1H%s", "Add region    >");
		printf("\x1b[1;20H%s", "^ Increase speed");
		printf("\x1b[2;20H%s", "v Decrease speed");
		printf("\x1b[5;0HBinary Angle %3d", angle);
		printf("\x1b[6;0HSin %9f", sin(PI/128 * tmpAngle));
		printf("\x1b[7;0HCos %9f", cos(PI/128 * tmpAngle));
		printf("\x1b[5;20HSpeed        %3d", speed);
		printf("\x1b[6;20HRegions      %3d", regions);
		
		//Draw lines
		tmpAngle = angle;
		for (i = 0; i < regions; i++) {
			drawLine(fbTop, 200, 120, 200 + 234*cos(PI/128 * tmpAngle), 120 + 234*sin(PI/128 * tmpAngle), 255, 255, 255);
			tmpAngle += (256 / regions);
		}
		//Rotate
		if (speed < 0) {
			for (i = 0; i > speed; i--) angle--;
		} else {
			for (i = 0; i < speed; i++) angle++;
		}
		
		if (kDown & KEY_UP) speed++;
		if (kDown & KEY_DOWN) speed--;
		if (kDown & KEY_LEFT) regions--;
		if (kDown & KEY_RIGHT) regions++;
		
		gfxFlushBuffers();
		gfxSwapBuffers();
		
		//Wait for VBlank
		gspWaitForVBlank();
	}

	// Exit services
	gfxExit();
	hidExit();
	aptExit();
	srvExit();
	return 0;
}
