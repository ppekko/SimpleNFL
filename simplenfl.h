void loadsprite(int screen, int ramslot, int vramslot, int width, int height, const char* dir, const char* dir2, bool transflag);

void loadsprite(int screen, int ramslot, int vramslot, int width, int height, const char* dir, const char* dir2, bool transflag){
NF_LoadSpriteGfx(dir, ramslot, width, height);
NF_LoadSpritePal(dir2, ramslot);
NF_VramSpriteGfx(screen, ramslot, vramslot, transflag);
NF_VramSpritePal(screen, ramslot, vramslot);
}

void loadfont(const char* file, const char* fontname, int width, int height, int rot, int screen, int layer);

void loadfont(const char* file, const char* fontname, int width, int height, int rot, int screen, int layer){
    NF_LoadTextFont(file, fontname, width, height, rot);
    NF_CreateTextLayer(screen, layer, rot, fontname);
}

void playandloadsound(const char* file, int channel, int freq, int sampleform, int vol, int pan, bool loop, int loopstart);

void playandloadsound(const char* file, int channel, int freq, int sampleform, int vol, int pan, bool loop, int loopstart){
    NF_LoadRawSound(file, channel, freq, sampleform);
    NF_PlayRawSound(channel, vol, pan, loop, loopstart)
}
