#ifndef CLIENT_DIBUJADOR_H
#define CLIENT_DIBUJADOR_H

#include <vector>

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "client_parseador.h"

using namespace SDL2pp;

// La clase 'Dibujador' implementa la logica
// del dibujo de la partida para el 'Cliente'.
class Dibujador {
private:
    Parseador parseador;
    Texture spriteSheetPato;
    Texture spriteSheetAK;
    Texture spriteSheetCaja;
    Texture spriteSheetArmadura;
    Texture mapa;
    std::vector<SDL_Rect> spritesPato;
    std::vector<SDL_Rect> spritesAK;
    std::vector<SDL_Rect> spritesCaja;
    std::vector<SDL_Rect> spritesArmadura;

    // Funcion provisoria (TESTING).
    void dibujar_sprites_fila(SDL2pp::Renderer& renderer, SDL2pp::Texture& spriteSheet,
                              const std::vector<SDL_Rect>& sprites, float x, float y, float escala, float separacion);

    // Convierte el 'X' e 'Y' recibido en valor relativo en relacion al 'X' e 'Y' maximos.
    std::pair<float, float> convertir_a_relativo(int x, int y);

    // Dibuja un sprite en la posicion correspondiente de la ventana.
    void dibujar_sprite(SDL2pp::Renderer& renderer, SDL2pp::Texture& spriteSheet,
                               const SDL_Rect& sprite, float x, float y, float escala);

public:
    // Constructor de la clase.
    explicit Dibujador(Renderer& renderer, const std::string& ruta_mapa);

    // Renderiza la imagen del estado actual de la partida para el 'Cliente'.
    void renderizar(Renderer& renderer, const int estado);

    // Deshabilito las copias.
    Dibujador(const Dibujador&) = delete;
    Dibujador& operator=(const Dibujador&) = delete;

    // Permito el movimiento del objeto.
    Dibujador(Dibujador&&) = default;
    Dibujador& operator=(Dibujador&&) = default;
};

#endif
