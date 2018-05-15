################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../mbedTLS/library/aes.c \
../mbedTLS/library/aesni.c \
../mbedTLS/library/arc4.c \
../mbedTLS/library/asn1parse.c \
../mbedTLS/library/asn1write.c \
../mbedTLS/library/base64.c \
../mbedTLS/library/bignum.c \
../mbedTLS/library/blowfish.c \
../mbedTLS/library/camellia.c \
../mbedTLS/library/ccm.c \
../mbedTLS/library/certs.c \
../mbedTLS/library/cipher.c \
../mbedTLS/library/cipher_wrap.c \
../mbedTLS/library/cmac.c \
../mbedTLS/library/ctr_drbg.c \
../mbedTLS/library/debug.c \
../mbedTLS/library/des.c \
../mbedTLS/library/dhm.c \
../mbedTLS/library/ecdh.c \
../mbedTLS/library/ecdsa.c \
../mbedTLS/library/ecjpake.c \
../mbedTLS/library/ecp.c \
../mbedTLS/library/ecp_curves.c \
../mbedTLS/library/entropy.c \
../mbedTLS/library/entropy_poll.c \
../mbedTLS/library/error.c \
../mbedTLS/library/gcm.c \
../mbedTLS/library/havege.c \
../mbedTLS/library/hmac_drbg.c \
../mbedTLS/library/md.c \
../mbedTLS/library/md2.c \
../mbedTLS/library/md4.c \
../mbedTLS/library/md5.c \
../mbedTLS/library/md_wrap.c \
../mbedTLS/library/memory_buffer_alloc.c \
../mbedTLS/library/net_sockets.c \
../mbedTLS/library/oid.c \
../mbedTLS/library/padlock.c \
../mbedTLS/library/pem.c \
../mbedTLS/library/pk.c \
../mbedTLS/library/pk_wrap.c \
../mbedTLS/library/pkcs12.c \
../mbedTLS/library/pkcs5.c \
../mbedTLS/library/pkparse.c \
../mbedTLS/library/pkwrite.c \
../mbedTLS/library/platform.c \
../mbedTLS/library/ripemd160.c \
../mbedTLS/library/rsa.c \
../mbedTLS/library/sha1.c \
../mbedTLS/library/sha256.c \
../mbedTLS/library/sha512.c \
../mbedTLS/library/ssl_cache.c \
../mbedTLS/library/ssl_ciphersuites.c \
../mbedTLS/library/ssl_cli.c \
../mbedTLS/library/ssl_cookie.c \
../mbedTLS/library/ssl_srv.c \
../mbedTLS/library/ssl_ticket.c \
../mbedTLS/library/ssl_tls.c \
../mbedTLS/library/threading.c \
../mbedTLS/library/timing.c \
../mbedTLS/library/version.c \
../mbedTLS/library/version_features.c \
../mbedTLS/library/x509.c \
../mbedTLS/library/x509_create.c \
../mbedTLS/library/x509_crl.c \
../mbedTLS/library/x509_crt.c \
../mbedTLS/library/x509_csr.c \
../mbedTLS/library/x509write_crt.c \
../mbedTLS/library/x509write_csr.c \
../mbedTLS/library/xtea.c 

OBJS += \
./mbedTLS/library/aes.o \
./mbedTLS/library/aesni.o \
./mbedTLS/library/arc4.o \
./mbedTLS/library/asn1parse.o \
./mbedTLS/library/asn1write.o \
./mbedTLS/library/base64.o \
./mbedTLS/library/bignum.o \
./mbedTLS/library/blowfish.o \
./mbedTLS/library/camellia.o \
./mbedTLS/library/ccm.o \
./mbedTLS/library/certs.o \
./mbedTLS/library/cipher.o \
./mbedTLS/library/cipher_wrap.o \
./mbedTLS/library/cmac.o \
./mbedTLS/library/ctr_drbg.o \
./mbedTLS/library/debug.o \
./mbedTLS/library/des.o \
./mbedTLS/library/dhm.o \
./mbedTLS/library/ecdh.o \
./mbedTLS/library/ecdsa.o \
./mbedTLS/library/ecjpake.o \
./mbedTLS/library/ecp.o \
./mbedTLS/library/ecp_curves.o \
./mbedTLS/library/entropy.o \
./mbedTLS/library/entropy_poll.o \
./mbedTLS/library/error.o \
./mbedTLS/library/gcm.o \
./mbedTLS/library/havege.o \
./mbedTLS/library/hmac_drbg.o \
./mbedTLS/library/md.o \
./mbedTLS/library/md2.o \
./mbedTLS/library/md4.o \
./mbedTLS/library/md5.o \
./mbedTLS/library/md_wrap.o \
./mbedTLS/library/memory_buffer_alloc.o \
./mbedTLS/library/net_sockets.o \
./mbedTLS/library/oid.o \
./mbedTLS/library/padlock.o \
./mbedTLS/library/pem.o \
./mbedTLS/library/pk.o \
./mbedTLS/library/pk_wrap.o \
./mbedTLS/library/pkcs12.o \
./mbedTLS/library/pkcs5.o \
./mbedTLS/library/pkparse.o \
./mbedTLS/library/pkwrite.o \
./mbedTLS/library/platform.o \
./mbedTLS/library/ripemd160.o \
./mbedTLS/library/rsa.o \
./mbedTLS/library/sha1.o \
./mbedTLS/library/sha256.o \
./mbedTLS/library/sha512.o \
./mbedTLS/library/ssl_cache.o \
./mbedTLS/library/ssl_ciphersuites.o \
./mbedTLS/library/ssl_cli.o \
./mbedTLS/library/ssl_cookie.o \
./mbedTLS/library/ssl_srv.o \
./mbedTLS/library/ssl_ticket.o \
./mbedTLS/library/ssl_tls.o \
./mbedTLS/library/threading.o \
./mbedTLS/library/timing.o \
./mbedTLS/library/version.o \
./mbedTLS/library/version_features.o \
./mbedTLS/library/x509.o \
./mbedTLS/library/x509_create.o \
./mbedTLS/library/x509_crl.o \
./mbedTLS/library/x509_crt.o \
./mbedTLS/library/x509_csr.o \
./mbedTLS/library/x509write_crt.o \
./mbedTLS/library/x509write_csr.o \
./mbedTLS/library/xtea.o 

C_DEPS += \
./mbedTLS/library/aes.d \
./mbedTLS/library/aesni.d \
./mbedTLS/library/arc4.d \
./mbedTLS/library/asn1parse.d \
./mbedTLS/library/asn1write.d \
./mbedTLS/library/base64.d \
./mbedTLS/library/bignum.d \
./mbedTLS/library/blowfish.d \
./mbedTLS/library/camellia.d \
./mbedTLS/library/ccm.d \
./mbedTLS/library/certs.d \
./mbedTLS/library/cipher.d \
./mbedTLS/library/cipher_wrap.d \
./mbedTLS/library/cmac.d \
./mbedTLS/library/ctr_drbg.d \
./mbedTLS/library/debug.d \
./mbedTLS/library/des.d \
./mbedTLS/library/dhm.d \
./mbedTLS/library/ecdh.d \
./mbedTLS/library/ecdsa.d \
./mbedTLS/library/ecjpake.d \
./mbedTLS/library/ecp.d \
./mbedTLS/library/ecp_curves.d \
./mbedTLS/library/entropy.d \
./mbedTLS/library/entropy_poll.d \
./mbedTLS/library/error.d \
./mbedTLS/library/gcm.d \
./mbedTLS/library/havege.d \
./mbedTLS/library/hmac_drbg.d \
./mbedTLS/library/md.d \
./mbedTLS/library/md2.d \
./mbedTLS/library/md4.d \
./mbedTLS/library/md5.d \
./mbedTLS/library/md_wrap.d \
./mbedTLS/library/memory_buffer_alloc.d \
./mbedTLS/library/net_sockets.d \
./mbedTLS/library/oid.d \
./mbedTLS/library/padlock.d \
./mbedTLS/library/pem.d \
./mbedTLS/library/pk.d \
./mbedTLS/library/pk_wrap.d \
./mbedTLS/library/pkcs12.d \
./mbedTLS/library/pkcs5.d \
./mbedTLS/library/pkparse.d \
./mbedTLS/library/pkwrite.d \
./mbedTLS/library/platform.d \
./mbedTLS/library/ripemd160.d \
./mbedTLS/library/rsa.d \
./mbedTLS/library/sha1.d \
./mbedTLS/library/sha256.d \
./mbedTLS/library/sha512.d \
./mbedTLS/library/ssl_cache.d \
./mbedTLS/library/ssl_ciphersuites.d \
./mbedTLS/library/ssl_cli.d \
./mbedTLS/library/ssl_cookie.d \
./mbedTLS/library/ssl_srv.d \
./mbedTLS/library/ssl_ticket.d \
./mbedTLS/library/ssl_tls.d \
./mbedTLS/library/threading.d \
./mbedTLS/library/timing.d \
./mbedTLS/library/version.d \
./mbedTLS/library/version_features.d \
./mbedTLS/library/x509.d \
./mbedTLS/library/x509_create.d \
./mbedTLS/library/x509_crl.d \
./mbedTLS/library/x509_crt.d \
./mbedTLS/library/x509_csr.d \
./mbedTLS/library/x509write_crt.d \
./mbedTLS/library/x509write_csr.d \
./mbedTLS/library/xtea.d 


# Each subdirectory must supply rules for building sources it contributes
mbedTLS/library/%.o: ../mbedTLS/library/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__NEWLIB__ -DENERGIA -DMXL12835F -DXIP_IMAGE -DSDK_OS_BAREMETAL -DFSL_RTOS_BM -DSDK_DEBUGCONSOLE=1 -DCPU_LPC54018JET180_cm4 -DCPU_LPC54018JET180 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -DUSE_RTOS=1 -DFSL_RTOS_FREE_RTOS -DMBEDTLS_CONFIG_FILE='"aws_mbedtls_config.h"' -DA_LITTLE_ENDIAN -DIMG_BAUDRATE=96000000 -I../board -I../wifi_qca/port/shields -I../wifi_qca/port/shields/gt202 -I../wifi_qca/port/env/freertos -I../wifi_qca/common_src/hcd -I../wifi_qca/common_src/include -I../wifi_qca/common_src/stack_common -I../wifi_qca/common_src/wmi -I../wifi_qca/custom_src/include -I../wifi_qca/custom_src/stack_custom -I../wifi_qca/include/AR6002/hw2.0/hw -I../wifi_qca/include/AR6002/hw4.0/hw -I../wifi_qca/include/AR6002 -I../wifi_qca/include -I../wifi_qca/port -I../wifi_qca/port/drivers/flexcomm_freertos -I../PervasiveDisplays_Library/src -I../source -I../ -I../amazon-freertos/portable -I../amazon-freertos/FreeRTOS/portable -I../amazon-freertos/include -I../amazon-freertos/drivers -I../amazon-freertos/pkcs11 -I../amazon-freertos/third_party/jsmn -I../amazon-freertos/config_files -I../mbedTLS/include/mbedtls -I../mbedTLS/port/ksdk -I../mbedTLS/include -I../drivers -I../CMSIS -I../drivers/freertos -I../utilities -I../startup -I../Pervasive_EPD_BoosterPack2 -I../exp_click1 -I../exp_click2 -I../exp_arduino -O0 -fno-common -g -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__NEWLIB__ -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


