// Copyright 2024 Axel Zielonka y Felipe Ascencio.
#ifndef COMMON_COMANDO_H_
#define COMMON_COMANDO_H_

#include <cstdint>
#include <iostream>

// 'Struct' utilizado para encapsular un comando.
typedef struct Comando {
    uint8_t id_cliente;
    uint8_t accion;
} comando_t;

#endif  // COMMON_COMANDO_H_
