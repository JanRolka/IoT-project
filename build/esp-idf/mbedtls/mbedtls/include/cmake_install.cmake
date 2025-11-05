# Install script for directory: /home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "TRUE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/home/rolowany/.espressif/tools/xtensa-esp-elf/esp-14.2.0_20241119/xtensa-esp-elf/bin/xtensa-esp32-elf-objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mbedtls" TYPE FILE PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ FILES
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/aes.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/aria.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/asn1.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/asn1write.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/base64.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/bignum.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/block_cipher.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/build_info.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/camellia.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ccm.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/chacha20.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/chachapoly.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/check_config.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/cipher.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/cmac.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/compat-2.x.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/config_adjust_legacy_crypto.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/config_adjust_legacy_from_psa.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/config_adjust_psa_from_legacy.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/config_adjust_psa_superset_legacy.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/config_adjust_ssl.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/config_adjust_x509.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/config_psa.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/constant_time.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ctr_drbg.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/debug.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/des.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/dhm.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ecdh.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ecdsa.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ecjpake.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ecp.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/entropy.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/error.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/gcm.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/hkdf.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/hmac_drbg.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/lms.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/mbedtls_config.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/md.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/md5.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/memory_buffer_alloc.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/net_sockets.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/nist_kw.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/oid.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/pem.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/pk.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/pkcs12.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/pkcs5.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/pkcs7.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/platform.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/platform_time.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/platform_util.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/poly1305.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/private_access.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/psa_util.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ripemd160.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/rsa.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/sha1.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/sha256.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/sha3.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/sha512.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ssl.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ssl_cache.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ssl_ciphersuites.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ssl_cookie.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ssl_ticket.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/threading.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/timing.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/version.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/x509.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/x509_crl.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/x509_crt.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/mbedtls/x509_csr.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/psa" TYPE FILE PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ FILES
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/psa/build_info.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/psa/crypto.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_adjust_auto_enabled.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_adjust_config_dependencies.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_adjust_config_key_pair_types.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_adjust_config_synonyms.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_builtin_composites.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_builtin_key_derivation.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_builtin_primitives.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_compat.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_config.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_driver_common.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_driver_contexts_composites.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_driver_contexts_key_derivation.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_driver_contexts_primitives.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_extra.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_legacy.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_platform.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_se_driver.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_sizes.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_struct.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_types.h"
    "/home/rolowany/esp/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_values.h"
    )
endif()

