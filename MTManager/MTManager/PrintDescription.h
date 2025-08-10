#pragma once

#include <string>

class PrintBank;
class PrintDescription
{
public:
	PrintDescription( PrintBank* _bank, std::string _key );

	void Print( );

	std::string m_bankName;
	PrintBank* m_bank;
	std::string m_key;
};