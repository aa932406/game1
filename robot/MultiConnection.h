#ifndef __TPOC_MUTI_CONNECTION_H__
#define __TPOC_MUTI_CONNECTION_H__

#include "Mutex.h"
#include "Thread.h"
#include "ClientConnection.h"

#include <list>
#include <map>

class MultiConnection
	: public Thread
{
public:
	MultiConnection();
	virtual ~MultiConnection();

protected:
	virtual void run();

public:
	void		stop();
	void		add( ClientConnection *pConn, MultiplexorMask mask);
	void		remove( ClientConnection *pConn);

private:
	void		getFdSets(fd_set *&rfds, fd_set *&wfds);
	void		getFdSet(fd_set &in, fd_set *&out);
	void		handleRemovedFds();
	void		dispatchEvent(const fd_set *rfds, const fd_set *wfds);
	void		dispatchEvent(const fd_set *fds, MultiplexorMask mask);

private:
	typedef std::list<socket_t> SockList;
	typedef std::map<socket_t, ClientConnection*> SockConnMap;
	SockConnMap	m_conns;
	SockList	m_removelist;
	Mutex		m_lock;
	fd_set		m_rfds;
	fd_set		m_wfds;
	timeval		m_timeout;
	bool		m_running;
};

#endif	//__TPOC_MUTI_CONNECTION_H__
