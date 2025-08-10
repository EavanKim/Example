#include "MTMgr.h"
#include "PrintDescription.h"

PrintDescription::PrintDescription( PrintBank* _bank, std::string _key )
	: m_bankName( _bank->m_name )
	, m_bank( _bank )
	, m_key( _key )
{

}

void PrintDescription::Print( )
{
}
