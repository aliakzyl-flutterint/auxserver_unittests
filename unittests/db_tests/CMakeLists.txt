
set(TEST_FILES
AuxDbmServerObject_test.cpp
)

source_group("Tests" FILES ${TEST_FILES})

add_executable(db_tests
${TEST_FILES}
)

target_include_directories(db_tests AFTER PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/../atf
	${CMAKE_CURRENT_SOURCE_DIR}/../db2_libs/CLI9/include
	${CMAKE_CURRENT_SOURCE_DIR}/../commextlib
	${CMAKE_CURRENT_SOURCE_DIR}/../commlib2a
	${CMAKE_CURRENT_SOURCE_DIR}/../plib
	${CMAKE_CURRENT_SOURCE_DIR}/../protocols
	${CMAKE_CURRENT_SOURCE_DIR}/../locales
	${CMAKE_CURRENT_SOURCE_DIR}/../auxiliary/auxlobby
	${CMAKE_CURRENT_SOURCE_DIR}/../auxiliary/auxictableserver/ICCommon)
	
target_link_libraries(db_tests gtest gmock gtest_main)

if (MSVC)
	target_compile_options(db_tests PRIVATE /bigobj)
	target_compile_options(db_tests PRIVATE /W1)
	target_include_directories(db_tests AFTER PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../commlib2a/openssl/windows/vs2017/include)
	
	if (${CMAKE_VS_PLATFORM_NAME} STREQUAL "x64")
		set(OPENSSL_LIB_PATH "${PRODUCTION_BASE_PATH}/commlib2a/openssl/windows/vs2017/x64/lib")
	else()
		set(OPENSSL_LIB_PATH "${PRODUCTION_BASE_PATH}/commlib2a/openssl/windows/vs2017/x86/lib")
	endif()

	target_link_libraries(db_tests ${OPENSSL_LIB_PATH}/libeay32.lib ${OPENSSL_LIB_PATH}/ssleay32.lib Ws2_32.lib)
endif()