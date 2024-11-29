#include <exception>
#include <iostream>

#include <stdbool.h>

#include "client_handler.h"

#define EXITO 0
#define FALLA 1
#define POS_HOSTNAME 1
#define POS_SERVICIO 2
#define ARGUMENTOS_ESPERADOS 3
#define MSJ_ERROR_FORMATO "Error de formato: El esperado es './client <hostname> <servicio>'."
#define MSJ_EXCEPCION_CONOCIDA "Hubo un error y se capturo la excepcion: "
#define MSJ_EXCEPCION_DESCONOCIDA "Hubo un error pero no se conoce la excepcion capturada."
#define MSJ_PARTIDA_ESTA_LLENA "Esta partida ya esta llena."

// PRE: - .
// POST: Devuelve 'true' si la cantidad de argumentos recibida por consola es la correcta.
bool argumentos_validos(int argumentos);

bool argumentos_validos(int argumentos) {
    if (argumentos != ARGUMENTOS_ESPERADOS) {
        std::cout << MSJ_ERROR_FORMATO << std::endl;
        return false;
    }

    return true;
}

int main(int argc, const char* argv[]) {
    try {
        if (!argumentos_validos(argc)) {
            return FALLA;
        }

        const char* hostname = argv[POS_HOSTNAME];
        const char* servicio = argv[POS_SERVICIO];
        try {
            Client client(hostname, servicio);
            client.controlar_loop_juego();
        } catch (const ErrorPartidaLlena& error) {
            std::cerr << MSJ_EXCEPCION_CONOCIDA << MSJ_PARTIDA_ESTA_LLENA << std::endl;
        }

        return EXITO;
    } catch (const std::exception& error) {
        std::cerr << MSJ_EXCEPCION_CONOCIDA << error.what() << std::endl;
        return FALLA;
    } catch (...) {
        std::cerr << MSJ_EXCEPCION_DESCONOCIDA << std::endl;
        return FALLA;
    }
}
