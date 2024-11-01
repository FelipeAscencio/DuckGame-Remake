#ifndef CLIENT_MOCK_H
#define CLIENT_MOCK_H

#include <atomic>
#include <iostream>
#include <string>

#include "../common/estado_juego.h"
#include "../common/queue.h"
#include "../common/thread.h"

#include "protocolo_cliente.h"


class EnviadorCliente: public Thread {
private:
    ProtocoloCliente protocol;  // conectado con el ServerRecibidor
    Queue<char>& queue_comandos;
    int id_cliente;
    std::atomic<bool> vivo;

public:
    EnviadorCliente(ProtocoloCliente& p, Queue<char>& q, int id):
            protocol(p), queue_comandos(q), id_cliente(id), vivo(true) {}

    void run() override {
        while (vivo) {
            std::string accion;
            try {
                // accion = queue_comandos.pop();
                std::getline(std::cin, accion);
                if (!protocol.enviar(accion[0]))
                    break;
            } catch (const ClosedQueue& e) {
                std::cerr << e.what();
            }
        }
    }

    void dejar_de_enviar() { this->vivo = false; }

    ~EnviadorCliente() { this->join(); }
    // Protocolo
    // Queue <comandos> --> pop --> sendall()
};

class RecibidorCliente: public Thread {
private:
    ProtocoloCliente protocol;  // conectado con el ServerEnviador
    Queue<EstadoJuego>& queue_estados;
    std::atomic<bool> vivo;

public:
    explicit RecibidorCliente(ProtocoloCliente& p, Queue<EstadoJuego>& q):
            protocol(p), queue_estados(q), vivo(true) {}

    void run() override {
        while (vivo) {
            EstadoJuego estado_actual;
            if (!protocol.recibir(estado_actual))
                break;
            try {
                queue_estados.push(estado_actual);
            } catch (const ClosedQueue& e) {
                std::cerr << e.what();
            }
        }
    }

    void dejar_de_recibir() { this->vivo = false; }

    ~RecibidorCliente() { this->join(); }
    // Protocolo
    //  recvall() --> push --> Queue <estado_juego>
};

class ClientMock {

private:
    Socket s;
    ProtocoloCliente protocolo;
    int id;
    Queue<char> queue_enviador;
    Queue<EstadoJuego> queue_recibidor;
    EnviadorCliente e;
    RecibidorCliente r;

    void loop_juego();

public:
    explicit ClientMock(const char* hostname, const char* servname);

    void start();

    ~ClientMock();
};


#endif
