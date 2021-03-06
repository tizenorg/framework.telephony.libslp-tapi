CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(SLP-tapi C)

SET(PREFIX ${CMAKE_INSTALL_PREFIX})
SET(EXEC_PREFIX "\${prefix}")
SET(LIBDIR "\${prefix}/lib")
SET(INCLUDEDIR "\${prefix}/include")

# Set required packages
INCLUDE(FindPkgConfig)
pkg_check_modules(pkgs REQUIRED glib-2.0 gio-2.0 gthread-2.0 dlog security-server)

FOREACH(flag ${pkgs_CFLAGS})
	SET(EXTRA_CFLAGS "${EXTRA_CFLAGS} ${flag}")
ENDFOREACH(flag)

SET(EXTRA_CFLAGS "${EXTRA_CFLAGS}  -Wl,-zdefs -fvisibility=hidden ")
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${EXTRA_CFLAGS} -Werror -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wmissing-declarations -Wredundant-decls -Wcast-align")
#SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${EXTRA_CFLAGS}")
SET(CMAKE_EXE_LINKER_FLAGS "-Wl,--as-needed")

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/src)

ADD_DEFINITIONS("-DFEATURE_DLOG_DEBUG")
ADD_DEFINITIONS("-DTAPI_LOG_TAG=\"LIBTAPI\"")
ADD_DEFINITIONS("-DPREFIX=\"${CMAKE_INSTALL_PREFIX}\"")
ADD_DEFINITIONS(" -DEXPORT_API=\"__attribute__((visibility(\\\"default\\\")))\" ")

MESSAGE(${CMAKE_C_FLAGS})
MESSAGE(${CMAKE_EXE_LINKER_FLAGS})

### Build ###
SET(SRCS
		src/tapi_common.c
		src/tapi_network.c
		src/tapi_sim.c
		src/tapi_phonebook.c
		src/tapi_sap.c
		src/tapi_call.c
		src/tapi_ss.c
		src/tapi_sms.c
		src/tapi_sat.c
		src/tapi_modem.c
   )

ADD_LIBRARY(SLP-tapi SHARED ${SRCS})
TARGET_LINK_LIBRARIES(SLP-tapi ${pkgs_LDFLAGS})
SET_TARGET_PROPERTIES(SLP-tapi PROPERTIES VERSION 0.0.0 SOVERSION 0 OUTPUT_NAME SLP-tapi)

# pkgconfig file
SET(PREFIX ${CMAKE_INSTALL_PREFIX})
CONFIGURE_FILE(tapi.pc.in tapi.pc @ONLY)

INSTALL(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/ DESTINATION include/telephony-client)
INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR}/tapi.pc DESTINATION lib/pkgconfig)
INSTALL(TARGETS SLP-tapi DESTINATION lib COMPONENT Runtime)
