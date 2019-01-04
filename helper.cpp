/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "helper.h"

#include <QPainter>
#include <QPaintEvent>
#include <QWidget>
#include <QtMath>
#include <qmath.h>

// DOOM fire
const int FIRE_WIDTH  = 320;
const int FIRE_HEIGHT = 240;
static int firePixels[FIRE_WIDTH*FIRE_HEIGHT];

static QRgb palette[37] = {
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

// Starfield :)
/*
struct Star {
    int x;
    int y;
    int speed;
};
static Star stars[200];
static QRgb speedColor[3] = {qRgb(100,100,100), qRgb(170,170,170), qRgb(255,255,255)};
*/

Helper::Helper()
{
    background = QBrush(QColor(64, 32, 64));
    circlePen = QPen(Qt::black);
    circlePen.setWidth(1);
    framebuffer = QImage(320, 240, QImage::Format_RGB16);
    framebuffer.fill(qRgb(0,0,0));

    // Starfield
    /*
    for (int i = 0; i<200 ; i++) {
        stars[i].x = qrand() % 320;
        stars[i].y = qrand() % 240;
        stars[i].speed = qrand() % 3;
    }
    */

    // DOOM fire
    for (int i = 0; i < FIRE_WIDTH*FIRE_HEIGHT; i++) {
        firePixels[i] = 0;
    }

    for(int i = 0; i < FIRE_WIDTH; i++) {
        firePixels[(FIRE_HEIGHT-1)*FIRE_WIDTH + i] = 36;
    }
}

void Helper::paint(QPainter *painter, QPaintEvent *event, int elapsed)
{
    // Starfield
/*
    framebuffer.fill(qRgb(0,0,0));
    for (int i = 0; i<200; i++) {
        framebuffer.setPixel(stars[i].x, stars[i].y, speedColor[stars[i].speed]);
        stars[i].x = (stars[i].x + (stars[i].speed + 1));
        stars[i].x = stars[i].x % 320;
    }
*/
    // DOOM fire
    doFire();
    for(int y = 0; y < FIRE_HEIGHT; y++) {
        for(int x = 0; x < FIRE_WIDTH; x++) {
            int index = firePixels[y * FIRE_WIDTH + x];
            QRgb color = palette[index];
            framebuffer.setPixel(x, y, color);
        }
    }

    painter->drawImage(0,0,framebuffer);
}


