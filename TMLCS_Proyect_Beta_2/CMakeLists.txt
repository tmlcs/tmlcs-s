cmake_minimum_required(VERSION 3.8)
project(TMLCS_Server-0.002)

# Incluye la subcarpeta "src"
add_subdirectory(src)

# Encuentra OpenSSL
find_package(OpenSSL REQUIRED)

# Agrega el directorio de módulos al CMAKE_MODULE_PATH
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR})

# Encuentra Crypto++
find_package(Cryptopp REQUIRED)

# Crea el ejecutable
add_executable(TMLCS_Server-0.002 main.cpp)

# Enlaza la biblioteca creada en la subcarpeta "src"
target_link_libraries(TMLCS_Server-0.002 PRIVATE src)

# Enlaza la biblioteca de MySQL Connector/C++
target_link_libraries(TMLCS_Server-0.002 PRIVATE mysqlcppconn)

# Enlaza OpenSSL y Crypto++
target_link_libraries(TMLCS_Server-0.002 PRIVATE OpenSSL::SSL OpenSSL::Crypto)
target_link_libraries(TMLCS_Server-0.002 PRIVATE ${Cryptopp_LIBRARIES})

# Incluye directorios de OpenSSL y Crypto++
target_include_directories(TMLCS_Server-0.002 PRIVATE ${OPENSSL_INCLUDE_DIR})
target_include_directories(TMLCS_Server-0.002 PRIVATE ${Cryptopp_INCLUDE_DIRS})

