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
    Queue<EstadoJuego>& queue;
    Parseador parseador;
    Texture spriteSheetPato;
    Texture spriteSheetAK; // Faltan la bala.
    Texture spriteSheetCaja;
    Texture spriteSheetArmadura; // Falta el casco, la pechera y el casco loteable.
    Texture spriteSheetEscopeta; // Falta la escopeta y las balas.
    Texture spriteSheetLaser; // Falta el arma y las balas.
    Texture spriteSheetPistola; // Falta el arma y las balas.
    Texture mapa;
    std::vector<SDL_Rect> spritesPato;
    std::vector<SDL_Rect> spritesAK;
    std::vector<SDL_Rect> spritesCaja;
    std::vector<SDL_Rect> spritesArmadura;
    std::vector<SDL_Rect> spritesEscopeta;
    std::vector<SDL_Rect> spritesLaser;
    std::vector<SDL_Rect> spritesPistola;

    // Funcion provisoria (TESTING).
    void dibujar_sprites_fila(SDL2pp::Renderer& renderer, SDL2pp::Texture& spriteSheet,
                              const std::vector<SDL_Rect>& sprites, int anchoVentana,
                              int altoVentana, float x, float y, float escala, float separacion);

    // Devuelve el 'Rect' correspondiente segun los parametros recibidos.
    SDL2pp::Rect calcular_dst_rect(float x, float y, float escala);

    // Convierte el 'X' e 'Y' recibido en el valor relativo en relacion al 'X' e 'Y' maximos.
    std::pair<float, float> convertir_a_relativo(int x, int y);

    // Dibuja el pato enemigo con el color correspondiente segun su id.
    void dibujar_pato_enemigo(SDL2pp::Renderer& renderer, SDL2pp::Texture& spriteSheet,
                               const SDL_Rect& sprite, SDL2pp::Rect& dstRect, const int id, const double angle, SDL_RendererFlip& flip);

    // Dibuja un sprite en la posicion correspondiente de la ventana.
    void dibujar_sprite(SDL2pp::Renderer& renderer, SDL2pp::Texture& spriteSheet,
                    const SDL_Rect& sprite, float x, float y, float escala,
                    orientacion_e orientacion, const int id);

    void parsear_estado_juego(EstadoJuego& estado_actual, SDL2pp::Renderer& renderer);

public:
    // Constructor de la clase.
    explicit Dibujador(Renderer& renderer, const std::string& ruta_mapa, const int id_jugador, Queue<EstadoJuego>& queue_recibidor);

    // Renderiza la imagen del estado actual de la partida para el 'Cliente'.
    void renderizar(Renderer& renderer);

    // Deshabilito las copias.
    Dibujador(const Dibujador&) = delete;
    Dibujador& operator=(const Dibujador&) = delete;

    // Permito el movimiento del objeto.
    Dibujador(Dibujador&&) = default;
    Dibujador& operator=(Dibujador&&) = default;
};

#endif
