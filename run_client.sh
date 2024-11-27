#!/bin/bash

# Obtener el directorio del script para ubicar la carpeta "build".
SCRIPT_DIR="$(dirname "$0")"

# Cambiar al directorio "build" relativo a la ubicación del script.
cd "$SCRIPT_DIR/src/build" || exit

# Ejecutar el comando "./taller_client" pasando los argumentos recibidos por el script.
LIBGL_ALWAYS_SOFTWARE=1 ./taller_client "$@"
