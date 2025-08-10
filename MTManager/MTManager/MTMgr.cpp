#include "MTMgr.h"

MTMgr* MTMgr::m_instance = nullptr;
MTLock MTMgr::m_lock = MTLock();

MTMgr* MTMgr::GetInstance( )
{
	m_lock.r_Lock( );

	MTMgr* result = m_instance;

	m_lock.r_Unlock( );
	
	return result;
}

void MTMgr::Initialize( )
{
	m_lock.w_Lock( );

	if(nullptr == m_instance)
	{
		m_instance = new MTMgr( );
	}

	m_lock.w_Unlock( );
}

void MTMgr::Destroy( )
{
	m_lock.w_Lock( );

	if( nullptr != m_instance )
	{
		delete m_instance;
		m_instance = nullptr;
	}

	m_lock.w_Unlock( );
}

std::string MTMgr::GetString( std::string& _key )
{
	std::string result = "";

	std::string* val = m_stringMap.Get( _key );
	if(nullptr != val)
	{
		result = *val;
	}

	return result;
}

bool MTMgr::SetString( std::string& _key, std::string _value )
{
	m_stringMap.Insert( _key, _value );

	return true;
}

MTMgr::MTMgr( )
{
}

MTMgr::~MTMgr( )
{
}
