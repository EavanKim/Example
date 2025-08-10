#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <memory>
#include <fstream>
#include <filesystem>

#include <thread>

#include <queue>
#include <unordered_map>

#include <Windows.h>

#include "MTUtil.h"

#include "MTSpinLock.h"
#include "MTMap.h"

#include "PrintInstance.h"
#include "PrintDescription.h"
#include "PrintBank.h"

class MTMgr
{
public:
	static MTMgr* GetInstance( );
	static void Initialize( );
	static void Destroy( );

	bool Load( std::string _storage );

	void SetQueue( const PrintDescription* _description );

	void GetLast( std::string& _pop );

private:
	MTMgr( );
	~MTMgr( );

	static MTMgr* m_instance;
	static MTLock m_lock;

	int ( *m_callFunc )( void* );
	HANDLE m_thread = INVALID_HANDLE_VALUE;
	MTLock m_queueLock;
	std::queue<std::string> m_queue;
	MTMap<std::string, PrintBank*> m_bankMap;
};