// Copyright 2024 Axel Zielonka y Felipe Ascencio.
#ifndef CLIENT_PARSEADOR_H
#define CLIENT_PARSEADOR_H

#include <vector>

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

// Suprimimos el reporte en 'CPPLINT' de los 'namespaces'.
using namespace SDL2pp;  // NOLINT(build/namespaces)

// La clase 'Parseador' se encarga de obtener
// y agrupar todos los 'sprites' a utilizar.
class Parseador {
private:
    // Agrega los "Rect" al vector de "sprites" en base a los parametros recibidos.
    void iterador_de_parseo(std::vector<SDL_Rect>& sprites, const int& cantidad_sprites,
                            const int& x, const int& y, const int& tamanio_sprite);

    // Parsea el "sniper" con la correccion necesaria por el tipo de 'sprite' que tiene (alargado).
    void parsear_sniper(std::vector<SDL_Rect>& sprites);

    // Parsea los 'sprites' de la 'armadura'.
    void obtener_sprites_armadura(std::vector<SDL_Rect>& sprites_equipamiento);

    // Parsea los 'sprites' del 'casco'.
    void obtener_sprites_casco(std::vector<SDL_Rect>& sprites_equipamiento);

public:
    // Constructor de la clase.
    Parseador();

    // Devuelve los 'sprites' de movimiento del 'pato blanco'.
    std::vector<SDL_Rect> obtener_sprites_pato();

    // Devuelve los 'sprites' del 'ak47'.
    std::vector<SDL_Rect> obtener_sprites_ak();

    // Devuelve los 'sprites' de la 'caja'.
    std::vector<SDL_Rect> obtener_sprites_caja();

    // Devuelve los 'sprites' de la 'armadura' y el 'casco'.
    std::vector<SDL_Rect> obtener_sprites_equipamiento();

    // Devuelve los 'sprites' del 'escopeta'.
    std::vector<SDL_Rect> obtener_sprites_escopeta();

    // Devuelve los 'sprites' del 'laser'.
    std::vector<SDL_Rect> obtener_sprites_laser();

    // Devuelve los 'sprites' del 'pistola'.
    std::vector<SDL_Rect> obtener_sprites_pistola();

    // Devuelve los 'sprites' del 'sniper'.
    std::vector<SDL_Rect> obtener_sprites_sniper();

    // Devuelve los 'sprites' de los equipamientos 'looteables'.
    std::vector<SDL_Rect> obtener_sprites_looteables();

    // Deshabilito las copias.
    Parseador(const Parseador&) = delete;
    Parseador& operator=(const Parseador&) = delete;

    // Permito el movimiento del objeto.
    Parseador(Parseador&&) = default;
    Parseador& operator=(Parseador&&) = default;
};

#endif  // CLIENT_PARSEADOR_H
