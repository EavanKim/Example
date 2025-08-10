#include "MTMgr.h"

MTLock::MTLock( )
{
	InterlockedExchange( &m_wlock, 0 );
}

MTLock::~MTLock( )
{
	InterlockedExchange( &m_wlock, 0 );
}

void MTLock::w_Lock( )
{
	// 일단 쓰기 세트가 들어간다고 알려주고
	while( 0 != InterlockedCompareExchange(&m_wlock, 1, 0))
	{
		// 이미 진입한 읽기가 끝나는 것을 대기
		while( !r_check( ) )
		{
			std::this_thread::yield( ); // Yield to allow other threads to run
		}

		std::this_thread::yield( ); // Yield to allow other threads to run
	}
}

bool MTLock::w_TryLock( )
{
	if( !r_check( ) )
	{
		return false; // Cannot acquire write lock if read lock is held
	}

	return 0 == InterlockedCompareExchange( &m_wlock, 1, 0 );
}

void MTLock::w_Unlock( )
{
	InterlockedExchange( &m_wlock, 0 );
}

void MTLock::r_Lock( )
{
	while(!w_check())
	{
		std::this_thread::yield( ); // Yield to allow other threads to run
	}

	InterlockedAdd( &m_rlock, 1 );
}

bool MTLock::r_TryLock( )
{
	if( !w_check( ) )
	{
		return false; // Cannot acquire read lock if write lock is held
	}

	InterlockedAdd( &m_rlock, 1 );

	return true;
}

void MTLock::r_Unlock( )
{
	InterlockedAdd( &m_rlock, -1 );
}

bool MTLock::w_check( )
{
	return 0 == InterlockedExchange( &m_wlock, m_wlock );
}

bool MTLock::r_check( )
{
	return 0 == InterlockedExchange( &m_rlock, m_rlock );
}
