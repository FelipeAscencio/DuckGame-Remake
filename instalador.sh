#!/bin/bash

# Obtener el directorio del script.
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# Obtener el directorio del SDL.
SDL2_DIR="${SCRIPT_DIR}/SDL2-dependencies"

# Utilizado para imprimir los mensajes del estado de la instalación.
imprimir_msj() {
    color=$1
    shift
    printf "\e[${color}m$@\e[0m\n"
}

# Color naranja para los mensajes.
ORANGE="0;33"

# Color verde para los mensajes.
GREEN="1;32"

# Instalación de todas las dependencias.
imprimir_msj $ORANGE "║ Ejecutando actualización adecuada ║"

sudo apt-get update
sudo apt-get --yes install update

imprimir_msj $ORANGE "║ Instalación de los paquetes necesarios de utilidades apt ║"

sudo apt-get --yes install gcc
sudo apt-get --yes install cmake
sudo apt-get --yes install g++
sudo apt-get --yes install build-essential libgl1-mesa-dev libclang-16-dev

imprimir_msj $ORANGE "║ Instalación de los paquetes apt necesarios para Qt 5 ║"

sudo apt-get --yes install qtcreator qtbase5-dev qtchooser qt5-qmake qtbase5-dev-tools
sudo apt-get --yes install libqt5charts5-dev libqt5datavisualization5-dev libqt5gamepad5-dev libqt5gstreamer-dev libqt5networkauth5-dev libqt5opengl5-dev libqt5remoteobjects5-dev libqt5scxml5-dev libqt5sensors5-dev libqt5serialbus5-dev libqt5serialport5-dev libqt5svg5-dev libqt5texttospeech5-dev libqt5virtualkeyboard5-dev libqt5waylandclient5-dev libqt5waylandcompositor5-dev libqt5webkit5-dev libqt5webchannel5-dev libqt5websockets5-dev libqt5webview5-dev libqt5x11extras5-dev libqt5xmlpatterns5-dev libqt5multimedia5-plugins qtmultimedia5-dev

imprimir_msj $ORANGE "║ Instalación de los paquetes apt necesarios para SDL2 ║"

sudo apt-get --yes install libsdl2-2.0-0 libjpeg-dev libwebp-dev libtiff5-dev libsdl2-image-2.0-0 libmikmod-dev libfishsound1-dev libsmpeg-dev liboggz2-dev libflac-dev libfluidsynth-dev libsdl2-mixer-2.0-0 libopusfile-dev libpng-dev libfreetype6-dev libsdl2-ttf-2.0-0 libwavpack-dev libxmp-dev libfreetype-dev libmodplug-dev
sudo apt-get --yes install libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-ttf-dev 

imprimir_msj $ORANGE "║ Instalación de paquetes apt necesarios para gtest ║"

sudo apt-get --yes install libyaml-cpp-dev
sudo apt-get --yes install libgtest-dev

# Dependencias necesarias para cargar imagenes, sonidos y textos en "SDL2".
imprimir_msj $ORANGE "║ Compilando dependencias SDL2 ║"

# Verifica y compila cada dependencia en SDL2-dependencies.
for dependency in SDL_image SDL_mixer SDL_ttf; do
    DEP_PATH="$SDL2_DIR/$dependency"
    if [[ -d "$DEP_PATH" ]]; then
        cd "$DEP_PATH"
        mkdir -p build
        cd build
        cmake ..
        make -j4
        sudo make install
    else
        imprimir_msj $ORANGE "║ Advertencia: No se encontró la carpeta $dependency ║"
    fi
done

# Compilación del juego.
imprimir_msj $ORANGE "║ Compilando el juego, ¡ya falta poco! ║"

cd "$SCRIPT_DIR"
sudo make clean
sudo make

imprimir_msj $GREEN "║ Instalación de depencencias terminada ║"
