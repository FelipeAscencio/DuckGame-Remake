#include "control_teclado.h"

#include <string>

#define EXIT "q"

ControladorTeclado::ControladorTeclado(): vivo(true) {}

void ControladorTeclado::run() {
    std::string linea;
    while (std::getline(std::cin, linea)) {
        if (linea == EXIT) {
            break;
        }
    }
    this->vivo = false;
}
