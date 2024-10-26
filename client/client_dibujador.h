#ifndef CLIENT_DIBUJADOR_H
#define CLIENT_DIBUJADOR_H

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>
#include <vector>

#include "client_parseador.h"

using namespace SDL2pp;

// La clase 'Dibujador' implementa la logica
// del dibujo de la partida para el 'Cliente'.
class Dibujador {
private:
    Parseador parseador;

    // Funcion provisoria (TESTING).
    void dibujar_sprites_fila(SDL2pp::Renderer& renderer, SDL2pp::Texture& spriteSheetPato, 
                          const std::vector<SDL_Rect>& spritesPato, 
                          int anchoVentana, int altoVentana);

public:
    // Constructor de la clase.
    explicit Dibujador();

    // Renderiza la imagen del estado actual de la partida para el 'Cliente'.
    void renderizar(Renderer& renderer, Window& window);

    // Deshabilito las copias.
    Dibujador(const Dibujador&) = delete;
    Dibujador& operator=(const Dibujador&) = delete;

    // Permito el movimiento del objeto.
    Dibujador(Dibujador&&) = default;
    Dibujador& operator=(Dibujador&&) = default;
};

#endif
