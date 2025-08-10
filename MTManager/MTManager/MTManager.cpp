#include "MTMgr.h"

unsigned int commandThread(void* _ptr)
{

	return 0;
}

unsigned int invokeThread(void* _ptr)
{


	return 0;
}

volatile int main()
{
	MTMgr::Initialize( );
	std::cout << "MTManager is running!" << std::endl;

	HANDLE command = ( HANDLE ) _beginthreadex( NULL, NULL,  &commandThread, NULL, NULL, NULL);
	HANDLE invoke = ( HANDLE ) _beginthreadex( NULL, NULL, &invokeThread, NULL, NULL, NULL );

	//std::cout << MTMgr::GetInstance( )->GetString( "test", "play" );

	WaitForSingleObject( command, INFINITE );
	WaitForSingleObject( invoke, INFINITE );

	return 0;
}
