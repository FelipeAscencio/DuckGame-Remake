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

public:
    // Constructor de la clase.
    explicit Parseador();

    // Devuelve los 'sprites' de movimiento del 'pato blanco'.
    std::vector<SDL_Rect> obtener_sprites_pato();

    // Deshabilito las copias.
    Parseador(const Parseador&) = delete;
    Parseador& operator=(const Parseador&) = delete;

    // Permito el movimiento del objeto.
    Parseador(Parseador&&) = default;
    Parseador& operator=(Parseador&&) = default;
};

#endif
