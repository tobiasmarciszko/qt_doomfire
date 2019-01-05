#ifndef STARFIELD_H
#define STARFIELD_H

#include <QObject>
#include "effect.h"

class starfield : public IEffect
{
public:
    starfield();

public slots:
    virtual void update();
};

#endif // STARFIELD_H
