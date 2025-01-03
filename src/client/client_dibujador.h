// Copyright 2024 Axel Zielonka y Felipe Ascencio.
#ifndef CLIENT_DIBUJADOR_H
#define CLIENT_DIBUJADOR_H

#include <algorithm>
#include <string>
#include <thread>
#include <utility>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2pp/SDL2pp.hh>

#include "../common/estado_juego.h"
#include "../common/orientacion.h"
#include "../common/queue.h"

#include "client_parseador.h"

// Suprimimos el reporte en 'CPPLINT' de los 'namespaces'.
using namespace SDL2pp;  // NOLINT(build/namespaces)

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
    Texture mapa1;
    Texture mapa2;
    Texture pantalla_victoria;
    Texture pantalla_derrota;
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
    int x_min;
    int y_min;
    int x_max;
    int y_max;

    // Devuelve el 'Rect' correspondiente segun los parametros recibidos.
    SDL2pp::Rect calcular_dst_rect(float& x, float& y, float& escala);

    // Convierte el 'X' e 'Y' recibido en el valor relativo en relacion al 'X' e 'Y' maximos.
    std::pair<float, float> convertir_a_relativo(float& x, float& y);

    // Dibuja el pato pintado segun el color correspondiente a su id.
    void dibujar_pato_pintado(SDL2pp::Renderer& renderer, SDL2pp::Texture& sprite_sheet,
                              const SDL_Rect& sprite, SDL2pp::Rect& dst_rect, const int& id,
                              const double& angle, SDL_RendererFlip& flip);

    // Dibuja un sprite en la posicion correspondiente de la ventana.
    void dibujar_sprite(SDL2pp::Renderer& renderer, SDL2pp::Texture& sprite_sheet,
                        const SDL_Rect& sprite, float x, float y, float& escala,
                        orientacion_e orientacion, const int& id);

    // Calcula los limites del 'Zoom' en relacion a los patos vivos, y si hay nuevo minimo o maximo
    // actualiza el valor.
    void calcular_limites_camara(float& x_relativo, float& y_relativo);

    // Dibuja un pato vivo en en la ventana.
    void dibujar_pato_vivo(SDL2pp::Renderer& renderer, float& escala, int& id, float& x_relativo,
                           float& y_relativo, orientacion_e orientacion, estado_pato_e& estado_pato,
                           sonido_e& sonido);

    // Dibuja la armadura de un pato.
    void dibujar_armadura_pato(SDL2pp::Renderer& renderer, float& escala, float& x_relativo,
                               const float& y_relativo, orientacion_e orientacion,
                               estado_pato_e& estado);

    // Dibuja el sniper (Metodo particular porque es el unico sprite que no es cuadrado).
    void dibujar_sniper(SDL2pp::Renderer& renderer, float x, float y, orientacion_e orientacion);

    // Preparar la renderizacion del sprite, para luego dibujarlo.
    void renderizar_sniper(SDL2pp::Renderer& renderer, const float& x_relativo,
                           const float& y_relativo, orientacion_e& orientacion,
                           estado_pato_e& estado);

    // Dibuja el arma de un pato.
    void dibujar_arma_pato(SDL2pp::Renderer& renderer, float& escala, float& x_relativo,
                           float& y_relativo, orientacion_e& orientacion, estado_pato_e& estado,
                           const int& id_arma);

    // Dibuja el casco de un pato.
    void dibujar_casco_pato(SDL2pp::Renderer& renderer, float& escala, const float& x_relativo,
                            const float& y_relativo, orientacion_e orientacion,
                            estado_pato_e& estado);

    // Reproduce el sonido del 'disparo de ak'.
    void reproducir_disparo_ak();

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

    // Reproduce el sonido emitido por el 'Pato' segun corresponda.
    void reproducir_sonido_pato(const int& id_arma, const sonido_e& sonido);

    // Dibuja los patos del 'estado_actual' en la ventana.
    void dibujar_patos(const EstadoJuego& estado_actual, SDL2pp::Renderer& renderer);

    // Obtiene el 'Sprite Sheet' del arma o bala correspondiente al ID recibido.
    SDL2pp::Texture* obtener_sprite_sheet_arma_bala(const int& id_arma);

    // Obtiene los 'Sprites' del arma o bala correspondiente al ID recibido.
    std::vector<SDL_Rect>* obtener_sprites_arma_bala(const int& id_arma);

    // Obtiene el indice del perdigon actual de la bala.
    int obtener_indice_sprite(inclinacion_e& inclinacion);

    // Dibuja las balas del 'estado_actual' en la ventana.
    void dibujar_balas(const EstadoJuego& estado_actual, SDL2pp::Renderer& renderer);

    // Dibuja las armas spawneadas en el piso.
    void dibujar_armas(const EstadoJuego& estado_actual, SDL2pp::Renderer& renderer);

    // Dibuja los cascos spawneados en el piso.
    void dibujar_cascos(const EstadoJuego& estado_actual, SDL2pp::Renderer& renderer);

    // Dibuja las armaduras spawneadas en el piso.
    void dibujar_armaduras(const EstadoJuego& estado_actual, SDL2pp::Renderer& renderer);

    // Dibuja las cajas spawneadas en el piso en su respectivo estado (INTACTA - ROTA - MUY_ROTA).
    void dibujar_cajas(const EstadoJuego& estado_actual, SDL2pp::Renderer& renderer);

    // Dibuja el 'estado_actual' de la partida.
    void dibujar_estado_juego(EstadoJuego& estado_actual, SDL2pp::Renderer& renderer);

    // Reinicia los valores iniciales del 'Zoom' de la camara.
    void reiniciar_valores_zoom();

    // Verifica que los valores para aplicar el 'Zoom' de la camara sean validos, y si no los son
    // los corrige.
    void verificar_valores_zoom();

    // Imprime la interfaz grafica para que el cliente pueda ver el estado del juego.
    void mostrar_estado_juego(SDL2pp::Renderer& renderer);

    // Dibuja los patos en el tablero.
    void dibujar_patos_tablero(SDL2pp::Renderer& renderer);

    // Dibuja el puntaje en el tablero.
    void dibujar_puntos_tablero(SDL2pp::Renderer& renderer, const std::vector<int>& puntajes);

    // Dibuja el 'tablero' con los puntajes actuales del juego.
    void dibujar_tablero(SDL2pp::Renderer& renderer);

public:
    // Constructor de la clase.
    explicit Dibujador(Renderer& renderer, const int id_jugador,
                       Queue<EstadoJuego>& cola_recibidor);

    // Renderiza la imagen del estado actual de la partida para el 'Cliente'.
    void renderizar(Renderer& renderer, bool& juego_activo);

    // Deshabilito las copias.
    Dibujador(const Dibujador&) = delete;
    Dibujador& operator=(const Dibujador&) = delete;

    // Permito el movimiento del objeto.
    Dibujador(Dibujador&&) = default;
    Dibujador& operator=(Dibujador&&) = default;

    // Destructor de la clase.
    ~Dibujador();
};

#endif  // CLIENT_DIBUJADOR_H
