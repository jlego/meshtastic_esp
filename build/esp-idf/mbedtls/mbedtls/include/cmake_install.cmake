# Install script for directory: /Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include

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
    set(CMAKE_INSTALL_CONFIG_NAME "")
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

# Set path to fallback-tool for dependency-resolution.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/Users/ronghuiyu/.espressif/tools/xtensa-esp-elf/esp-14.2.0_20241119/xtensa-esp-elf/bin/xtensa-esp32s3-elf-objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mbedtls" TYPE FILE PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ FILES
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/aes.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/aria.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/asn1.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/asn1write.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/base64.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/bignum.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/block_cipher.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/build_info.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/camellia.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ccm.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/chacha20.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/chachapoly.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/check_config.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/cipher.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/cmac.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/compat-2.x.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/config_adjust_legacy_crypto.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/config_adjust_legacy_from_psa.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/config_adjust_psa_from_legacy.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/config_adjust_psa_superset_legacy.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/config_adjust_ssl.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/config_adjust_x509.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/config_psa.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/constant_time.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ctr_drbg.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/debug.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/des.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/dhm.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ecdh.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ecdsa.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ecjpake.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ecp.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/entropy.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/error.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/gcm.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/hkdf.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/hmac_drbg.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/lms.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/mbedtls_config.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/md.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/md5.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/memory_buffer_alloc.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/net_sockets.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/nist_kw.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/oid.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/pem.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/pk.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/pkcs12.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/pkcs5.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/pkcs7.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/platform.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/platform_time.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/platform_util.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/poly1305.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/private_access.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/psa_util.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ripemd160.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/rsa.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/sha1.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/sha256.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/sha3.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/sha512.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ssl.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ssl_cache.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ssl_ciphersuites.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ssl_cookie.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/ssl_ticket.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/threading.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/timing.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/version.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/x509.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/x509_crl.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/x509_crt.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/mbedtls/x509_csr.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/psa" TYPE FILE PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ FILES
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/psa/build_info.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/psa/crypto.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_adjust_auto_enabled.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_adjust_config_dependencies.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_adjust_config_key_pair_types.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_adjust_config_synonyms.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_builtin_composites.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_builtin_key_derivation.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_builtin_primitives.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_compat.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_config.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_driver_common.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_driver_contexts_composites.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_driver_contexts_key_derivation.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_driver_contexts_primitives.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_extra.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_legacy.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_platform.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_se_driver.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_sizes.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_struct.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_types.h"
    "/Volumes/disk1t/esp/v5.5/esp-idf/components/mbedtls/mbedtls/include/psa/crypto_values.h"
    )
endif()

