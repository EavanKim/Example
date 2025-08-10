#pragma once

template<typename Key, typename Value>
class MTMap
{
public:
	MTMap( )
	{
	}
	
	~MTMap( )
	{
	}

	void Insert(const Key& key, const Value& value)
	{
		m_lock.w_Lock();
		m_map[key] = value;
		m_lock.w_Unlock();
	}

	Value* Get(const Key& key)
	{
		m_lock.r_Lock();
		auto it = m_map.find(key);
		Value* result = nullptr;
		if (it != m_map.end())
		{
			result = &it->second;
		}
		m_lock.r_Unlock();
		return result;
	}

	void Delete(const Key& key)
	{
		m_lock.w_Lock();
		m_map.erase(key);
		m_lock.w_Unlock();
	}

	void Lock()
	{
		m_lock.w_Lock( );
	}

	void Unlock()
	{
		m_lock.w_Unlock( );
	}

	typename std::unordered_map<Key, Value>::iterator begin()
	{
		return m_map.begin();
	}

	typename std::unordered_map<Key, Value>::iterator end()
	{
		return m_map.end();
	}

	void Clear()
	{
		m_lock.w_Lock( );
		m_map.clear( );
		m_lock.w_Unlock( );
	}

private:
	MTLock m_lock = MTLock();
	std::unordered_map<Key, Value> m_map = {};
};