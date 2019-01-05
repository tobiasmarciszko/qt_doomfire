#ifndef DOOMFIRE_H
#define DOOMFIRE_H

#include <QObject>
#include "effect.h"

class doomfire : public IEffect
{
public:
    doomfire();

public slots:
    virtual void update();
};

#endif // DOOMFIRE_H
