// Copyright 2024 Axel Zielonka y Felipe Ascensio
#ifndef COMMON_COMANDO_H_
#define COMMON_COMANDO_H_

#include <iostream>

typedef struct Comando {
    uint8_t id_cliente;  // cppcheck-suppress unusedStructMember
    uint8_t accion;      // cppcheck-suppress unusedStructMember
} comando_t;

#endif  // COMMON_COMANDO_H_
