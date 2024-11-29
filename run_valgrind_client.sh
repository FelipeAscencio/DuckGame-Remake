#!/bin/bash

# Obtener el directorio del script para ubicar la carpeta "build".
SCRIPT_DIR="$(dirname "$0")"

# Cambiar al directorio "build" relativo a la ubicación del script.
cd "$SCRIPT_DIR/src/build" || exit

# Este comando ejecuta la verificacion completa de perdidas de memoria, pero solo lista las perdidas "indirectas" y "definitivas" para evitarnos todos los "falsos" positivos de "SDL2".
LIBGL_ALWAYS_SOFTWARE=1 valgrind --tool=memcheck --leak-check=full --show-leak-kinds=definite,indirect --trace-children=yes --track-fds=yes --track-origins=yes ./taller_client "$@"

# Este comando ejecuta la verificacion completa de perdidas de memoria, pero listando absolutamente todos los 'Leaks', por si se quiere tambien ver los "falsos" positivos de "SDL2".
# LIBGL_ALWAYS_SOFTWARE=1 valgrind --tool=memcheck --leak-check=full --show-reachable=yes --trace-children=yes --track-fds=yes --track-origins=yes ./taller_client "$@"
