target_sources(taller_client
    PRIVATE
    # .cpp files
    main.cpp
    client_handler.cpp
    client_controlador.cpp
    client_dibujador.cpp
    client_parseador.cpp
    protocolo_cliente.cpp
    client_enviador.cpp
    client_recibidor.cpp
    PUBLIC
    # .h files
    client_handler.h
    client_controlador.h
    client_dibujador.h
    client_parseador.h
    protocolo_cliente.h
    client_enviador.h
    client_recibidor.h
    )
