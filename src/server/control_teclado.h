#ifndef CONTROL_TECLADO_H
#define CONTROL_TECLADO_H

#include <iostream>
#include "../common/thread.h"
#include <atomic>

class ControladorTeclado: public Thread {
    private:
        std::atomic<bool> vivo;
    public:
        ControladorTeclado();
        bool esta_vivo() { return this->vivo; }
        void run() override;
};

#endif