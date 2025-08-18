set(AUX_PATH "${PRODUCTION_BASE_PATH}/auxiliary")
set(PROTOCOL_PATH "${PRODUCTION_BASE_PATH}/protocols")
set(ATF_PATH "${PRODUCTION_BASE_PATH}/atf")
set(COMMLIB_PATH "${PRODUCTION_BASE_PATH}/commlib2a")
set(PLIB_PATH "${PRODUCTION_BASE_PATH}/plib")
set(UNITTESTS_PATH ..)

set(ADMINIS_TEST_FILES
${UNITTESTS_PATH}/common/GenericServerObjectSuite.cpp
${UNITTESTS_PATH}/common/ServerObjectsExpects.cpp
TestAdminAndISServers.cpp
)

set(STUB_FILES
${STUBS_PATH}/asserts.cpp
${STUBS_PATH}/commlib_stubs.cpp
${STUBS_PATH}/commlib_interfaces_stubs.cpp
${STUBS_PATH}/commlib_factories_stubs.cpp
${STUBS_PATH}/plib_stubs.cpp
${STUBS_PATH}/ppjsoncomposer_stubs.cpp
${STUBS_PATH}/protocols_stubs.cpp
${STUBS_PATH}/aux_stubs.cpp
${STUBS_PATH}/atf_stubs.cpp
${STUBS_PATH}/atf1_stubs.cpp
${STUBS_PATH}/auxgenerictypes_stubs.cpp
${STUBS_PATH}/AtfCommObjectImpl_stubs.cpp
)

set(FAKE_FILES
${FAKES_PATH}/auxservercommon/FakeAuxCommServerObject.cpp
${FAKES_PATH}/auxservercommon/FakeAuxReefAccessor.cpp
${FAKES_PATH}/atf/FakeServer.cpp
${FAKES_PATH}/atf/FakeConnection.cpp
)

set(MOCK_FILES
${MOCKS_PATH}/atf/MockAtfCommObjectImpl.cpp
${MOCKS_PATH}/auxcommon/MockAuxgenerictypes.cpp
${MOCKS_PATH}/commlib2a/MockServerStartParams.cpp
${MOCKS_PATH}/plib/MockPIniFile.cpp
)

set(PRODUCTION_FILES
		${AUX_PATH}/auxservercommon/AuxCommServerObject.cpp
		${AUX_PATH}/auxservercommon/AuxServerCommonDefs.cpp
		${AUX_PATH}/auxservercommon/AuxConfigCommonParser.cpp
		${AUX_PATH}/auxservercommon/RaceScriptsParser.cpp
		# Admin Server
		${AUX_PATH}/auxadmin/AuxAdminServerObject.cpp
		# IS Server
		${AUX_PATH}/auxintegrationserver/integrationserverobject.cpp
		${AUX_PATH}/auxintegrationserver/integrationcounters.cpp
)

set (AUX_FILES
${ATF_PATH}/TimerServer.cpp
)

set (PROTOCOL_FILES
${PROTOCOL_PATH}/AtfXml.cpp
${PROTOCOL_PATH}/UserDefStructs.cpp
${PRODUCTION_BASE_PATH}/auxprotocols/CommonProtocolStructs.cpp
${AUX_PATH}/auxserverprotocols/ServerCommonProtocolStructs.cpp
${AUX_PATH}/auxserverprotocols/AuxProxyProtocolStructs.cpp
${AUX_PATH}/auxprotocols/isprotocols.cpp
${AUX_PATH}/auxprotocols/TableDbmProtocols.cpp
${AUX_PATH}/auxprotocols/TableServerProtocols.cpp
${AUX_PATH}/auxprotocols/LobbyServerProtocols.cpp
${AUX_PATH}/auxprotocols/ShadowLobbyClientProtocols.cpp

${PROTOCOL_PATH}/sitemasks.cpp
${PROTOCOL_PATH}/counters.cpp
${PROTOCOL_PATH}/timezone.cpp
${PROTOCOL_PATH}/esl/SecureStorageManager.cpp
${PROTOCOL_PATH}/esl/EslResolver.cpp
${PROTOCOL_PATH}/esl/utils.cpp
${PROTOCOL_PATH}/shared/str_convert.cpp
${PROTOCOL_PATH}/shared/string_utils.cpp
${PROTOCOL_PATH}/shared/numeric_utils.cpp

${AUX_PATH}/auxprotocols/RaceServerProtocols.cpp
${AUX_PATH}/auxprotocols/RaceDbmProtocols.cpp
${AUX_PATH}/auxprotocols/NotificationProtocols.cpp
${AUX_PATH}/auxprotocols/AuxReefProtocols.cpp
${AUX_PATH}/auxprotocols/JackpotServerProtocols.cpp
${AUX_PATH}/auxprotocols/MainDbmProtocols.cpp
${AUX_PATH}/auxprotocols/QueryDbmProtocols.cpp

# IS Protocols 
${AUX_PATH}/auxprotocols/IntegrationDbmProtocols.cpp
${AUX_PATH}/auxprotocols/BackofficeAdaptorProtocols.cpp
${AUX_PATH}/auxprotocols/ISAssistantProtocols.cpp
${AUX_PATH}/auxprotocols/WebProtocols.cpp
${AUX_PATH}/auxprotocols/AuxTriggerProtocols.cpp

# Admin Protocols
${AUX_PATH}/auxprotocols/RGProxyServerProtocols.cpp
${AUX_PATH}/auxprotocols/AdmProtocols.cpp
${AUX_PATH}/auxprotocols/AbeServerProtocols.cpp
${AUX_PATH}/auxprotocols/FASTGatewayProtocols.cpp
${AUX_PATH}/auxprotocols/AuxAamsGatewayProtocols.cpp
${AUX_PATH}/auxprotocols/RaceSchedulerProtocols.cpp
${AUX_PATH}/auxprotocols/TemplateServerProtocols.cpp
${AUX_PATH}/auxprotocols/HHServerInternalProtocols.cpp
${AUX_PATH}/auxserverprotocols/EmailServerProtocols.cpp
${PROTOCOL_PATH}/itgateway/itGatewayProtocols.cpp
${PROTOCOL_PATH}/loginhelper.cpp

${PROTOCOL_PATH}/i18n.locales.cpp
${PROTOCOL_PATH}/i18n.localutil.cpp
${PROTOCOL_PATH}/i18n.utils.cpp
${PRODUCTION_BASE_PATH}/locales/i18n.str_int.cpp
${PRODUCTION_BASE_PATH}/locales/i18n.str_ahh.cpp
${PRODUCTION_BASE_PATH}/locales/i18n.msg_int.cpp
${PRODUCTION_BASE_PATH}/locales/i18n.msg_ahh.cpp
)

set(COMMLIB_FILES
${COMMLIB_PATH}/commmsgbody.cpp
)

set(PLIB_FILES
${PLIB_PATH}/ppblock.cpp
${PLIB_PATH}/ppiofile.cpp
${PLIB_PATH}/ppjsonparser.cpp
${PLIB_PATH}/ppstring.cpp
${PLIB_PATH}/ppincludebase.cpp
${PLIB_PATH}/ppmsg.cpp
)

source_group("Tests" FILES ${ADMINIS_TEST_FILES})
source_group("Stubs" FILES ${STUB_FILES})
source_group("Fakes" FILES ${FAKE_FILES})
source_group("Mocks" FILES ${MOCK_FILES})
source_group("Production" FILES ${PRODUCTION_FILES})
source_group("Aux" FILES ${AUX_FILES})
source_group("Commlib"  FILES ${COMMLIB_FILES})
source_group("PLib" FILES ${PLIB_FILES})
source_group("Protocols" FILES ${PROTOCOL_FILES})

add_executable(adminis_unittests
${ADMINIS_TEST_FILES}
${STUB_FILES}
${FAKE_FILES}
${MOCK_FILES}
${PRODUCTION_FILES}
${PROTOCOL_FILES}
${AUX_FILES}
${COMMLIB_FILES}
${PLIB_FILES}
)

target_include_directories(adminis_unittests AFTER PRIVATE
${COMMLIB_PATH}
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
${MOCKS_PATH}
${FAKES_PATH}
${UNITTESTS_PATH}
${UNITTESTS_PATH}/common
)

target_link_libraries(adminis_unittests gtest gmock gtest_main)

if (MSVC)
	target_compile_options(adminis_unittests PRIVATE /bigobj)
	target_compile_options(adminis_unittests PRIVATE /W1)
	target_include_directories(adminis_unittests AFTER PRIVATE ${PRODUCTION_BASE_PATH}/commlib2a/openssl/windows/vs2017/include)
	if (${CMAKE_VS_PLATFORM_NAME} STREQUAL "x64")
		set(OPENSSL_LIB_PATH "${PRODUCTION_BASE_PATH}/commlib2a/openssl/windows/vs2017/x64/lib")
	else()
		set(OPENSSL_LIB_PATH "${PRODUCTION_BASE_PATH}/commlib2a/openssl/windows/vs2017/x86/lib")
	endif()
	target_link_libraries(adminis_unittests ${OPENSSL_LIB_PATH}/libeay32.lib ${OPENSSL_LIB_PATH}/ssleay32.lib Ws2_32.lib)
endif()