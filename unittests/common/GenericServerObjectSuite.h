#pragma once

#include <gtest/gtest.h>


class GenericServerObjectSuite : public ::testing::Test
{
protected:
	int min_num_servlets = 0;
    
	void SetUp() override;
	void TearDown() override;

	virtual void ExpectInit() = 0;

protected:
	const std::string iniFileName = "TestFileName";
	const std::string defaultValue = "testDefaultValue";
	const std::string hundredValue = "100";

	const std::string connType = "auxlobby";
	const std::string connAuxApp = "auxapp";
	const std::string dbmAddress = "testDbmAddress";
	const std::string dbmInstance = "testDbmInstance";
	const std::string roOltpDbmAddress = "testRoOltpDbmAddress";
	const std::string roOltpDbmInstance = "testRoOltpDbmInstance";
	const std::string idDbmAddress = "testIdDbmAddress";
	const std::string idDbmInstance = "testIdDbmInstance";
	const std::string authIntegrationServerAddress = "testAuthIntegrationServerAddress";
	const std::string authIntegrationServerInstance = "testAuthIntegrationServerInstance";
	const std::string integrationServerAddress = "testIntegrationServerAddress";
	const std::string integrationServerInstance = "testIntegrationServerInstance";
};