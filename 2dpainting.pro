QT          += widgets

HEADERS     = glwidget.h \
              helper.h \
              window.h \
    effect.h \
    doomfire.h \
    starfield.h
SOURCES     = glwidget.cpp \
              helper.cpp \
              main.cpp \
              window.cpp \
    doomfire.cpp \
    starfield.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/opengl/2dpainting
INSTALLS += target
