#include <exception>
#include <iostream>

#include <stdbool.h>

#define MSJ_EXCEPCION_CONOCIDA "Hubo un error y se capturo la excepcion: "
#define MSJ_EXCEPCION_DESCONOCIDA "Hubo un error pero no se conoce la excepcion capturada."
#define EXITO 0
#define FALLA 1

void secuencia_logica_servidor() {
    std::cout << "Entrando a secuencia logica del servidor." << std::endl;
}

int main(int argc, const char* argv[]) {
    // 'Print' utilizado para ver los parametros recibidos en el servidor.
    std::cout <<"ARGC: " << argc << " / ARGV: " << argv << std::endl;

    try {
        secuencia_logica_servidor();
        return EXITO;
    } catch (const std::exception& error) {
        std::cerr << MSJ_EXCEPCION_CONOCIDA << error.what() << std::endl;
        return FALLA;
    } catch (...) {
        std::cerr << MSJ_EXCEPCION_DESCONOCIDA << std::endl;
        return FALLA;
    }
}
