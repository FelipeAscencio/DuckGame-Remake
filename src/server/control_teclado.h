#ifndef CONTROL_TECLADO_H
#define CONTROL_TECLADO_H

#include <iostream>
#include <atomic>

#include "../common/thread.h"

// La clase 'ControladorTeclado' implementa la logica
// de cierre del 'Servidor'.
class ControladorTeclado: public Thread {
    private:
        std::atomic<bool> vivo;

    public:
        // Constructor de la clase.
        ControladorTeclado();

        // Devuelve el estado del hilo.
        bool esta_vivo() { return this->vivo; }

        // Implementa la logica de finalizacion del 'Servidor' al ingresar la 'q' por consola.
        void run() override;
};

#endif
