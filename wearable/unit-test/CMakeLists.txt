CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(libslp-tapi-unit-test C)

SET(PREFIX ${CMAKE_INSTALL_PREFIX})
SET(EXEC_PREFIX "\${prefix}")
SET(LIBDIR "\${prefix}/lib")
SET(INCLUDEDIR "\${prefix}/include")

SET(TESTS
		test-thread
)

REMOVE_DEFINITIONS("-DTAPI_LOG_TAG=\"LIBTAPI\"")
ADD_DEFINITIONS("-DTAPI_LOG_TAG=\"TAPIUNIT\"")

FOREACH(test ${TESTS})
	ADD_EXECUTABLE(${test} ${test}.c)
	TARGET_LINK_LIBRARIES(${test} ${pkgs_LDFLAGS} "-L${CMAKE_BINARY_DIR} -lSLP-tapi")
#	INSTALL(TARGETS ${test} RUNTIME DESTINATION bin/)
	ADD_DEPENDENCIES(${test} run.sh)
	SET(TEST_LIST "${TEST_LIST} ${test}")
ENDFOREACH(test)


ADD_CUSTOM_TARGET(run.sh)
ADD_CUSTOM_COMMAND(
	TARGET run.sh
	POST_BUILD
	COMMAND echo "gtester ${TEST_LIST} -o report.xml" > run.sh
	COMMAND chmod +x run.sh
	COMMENT "Generating gtester script"
	VERBATIM # for double-quoted strings..
	)
ADD_DEPENDENCIES(run.sh SLP-tapi)
