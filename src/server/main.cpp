#include <cstdlib>
#include <exception>
#include <iostream>

#include "server/server.h"

#include "config_juego.h"

#define RUTA_ARCHIVO_YAML "../config_juego.yaml"
#define MSJ_ERROR_FORMATO "Error de formato: El esperado es './server <puerto>'.\n"
#define MSJ_EXCEPCION_CONOCIDA "Hubo un error y se capturo la excepcion: "
#define MSJ_EXCEPCION_DESCONOCIDA "Hubo un error pero no se conoce la excepcion capturada."
#define EXITO 0
#define FALLA 1
#define POS_SERVICIO 1
#define ARGUMENTOS_ESPERADOS 2

// PRE: - .
// POST: Devuelve 'true' si la cantidad de argumentos recibida por consola es la correcta.
bool argumentos_validos(int argumentos);

// PRE: El servicio recibido debe ser valido.
// POST: Inicia la secuencia logica del servidor.
void secuencia_logica_servidor(const char* servicio);

bool argumentos_validos(int argumentos) {
    if (argumentos != ARGUMENTOS_ESPERADOS) {
        std::cout << MSJ_ERROR_FORMATO << std::endl;
        return false;
    }

    return true;
}

void secuencia_logica_servidor(const char* servicio) {
    Server servidor(servicio);
    servidor.start();
}

int main(int argc, const char* argv[]) {
    srand((unsigned)time(NULL));
    ConfigJuego::cargar_configuracion(RUTA_ARCHIVO_YAML);
    try {
        if (!argumentos_validos(argc)) {
            return FALLA;
        }

        const char* servicio = argv[POS_SERVICIO];
        secuencia_logica_servidor(servicio);
        return EXITO;
    } catch (const std::exception& error) {
        std::cerr << MSJ_EXCEPCION_CONOCIDA << error.what() << std::endl;
        return FALLA;
    } catch (...) {
        std::cerr << MSJ_EXCEPCION_DESCONOCIDA << std::endl;
        return FALLA;
    }
}
