#include "MTMgr.h"

PrintInstance::PrintInstance( )
{
}

PrintInstance::PrintInstance( std::string _data )
	: m_data( _data )
{
}

std::string PrintInstance::operator*()
{
	return m_data;
}