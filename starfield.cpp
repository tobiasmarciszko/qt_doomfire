#include "starfield.h"
#include "effect.h"
#include "QRgb"

struct Star {
    int x;
    int y;
    int speed;
};
static Star stars[200];
static QRgb speedColor[3] = {qRgb(100,100,100), qRgb(170,170,170), qRgb(255,255,255)};

starfield::starfield()
{
    // Initialize framebuffer
    framebuffer = QImage(320, 240, QImage::Format_RGB16);
    framebuffer.fill(qRgb(0,0,0));

    // Initialize effect
    for (int i = 0; i<200 ; i++) {
        stars[i].x = qrand() % 320;
        stars[i].y = qrand() % 240;
        stars[i].speed = qrand() % 3;
    }
}

void starfield::update()
{
    framebuffer.fill(qRgb(0,0,0));
    for (int i = 0; i<200; i++) {
        framebuffer.setPixel(stars[i].x, stars[i].y, speedColor[stars[i].speed]);
        stars[i].x = (stars[i].x + (stars[i].speed + 1));
        stars[i].x = stars[i].x % 320;
    }
}
