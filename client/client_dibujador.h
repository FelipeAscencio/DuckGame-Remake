// Copyright 2024 Axel Zielonka y Felipe Ascencio.
#ifndef CLIENT_DIBUJADOR_H
#define CLIENT_DIBUJADOR_H

#include <vector>

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "client_parseador.h"
#include "../common/orientacion.h"
#include "../common/queue.h"
#include "../common/estado_juego.h"

using namespace SDL2pp;

// La clase 'Dibujador' implementa la logica
// del dibujo de la partida para el 'Cliente'.
class Dibujador {
private:
    const int id_jugador;
    Queue<EstadoJuego>& cola_estados;
    EstadoJuego ultimo_estado_recibido;
    Parseador parseador;
    Texture sprite_sheet_pato;
    Texture sprite_sheet_ak; // Falta la bala.
    Texture sprite_sheet_caja;
    Texture sprite_sheet_armadura; // Falta el casco, la pechera y el casco loteable.
    Texture sprite_sheet_escopeta; // Falta la escopeta y las balas.
    Texture sprite_sheet_laser; // Falta el arma y las balas.
    Texture sprite_sheet_pistola; // Falta el arma y las balas.
    Texture mapa;
    std::vector<SDL_Rect> sprites_pato;
    std::vector<SDL_Rect> sprites_ak;
    std::vector<SDL_Rect> sprites_caja;
    std::vector<SDL_Rect> sprites_armadura;
    std::vector<SDL_Rect> sprites_escopeta;
    std::vector<SDL_Rect> sprites_laser;
    std::vector<SDL_Rect> sprites_pistola;

    // Funcion provisoria (TESTING).
    void dibujar_sprites_fila(SDL2pp::Renderer& renderer, SDL2pp::Texture& sprite_sheet,
                              const std::vector<SDL_Rect>& sprites, int ancho_ventana,
                              int alto_ventana, float x, float y, float escala, float separacion);

    // Devuelve el 'Rect' correspondiente segun los parametros recibidos.
    SDL2pp::Rect calcular_dst_rect(float x, float y, float escala);

    // Convierte el 'X' e 'Y' recibido en el valor relativo en relacion al 'X' e 'Y' maximos.
    std::pair<float, float> convertir_a_relativo(int x, int y);

    // Dibuja el pato enemigo con el color correspondiente segun su id.
    void dibujar_pato_enemigo(SDL2pp::Renderer& renderer, SDL2pp::Texture& sprite_sheet,
                               const SDL_Rect& sprite, SDL2pp::Rect& dst_rect, const int id, const double angle, SDL_RendererFlip& flip);

    // Dibuja un sprite en la posicion correspondiente de la ventana.
    void dibujar_sprite(SDL2pp::Renderer& renderer, SDL2pp::Texture& sprite_sheet,
                    const SDL_Rect& sprite, float x, float y, float escala,
                    orientacion_e orientacion, const int id);

    // Dibuja los patos del 'estado_actual' en la ventana.
    void dibujar_patos(EstadoJuego& estado_actual, SDL2pp::Renderer& renderer);

    // Dibuja el 'estado_actual' en la ventana.
    void dibujar_estado_juego(EstadoJuego& estado_actual, SDL2pp::Renderer& renderer);

public:
    // Constructor de la clase.
    explicit Dibujador(Renderer& renderer, const std::string& ruta_mapa, const int id_jugador, Queue<EstadoJuego>& cola_recibidor);

    // Renderiza la imagen del estado actual de la partida para el 'Cliente'.
    void renderizar(Renderer& renderer);

    // Deshabilito las copias.
    Dibujador(const Dibujador&) = delete;
    Dibujador& operator=(const Dibujador&) = delete;

    // Permito el movimiento del objeto.
    Dibujador(Dibujador&&) = default;
    Dibujador& operator=(Dibujador&&) = default;
};

#endif // CLIENT_DIBUJADOR_H
