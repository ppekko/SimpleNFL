//SimpleNFL - Version 1.65
//By Pipewarp 
//With Help from PolyMars and SkilLP
//https://github.com/PipeWarp/SimpleNFL/
//
//Licensed under Creative Commons Attribution-NonCommercial 3.0
//Read it here: https://github.com/PipeWarp/SimpleNFL/blob/master/LICENSE
//
//The Docs/wiki is in the github repository
//Have fun!

#pragma once

enum Key {
    UP, DOWN, LEFT, RIGHT,
    START, SELECT,
    A, B, X, Y,
    R, L
};

enum KeyPhase { release, press, held };

touchPosition Stylus;
touchPosition PrevStylus; // previous frame stylus position

void loadsprite(int screen, int ramslot, int vramslot, int width, int height, const char *dir, const char *dir2,
                bool transflag);

void loadsprite(int screen, int ramslot, int vramslot, int width, int height, const char *dir, const char *dir2,
                bool transflag) {
    NF_LoadSpriteGfx(dir, ramslot, width, height);
    NF_LoadSpritePal(dir2, ramslot);
    NF_VramSpriteGfx(screen, ramslot, vramslot, transflag);
    NF_VramSpritePal(screen, ramslot, vramslot);
}

// unload gfx and sprite in ram and vram
void unloadsprite(int screen, int ramslot, int vramslot);

void unloadsprite(int screen, int ramslot, int vramslot) {
    // ram
    NF_UnloadSpriteGfx(ramslot);
    NF_UnloadSpritePal(ramslot);

    // vram
    NF_FreeSpriteGfx(screen, vramslot);
}

void loadfont(const char *file, const char *fontname, int width, int height, int rot, int screen, int layer);

void loadfont(const char *file, const char *fontname, int width, int height, int rot, int screen, int layer) {
    NF_LoadTextFont(file, fontname, width, height, rot);
    NF_CreateTextLayer(screen, layer, rot, fontname);
}

void loadbg(const char *dir, const char *name, int width, int height, int screen, int layer);

void loadbg(const char *dir, const char *name, int width, int height, int screen, int layer) {
    NF_LoadTiledBg(dir, name, width, height);
    NF_CreateTiledBg(screen, layer, name);
}

void
playandloadsound(const char *file, int channel, int freq, int sampleform, int vol, int pan, bool loop, int loopstart);

void
playandloadsound(const char *file, int channel, int freq, int sampleform, int vol, int pan, bool loop, int loopstart) {
    NF_LoadRawSound(file, channel, freq, sampleform);
    NF_PlayRawSound(channel, vol, pan, loop, loopstart);
}

bool getTouch(KeyPhase phase);

bool getTouch(KeyPhase phase) {
    touchRead(&Stylus);
    
    switch (phase){
        case KeyPhase::release:
            // store prev stylus because px,py return 0 when KeysUp()
            if (KEY_TOUCH & keysHeld()) PrevStylus = Stylus;

            if (KEY_TOUCH & keysUp()) {
                Stylus = PrevStylus;
                return true;
            }
            else break;
        
        case KeyPhase::press:
            return (KEY_TOUCH & keysDown());
            break;

        case KeyPhase::held:
            return (KEY_TOUCH & keysHeld());
            break;
    }

    return false;
}

bool getTouchRect(int x, int y, int width, int height, KeyPhase phase);

bool getTouchRect(int x, int y, int width, int height, KeyPhase phase) {
    if (getTouch(phase)) {
        int mathx = x + width;
        int mathy = y + height;
        return Stylus.px > x && Stylus.px < mathx && Stylus.py > y && Stylus.py < mathy;
    }
    return false;
}

bool overlap(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);

bool overlap(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) {
    if ((x3 <= x1 && x1 <= x4 && y3 <= y1 && y1 <= y4) ||
        (x3 <= x1 && x1 <= x4 && y3 <= y2 && y2 <= y4) ||
        (x3 <= x2 && x2 <= x4 && y3 <= y1 && y1 <= y4) ||
        (x3 <= x2 && x2 <= x4 && y3 <= y2 && y2 <= y4)) {
        return true;
    }

    return false;
}

bool getKeys(Key key, KeyPhase phase);

bool getKeys(Key key, KeyPhase phase) {
    switch (key) {
        case Key::A:
            switch (phase) {
                case KeyPhase::release:
                    return (KEY_A & keysUp());
                    break;
                case KeyPhase::press:
                    return (KEY_A & keysDown());
                    break;
                case KeyPhase::held:
                    return (KEY_A & keysHeld());
                    break;
            }
            break;
        
        case Key::B:
            switch (phase) {
                case KeyPhase::release:
                    return (KEY_B & keysUp());
                    break;
                case KeyPhase::press:
                    return (KEY_B & keysDown());
                    break;
                case KeyPhase::held:
                    return (KEY_B & keysHeld());
                    break;
            }
            break;
        
        case Key::X:
            switch (phase) {
                case KeyPhase::release:
                    return (KEY_X & keysUp());
                    break;
                case KeyPhase::press:
                    return (KEY_X & keysDown());
                    break;
                case KeyPhase::held:
                    return (KEY_X & keysHeld());
                    break;
            }
            break;
        
        case Key::Y:
            switch (phase) {
                case KeyPhase::release:
                    return (KEY_Y & keysUp());
                    break;
                case KeyPhase::press:
                    return (KEY_Y & keysDown());
                    break;
                case KeyPhase::held:
                    return (KEY_Y & keysHeld());
                    break;
            }
            break;
        
        case Key::L:
            switch (phase) {
                case KeyPhase::release:
                    return (KEY_L & keysUp());
                    break;
                case KeyPhase::press:
                    return (KEY_L & keysDown());
                    break;
                case KeyPhase::held:
                    return (KEY_L & keysHeld());
                    break;
            }
            break;
        
        case Key::R:
            switch (phase) {
                case KeyPhase::release:
                    return (KEY_R & keysUp());
                    break;
                case KeyPhase::press:
                    return (KEY_R & keysDown());
                    break;
                case KeyPhase::held:
                    return (KEY_R & keysHeld());
                    break;
            }
            break;
        
        case Key::UP:
            switch (phase) {
                case KeyPhase::release:
                    return (KEY_UP & keysUp());
                    break;
                case KeyPhase::press:
                    return (KEY_UP & keysDown());
                    break;
                case KeyPhase::held:
                    return (KEY_UP & keysHeld());
                    break;
            }
            break;
        
        case Key::DOWN:
            switch (phase) {
                case KeyPhase::release:
                    return (KEY_DOWN & keysUp());
                    break;
                case KeyPhase::press:
                    return (KEY_DOWN & keysDown());
                    break;
                case KeyPhase::held:
                    return (KEY_DOWN & keysHeld());
                    break;
            }
            break;
        
        case Key::LEFT:
            switch (phase) {
                case KeyPhase::release:
                    return (KEY_LEFT & keysUp());
                    break;
                case KeyPhase::press:
                    return (KEY_LEFT & keysDown());
                    break;
                case KeyPhase::held:
                    return (KEY_LEFT & keysHeld());
                    break;
            }
            break;
        
        case Key::RIGHT:
            switch (phase) {
                case KeyPhase::release:
                    return (KEY_RIGHT & keysUp());
                    break;
                case KeyPhase::press:
                    return (KEY_RIGHT & keysDown());
                    break;
                case KeyPhase::held:
                    return (KEY_RIGHT & keysHeld());
                    break;
            }
            break;
        
        case Key::SELECT:
            switch (phase) {
                case KeyPhase::release:
                    return (KEY_SELECT & keysUp());
                    break;
                case KeyPhase::press:
                    return (KEY_SELECT & keysDown());
                    break;
                case KeyPhase::held:
                    return (KEY_SELECT & keysHeld());
                    break;
            }
            break;
        
        case Key::START:
            switch (phase) {
                case KeyPhase::release:
                    return (KEY_START & keysUp());
                    break;
                case KeyPhase::press:
                    return (KEY_START & keysDown());
                    break;
                case KeyPhase::held:
                    return (KEY_START & keysHeld());
                    break;
            }
            break;    
    }
    return false;
}
