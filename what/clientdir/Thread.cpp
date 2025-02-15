#include "Thread.h"
#include <assert.h>
namespace CacheTube {
	Thread::Thread( void ) {
		m_strThreadID = "";
		m_strConfPath = "";
		m_strTopic = "";
		m_Thread = static_cast< pthread_t >( 0 );
	}
	Thread::~Thread( void ) {
		m_strThreadID = "";
		m_strConfPath = "";
		m_strTopic = "";
		m_Thread = static_cast< pthread_t >( 0 );
	}
	bool Thread::Start( void ) {
		assert( static_cast< pthread_t >( 0 ) == m_Thread );
		if ( 0 != pthread_create( &m_Thread, NULL, CallBack, reinterpret_cast< void * >( this ) ) ) {
			return false;
		}
		return true;
	}
	bool Thread::Join( void ) {
		assert( static_cast< pthread_t >( 0 ) != m_Thread );
		if ( 0 != pthread_join( m_Thread, NULL ) ) {
			return false;
		}
		return true;
	}
	void * Thread::CallBack( void * arg ) {
		assert( NULL != arg );
		Thread * pThread = NULL;
		pThread = reinterpret_cast< Thread * >( arg );
		pThread->Entry();
		return NULL;
	}
}
