#include "stdafx.h"

#include "DayTime.h"
#include "Logger.h"
#include "SockOpts.h"
#include "ClientConnection.h"
#include "MultiConnection.h"

using namespace Answer;
using namespace std;

MultiConnection::MultiConnection()
	: m_running(false)
{
	m_timeout.tv_sec = 0;
	m_timeout.tv_usec = 50*1000;//50ms
}

MultiConnection::~MultiConnection()
{

}

void MultiConnection::run()
{
	m_running = true;
	while ( m_running )
	{
		handleRemovedFds();

		fd_set *rfds = NULL;
		fd_set *wfds = NULL;

		getFdSets(rfds, wfds);
		if (rfds == NULL && wfds == NULL)
		{
			DayTime::sleep(m_timeout.tv_sec*1000+m_timeout.tv_usec/1000);
			continue;
		}

		int ret = select(0, rfds, wfds, NULL, &m_timeout);

		if (ret > 0)
		{
			dispatchEvent(rfds, wfds);
		}
		else if (ret == 0)
		{
			continue;
		}
		else
		{
			LOG_ERROR("TcpMultiplexor::run() select return %d, errno %d\n", ret, WSAGetLastError());
			m_running = false;
		}
	}
}

void MultiConnection::stop()
{
	m_running = false;
	join();
}

void MultiConnection::add( ClientConnection *pConn, MultiplexorMask mask )
{
	if (pConn != NULL)
	{
		MutexGuard lock(m_lock);
		m_conns.insert( SockConnMap::value_type( pConn->getfd(), pConn ) );
	}
}

void MultiConnection::remove( ClientConnection *pConn )
{
	if (pConn != NULL)
	{
		MutexGuard lock(m_lock);
		m_removelist.push_back( pConn->getfd() );
	}
}

void MultiConnection::getFdSets(fd_set *&rfds, fd_set *&wfds)
{
	FD_ZERO(&m_rfds);
	FD_ZERO(&m_wfds);

	MutexGuard lock(m_lock);
	for (SockConnMap::iterator it = m_conns.begin(); it != m_conns.end(); ++it)
	{
		ClientConnection *pConn = it->second;
		if (pConn != NULL)
		{
			socket_t fd = pConn->getfd();
			if (fd == INVALID_SOCKET)
			{
				continue;
			}
			FD_SET( fd, &m_rfds );
			if ( pConn->needSend() )
			{
				FD_SET( fd, &m_wfds );
			}
		}
	}

	getFdSet(m_rfds, rfds);
	getFdSet(m_wfds, wfds);
}

void MultiConnection::getFdSet(fd_set &in, fd_set *&out)
{
	if ( !in.fd_count )
	{
		out = NULL;
	}
	else
	{
		out = &in;
	}
}

void MultiConnection::handleRemovedFds()
{
	MutexGuard lock(m_lock);
	for (SockList::iterator it = m_removelist.begin(); it != m_removelist.end(); ++it)
	{
		m_conns.erase(*it);
	}
	m_removelist.clear();
}

void MultiConnection::dispatchEvent(const fd_set *rfds, const fd_set *wfds)
{
	if (rfds != NULL)
	{
		dispatchEvent(rfds, MASK_READ);
	}

	if (wfds != NULL)
	{
		dispatchEvent(wfds, MASK_WRITE);
	}
}

void MultiConnection::dispatchEvent(const fd_set *fds, MultiplexorMask mask)
{
	if (fds != NULL)
	{
		for (unsigned int i = 0; i < fds->fd_count; i++)
		{
			SOCKET fd = fds->fd_array[i];
			ClientConnection *pConn = NULL;
			{
				MutexGuard lock(m_lock);
				SockConnMap::iterator it = m_conns.find(fd);
				if (it != m_conns.end())
				{
					pConn = it->second;
				}			
			}

			if (pConn != NULL)
			{
				switch (mask)
				{
				case MASK_READ:
					if ( pConn->onRecv() == -1 )
					{
						remove( pConn );
						pConn->close();
					}
					break;
				case MASK_WRITE:
					{
						if ( pConn->onSend() == -1)
						{
							remove( pConn );
							pConn->close();
						}
					}
					break;
				default:
					LOG_ERROR("TcpMultiplexor::dispatchEvent with wrong mask %d\n", mask);
					break;
				}
			}
		}
	}
}

