#include "partida.h"

#define MSJ_PARTIDA_CREADA "Partida creada con id: "

#define DUMMY 0xCC
#define MAX_PLAYERS 8
#define CERO 0
#define CANTIDAD_DIGITOS_ID 6
#define DIEZ 10

Partida::Partida(const std::string& id):
        id_partida(id), clientes(), queue(), juego(queue, clientes), ultimo_cliente_agregado(CERO) {
    std::cout << MSJ_PARTIDA_CREADA << this->id_partida << std::endl;
    juego.start();
}

void Partida::agregar_jugador(Socket&& peer) {
    bool was_closed = false;
    if (ultimo_cliente_agregado >= MAX_PLAYERS) {
        uint8_t dummy = DUMMY;
        peer.sendall(&dummy, sizeof(dummy), &was_closed);
        if (was_closed) {
            terminar_partida();
        }

        return;
    }

    peer.sendall(&ultimo_cliente_agregado, sizeof(ultimo_cliente_agregado), &was_closed);
    if (was_closed) {
        terminar_partida();
        return;
    }

    ThreadUsuario* jugador = new ThreadUsuario(std::move(peer), queue, ultimo_cliente_agregado);
    clientes.agregar_queue(jugador->obtener_queue(), ultimo_cliente_agregado);
    ultimo_cliente_agregado++;
    jugadores.push_back(jugador);
    jugador->iniciar();
}

void Partida::eliminar_cliente(ThreadUsuario* jugador) {
    std::lock_guard<std::mutex> lck(mtx);
    jugador->cortar_conexion();
    int id = jugador->get_id();
    clientes.eliminar_queue(id);
    delete jugador;
}

std::string Partida::generar_codigo() {
    std::string codigo;
    int i = CERO;
    int caracter;
    while (i < CANTIDAD_DIGITOS_ID) {
        caracter = (rand() % DIEZ);
        codigo += std::to_string(caracter);
        i++;
    }

    return codigo;
}

void Partida::buscar_jugadores_desconectados() {
    jugadores.remove_if([this](ThreadUsuario* j) {
        if (!(j->esta_vivo())) {
            eliminar_cliente(j);
            return true;
        }

        return false;
    });
}

void Partida::terminar_partida() {
    juego.finalizar_juego();
    juego.join();
    for (auto& j: jugadores) {
        eliminar_cliente(j);
    }

    jugadores.clear();
    queue.close();
}
