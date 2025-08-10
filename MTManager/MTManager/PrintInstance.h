#pragma once

class PrintInstance
{
public:
	PrintInstance( );
	PrintInstance( std::string _data );

	std::string operator*( );

	std::string m_data = "";
};