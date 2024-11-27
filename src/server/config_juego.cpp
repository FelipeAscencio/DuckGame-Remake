#include "config_juego.h"

#include <iostream>

#define MSJ_ERROR_CONFIGURACION "Error al cargar la configuracion: "
#define ALCANCE_SNIPER_STR "ALCANCE_SNIPER"
#define MUNICIONES_SNIPER_STR "MUNICIONES_SNIPER"
#define ALCANCE_AK_STR "ALCANCE_AK47"
#define MUNICIONES_AK_STR "MUNICIONES_AK47"
#define FPS_STR "FPS"
#define ALCANCE_MAGNUM_STR "ALCANCE_MAGNUM"
#define MUNICIONES_MAGNUM_STR "MUNICIONES_MAGNUM"
#define ALCANCE_MIN_PEW_PEW_STR "ALCANCE_MINIMO_PP_LASER"
#define ALCANCE_MAX_PEW_PEW_STR "ALCANCE_MAXIMO_PP_LASER"
#define MUNICIONES_PEW_PEW_STR "MUNICIONES_PP_LASER"
#define ALCANCE_MIN_SHOTGUN_STR "ALCANCE_MINIMO_SHOTGUN"
#define ALCANCE_MAX_SHOTGUN_STR "ALCANCE_MAXIMO_SHOTGUN"
#define MUNICIONES_SHOTGUN_STR "MUNICIONES_SHOTGUN"
#define PERDIGONES_SHOTGUN_STR "PERDIGONES_POR_DISPARO_SG"
#define PERDIGONES_LASER_STR "LASERS_POR_DISPARO_PP"

#define CERO 0

int ConfigJuego::ALCANCE_SNIPER = CERO;
int ConfigJuego::MUNICIONES_SNIPER = CERO;
int ConfigJuego::ALCANCE_AK47 = CERO;
int ConfigJuego::MUNICIONES_AK47 = CERO;
int ConfigJuego::FPS = CERO;
int ConfigJuego::ALCANCE_MAGNUM = CERO;
int ConfigJuego::MUNICIONES_MAGNUM = CERO;
int ConfigJuego::ALCANCE_MINIMO_PP_LASER = CERO;
int ConfigJuego::ALCANCE_MAXIMO_PP_LASER = CERO;
int ConfigJuego::MUNICIONES_PP_LASER = CERO;
int ConfigJuego::ALCANCE_MINIMO_SHOTGUN = CERO;
int ConfigJuego::ALCANCE_MAXIMO_SHOTGUN = CERO;
int ConfigJuego::MUNICIONES_SHOTGUN = CERO;
int ConfigJuego::PERDIGONES_POR_DISPARO_SG = CERO;
int ConfigJuego::LASERS_POR_DISPARO_PP = CERO;

void ConfigJuego::cargar_configuracion(const std::string& archivo){
    try{
        YAML::Node config = YAML::LoadFile(archivo);
        if (config[ALCANCE_SNIPER_STR]){
            ALCANCE_SNIPER = config[ALCANCE_SNIPER_STR].as<int>();
        }
        if (config[MUNICIONES_SNIPER_STR]){
            MUNICIONES_SNIPER = config[MUNICIONES_SNIPER_STR].as<int>();
        }
        if (config[ALCANCE_AK_STR]){
            ALCANCE_AK47 = config[ALCANCE_AK_STR].as<int>();
        }
        if (config[MUNICIONES_AK_STR]){
            MUNICIONES_AK47 = config[MUNICIONES_AK_STR].as<int>();
        }
        if (config[FPS_STR]){
            FPS = config[FPS_STR].as<int>();
        }
        if (config[ALCANCE_MAGNUM_STR]){
            ALCANCE_MAGNUM = config[ALCANCE_MAGNUM_STR].as<int>();
        }
        if (config[MUNICIONES_MAGNUM_STR]){
            MUNICIONES_MAGNUM = config[MUNICIONES_MAGNUM_STR].as<int>();
        }
        if (config[ALCANCE_MIN_PEW_PEW_STR]){
            ALCANCE_MINIMO_PP_LASER = config[ALCANCE_MIN_PEW_PEW_STR].as<int>();
        }
        if (config[ALCANCE_MAX_PEW_PEW_STR]){
            ALCANCE_MAXIMO_PP_LASER = config[ALCANCE_MAX_PEW_PEW_STR].as<int>();
        }
        if (config[MUNICIONES_PEW_PEW_STR]){
            MUNICIONES_PP_LASER = config[MUNICIONES_PEW_PEW_STR].as<int>();
        }
        if (config[ALCANCE_MIN_SHOTGUN_STR]){
            ALCANCE_MINIMO_SHOTGUN = config[ALCANCE_MIN_SHOTGUN_STR].as<int>();
        }
        if (config[ALCANCE_MAX_SHOTGUN_STR]){
            ALCANCE_MAXIMO_SHOTGUN = config[ALCANCE_MAX_SHOTGUN_STR].as<int>();
        }
        if (config[MUNICIONES_SHOTGUN_STR]){
            MUNICIONES_SHOTGUN = config[MUNICIONES_SHOTGUN_STR].as<int>();
        }
        if (config[PERDIGONES_SHOTGUN_STR]){
            PERDIGONES_POR_DISPARO_SG = config[PERDIGONES_SHOTGUN_STR].as<int>();
        }
        if (config[PERDIGONES_LASER_STR]){
            LASERS_POR_DISPARO_PP = config[PERDIGONES_LASER_STR].as<int>();
        }
    } catch (const YAML::Exception& error){
        std::cerr << MSJ_ERROR_CONFIGURACION << error.what() << std::endl;
    }
}
