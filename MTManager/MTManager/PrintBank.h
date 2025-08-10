#pragma once

class PrintBank
{
public:
	bool Loading( std::string _name );
	PrintDescription* CreateDescription( std::string _key );

	std::string m_name;
	MTMap<std::string, PrintInstance> m_map;
};