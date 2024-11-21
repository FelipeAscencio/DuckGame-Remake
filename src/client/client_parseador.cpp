#include "client_parseador.h"

#define CERO 0
#define UNO 1
#define DOS 2
#define TRES 3
#define CUATRO 4
#define TIRA_COMPLETA_SPRITES 6
#define MEDIA_TIRA_SPRITES 3
#define TIRA_COMPLETA_CAJAS 4
#define TAMANIO_SPRITE_GRANDE 32
#define TAMANIO_SPRITES_BUG 31  // Hay algunos sprites que no llegan justo a 32.
#define TAMANIO_SPRITE_MEDIANO 16
#define TAMANIO_SPRITE_CHICO 8
#define TAMANIO_SPRITE_CHICO_BUG 7 // Hay algunos sprites que no llegan justo a 8.
#define INICIO_PATO_X 1
#define INICIO_PATO_Y 10
#define INICIO_PATO_QUACK_X 194
#define INICIO_PATO_QUACK_Y 10
#define INICIO_CAJA_X 183
#define INICIO_CAJA_Y 20
#define INICIO_ARMADURA_X 387
#define INICIO_ARMADURA_Y 13
#define INICIO_CASCO_X 387
#define INICIO_CASCO_Y 213
#define INICIO_AK_47_X 1
#define INICIO_AK_47_Y 19
#define INICIO_BALAS_AK_X 2
#define INICIO_BALAS_AK_Y 205
#define INICIO_ESCOPETA_X 1
#define INICIO_ESCOPETA_Y 25
#define INICIO_BALAS_ESCOPETA_X 48
#define INICIO_BALAS_ESCOPETA_Y 119
#define INICIO_MANGUM_X 1
#define INICIO_MAGNUM_Y 47
#define INICIO_BALAS_MAGNUM_X 48
#define INICIO_BALAS_MAGNUM_Y 89
#define INICIO_SNIPER_X 36
#define INICIO_SNIPER_Y 237
#define INICIO_BALAS_SNIPER_X 35
#define INICIO_BALAS_SNIPER_Y 62
#define INICIO_LASER_X 336
#define INICIO_LASER_Y 94
#define INICIO_BALAS_LASER_X 1
#define INICIO_BALAS_LASER_Y 138
#define INICIO_CASCO_LOOT_X 602
#define INICIO_CASCO_LOOT_Y 316
#define INICIO_ARMADURA_LOOT_X 585
#define INICIO_ARMADURA_LOOT_Y 289

using namespace SDL2pp;

Parseador::Parseador() {}

void Parseador::iterador_de_parseo(std::vector<SDL_Rect>& sprites, const int& cantidad_sprites,
                                   const int& x, const int& y, const int& tamanio_sprite) {
    for (int i = CERO; i < cantidad_sprites; ++i) {
        SDL_Rect rect;
        rect.x = x + i * tamanio_sprite;
        rect.y = y;
        rect.w = tamanio_sprite;
        rect.h = tamanio_sprite;
        sprites.push_back(rect);
    }
}

void Parseador::parsear_sniper(std::vector<SDL_Rect>& sprites) {
    int tamanio_sprite = TAMANIO_SPRITE_CHICO;
    SDL_Rect rect;
    rect.x = INICIO_SNIPER_X;
    rect.y = INICIO_SNIPER_Y;
    rect.w = (tamanio_sprite * CUATRO);
    rect.h = tamanio_sprite;
    sprites.push_back(rect);
}

std::vector<SDL_Rect> Parseador::obtener_sprites_pato() {
    std::vector<SDL_Rect> sprites_pato;
    int tamanio_sprite = TAMANIO_SPRITE_GRANDE;

    // Parseo de los sprites del pato base.
    int x_inicial = INICIO_PATO_X;
    int y_inicial = INICIO_PATO_Y;
    iterador_de_parseo(sprites_pato, TIRA_COMPLETA_SPRITES, x_inicial, y_inicial, tamanio_sprite);
    y_inicial += tamanio_sprite;
    iterador_de_parseo(sprites_pato, MEDIA_TIRA_SPRITES, x_inicial, y_inicial, tamanio_sprite);
    y_inicial += tamanio_sprite;
    iterador_de_parseo(sprites_pato, MEDIA_TIRA_SPRITES, x_inicial, y_inicial, tamanio_sprite);

    // Parseo de los sprites del pato haciendo 'quack'.
    x_inicial = INICIO_PATO_QUACK_X;
    y_inicial = INICIO_PATO_QUACK_Y;
    iterador_de_parseo(sprites_pato, TIRA_COMPLETA_SPRITES, x_inicial, y_inicial, tamanio_sprite);
    y_inicial += tamanio_sprite;
    iterador_de_parseo(sprites_pato, MEDIA_TIRA_SPRITES, x_inicial, y_inicial, tamanio_sprite);
    y_inicial += tamanio_sprite;
    iterador_de_parseo(sprites_pato, MEDIA_TIRA_SPRITES, x_inicial, y_inicial, tamanio_sprite);

    return sprites_pato;
}

std::vector<SDL_Rect> Parseador::obtener_sprites_ak() {
    std::vector<SDL_Rect> sprites_ak;
    int tamanio_sprite = TAMANIO_SPRITES_BUG;
    int x_inicial = INICIO_AK_47_X;
    int y_inicial = INICIO_AK_47_Y;
    iterador_de_parseo(sprites_ak, UNO, x_inicial, y_inicial, tamanio_sprite);

    tamanio_sprite = TAMANIO_SPRITE_CHICO_BUG;
    x_inicial = INICIO_BALAS_AK_X;
    y_inicial = INICIO_BALAS_AK_Y;
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

void Parseador::obtener_sprites_armadura(std::vector<SDL_Rect>& sprites_equipamiento) {
    int tamanio_sprite = TAMANIO_SPRITE_GRANDE;
    int x_inicial = INICIO_ARMADURA_X;
    int y_inicial = INICIO_ARMADURA_Y;

    // Correccion porque el 'sprite' de la tira esta mal en relacion a la posicion del Pato.
    iterador_de_parseo(sprites_equipamiento, UNO, x_inicial + (TAMANIO_SPRITE_GRANDE * TRES),
                       y_inicial, tamanio_sprite);
    iterador_de_parseo(sprites_equipamiento, TIRA_COMPLETA_SPRITES - UNO,
                       x_inicial + TAMANIO_SPRITE_GRANDE, y_inicial, tamanio_sprite);
    y_inicial += tamanio_sprite;
    iterador_de_parseo(sprites_equipamiento, MEDIA_TIRA_SPRITES, x_inicial, y_inicial,
                       tamanio_sprite);
    y_inicial += tamanio_sprite;
    iterador_de_parseo(sprites_equipamiento, MEDIA_TIRA_SPRITES, x_inicial, y_inicial,
                       tamanio_sprite);
}

void Parseador::obtener_sprites_casco(std::vector<SDL_Rect>& sprites_equipamiento) {
    int tamanio_sprite = TAMANIO_SPRITES_BUG;
    int x_inicial = INICIO_CASCO_X;
    int y_inicial = INICIO_CASCO_Y;
    iterador_de_parseo(sprites_equipamiento, UNO, x_inicial, y_inicial, tamanio_sprite);
}

std::vector<SDL_Rect> Parseador::obtener_sprites_equipamiento() {
    std::vector<SDL_Rect> sprites_equipamiento;

    obtener_sprites_armadura(sprites_equipamiento);
    obtener_sprites_casco(sprites_equipamiento);

    return sprites_equipamiento;
}

std::vector<SDL_Rect> Parseador::obtener_sprites_escopeta() {
    std::vector<SDL_Rect> sprites_escopeta;
    int tamanio_sprite = TAMANIO_SPRITES_BUG;
    int x_inicial = INICIO_ESCOPETA_X;
    int y_inicial = INICIO_ESCOPETA_Y;
    iterador_de_parseo(sprites_escopeta, UNO, x_inicial, y_inicial, tamanio_sprite);

    tamanio_sprite = TAMANIO_SPRITE_MEDIANO;
    x_inicial = INICIO_BALAS_ESCOPETA_X;
    y_inicial = INICIO_BALAS_ESCOPETA_Y;
    iterador_de_parseo(sprites_escopeta, UNO, x_inicial, y_inicial, tamanio_sprite);
    iterador_de_parseo(sprites_escopeta, UNO, x_inicial + TAMANIO_SPRITE_MEDIANO, y_inicial,
                       tamanio_sprite);
    iterador_de_parseo(sprites_escopeta, UNO, x_inicial + (DOS * TAMANIO_SPRITE_MEDIANO), y_inicial,
                       tamanio_sprite);

    return sprites_escopeta;
}

std::vector<SDL_Rect> Parseador::obtener_sprites_laser() {
    std::vector<SDL_Rect> sprites_laser;
    int tamanio_sprite = TAMANIO_SPRITES_BUG;
    int x_inicial = INICIO_LASER_X;
    int y_inicial = INICIO_LASER_Y;
    iterador_de_parseo(sprites_laser, UNO, x_inicial, y_inicial, tamanio_sprite);

    tamanio_sprite = TAMANIO_SPRITE_CHICO;
    x_inicial = INICIO_BALAS_LASER_X;
    y_inicial = INICIO_BALAS_LASER_Y;
    iterador_de_parseo(sprites_laser, UNO, x_inicial, y_inicial, tamanio_sprite);

    return sprites_laser;
}

std::vector<SDL_Rect> Parseador::obtener_sprites_pistola() {
    std::vector<SDL_Rect> sprites_pistola;
    int tamanio_sprite = TAMANIO_SPRITES_BUG;
    int x_inicial = INICIO_MANGUM_X;
    int y_inicial = INICIO_MAGNUM_Y;
    iterador_de_parseo(sprites_pistola, UNO, x_inicial, y_inicial, tamanio_sprite);

    tamanio_sprite = TAMANIO_SPRITE_MEDIANO;
    x_inicial = INICIO_BALAS_MAGNUM_X;
    y_inicial = INICIO_BALAS_MAGNUM_Y;
    iterador_de_parseo(sprites_pistola, UNO, x_inicial, y_inicial, tamanio_sprite);
    iterador_de_parseo(sprites_pistola, UNO, x_inicial + TAMANIO_SPRITE_MEDIANO, y_inicial,
                       tamanio_sprite);
    iterador_de_parseo(sprites_pistola, UNO, x_inicial + (TAMANIO_SPRITE_MEDIANO * DOS), y_inicial,
                       tamanio_sprite);

    return sprites_pistola;
}

std::vector<SDL_Rect> Parseador::obtener_sprites_sniper() {
    std::vector<SDL_Rect> sprites_sniper;
    parsear_sniper(sprites_sniper);

    int tamanio_sprite = TAMANIO_SPRITE_MEDIANO;
    int x_inicial = INICIO_BALAS_SNIPER_X;
    int y_inicial = INICIO_BALAS_SNIPER_Y;
    iterador_de_parseo(sprites_sniper, UNO, x_inicial, y_inicial, tamanio_sprite);

    return sprites_sniper;
}

std::vector<SDL_Rect> Parseador::obtener_sprites_looteables() {
    std::vector<SDL_Rect> sprites_loot;
    int tamanio_sprite = TAMANIO_SPRITE_MEDIANO;
    int x_inicial = INICIO_ARMADURA_LOOT_X;
    int y_inicial = INICIO_ARMADURA_LOOT_Y;
    iterador_de_parseo(sprites_loot, UNO, x_inicial, y_inicial, tamanio_sprite);

    tamanio_sprite = TAMANIO_SPRITE_MEDIANO;
    x_inicial = INICIO_CASCO_LOOT_X;
    y_inicial = INICIO_CASCO_LOOT_Y;
    iterador_de_parseo(sprites_loot, UNO, x_inicial, y_inicial, tamanio_sprite);

    return sprites_loot;
}
