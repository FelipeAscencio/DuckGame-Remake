#include "client_parseador.h"

#define CERO 0
#define UNO 1
#define TRES 3
#define BORDE_FINO_SPRITESHEET 1
#define BORDE_GRUESO_SPRITESHEET 10
#define TIRA_COMPLETA_SPRITES 6
#define MEDIA_TIRA_SPRITES 3
#define TIRA_COMPLETA_CAJAS 4
#define TAMANIO_SPRITE_GRANDE 32
#define TAMANIO_SPRITE_MEDIANO 16
#define TAMANIO_SPRITE_CHICO 8
#define INICIO_PATO_QUACK_X 194
#define INICIO_AK_47_Y 19
#define INICIO_CAJA_X 183
#define INICIO_CAJA_Y 20
#define INICIO_ARMADURA_X 387
#define INICIO_ARMADURA_Y 13

using namespace SDL2pp;

Parseador::Parseador() {}

void Parseador::iterador_de_parseo(std::vector<SDL_Rect>& sprites, int cantidad_sprites, int x,
                                   int y, int tamanio_sprite) {
    for (int i = CERO; i < cantidad_sprites; ++i) {
        SDL_Rect rect;
        rect.x = x + i * tamanio_sprite;
        rect.y = y;
        rect.w = tamanio_sprite;
        rect.h = tamanio_sprite;
        sprites.push_back(rect);
    }
}

std::vector<SDL_Rect> Parseador::obtener_sprites_pato() {
    std::vector<SDL_Rect> sprites_pato;
    int tamanio_sprite = TAMANIO_SPRITE_GRANDE;

    // Parseo de los sprites del pato base.
    int x_inicial = BORDE_FINO_SPRITESHEET;
    int y_inicial = BORDE_GRUESO_SPRITESHEET;
    iterador_de_parseo(sprites_pato, TIRA_COMPLETA_SPRITES, x_inicial, y_inicial, tamanio_sprite);
    y_inicial += tamanio_sprite;
    iterador_de_parseo(sprites_pato, MEDIA_TIRA_SPRITES, x_inicial, y_inicial, tamanio_sprite);
    y_inicial += tamanio_sprite;
    iterador_de_parseo(sprites_pato, MEDIA_TIRA_SPRITES, x_inicial, y_inicial, tamanio_sprite);

    // Parseo de los sprites del pato haciendo 'quack'.
    x_inicial = INICIO_PATO_QUACK_X;
    y_inicial = BORDE_GRUESO_SPRITESHEET;
    iterador_de_parseo(sprites_pato, TIRA_COMPLETA_SPRITES, x_inicial, y_inicial, tamanio_sprite);
    y_inicial += tamanio_sprite;
    iterador_de_parseo(sprites_pato, MEDIA_TIRA_SPRITES, x_inicial, y_inicial, tamanio_sprite);
    y_inicial += tamanio_sprite;
    iterador_de_parseo(sprites_pato, MEDIA_TIRA_SPRITES, x_inicial, y_inicial, tamanio_sprite);

    return sprites_pato;
}

std::vector<SDL_Rect> Parseador::obtener_sprites_ak() {
    std::vector<SDL_Rect> sprites_ak;
    int tamanio_sprite = TAMANIO_SPRITE_GRANDE;

    int x_inicial = BORDE_FINO_SPRITESHEET;
    int y_inicial = INICIO_AK_47_Y;
    iterador_de_parseo(sprites_ak, UNO, x_inicial, y_inicial, tamanio_sprite);

    return sprites_ak;
}

std::vector<SDL_Rect> Parseador::obtener_sprites_caja() {
    std::vector<SDL_Rect> sprites_caja;
    int tamanio_sprite = TAMANIO_SPRITE_MEDIANO;

    int x_inicial = INICIO_CAJA_X;
    int y_inicial = INICIO_CAJA_Y;
    iterador_de_parseo(sprites_caja, TIRA_COMPLETA_CAJAS, x_inicial, y_inicial, tamanio_sprite);

    return sprites_caja;
}

std::vector<SDL_Rect> Parseador::obtener_sprites_armadura() {
    std::vector<SDL_Rect> sprites_armadura;
    int tamanio_sprite = TAMANIO_SPRITE_GRANDE;
    int x_inicial = INICIO_ARMADURA_X;
    int y_inicial = INICIO_ARMADURA_Y;

    // Correccion porque el 'sprite' de la tira esta mal en relacion a la posicion del Pato.
    iterador_de_parseo(sprites_armadura, UNO, x_inicial + (TAMANIO_SPRITE_GRANDE * TRES), y_inicial,
                       tamanio_sprite);
    iterador_de_parseo(sprites_armadura, TIRA_COMPLETA_SPRITES - UNO,
                       x_inicial + TAMANIO_SPRITE_GRANDE, y_inicial, tamanio_sprite);
    y_inicial += tamanio_sprite;
    iterador_de_parseo(sprites_armadura, MEDIA_TIRA_SPRITES, x_inicial, y_inicial, tamanio_sprite);
    y_inicial += tamanio_sprite;
    iterador_de_parseo(sprites_armadura, MEDIA_TIRA_SPRITES, x_inicial, y_inicial, tamanio_sprite);

    return sprites_armadura;
}

std::vector<SDL_Rect> Parseador::obtener_sprites_escopeta() {
    std::vector<SDL_Rect> sprites_escopeta;
    int tamanio_sprite = TAMANIO_SPRITE_GRANDE;

    int x_inicial = BORDE_FINO_SPRITESHEET;
    int y_inicial = INICIO_AK_47_Y;
    iterador_de_parseo(sprites_escopeta, UNO, x_inicial, y_inicial, tamanio_sprite);

    return sprites_escopeta;
}

std::vector<SDL_Rect> Parseador::obtener_sprites_laser() {
    std::vector<SDL_Rect> sprites_laser;
    int tamanio_sprite = TAMANIO_SPRITE_GRANDE;

    int x_inicial = BORDE_FINO_SPRITESHEET;
    int y_inicial = INICIO_AK_47_Y;
    iterador_de_parseo(sprites_laser, UNO, x_inicial, y_inicial, tamanio_sprite);

    return sprites_laser;
}

std::vector<SDL_Rect> Parseador::obtener_sprites_pistola() {
    std::vector<SDL_Rect> sprites_pistola;
    int tamanio_sprite = TAMANIO_SPRITE_GRANDE;

    int x_inicial = BORDE_FINO_SPRITESHEET;
    int y_inicial = INICIO_AK_47_Y;
    iterador_de_parseo(sprites_pistola, UNO, x_inicial, y_inicial, tamanio_sprite);

    return sprites_pistola;
}
