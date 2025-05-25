TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt
# Incluir headers desde la carpeta .h
INCLUDEPATH += .h
# Archivos fuente del sistema
SOURCES += \
    .cpp/Fecha.cpp \
    .cpp/Reserva.cpp \
    .cpp/Huesped.cpp \
    .cpp/Anfitrion.cpp \
    .cpp/Alojamiento.cpp \
    .cpp/UdeAStay.cpp \
    main.cpp
# Archivos de cabecera
HEADERS += \
    .h/Fecha.h \
    .h/Reserva.h \
    .h/Huesped.h \
    .h/Anfitrion.h \
    .h/Alojamiento.h \
    .h/UdeAStay.h

# Archivos de datos que se copiarán al build
DISTFILES += \
    datos/huespedes.txt \
    datos/anfitriones.txt \
    datos/alojamientos.txt \
    datos/reservas.txt \
    datos/historico_reservas.txt\
    datos/lastdate.txt
