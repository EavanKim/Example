#pragma once


class MTUtil
{
public:
	static void format( std::string& _result, const char* _format, ... )
    {
        va_list args;

        // 1. 가변 인자 리스트 준비 (길이 체크용)
        va_start( args, _format );
        int len = vsnprintf( nullptr, 0, _format, args );
        va_end( args );

        // 2. 동적 메모리 할당 (널 포함)
        _result.clear( );
        _result.reserve( len + 1 );

        // 3. 가변 인자 리스트 다시 준비 (포맷 실제 적용)
        va_start( args, _format );
        vsnprintf( _result.data(), len + 1, _format, args );
        va_end( args );
    }

    static void split( std::vector<std::string>& _result, const std::string& input, char delimiter )
    {
        std::istringstream iss( input );
        std::string token;
        while( getline( iss, token, delimiter ) )
        {
            _result.push_back( token );
        }
    }

    static bool readFile( std::vector<std::string>& _result, const std::filesystem::path _path)
    {
        if(std::filesystem::exists(_path))
        {
            std::ifstream ifs( _path );
            std::string line;
            while(std::getline(ifs, line))
            {
                _result.push_back( line );
            }

            return true;
        }

        return false;
    }
};