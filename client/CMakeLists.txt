target_sources(taller_client
    PRIVATE
    # .cpp files
    main.cpp
    client_handler.cpp
    client_controlador.cpp
    client_dibujador.cpp
    client_parseador.cpp
    client_mock.cpp
    protocolo_cliente.cpp
    PUBLIC
    # .h files
    client_handler.h
    client_controlador.h
    client_dibujador.h
    client_parseador.h
    client_mock.h
    protocolo_cliente.h
    )
