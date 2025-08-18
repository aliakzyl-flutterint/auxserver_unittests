set(AUX_PATH "${PRODUCTION_BASE_PATH}/auxiliary")
set(PROTOCOL_PATH "${PRODUCTION_BASE_PATH}/protocols")
set(ATF_PATH "${PRODUCTION_BASE_PATH}/atf")
set(COMMLIB_PATH "${PRODUCTION_BASE_PATH}/commlib2a")
set(PLIB_PATH "${PRODUCTION_BASE_PATH}/plib")
set(UNITTESTS_PATH ..)

set(LOBBY_TEST_FILES
${UNITTESTS_PATH}/common/GenericServerObjectSuite.cpp
${UNITTESTS_PATH}/common/ServerObjectsExpects.cpp
GenericLobbyTestSuite.cpp
TestAuxLobbyServerObject.cpp
TestAuxGameRestriction.cpp
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
${STUBS_PATH}/atf_connections_stub.cpp
${STUBS_PATH}/atf1_stubs.cpp
${STUBS_PATH}/AtfCommObjectImpl_stubs.cpp
${STUBS_PATH}/lobby_stubs.cpp
)

set(FAKE_FILES
${FAKES_PATH}/auxservercommon/FakeAuxCommServerObject.cpp
${FAKES_PATH}/auxservercommon/FakeAuxReefAccessor.cpp
${FAKES_PATH}/atf/FakeServer.cpp
${FAKES_PATH}/lobby/FakeLobby.cpp
)

set(MOCK_FILES
${MOCKS_PATH}/atf/MockAtfCommObjectImpl.cpp
${MOCKS_PATH}/auxcommon/MockAuxgenerictypes.cpp
${MOCKS_PATH}/commlib2a/MockServerStartParams.cpp
${MOCKS_PATH}/plib/MockPIniFile.cpp
)

set(PRODUCTION_FILES
    ${AUX_PATH}/auxlobby/AuxLobbyServerObject.cpp
	${AUX_PATH}/auxlobby/AuxLobbyGameRestriction.cpp
	${AUX_PATH}/auxservercommon/AuxCommServerObject.cpp
    #${AUX_PATH}/auxallinonemain.cpp
)

set (PROTOCOL_FILES
	${PRODUCTION_BASE_PATH}/auxprotocols/CommonProtocolStructs.cpp
	${PRODUCTION_BASE_PATH}/auxprotocols/HHServerProtocols.cpp
	${AUX_PATH}/auxserverprotocols/AuxProxyProtocolStructs.cpp
	${AUX_PATH}/auxserverprotocols/CdlDbmProtocols.cpp
	${AUX_PATH}/auxserverprotocols/ServerCommonProtocolStructs.cpp
	${AUX_PATH}/auxprotocols/AuxUserSettingsDbmProtocols.cpp
	${AUX_PATH}/auxprotocols/AuxServerErrors.cpp
	${AUX_PATH}/auxprotocols/AuxReefProtocols.cpp
	${AUX_PATH}/auxprotocols/AdmProtocols.cpp
	${AUX_PATH}/auxprotocols/RGProxyServerProtocols.cpp
	${AUX_PATH}/auxprotocols/isprotocols.cpp
	${AUX_PATH}/auxprotocols/baccaratprotocols.cpp
	${AUX_PATH}/auxprotocols/blackjackprotocols.cpp
	${AUX_PATH}/auxprotocols/CommunityBaccaratProtocols.cpp
	${AUX_PATH}/auxprotocols/DoubleBallRouletteProtocols.cpp
	${AUX_PATH}/auxprotocols/JackpotServerProtocols.cpp
	${AUX_PATH}/auxprotocols/HeadsUpHoldemProtocols.cpp
	${AUX_PATH}/auxprotocols/LobbyClientProtocols.cpp
	${AUX_PATH}/auxprotocols/LobbyServerProtocols.cpp
	${AUX_PATH}/auxprotocols/ShadowLobbyProtocols.cpp
	${AUX_PATH}/auxprotocols/ShadowLobbyClientProtocols.cpp
	${AUX_PATH}/auxprotocols/RaceServerProtocols.cpp
	${AUX_PATH}/auxprotocols/rouletteprotocols.cpp
	${AUX_PATH}/auxprotocols/TableServerProtocols.cpp
	${AUX_PATH}/auxprotocols/ThreeCardPokerProtocols.cpp
	${AUX_PATH}/auxprotocols/MainDbmProtocols.cpp
	${AUX_PATH}/auxprotocols/QueryDbmProtocols.cpp
	${AUX_PATH}/auxprotocols/VTTMServerProtocols.cpp
	${PROTOCOL_PATH}/AtfXml.cpp
	${PROTOCOL_PATH}/timezone.cpp
	${PROTOCOL_PATH}/UserDefStructs.cpp
	${PROTOCOL_PATH}/shared/string_utils.cpp
	${PROTOCOL_PATH}/esl/SecureStorageManager.cpp
	${PROTOCOL_PATH}/esl/EslResolver.cpp
	${PROTOCOL_PATH}/esl/utils.cpp
)

set(AUX_FILES
#${ATF_PATH}/AtfUtility.cpp
)

set(COMMLIB_FILES
#${COMMLIB_PATH}/commmail.cpp
#${COMMLIB_PATH}/commcgi.cpp
#${COMMLIB_PATH}/commmime.cpp
${COMMLIB_PATH}/commmsgbody.cpp
#${COMMLIB_PATH}/commmsgheader.cpp
#${COMMLIB_PATH}/commsmtp.cpp
#${COMMLIB_PATH}/commsrvconn.cpp
#${COMMLIB_PATH}/commssl.cpp
#${COMMLIB_PATH}/commssl0.cpp
#${COMMLIB_PATH}/commsslbase64.cpp
#${COMMLIB_PATH}/commsslchksum.cpp
#${COMMLIB_PATH}/commsslthrow.cpp
#${COMMLIB_PATH}/commsslrand.cpp
#${COMMLIB_PATH}/commqueue.cpp
#${COMMLIB_PATH}/commurl.cpp
)

set(PLIB_FILES
#${PLIB_PATH}/zip/ppdeflate.cpp
#${PLIB_PATH}/zip/ppinflate.cpp
#${PLIB_PATH}/zip/adler32.c
#${PLIB_PATH}/zip/deflate.c
#${PLIB_PATH}/zip/inflate.c
#${PLIB_PATH}/zip/infblock.c
#${PLIB_PATH}/zip/infcodes.c
#${PLIB_PATH}/zip/inftrees.c
#${PLIB_PATH}/zip/inffast.c
#${PLIB_PATH}/zip/infutil.c
#${PLIB_PATH}/zip/trees.c
#${PLIB_PATH}/zip/zutil.c
#${PLIB_PATH}/pbase64.cpp
${PLIB_PATH}/ppblock.cpp
#${PLIB_PATH}/pperror.cpp
#${PLIB_PATH}/ppfstream.cpp
#${PLIB_PATH}/ppi18n_1252.cpp
#${PLIB_PATH}/ppi18n_casefolding.cpp
#${PLIB_PATH}/ppi18n_codepage.cpp
#${PLIB_PATH}/ppi18n_stream.cpp
${PLIB_PATH}/ppincludebase.cpp
#${PLIB_PATH}/ppinifile.cpp
#${PLIB_PATH}/ppinifileex.cpp
${PLIB_PATH}/ppiofile.cpp
${PLIB_PATH}/ppjsoncomposer.cpp
${PLIB_PATH}/ppjsonparser.cpp
#${PLIB_PATH}/pplogtag.cpp
#${PLIB_PATH}/ppmstream.cpp
#${PLIB_PATH}/ppsocket.cpp
#${PLIB_PATH}/ppsocketc.cpp
${PLIB_PATH}/ppstring.cpp
#${PLIB_PATH}/ppstringx.cpp
#${PLIB_PATH}/ppstringutf8.cpp
#${PLIB_PATH}/ppthread.cpp
#${PLIB_PATH}/ppwinwnd.cpp
)

source_group("LobbyTests" FILES ${LOBBY_TEST_FILES})
source_group("Stubs" FILES ${STUB_FILES})
source_group("Fakes" FILES ${FAKE_FILES})
source_group("Mocks" FILES ${MOCK_FILES})
source_group("Production" FILES ${PRODUCTION_FILES})
source_group("Aux" FILES ${AUX_FILES})
source_group("Commlib"  FILES ${COMMLIB_FILES})
source_group("PLib" FILES ${PLIB_FILES})
source_group("Protocols" FILES ${PROTOCOL_FILES})

add_executable(lobby_unittests
${LOBBY_TEST_FILES}
${STUB_FILES}
${FAKE_FILES}
${MOCK_FILES}
${PRODUCTION_FILES}
${PROTOCOL_FILES}
${AUX_FILES}
${COMMLIB_FILES}
${PLIB_FILES}
)

target_include_directories(lobby_unittests AFTER PRIVATE
${PRODUCTION_BASE_PATH}/atf
${PRODUCTION_BASE_PATH}/db2_libs/CLI9/include
${PRODUCTION_BASE_PATH}/commextlib
${PRODUCTION_BASE_PATH}/commlib2a
${PRODUCTION_BASE_PATH}/plib
${PRODUCTION_BASE_PATH}/protocols
${PRODUCTION_BASE_PATH}/locales
${PRODUCTION_BASE_PATH}/auxprotocols
${PRODUCTION_BASE_PATH}/auxprotocols
${PRODUCTION_BASE_PATH}/auxserverprotocols
${AUX_PATH}
${AUX_PATH}/auxlobby
${MOCKS_PATH}
${FAKES_PATH}
${UNITTESTS_PATH}/common
)

target_link_libraries(lobby_unittests gtest gmock gtest_main)

if (MSVC)
	target_compile_options(lobby_unittests PRIVATE /bigobj)
	target_compile_options(lobby_unittests PRIVATE /W1)
	target_include_directories(lobby_unittests AFTER PRIVATE ${PRODUCTION_BASE_PATH}/commlib2a/openssl/windows/vs2017/include)
	if (${CMAKE_VS_PLATFORM_NAME} STREQUAL "x64")
		set(OPENSSL_LIB_PATH "${PRODUCTION_BASE_PATH}/commlib2a/openssl/windows/vs2017/x64/lib")
	else()
		set(OPENSSL_LIB_PATH "${PRODUCTION_BASE_PATH}/commlib2a/openssl/windows/vs2017/x86/lib")
	endif()
	target_link_libraries(lobby_unittests ${OPENSSL_LIB_PATH}/libeay32.lib ${OPENSSL_LIB_PATH}/ssleay32.lib Ws2_32.lib)
endif()