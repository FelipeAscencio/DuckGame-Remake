#ifndef CLIENT_PARSEADOR_H
#define CLIENT_PARSEADOR_H

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>
#include <vector>

using namespace SDL2pp;

// La clase 'Parseador' se encarga de obtener
// y agrupar todos los 'sprites' a utilizar.
class Parseador {
private:

    // Agrega los "Rect" al vector de "sprites" en base a los parametros recibidos.
    void iterador_de_parseo(std::vector<SDL_Rect>& sprites, int cantidad_sprites, int x, int y, int tamanio_sprite);

public:
    // Constructor de la clase.
    explicit Parseador();

    // Devuelve los 'sprites' de movimiento del 'pato blanco'.
    std::vector<SDL_Rect> obtener_sprites_pato();

    // Devuelve los 'sprites' del 'ak47'.
    std::vector<SDL_Rect> obtener_sprites_ak();

    // Devuelve los 'sprites' de la 'caja'.
    std::vector<SDL_Rect> obtener_sprites_caja();

    // Devuelve los 'sprites' de la 'armadura'.
    std::vector<SDL_Rect> obtener_sprites_armadura();

    // Deshabilito las copias.
    Parseador(const Parseador&) = delete;
    Parseador& operator=(const Parseador&) = delete;

    // Permito el movimiento del objeto.
    Parseador(Parseador&&) = default;
    Parseador& operator=(Parseador&&) = default;
};

#endif
