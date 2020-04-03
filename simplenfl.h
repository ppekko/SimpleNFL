//SimpleNFL - Version 1.60
//By Pipewarp and PolyMars
//
//https://github.com/PipeWarp/SimpleNFL/
//
//Licensed under Creative Commons Attribution-NonCommercial 3.0
//Read it here: https://github.com/PipeWarp/SimpleNFL/blob/master/LICENSE
//
//The Docs/wiki is in the github repository


u16 Pressed;
u16 Held;
u16 Released;
touchPosition Stylus;

const char *A = "A";
const char *B = "B";
const char *X = "X";
const char *Y = "Y";
const char *UP = "UP";
const char *DOWN = "DOWN";
const char *LEFT = "LEFT";
const char *RIGHT = "RIGHT";
const char *R = "R";
const char *L = "L";
const char *SELECT = "SELECT";
const char *START = "START";
const char *PRESS = "press";
const char *HELD = "held";
const char *RELEASE = "release";



void loadsprite(int screen, int ramslot, int vramslot, int width, int height, const char *dir, const char *dir2,
                bool transflag);

void loadsprite(int screen, int ramslot, int vramslot, int width, int height, const char *dir, const char *dir2,
                bool transflag) {
    NF_LoadSpriteGfx(dir, ramslot, width, height);
    NF_LoadSpritePal(dir2, ramslot);
    NF_VramSpriteGfx(screen, ramslot, vramslot, transflag);
    NF_VramSpritePal(screen, ramslot, vramslot);
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


bool istouched(int x, int y, int width, int height);

bool istouched(int x, int y, int width, int height) {
    scanKeys();// Scan for Input
    touchRead(&Stylus);// Read Stylus data


    if (KEY_TOUCH & keysDown()) {
        int mathx = x + width;
        int mathy = y + height;
        return Stylus.px > x && Stylus.px < mathx && Stylus.py > y && Stylus.py < mathy;
    }
    return false;

}

bool ispressed(const char *button, const char *type);

bool ispressed(const char *button, const char *type) {return false;
    scanKeys();
    Pressed = keysDown();
    Held = keysHeld();
    Released = keysUp();
    if (button == A) {
        if (type == PRESS) {
            if (KEY_A & Pressed) {
                return true;
            } else {
                return false;
            }
        } else if (type == HELD) {
            if (KEY_A & Held) {
                return true;
            } else {
                return false;
            }
        } else if (type == RELEASE) {
            if (KEY_A & Released) {
                return true;
            } else {
                return false;
            }

        }
    } else if (button == B) {
        if (type == PRESS) {
            if (KEY_B & Pressed) {
                return true;
            } else {
                return false;
            }
        } else if (type == HELD) {
            if (KEY_B & Held) {
                return true;
            } else {
                return false;
            }
        } else if (type == RELEASE) {
            if (KEY_B & Released) {
                return true;
            } else {
                return false;
            }

        }

    } else if (button == Y) {
        if (type == PRESS) {
            if (KEY_Y & Pressed) {
                return true;
            } else {
                return false;
            }
        } else if (type == HELD) {
            if (KEY_Y & Held) {
                return true;
            } else {
                return false;
            }
        } else if (type == RELEASE) {
            if (KEY_Y & Released) {
                return true;
            } else {
                return false;
            }

        }

    } else if (button == X) {
        if (type == PRESS) {
            if (KEY_X & Pressed) {
                return true;
            } else {
                return false;
            }
        } else if (type == HELD) {
            if (KEY_X & Held) {
                return true;
            } else {
                return false;
            }
        } else if (type == RELEASE) {
            if (KEY_X & Released) {
                return true;
            } else {
                return false;
            }

        }

    } else if (button == UP) {
        if (type == PRESS) {
            if (KEY_UP & Pressed) {
                return true;
            } else {
                return false;
            }
        } else if (type == HELD) {
            if (KEY_UP & Held) {
                return true;
            } else {
                return false;
            }
        } else if (type == RELEASE) {
            if (KEY_UP & Released) {
                return true;
            } else {
                return false;
            }

        }

    } else if (button == DOWN) {
        if (type == PRESS) {
            if (KEY_DOWN & Pressed) {
                return true;
            } else {
                return false;
            }
        } else if (type == HELD) {
            if (KEY_DOWN & Held) {
                return true;
            } else {
                return false;
            }
        } else if (type == RELEASE) {
            if (KEY_DOWN & Released) {
                return true;
            } else {
                return false;
            }

        }

    } else if (button == LEFT) {
        if (type == PRESS) {
            if (KEY_LEFT & Pressed) {
                return true;
            } else {
                return false;
            }
        } else if (type == HELD) {
            if (KEY_LEFT & Held) {
                return true;
            } else {
                return false;
            }
        } else if (type == RELEASE) {
            if (KEY_LEFT & Released) {
                return true;
            } else {
                return false;
            }

        }

    } else if (button == RIGHT) {
        if (type == PRESS) {
            if (KEY_RIGHT & Pressed) {
                return true;
            } else {
                return false;
            }
        } else if (type == HELD) {
            if (KEY_RIGHT & Held) {
                return true;
            } else {
                return false;
            }
        } else if (type == RELEASE) {
            if (KEY_RIGHT & Released) {
                return true;
            } else {
                return false;
            }

        }

    } else if (button == R) {
        if (type == PRESS) {
            if (KEY_R & Pressed) {
                return true;
            } else {
                return false;
            }
        } else if (type == HELD) {
            if (KEY_R & Held) {
                return true;
            } else {
                return false;
            }
        } else if (type == RELEASE) {
            if (KEY_R & Released) {
                return true;
            } else {
                return false;
            }

        }

    } else if (button == L) {
        if (type == PRESS) {
            if (KEY_L & Pressed) {
                return true;
            } else {
                return false;
            }
        } else if (type == HELD) {
            if (KEY_L & Held) {
                return true;
            } else {
                return false;
            }
        } else if (type == RELEASE) {
            if (KEY_L & Released) {
                return true;
            } else {
                return false;
            }

        }

    } else if (button == START) {
        if (type == PRESS) {
            if (KEY_START & Pressed) {
                return true;
            } else {
                return false;
            }
        } else if (type == HELD) {
            if (KEY_START & Held) {
                return true;
            } else {
                return false;
            }
        } else if (type == RELEASE) {
            if (KEY_START & Released) {
                return true;
            } else {
                return false;
            }

        }

    } else if (button == SELECT) {
        if (type == PRESS) {
            if (KEY_SELECT & Pressed) {
                return true;
            } else {
                return false;
            }
        } else if (type == HELD) {
            if (KEY_SELECT & Held) {
                return true;
            } else {
                return false;
            }
        } else if (type == RELEASE) {
            if (KEY_SELECT & Released) {
                return true;
            } else {
                return false;
            }

        }

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
