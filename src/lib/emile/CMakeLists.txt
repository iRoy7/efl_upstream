set(DESCRIPTION "Library for simplified serialization, compression and ciphering")

set(PKG_CONFIG_REQUIRES_PRIVATE
  zlib>=1.2.3
)

set(LIBRARIES
  eina
  efl
  m
  support-rg_etc
  find-JPEG
)

set(PUBLIC_HEADERS
  Emile.h
  emile_base64.h
  emile_cipher.h
  emile_compress.h
  emile_image.h
)

set(SOURCES
  emile_base64.c
  emile_compress.c
  emile_image.c
  emile_main.c
  emile_private.h
)

if(WITH_CRYPTO STREQUAL "gnutls")
  list(APPEND SOURCES emile_cipher_gnutls.c)
  list(APPEND PKG_CONFIG_REQUIRES_PRIVATE gnutls)
elseif(WITH_CRYPTO STREQUAL "openssl")
  list(APPEND SOURCES emile_cipher_openssl.c)
  list(APPEND PKG_CONFIG_REQUIRES_PRIVATE openssl)
else()
  list(APPEND SOURCES emile_cipher.c)
endif()

if(WITH_LZ4 STREQUAL "system")
  list(APPEND PKG_CONFIG_REQUIRES_PRIVATE liblz4)
else()
  list(APPEND LIBRARIES support-lz4)
endif()
