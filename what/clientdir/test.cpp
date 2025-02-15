
#include "CacheTube.h"
#include <iostream>
#include <fstream>
namespace CacheTube {
	extern "C"	int main( int argc, char * argv[] )
	{
		Error_Info e_info;
		CCacheTube cacheTube;
		::std::string strConfPath = "./client.conf";
		::std::string strTopic = "topic_liwei";
		::std::vector< Message > v_msgs;
		::std::vector< Message >::iterator iter;
		e_info = cacheTube.Init( strConfPath );
		if ( kErrCode_OK != e_info.code ) {
			::std::cout<<" error code = "<<e_info.code<<" description = "<<e_info.description<<::std::endl;
			return -1;
		}
		::std::cout<<" Init OK! "<<::std::endl;
		v_msgs.clear();
		char temp[ 10 ];
		Message msg;
		for ( int32_t i = 0; i < 100; ++i ) {
			msg.uid = 12345;
			msg.srcip = "123.123.123.123";
			(void)time( (long int *)&msg.created_time );
			(void)sprintf( temp, "%d", i );
			msg.content = ::std::string( "this is content of wangjianguo 0.8.0 " ) + ::std::string( temp );
			//::std::cout<<msg.content<<::std::endl;
			v_msgs.push_back( msg );
		}
		e_info = cacheTube.Put( strTopic, v_msgs );
		if ( kErrCode_OK != e_info.code ) {
			::std::cout<<" error code = "<<e_info.code<<" description = "<<e_info.description<<::std::endl;
			return -1;
		}
		::std::cout<<" Put OK! "<<::std::endl;
		v_msgs.clear();
		e_info = cacheTube.Get( strTopic, v_msgs );
		if ( kErrCode_OK != e_info.code ) {
			::std::cout<<" error code = "<<e_info.code<<" description = "<<e_info.description<<::std::endl;
			return -1;
		}
		try {
			::std::ofstream out( "./get.out" ); 	
			for ( iter = v_msgs.begin(); iter != v_msgs.end(); ++iter ) {
				out<<" queuename="<<iter->queue_name<<" uid="<<iter->uid<<" srcip="<<iter->srcip<<" time="<<iter->created_time<<" content"<<iter->content<<::std::endl;
			}
			out.close();
		} catch ( ... ) {
			::std::cout<<"write file exception"<<::std::endl;
			return -1;	
		}
		::std::cout<<" Get OK! "<<::std::endl;
		e_info = cacheTube.Destroy();
		if ( kErrCode_OK != e_info.code ) {
			::std::cout<<" error code = "<<e_info.code<<" description = "<<e_info.description<<::std::endl;
			return -1;
		}
		::std::cout<<" Destroy OK! "<<::std::endl;
		return 0;
	}
}

