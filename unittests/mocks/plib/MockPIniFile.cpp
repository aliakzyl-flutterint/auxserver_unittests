#include "MockPIniFile.h"

void PIniFile::_load(const char* fileName)
{
	mockPIniFile->_load(this, fileName);
}

void PIniFile::_load(const BYTE* p, size_t sz)
{
}

const char* PIniFile::Section::getProperty(const char* name_) const
{
	auto retval = mockPIniFile->getSectionProperty(this->name.c_str(), name_);
	return (retval != nullptr)? retval: "";
}

const PIniFile::Section* PIniFile::getSection(const char* secName) const
{
	auto retval = new PIniFile::Section;
	retval->name = PString(secName);
	mockPIniFile->getSection(this, secName, retval);
	return retval;
}

PIniFile::Section* PIniFile::getSection(const char* secName)
{
	auto retval = new PIniFile::Section;
	retval->name = PString(secName);
	bool overloaded = mockPIniFile->getSection(this, secName, retval);
    if (!overloaded)
    {
		return retval;
    }
    else {
        delete retval;
        return nullptr;
    }
}

int PIniFile::Section::getIntProperty(const char* name_, int defaultValue) const
{
	return mockPIniFile->getSectionIntProperty(this->name.c_str(), name_, defaultValue);
}

INT64 PIniFile::Section::getInt64Property(const char* name_, INT64 defaultValue) const
{
	// Add another mock method for INT64 if it gets important
	return mockPIniFile->getSectionIntProperty(this->name.c_str(), name_, defaultValue);
}
