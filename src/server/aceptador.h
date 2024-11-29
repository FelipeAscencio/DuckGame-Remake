// Copyright 2024 Axel Zielonka y Felipe Ascencio.
#ifndef ACEPTADOR_H
#define ACEPTADOR_H

#include <atomic>
#include <list>
#include <utility>
#include <vector>

#include <netinet/in.h>
#include <syslog.h>

#include "../common/liberror.h"
#include "../common/queue.h"
#include "../common/thread.h"

#include "partida.h"
#include "queues_jugadores.h"
#include "thread_usuario.h"

// La clase 'Aceptador' controla la logica de la conexion
// (conexion y desconexion) del 'Cliente' con el 'Server'.
class Aceptador: public Thread {
private:
    Socket skt;
    std::list<ThreadUsuario*> jugadores;
    std::atomic<bool> aceptando_jugadores;
    std::vector<Partida*>& partidas;

    // Envia el mensaje inicial al Cliente.
    bool enviar_mensaje_inicial(Socket& s, const std::string& mensaje);

    // Recolecta y elimina los hilos de jugadores que hayan finalizado.
    void recolectar();

    // Elimina al cliente representado por 'jugador' de las colas y libera su memoria.
    void eliminar_cliente(ThreadUsuario* jugador);

    // Recibe la respuesta inicial del cliente.
    bool recibir_respuesta_cliente(uint8_t& rta, Socket& s);

    // Crea una nueva partida en el servidor.
    void crear_nueva_partida(Socket& peer);

    // Controla el loop de ingreso para usuarios a partidas existentes.
    bool loop_ingreso_partida_usuario(Socket& peer);

public:
    // Constructor de la clase.
    explicit Aceptador(const char* servname, std::vector<Partida*>& partidas);

    // Inicia el hilo que acepta la conexion de los 'Clientes' con el 'Server'.
    virtual void run() override;

    // Cambia el estado del hilo para que no siga aceptando usuarios.
    void dejar_de_aceptar();

    // Destructor de la clase.
    ~Aceptador() override;

    // Deshabilito las copias.
    Aceptador(const Aceptador&) = delete;
    Aceptador& operator=(const Aceptador&) = delete;

    // Permito el movimiento del objeto.
    Aceptador(Aceptador&&) = default;
    Aceptador& operator=(Aceptador&&) = default;
};

#endif  // ACEPTADOR_H
