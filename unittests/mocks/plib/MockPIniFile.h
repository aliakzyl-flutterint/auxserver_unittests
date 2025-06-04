#pragma once

#include <gmock/gmock.h>
#include "ppinifile.h"
#include <string>


class MockPIniFile
{
public:
	MOCK_METHOD(void, _load, (PIniFile*, const std::string& fileName), ());
	MOCK_METHOD(void, getSection, (const PIniFile*, const std::string& secName, PIniFile::Section* retval));
	MOCK_METHOD(const char*, getSectionProperty, (const std::string& section, const std::string& property));
	MOCK_METHOD(int, getSectionIntProperty, (const std::string& section, const std::string& name, int defaultValue));
};

extern MockPIniFile* mockPIniFile;