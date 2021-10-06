TEMPLATE = app
CONFIG += console
CONFIG -= qt

SOURCES += main.cpp

HEADERS += \
    timer.h \
    telas_apresentacao.h \
    rebatedor.h \
    ranking.h \
    processa_jogo.h \
    carrega_jogo.h \
    bola.h \
    blocos.h

LIBS += `allegro-config --libs` -lalleg
