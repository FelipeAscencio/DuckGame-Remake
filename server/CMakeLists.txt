add_subdirectory(armas)

target_sources(taller_server
    PRIVATE
    # .cpp files
    main.cpp
    aceptador.cpp
    enviador.cpp
    gameloop.cpp
    mapa.cpp
    pato.cpp
    protocol.cpp
    queues_jugadores.cpp
    recibidor.cpp
    server.cpp
    thread_usuario.cpp
    PUBLIC
    # .h files
    aceptador.h
    enviador.h
    mapa.h
    pato.h
    protocol.h
    queues_jugadores.h
    recibidor.h
    server.h
    thread_usuario.h
    )
