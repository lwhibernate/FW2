
#include "CacheTube.h"
#include <iostream>
#include <sys/time.h>
#include <fstream>
namespace CacheTube {
	extern "C"	int main( int argc, char * argv[] )
	{
		Error_Info e_info;
		CCacheTube cacheTube;
		::std::string strConfPath = "./client.conf";
		::std::string strTopic = "topic1";
		::std::vector< Message > v_msgs;
		::std::vector< Message >::iterator iter;
		e_info = cacheTube.Init( strConfPath );
		if ( kErrCode_OK != e_info.code ) {
			::std::cout<<" error code = "<<e_info.code<<" description = "<<e_info.description<<::std::endl;
			return -1;
		}
		::std::cout<<" Init OK! "<<::std::endl;
		v_msgs.clear();
		Message msg;
		for ( int32_t i = 0; i < 100; ++i ) {
			msg.queue_name = strTopic;
			msg.srcip = "123.123.123.123";
			(void)time( &msg.created_time );
			v_msgs.push_back( msg );
		}
		::std::ofstream out( "./clientw.out" );
		uint32_t uCounter = 0;
		uint32_t uCounter_Put = 0;
		char temp[ 10 ];
		struct timeval timeStart;
		struct timeval timeEnd;
		(void)gettimeofday( &timeStart, NULL ); 
		while ( true ) {
			uCounter_Put++;
			for ( iter = v_msgs.begin(); iter < v_msgs.end(); ++iter ) {
				(*iter).uid = uCounter;
				sprintf( temp, "%d", uCounter );
				(*iter).content = ::std::string( temp );
				uCounter++;
			}
			e_info = cacheTube.Put( strTopic, v_msgs );
			for ( iter = v_msgs.begin(); iter < v_msgs.end(); ++iter ) {
				out<<(*iter).queue_name<<" "<<(*iter).uid<<" "<<(*iter).srcip<<" "<<(*iter).created_time<<" "<<(*iter).content<<::std::endl;	
			}
			if ( kErrCode_OK != e_info.code ) {
				::std::cout<<" error code = "<<e_info.code<<" description = "<<e_info.description<<::std::endl;
				return -1;
			}
			if ( uCounter_Put%50 == 0 ) {
				(void)gettimeofday( &timeEnd, NULL ); 
				printf(" put: %u counter %lu s %lu ms \n", uCounter_Put, static_cast<uint64_t>( timeEnd.tv_sec ) - static_cast<uint64_t>( timeStart.tv_sec ), static_cast<uint64_t>( timeEnd.tv_usec ) - static_cast<uint64_t>( timeStart.tv_usec ) );
				(void)gettimeofday( &timeStart, NULL );
			}	
			if ( 1000 == uCounter_Put ) {
				break;
			} 
		}
		::std::cout<<" Put OK! "<<::std::endl;
		e_info = cacheTube.Destroy();
		if ( kErrCode_OK != e_info.code ) {
			::std::cout<<" error code = "<<e_info.code<<" description = "<<e_info.description<<::std::endl;
			return -1;
		}
		::std::cout<<" Destroy OK! "<<::std::endl;
		return 0;
	}
}

