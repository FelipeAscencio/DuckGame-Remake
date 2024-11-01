#include "client_dibujador.h"

#define RUTA_SPR_PATO "/sprites-pato-blanco.png"
#define RUTA_SPR_AK "/sprites-ak47.png"
#define RUTA_SPR_CAJAS "/sprites-cajas.png"
#define RUTA_SPR_ARMADURAS "/sprites-armaduras.png"
#define RUTA_SPR_ESCOPETA "/sprites-escopeta.png"
#define RUTA_SPR_LASER "/sprites-laser.png"
#define RUTA_SPR_PISTOLA "/sprites-pistola.png"
#define ANCHO_VENTANA 960
#define ALTO_VENTANA 720
#define MAX_COORD_X 200
#define MAX_COORD_Y 160
#define ANGULO_NULO 0.0
#define ANGULO_270 270.0
#define ESCALA_SPRITES_GRANDES 0.07
#define MAX_INTENSIDAD_RGB 255
#define CERO 0
#define UNO 1
#define DOS 2
#define TRES 3
#define CUATRO 4

using namespace SDL2pp;

Dibujador::Dibujador(Renderer& renderer, const std::string& ruta_mapa, const int id, Queue<EstadoJuego>& queue_recibidor):
        id_jugador(id), queue(queue_recibidor), parseador(),
        spriteSheetPato(renderer, DATA_PATH RUTA_SPR_PATO),
        spriteSheetAK(renderer, DATA_PATH RUTA_SPR_AK),
        spriteSheetCaja(renderer, DATA_PATH RUTA_SPR_CAJAS),
        spriteSheetArmadura(renderer, DATA_PATH RUTA_SPR_ARMADURAS),
        spriteSheetEscopeta(renderer, DATA_PATH RUTA_SPR_ESCOPETA),
        spriteSheetLaser(renderer, DATA_PATH RUTA_SPR_LASER),
        spriteSheetPistola(renderer, DATA_PATH RUTA_SPR_PISTOLA),
        mapa(renderer, (DATA_PATH + ruta_mapa).c_str()),
        spritesPato(parseador.obtener_sprites_pato()),
        spritesAK(parseador.obtener_sprites_ak()),
        spritesCaja(parseador.obtener_sprites_caja()),
        spritesArmadura(parseador.obtener_sprites_armadura()),
        spritesEscopeta(parseador.obtener_sprites_escopeta()),
        spritesLaser(parseador.obtener_sprites_laser()),
        spritesPistola(parseador.obtener_sprites_pistola()) {}

// PROVISORIA PARA TESTEAR LOS PARSEOS.
void Dibujador::dibujar_sprites_fila(SDL2pp::Renderer& renderer, SDL2pp::Texture& spriteSheet,
                                     const std::vector<SDL_Rect>& sprites, int anchoVentana,
                                     int altoVentana, float x, float y, float escala,
                                     float separacion) {
    int startX = static_cast<int>(anchoVentana * x);
    int startY = static_cast<int>(altoVentana * y);
    int scaledWidth = static_cast<int>(anchoVentana * escala);
    int scaledHeight = static_cast<int>(altoVentana * escala);
    int gap = static_cast<int>(anchoVentana * separacion);
    int contador = 0;

    for (size_t i = 0; i < sprites.size(); ++i) {
        if (contador >= 12) {
            contador = 0;
            startY += 50;
        }
        SDL_Rect dstRect;
        dstRect.x = startX + contador * (scaledWidth + gap);
        dstRect.y = startY;
        dstRect.w = scaledWidth;
        dstRect.h = scaledHeight;
        renderer.Copy(spriteSheet, sprites[i], dstRect);
        contador++;
    }
}

std::pair<float, float> Dibujador::convertir_a_relativo(int x, int y) {
    float x_convertido = static_cast<float>(x) / MAX_COORD_X;
    float y_convertido = static_cast<float>(y) / MAX_COORD_Y;
    return {x_convertido, y_convertido};
}

SDL2pp::Rect Dibujador::calcular_dst_rect(float x, float y, float escala) {
    int anchoVentana = ANCHO_VENTANA;
    int altoVentana = ALTO_VENTANA;
    int scaledWidth = static_cast<int>(anchoVentana * escala);
    int scaledHeight = static_cast<int>(altoVentana * escala);

    // Centramos el sprite en el eje 'X' y ponemos el '0' del eje 'Y' en la parte inferior del sprite.
    int dstX = static_cast<int>(anchoVentana * x) - (scaledWidth / DOS);
    int dstY = static_cast<int>(altoVentana * y) - scaledHeight;
    return SDL2pp::Rect(dstX, dstY, scaledWidth, scaledHeight);
}

void Dibujador::dibujar_pato_enemigo(SDL2pp::Renderer& renderer, SDL2pp::Texture& spriteSheet,
                               const SDL_Rect& sprite, SDL2pp::Rect& dstRect, const int id, const double angle, SDL_RendererFlip& flip){
    SDL_Color colorMod;
    if (id == UNO) { // ROJO
        colorMod = {255, 0, 0, 255};
    } else if (id == DOS) { // VERDE
        colorMod = {0, 255, 0, 255};
    } else if (id == TRES) { // AZUL
        colorMod = {0, 0, 255, 255};
    } else { // AMARILLO
        colorMod = {255, 255, 0, 255};
    }

    SDL_SetTextureColorMod(spriteSheet.Get(), colorMod.r, colorMod.g, colorMod.b);
    renderer.Copy(spriteSheet, SDL2pp::Optional<SDL2pp::Rect>(sprite), SDL2pp::Optional<SDL2pp::Rect>(dstRect), angle, SDL2pp::Optional<SDL2pp::Point>(), flip);
    SDL_SetTextureColorMod(spriteSheet.Get(), MAX_INTENSIDAD_RGB, MAX_INTENSIDAD_RGB, MAX_INTENSIDAD_RGB);
}

void Dibujador::dibujar_sprite(SDL2pp::Renderer& renderer, SDL2pp::Texture& spriteSheet,
                               const SDL_Rect& sprite, float x, float y, float escala,
                               orientacion_e orientacion, const int id) {
    SDL2pp::Rect dstRect = calcular_dst_rect(x, y, escala);
    double angle = ANGULO_NULO;
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    if (orientacion == IZQUIERDA) {
        flip = SDL_FLIP_HORIZONTAL;
    } else if (orientacion == ARRIBA) {
        angle = ANGULO_270;
    }

    if (id > CERO && id <= CUATRO){
        if (id != this->id_jugador){
            dibujar_pato_enemigo(renderer, spriteSheet, sprite, dstRect, id, angle, flip);
            return;
        }
    }
    
    renderer.Copy(spriteSheet, SDL2pp::Optional<SDL2pp::Rect>(sprite), SDL2pp::Optional<SDL2pp::Rect>(dstRect), angle, SDL2pp::Optional<SDL2pp::Point>(), flip);
}

void Dibujador::parsear_estado_juego(EstadoJuego& estado_actual, SDL2pp::Renderer& renderer){
    float escala = 0.07;
    int id;
    float x;
    float y;
    orientacion_e orientacion;
    estado_pato_e estado;
    for (auto& pato: estado_actual.info_patos){
        id = pato.id;
        x = pato.posicion.coordenada_x;
        y = pato.posicion.coordenada_y;
        orientacion = pato.orientacion;
        estado = pato.estado;
        if (estado == 0){
            auto [x_1, y_1] = convertir_a_relativo(x, y);
            dibujar_sprite(renderer, this->spriteSheetPato, this->spritesPato[0], x_1, y_1, escala, orientacion, id);
        } else if (estado == 1){
            auto [x_1, y_1] = convertir_a_relativo(x, y);
            dibujar_sprite(renderer, this->spriteSheetPato, this->spritesPato[10], x_1, y_1, escala, orientacion, id);
        } else if (estado == 2){
            auto [x_1, y_1] = convertir_a_relativo(x, y);
            dibujar_sprite(renderer, this->spriteSheetPato, this->spritesPato[7], x_1, y_1, escala, orientacion, id);
        } else if (estado == 3){
            auto [x_1, y_1] = convertir_a_relativo(x, y);
            dibujar_sprite(renderer, this->spriteSheetPato, this->spritesPato[8], x_1, y_1, escala, orientacion, id);
        } else if (estado == 4){
            auto [x_1, y_1] = convertir_a_relativo(x, y);
            dibujar_sprite(renderer, this->spriteSheetPato, this->spritesPato[9], x_1, y_1, escala, orientacion, id);
        } else if (estado == 5) {
            auto [x_1, y_1] = convertir_a_relativo(x, y);
            dibujar_sprite(renderer, this->spriteSheetPato, this->spritesPato[1], x_1, y_1, escala, orientacion, id);
        }
    }
}

void Dibujador::renderizar(SDL2pp::Renderer& renderer) {
    //unsigned int current_ticks = SDL_GetTicks();
    EstadoJuego estado_actual;
    if (queue.try_pop(estado_actual)) {
        renderer.Clear();
        renderer.Copy(this->mapa);
        parsear_estado_juego(estado_actual, renderer);
        renderer.Present();
    }
}
