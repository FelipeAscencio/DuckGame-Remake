#include "config_juego.h"
#include <iostream>

int ConfigJuego::ALCANCE_SNIPER = 0;
int ConfigJuego::MUNICIONES_SNIPER = 0;
int ConfigJuego::ALCANCE_AK47 = 0;
int ConfigJuego::MUNICIONES_AK47 = 0;
int ConfigJuego::FPS = 0;
int ConfigJuego::ALCANCE_MAGNUM = 0;
int ConfigJuego::MUNICIONES_MAGNUM = 0;
int ConfigJuego::ALCANCE_MINIMO_PP_LASER = 0;
int ConfigJuego::ALCANCE_MAXIMO_PP_LASER = 0;
int ConfigJuego::MUNICIONES_PP_LASER = 0;
int ConfigJuego::ALCANCE_MINIMO_SHOTGUN = 0;
int ConfigJuego::ALCANCE_MAXIMO_SHOTGUN = 0;
int ConfigJuego::MUNICIONES_SHOTGUN = 0;
int ConfigJuego::PERDIGONES_POR_DISPARO_SG = 0;
int ConfigJuego::LASERS_POR_DISPARO_PP = 0;

void ConfigJuego::cargar_configuracion(const std::string& archivo){
    try{
        YAML::Node config = YAML::LoadFile(archivo);
        if (config["ALCANCE_SNIPER"]){
            ALCANCE_SNIPER = config["ALCANCE_SNIPER"].as<int>();
        }
        if (config["MUNICIONES_SNIPER"]){
            MUNICIONES_SNIPER = config["MUNICIONES_SNIPER"].as<int>();
        }
        if (config["ALCANCE_AK47"]){
            ALCANCE_AK47 = config["ALCANCE_AK47"].as<int>();
        }
        if (config["MUNICIONES_AK47"]){
            MUNICIONES_AK47 = config["MUNICIONES_AK47"].as<int>();
        }
        if (config["FPS"]){
            FPS = config["FPS"].as<int>();
        }
        if (config["ALCANCE_MAGNUM"]){
            ALCANCE_MAGNUM = config["ALCANCE_MAGNUM"].as<int>();
        }
        if (config["MUNICIONES_MAGNUM"]){
            MUNICIONES_MAGNUM = config["MUNICIONES_MAGNUM"].as<int>();
        }
        if (config["ALCANCE_MINIMO_PP_LASER"]){
            ALCANCE_MINIMO_PP_LASER = config["ALCANCE_MINIMO_PP_LASER"].as<int>();
        }
        if (config["ALCANCE_MAXIMO_PP_LASER"]){
            ALCANCE_MAXIMO_PP_LASER = config["ALCANCE_MAXIMO_PP_LASER"].as<int>();
        }
        if (config["MUNICIONES_PP_LASER"]){
            MUNICIONES_PP_LASER = config["MUNICIONES_PP_LASER"].as<int>();
        }
        if (config["ALCANCE_MINIMO_SHOTGUN"]){
            ALCANCE_MINIMO_SHOTGUN = config["ALCANCE_MINIMO_SHOTGUN"].as<int>();
        }
        if (config["ALCANCE_MAXIMO_SHOTGUN"]){
            ALCANCE_MAXIMO_SHOTGUN = config["ALCANCE_MAXIMO_SHOTGUN"].as<int>();
        }
        if (config["MUNICIONES_SHOTGUN"]){
            MUNICIONES_SHOTGUN = config["MUNICIONES_SHOTGUN"].as<int>();
        }
        if (config["PERDIGONES_POR_DISPARO_SG"]){
            PERDIGONES_POR_DISPARO_SG = config["PERDIGONES_POR_DISPARO_SG"].as<int>();
        }
        if (config["LASERS_POR_DISPARO_PP"]){
            LASERS_POR_DISPARO_PP = config["LASERS_POR_DISPARO_PP"].as<int>();
        }
    } catch (const YAML::Exception& e){
        std::cerr << "Error al cargar la configuracion: " << e.what() << std::endl;
    }
}