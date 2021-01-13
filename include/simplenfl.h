// SimpleNFL - Version 1.7
// By Pipewarp 
// With Help from KonPet, PolyMars and ngawung
// https://github.com/PipeWarp/SimpleNFL/
// 
// Licensed under Creative Commons Attribution-NonCommercial 3.0
// Read it here: https://github.com/PipeWarp/SimpleNFL/blob/master/LICENSE
//
// The Docs/wiki is in the github repository
// Have fun!

#pragma once

#include <nds.h>
#include "nf_lib.h"

#ifdef __cplusplus
namespace SNF {
#endif

enum KeyPhase { release, press, held };

enum Swipe { SwipeRight, SwipeLeft, SwipeUp, SwipeDown };

touchPosition Stylus;
touchPosition PrevStylus; // previous frame stylus position

// store stylus position for swipe gesture
int startX;
int startY;

// quick load gfx and pallete to ram and vram
void loadsprite(int screen, int ramslot, int vramslot, int width, int height, const char *dir, const char *dir2, bool transflag) {
    NF_LoadSpriteGfx(dir, ramslot, width, height);
    NF_LoadSpritePal(dir2, ramslot);
    NF_VramSpriteGfx(screen, ramslot, vramslot, transflag);
    NF_VramSpritePal(screen, ramslot, vramslot);
}

// quick load gfx and pallete to ram and vram3D
void loadsprite3D(int ramslot, int vramslot, int width, int height, const char *dir, const char *dir2, bool transflag) {
    NF_LoadSpriteGfx(dir, ramslot, width, height);
    NF_LoadSpritePal(dir2, ramslot);
    NF_Vram3dSpriteGfx(ramslot, vramslot, transflag);
    NF_Vram3dSpritePal(ramslot, vramslot);
}

// unload gfx and pallete in ram and vram
void unloadsprite(int screen, int ramslot, int vramslot) {
    // ram
    NF_UnloadSpriteGfx(ramslot);
    NF_UnloadSpritePal(ramslot);

    // vram
    NF_FreeSpriteGfx(screen, vramslot);
}

// unload gfx and pallete in ram and vram3D
void unloadsprite3D(int ramslot, int vramslot) {
    // ram
    NF_UnloadSpriteGfx(ramslot);
    NF_UnloadSpritePal(ramslot);

    // vram3D
    NF_Free3dSpriteGfx(vramslot);
}

// quick load font and create font layer
void loadfont(const char *file, const char *fontname, int width, int height, int rot, int screen, int layer) {
    NF_LoadTextFont(file, fontname, width, height, rot);
    NF_CreateTextLayer(screen, layer, rot, fontname);
}

// quick load and create tiled background
void loadbg(const char *dir, const char *name, int width, int height, int screen, int layer) {
    NF_LoadTiledBg(dir, name, width, height);
    NF_CreateTiledBg(screen, layer, name);
}

// quick unload and remove tiled background
void unloadbg(int screen, int layer, const char *name) {
    NF_DeleteTiledBg(screen, layer);
    NF_UnloadTiledBg(name);
}

// quick load and play raw sound
void playandloadsound(const char *file, int channel, int freq, int sampleform, int vol, int pan, bool loop, int loopstart) {
    NF_LoadRawSound(file, channel, freq, sampleform);
    NF_PlayRawSound(channel, vol, pan, loop, loopstart);
}

// get touch input
bool getTouch(KeyPhase phase) {
    touchRead(&Stylus);
    
    switch (phase){
        case KeyPhase::release:
            // store prev stylus because px,py return 0 when KeysUp()
            if (keysHeld() & KEY_TOUCH) {
		    PrevStylus = Stylus;
	    }

            if (keysUp() & KEY_TOUCH) {
                Stylus = PrevStylus;
                return true;
            }
	    break;
        
        case KeyPhase::press:
            return (keysDown() & KEY_TOUCH);

        case KeyPhase::held:
            return (keysHeld() & KEY_TOUCH);
    }

    return false;
}

// get touch input inside rectangle
bool getTouchRect(int x, int y, int width, int height, KeyPhase phase) {
    if (getTouch(phase)) {
        int mathx = x + width - 1;
        int mathy = y + height - 1;
        return Stylus.px >= x && Stylus.px <= mathx && Stylus.py >= y && Stylus.py <= mathy;
    }
    return false;
}

// get touch input inside circle
bool getTouchCircle(int x, int y, int radius, KeyPhase phase) {
    if (getTouch(phase)) {
	    return ((Stylus.px - x) * (Stylus.px - x)) + ((Stylus.py - y) * (Stylus.py - y)) < radius * radius;
    }
    return false;
}

// get simple swipe gesture
bool getSwipeGesture(Swipe gesture) {
    if (getTouch(KeyPhase::press)) {
        startX = Stylus.px;
        startY = Stylus.py;
    }

    if (getTouch(KeyPhase::release)) {
        int currentX = Stylus.px;
        int currentY = Stylus.py;
        
        int diffX = startX - currentX;
        int diffY = startY - currentY;

        // get absolute without math lib
        int absX = diffX * ((diffX > 0) - (diffX < 0));
        int absY = diffY * ((diffY > 0) - (diffY < 0));
        
        bool result = absX > absY;

		switch (gesture) {
		    case Swipe::SwipeLeft:
		        return (result && diffX > 0);
		    case Swipe::SwipeRight:
		        return (result && diffX < 0);
		    case Swipe::SwipeUp:
		        return (!result && diffY > 0);
		    case Swipe::SwipeDown:
		        return (!result && diffY < 0);
		}
    }

    return false;
}

// check overlap of two rectangles
bool overlap(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) {
    return ((x1 		 >= x2 && x1 		  <= x2 + w2 - 1 && y1 			>= y2 && y1 		 <= y2 + h2 - 1) ||
    	    (x1 + w1 - 1 >= x2 && x1 + w1 - 1 <= x2 + w2 - 1 && y1 			>= y2 && y1 		 <= y2 + h2 - 1) ||
    	    (x1			 >= x2 && x1 		  <= x2 + w2 - 1 && y1 + h1 - 1 >= y2 && y1 + h1 - 1 <= y2 + h2 - 1) ||
    	    (x1 + w1 - 1 >= x2 && x1 + w1 - 1 <= x2 + w2 - 1 && y1 + h1 - 1 >= y2 && y1 + h1 - 1 <= y2 + h2 - 1));
}

// get button input
bool getKeys(KEYPAD_BITS key, KeyPhase phase) {
    switch (phase) {
        case KeyPhase::release:
            return (keysUp() & key);
            break;
        case KeyPhase::press:
            return (keysDown() & key);
            break;
        case KeyPhase::held:
            return (keysHeld() & key);
            break;
    }
    return false;
}

#ifdef __cplusplus
}
#endif
