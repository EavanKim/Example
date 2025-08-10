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
	std::cout << "MTManager is running!" << std::endl;

	HANDLE command = ( HANDLE ) _beginthreadex( NULL, NULL,  &commandThread, NULL, NULL, NULL);

	// 시간이 충분히 지난 뒤
	unsigned long long counter = 0;
	for( ; counter > 100000000; ++counter ) 
	{
		std::this_thread::yield( ); // Simulate some work
	};

	//Simulation Hardware Interrupts
	HANDLE invoke = ( HANDLE ) _beginthreadex( NULL, NULL, &invokeThread, NULL, NULL, NULL );

	WaitForSingleObject( invoke, INFINITY );

	std::string str = "GetKey";
	std::cout << MTMgr::GetInstance( )->GetString( str );

	WaitForSingleObject( command, INFINITY );

	return 0;
}
