#include "doomfire.h"
#include "effect.h"
#include "QRgb"

const int FIRE_WIDTH  = 320;
const int FIRE_HEIGHT = 240;
static uint firePixels[FIRE_WIDTH*FIRE_HEIGHT];

static QVector<QRgb> palette = {
    qRgb(0x07,0x07,0x07),
    qRgb(0x1F,0x07,0x07),
    qRgb(0x2F,0x0F,0x07),
    qRgb(0x47,0x0F,0x07),
    qRgb(0x57,0x17,0x07),
    qRgb(0x67,0x1F,0x07),
    qRgb(0x77,0x1F,0x07),
    qRgb(0x8F,0x27,0x07),
    qRgb(0x9F,0x2F,0x07),
    qRgb(0xAF,0x3F,0x07),
    qRgb(0xBF,0x47,0x07),
    qRgb(0xC7,0x47,0x07),
    qRgb(0xDF,0x4F,0x07),
    qRgb(0xDF,0x57,0x07),
    qRgb(0xDF,0x57,0x07),
    qRgb(0xD7,0x5F,0x07),
    qRgb(0xD7,0x5F,0x07),
    qRgb(0xD7,0x67,0x0F),
    qRgb(0xCF,0x6F,0x0F),
    qRgb(0xCF,0x77,0x0F),
    qRgb(0xCF,0x7F,0x0F),
    qRgb(0xCF,0x87,0x17),
    qRgb(0xC7,0x87,0x17),
    qRgb(0xC7,0x8F,0x17),
    qRgb(0xC7,0x97,0x1F),
    qRgb(0xBF,0x9F,0x1F),
    qRgb(0xBF,0x9F,0x1F),
    qRgb(0xBF,0xA7,0x27),
    qRgb(0xBF,0xA7,0x27),
    qRgb(0xBF,0xAF,0x2F),
    qRgb(0xB7,0xAF,0x2F),
    qRgb(0xB7,0xB7,0x2F),
    qRgb(0xB7,0xB7,0x37),
    qRgb(0xCF,0xCF,0x6F),
    qRgb(0xDF,0xDF,0x9F),
    qRgb(0xEF,0xEF,0xC7),
    qRgb(0xFF,0xFF,0xFF)
};

static void spreadFire(int src) {
    auto pixel = firePixels[src];
    if(pixel == 0) {
        firePixels[src - FIRE_WIDTH] = 0;
    } else {
        int randIdx = qrand() % 4;
        int dst = src - randIdx + 1;
        firePixels[dst - FIRE_WIDTH] = pixel - (randIdx & 1);
    }
}

static void doFire() {
    for(int x = 0 ; x < FIRE_WIDTH; x++) {
        for (int y = 1; y < FIRE_HEIGHT; y++) {
            spreadFire(y * FIRE_WIDTH + x);
        }
    }
}

doomfire::doomfire()
{
    // Initialize framebuffer
    framebuffer = QImage(320, 240, QImage::Format_Indexed8);
    framebuffer.setColorTable(palette);

    // Initialize effect
    for (uint i = 0; i < FIRE_WIDTH*FIRE_HEIGHT; i++) {
        firePixels[i] = 15;
    }

    for(uint i = 0; i < FIRE_WIDTH; i++) {
        firePixels[(FIRE_HEIGHT-1)*FIRE_WIDTH + i] = 36;
    }
}

void doomfire::update()
{
    doFire();

    for(int y = 0; y < FIRE_HEIGHT; y++) {
        for(int x = 0; x < FIRE_WIDTH; x++) {
            uint index = firePixels[y * FIRE_WIDTH + x];
            framebuffer.setPixel(x, y, index);
        }
    }
}
