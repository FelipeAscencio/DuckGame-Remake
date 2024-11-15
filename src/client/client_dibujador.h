// Copyright 2024 Axel Zielonka y Felipe Ascencio.
#ifndef CLIENT_DIBUJADOR_H
#define CLIENT_DIBUJADOR_H

#include <string>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2pp/SDL2pp.hh>

#include "../common/estado_juego.h"
#include "../common/orientacion.h"
#include "../common/queue.h"

#include "client_parseador.h"

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
    Texture sprite_sheet_ak;
    Texture sprite_sheet_caja;
    Texture sprite_sheet_equipamiento;
    Texture sprite_sheet_escopeta;
    Texture sprite_sheet_laser;
    Texture sprite_sheet_pistola;
    Texture sprite_sheet_sniper;
    Texture mapa;
    std::vector<SDL_Rect> sprites_pato;
    std::vector<SDL_Rect> sprites_ak;
    std::vector<SDL_Rect> sprites_caja;
    std::vector<SDL_Rect> sprites_equipamiento;
    std::vector<SDL_Rect> sprites_escopeta;
    std::vector<SDL_Rect> sprites_laser;
    std::vector<SDL_Rect> sprites_pistola;
    std::vector<SDL_Rect> sprites_sniper;
    std::vector<SDL_Rect> sprites_lootables;
    Mix_Chunk* sonido_ak;
    Mix_Chunk* sonido_explosion;
    Mix_Chunk* sonido_laser;
    Mix_Chunk* sonido_pistola;
    Mix_Chunk* sonido_escopeta;
    Mix_Chunk* sonido_sniper;
    Mix_Chunk* sonido_quack;

    // Devuelve el 'Rect' correspondiente segun los parametros recibidos.
    SDL2pp::Rect calcular_dst_rect(float x, float y, float escala);

    // Convierte el 'X' e 'Y' recibido en el valor relativo en relacion al 'X' e 'Y' maximos.
    std::pair<float, float> convertir_a_relativo(float x, float y);

    // Dibuja el pato enemigo con el color correspondiente segun su id.
    void dibujar_pato_enemigo(SDL2pp::Renderer& renderer, SDL2pp::Texture& sprite_sheet,
                              const SDL_Rect& sprite, SDL2pp::Rect& dst_rect, const int id,
                              const double angle, SDL_RendererFlip& flip);

    // Dibuja un sprite en la posicion correspondiente de la ventana.
    void dibujar_sprite(SDL2pp::Renderer& renderer, SDL2pp::Texture& sprite_sheet,
                        const SDL_Rect& sprite, float x, float y, float escala,
                        orientacion_e orientacion, const int id);

    // Dibuja un pato vivo en en la ventana.
    void dibujar_pato_vivo(SDL2pp::Renderer& renderer, float& escala, int& id, float& x_relativo, float& y_relativo, orientacion_e& orientacion, estado_pato_e& estado_pato);

    // Dibuja la armadura de un pato.
    void dibujar_armadura_pato(SDL2pp::Renderer& renderer, float& escala, float& x_relativo, float& y_relativo, orientacion_e& orientacion, estado_pato_e& estado);

    // Dibuja el arma de un pato.
    void dibujar_arma_pato(SDL2pp::Renderer& renderer, float& escala, float& x_relativo, float& y_relativo, orientacion_e& orientacion, estado_pato_e& estado, int& id_arma);

    // Dibuja el casco de un pato.
    void dibujar_casco_pato(SDL2pp::Renderer& renderer, float& escala, float& x_relativo, float& y_relativo, orientacion_e& orientacion, estado_pato_e& estado);

    // Dibuja los patos del 'estado_actual' en la ventana.
    void dibujar_patos(EstadoJuego& estado_actual, SDL2pp::Renderer& renderer);

    // Dibuja el 'estado_actual' en la ventana.
    void dibujar_estado_juego(EstadoJuego& estado_actual, SDL2pp::Renderer& renderer);

    // Dibuja los patos en el tablero.
    void dibujar_patos_tablero(SDL2pp::Renderer& renderer);

    // Dibuja el puntaje en el tablero.
    void dibujar_puntos_tablero(SDL2pp::Renderer& renderer, const std::vector<int>& puntajes);

    // Dibuja el 'tablero' con los puntajes actuales del juego.
    void dibujar_tablero(SDL2pp::Renderer& renderer, const std::vector<int>& puntajes);

    // Reproduce el sonido del 'disparo de ak'.
    void reproducir_disparo_ak();

    // Reproduce el sonido de la 'explosion'.
    void reproducir_explosion();

    // Reproduce el sonido de la 'disparo de escopeta'.
    void reproducir_disparo_escopeta();

    // Reproduce el sonido del 'disparo laser'.
    void reproducir_disparo_laser();

    // Reproduce el sonido del 'disparo de sniper'.
    void reproducir_disparo_sniper();

    // Reproduce el sonido del 'disparo de pistola'.
    void reproducir_disparo_pistola();

    // Reproduce el sonido del 'quack'.
    void reproducir_quack();

public:
    // Constructor de la clase.
    explicit Dibujador(Renderer& renderer, const std::string& ruta_mapa, const int id_jugador,
                       Queue<EstadoJuego>& cola_recibidor);

    // Renderiza la imagen del estado actual de la partida para el 'Cliente'.
    void renderizar(Renderer& renderer);

    // Deshabilito las copias.
    Dibujador(const Dibujador&) = delete;
    Dibujador& operator=(const Dibujador&) = delete;

    // Permito el movimiento del objeto.
    Dibujador(Dibujador&&) = default;
    Dibujador& operator=(Dibujador&&) = default;
};

#endif  // CLIENT_DIBUJADOR_H
