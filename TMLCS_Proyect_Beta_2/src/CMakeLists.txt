add_library(src SHARED
	        database.h
	        database.cpp
            server.h
            server.cpp
            ssl_server.h
            ssl_server.cpp
            request.h
            request.cpp
            response.h
            response.cpp
            router.h
            router.cpp
            server_config.h
            server_config.cpp
            ssl_config.cpp
            ssl_config.h)

target_include_directories(src PUBLIC
                        $(CMAKE_CURRENT_LIST_DIR))
