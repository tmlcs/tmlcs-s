# FindCryptopp.cmake
find_path(Cryptopp_INCLUDE_DIR NAMES cryptopp/cryptlib.h PATH_SUFFIXES cryptopp)
find_library(Cryptopp_LIBRARY NAMES cryptopp)

set(Cryptopp_INCLUDE_DIRS ${Cryptopp_INCLUDE_DIR})
set(Cryptopp_LIBRARIES ${Cryptopp_LIBRARY})
