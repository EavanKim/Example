#pragma once

class MTLock
{
public:
	MTLock( );
	~MTLock( );

	void w_Lock( );
	bool w_TryLock( );
	void w_Unlock( );

	void r_Lock( );
	bool r_TryLock( );
	void r_Unlock( );

private:
	bool w_check( );
	bool r_check( );

private:
	volatile unsigned long long m_wlock;
	volatile LONG m_rlock;
};