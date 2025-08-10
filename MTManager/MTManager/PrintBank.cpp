#include "MTMgr.h"

bool PrintBank::Loading( std::string _name )
{
	std::string path = "";
	MTUtil::format( path, "%s\\%s.txt", std::filesystem::current_path( ).c_str( ), _name );
	std::filesystem::path filePath( path );

	std::vector<std::string> fileLines;
	if( MTUtil::readFile( fileLines, filePath ) )
	{
		int max = ( int ) fileLines.size( );
		for( int count = 0; max > count; ++count )
		{
			std::vector<std::string> split;
			MTUtil::split( split, fileLines[ count ], ',' );

			m_map.Insert( split[ 0 ], split[ 1 ] );
		}

		m_name = _name;

		return true;
	}

	return false;
}

PrintDescription* PrintBank::CreateDescription( std::string _key )
{
	PrintInstance* inst = m_map.Get( _key );
	if(nullptr != inst)
	{
		return new PrintDescription( this, _key );
	}

	return nullptr;
}
