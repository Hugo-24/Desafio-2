TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt
# Incluir la carpeta donde están los headers (.h)
INCLUDEPATH += .h
# Archivos fuente (.cpp)
SOURCES += \
    .cpp/Fecha.cpp \
    .cpp/Reserva.cpp \
    .cpp/Huesped.cpp \
    .cpp/Anfitrion.cpp \
    .cpp/Alojamiento.cpp \
    .cpp/UdeAStay.cpp \
    main.cpp
# Archivos de cabecera (.h)
HEADERS += \
    .h/Fecha.h \
    .h/Reserva.h \
    .h/Huesped.h \
    .h/Anfitrion.h \
    .h/Alojamiento.h \
    .h/UdeAStay.h
