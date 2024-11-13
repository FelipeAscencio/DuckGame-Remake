#!/bin/bash

# Obtener el directorio del script para ubicar la carpeta "build".
SCRIPT_DIR="$(dirname "$0")"

# Cambiar al directorio "build" relativo a la ubicación del script.
cd "$SCRIPT_DIR/build" || exit

# Ejecutar el comando "./taller_tests".
./taller_tests