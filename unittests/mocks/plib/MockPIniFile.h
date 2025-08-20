#pragma once

#include <gmock/gmock.h>
#include "ppinifile.h"
#include <string>


class MockPIniFile
{
public:
	MOCK_METHOD(void, _load, (PIniFile*, const std::string& fileName), ());
	// To return a nullptr one should return true, like
	// EXPECT_CALL(*mockPIniFile, getSection(_, _, _)).WillRepeatedly(Return(true));
	MOCK_METHOD(bool, getSection, (const PIniFile*, const std::string& secName, PIniFile::Section* retval));
	MOCK_METHOD(const char*, getSectionProperty, (const std::string& section, const std::string& property));
	MOCK_METHOD(int, getSectionIntProperty, (const std::string& section, const std::string& name, int defaultValue));
};

extern MockPIniFile* mockPIniFile;