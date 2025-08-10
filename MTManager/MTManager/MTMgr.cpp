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

bool MTMgr::Load( std::string _storage )
{
	if( nullptr != m_bankMap.Get(_storage) )
	{
		PrintBank* newBank = new PrintBank( );

		if( !newBank->Loading( _storage ) )
		{
			delete newBank;
			return false;
		}

		m_bankMap.Insert( _storage, newBank );
	}

	return true;
}

void MTMgr::SetQueue( const PrintDescription* _description )
{
	PrintBank** bankptr = m_bankMap.Get( _description->m_key );
	PrintBank* bank = nullptr;
	if(nullptr == bankptr )
	{
		if(Load( _description->m_bankName ))
		{

		}
		else
		{
			throw std::exception( "Print Loading Fail" );
		}

		bankptr = m_bankMap.Get( _description->m_key );
		if(nullptr == bankptr)
			throw std::exception( "Print Loading Fail" );
	}

	bank = *bankptr;

	m_queueLock.r_Lock( );
	m_queue.push( bank->m_map.Get( _description->m_key )->m_data );
	m_queueLock.r_Unlock( );
}

void MTMgr::GetLast( std::string& _pop )
{
	m_queueLock.r_Lock( );

	if( 0 != m_queue.size( ) )
	{
		_pop = m_queue.front( );
		m_queue.pop( );
	}

	m_queueLock.r_Unlock( );
}

MTMgr::MTMgr( )
{

}

MTMgr::~MTMgr( )
{
	m_bankMap.Lock( );

	std::unordered_map<std::string, PrintBank*>::iterator iter = m_bankMap.begin( );
	std::unordered_map<std::string, PrintBank*>::iterator end = m_bankMap.end( );

	for( ; iter != end; ++iter )
	{
		delete iter->second;
		iter->second = nullptr;
	}

	m_bankMap.Unlock( );
}
