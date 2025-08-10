#pragma once
#include <iostream>
#include <string>
#include <memory>

#include <thread>

#include <unordered_map>

#include <Windows.h>

#include "MTSpinLock.h"
#include "MTMap.h"

class MTMgr
{
public:
	static MTMgr* GetInstance( );
	static void Initialize( );
	static void Destroy( );

	std::string GetString(std::string& _key);
	bool SetString( std::string& _key, std::string _value );

private:
	MTMgr( );
	~MTMgr( );

	static MTMgr* m_instance;
	static MTLock m_lock;

	MTMap<std::string, std::string> m_stringMap;
};