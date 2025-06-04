set(AUX_PATH "${PRODUCTION_BASE_PATH}/auxiliary")
set(PROTOCOL_PATH "${PRODUCTION_BASE_PATH}/protocols")
set(ATF_PATH "${PRODUCTION_BASE_PATH}/atf")
set(COMMLIB_PATH "${PRODUCTION_BASE_PATH}/commlib2a")
set(PLIB_PATH "${PRODUCTION_BASE_PATH}/plib")

set(JACKPOT_TEST_FILES
TestJackpotServerObject.cpp
)

set(STUB_FILES
${STUBS_PATH}/asserts.cpp
${STUBS_PATH}/commlib_stubs.cpp
${STUBS_PATH}/commlib_interfaces_stubs.cpp
${STUBS_PATH}/commlib_factories_stubs.cpp
${STUBS_PATH}/plib_stubs.cpp
${STUBS_PATH}/protocols_stubs.cpp
${STUBS_PATH}/aux_stubs.cpp
${STUBS_PATH}/atf_stubs.cpp
${STUBS_PATH}/AtfCommObjectImpl_stubs.cpp
${STUBS_PATH}/unique_seqid_stubs.cpp
${STUBS_PATH}/checkserver_stubs.cpp
${STUBS_PATH}/jackpot_stubs.cpp
${STUBS_PATH}/telemetry_stubs.cpp
${STUBS_PATH}/commmonitorlogger_stubs.cpp
)

set(FAKE_FILES
${FAKES_PATH}/auxservercommon/FakeAuxCommServerObject.cpp
${FAKES_PATH}/auxservercommon/FakeAuxReefAccessor.cpp
${FAKES_PATH}/atf/FakeServer.cpp
)

set(MOCK_FILES
${MOCKS_PATH}/atf/MockAtfCommObjectImpl.cpp
${MOCKS_PATH}/auxcommon/MockAuxgenerictypes.cpp
${MOCKS_PATH}/commlib2a/MockServerStartParams.cpp
${MOCKS_PATH}/plib/MockPIniFile.cpp
)

set(PRODUCTION_FILES
    ${AUX_PATH}/auxjackpotserver/JackpotServerObject.cpp
	${AUX_PATH}/auxservercommon/AuxCommServerObject.cpp
	${PRODUCTION_BASE_PATH}/atf/PerformanceCounter.cpp
)

set (PROTOCOL_FILES
${PRODUCTION_BASE_PATH}/auxprotocols/CommonProtocolStructs.cpp
${AUX_PATH}/auxserverprotocols/ServerCommonProtocolStructs.cpp
${AUX_PATH}/auxprotocols/AuxReefProtocols.cpp
${AUX_PATH}/auxprotocols/isprotocols.cpp
${AUX_PATH}/auxprotocols/JackpotServerProtocols.cpp
${AUX_PATH}/auxprotocols/ShadowLobbyProtocols.cpp
${AUX_PATH}/auxprotocols/ShadowLobbyClientProtocols.cpp
${PRODUCTION_BASE_PATH}/atf/TimerServer.cpp
${PROTOCOL_PATH}/AtfXml.cpp
${PROTOCOL_PATH}/UserDefStructs.cpp
${PROTOCOL_PATH}/counters.cpp
${PROTOCOL_PATH}/shared/str_convert.cpp
${PROTOCOL_PATH}/esl/SecureStorageManager.cpp
${PROTOCOL_PATH}/esl/EslResolver.cpp
${PROTOCOL_PATH}/esl/utils.cpp
${PROTOCOL_PATH}/srvutils/ConnectionSettingsManager.cpp
)

set(COMMLIB_FILES
${COMMLIB_PATH}/commmsgbody.cpp
)

set(PLIB_FILES
${PLIB_PATH}/ppblock.cpp
${PLIB_PATH}/ppincludebase.cpp
${PLIB_PATH}/ppiofile.cpp
${PLIB_PATH}/ppjsoncomposer.cpp
${PLIB_PATH}/ppjsonparser.cpp
${PLIB_PATH}/ppstring.cpp
)

source_group("Tests" FILES ${JACKPOT_TEST_FILES})
source_group("Stubs" FILES ${STUB_FILES})
source_group("Fakes" FILES ${FAKE_FILES})
source_group("Mocks" FILES ${MOCK_FILES})
source_group("Production" FILES ${PRODUCTION_FILES})
source_group("Aux" FILES ${AUX_FILES})
source_group("Commlib"  FILES ${COMMLIB_FILES})
source_group("PLib" FILES ${PLIB_FILES})
source_group("Protocols" FILES ${PROTOCOL_FILES})

add_executable(jackpot_unittests
${JACKPOT_TEST_FILES}
${STUB_FILES}
${FAKE_FILES}
${MOCK_FILES}
${PRODUCTION_FILES}
${PROTOCOL_FILES}
${AUX_FILES}
${COMMLIB_FILES}
${PLIB_FILES}
)

target_include_directories(jackpot_unittests AFTER PRIVATE
${PRODUCTION_BASE_PATH}/atf
${PRODUCTION_BASE_PATH}/db2_libs/CLI9/include
${PRODUCTION_BASE_PATH}/commextlib
${PRODUCTION_BASE_PATH}/commlib2a
${PRODUCTION_BASE_PATH}/plib
${PRODUCTION_BASE_PATH}/protocols
${PRODUCTION_BASE_PATH}/locales
${PRODUCTION_BASE_PATH}/auxprotocols
${PRODUCTION_BASE_PATH}/auxserverprotocols
${AUX_PATH}
${AUX_PATH}/auxjackpotserver
${MOCKS_PATH}
${FAKES_PATH}
)

target_link_libraries(jackpot_unittests gtest gmock gtest_main)

if (MSVC)
	target_compile_options(jackpot_unittests PRIVATE /bigobj)
	target_compile_options(jackpot_unittests PRIVATE /W1)
	target_include_directories(jackpot_unittests AFTER PRIVATE ${PRODUCTION_BASE_PATH}/commlib2a/openssl/windows/vs2017/include)
	if (${CMAKE_VS_PLATFORM_NAME} STREQUAL "x64")
		set(OPENSSL_LIB_PATH "${PRODUCTION_BASE_PATH}/commlib2a/openssl/windows/vs2017/x64/lib")
	else()
		set(OPENSSL_LIB_PATH "${PRODUCTION_BASE_PATH}/commlib2a/openssl/windows/vs2017/x86/lib")
	endif()
	target_link_libraries(jackpot_unittests ${OPENSSL_LIB_PATH}/libeay32.lib ${OPENSSL_LIB_PATH}/ssleay32.lib Ws2_32.lib)
endif()