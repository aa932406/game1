/********************************************************
* 对象池												*
* 游戏中所有对象的预创建与内存管理						*
* 2014.12.3												*
* robin													*
********************************************************/

#ifndef __TPOC_POOL_MANAGER_H__
#define	__TPOC_POOL_MANAGER_H__

#if defined(LIBANSWER_LINUX)
#include <typeinfo>
#endif

#include "ObjectPool.h"

namespace tpoc
{
	class ObjectPoolBase
	{
	public:
		template<typename T>
		T* pop()
		{
			return (T*)_pop();
		}

		template<typename T>
		void push( T* pObj )
		{
			_push( (void*)pObj );
		}

	protected:
		virtual	void* _pop() = 0;
		virtual void _push( void* pObj ) = 0;
	};

	template<typename T>
	class ObjectPool : public ObjectPoolBase
	{
	public:
		ObjectPool(unsigned int initCount, unsigned int maxCount)
			: m_initCount(initCount), m_maxCount(maxCount)
		{
			for (unsigned int i = 0; i != initCount; ++i)
			{
				_push(new T);
			}
		}

		~ObjectPool()
		{
			T *pVal = NULL;
			while ((pVal = m_pool.pop()) != NULL)
			{
				delete pVal;
			}
		}

	protected:
		virtual void* _pop()
		{
			T *pVal = m_pool.pop();
			if (pVal == NULL)
			{
				pVal = new T;
			}
			pVal->reset();

			return (void*)pVal;
		}

		virtual void _push( void *pObj)
		{
			T* pVal = (T*)pObj;
			if (pVal != NULL)
			{
				pVal->reset();
				m_pool.push(pVal);

				if (m_pool.size() > m_maxCount)
				{
					delete m_pool.pop();
				}
			}
		}

	private:
		Answer::SafeQueue<T*> m_pool;

		int m_initCount;
		int m_maxCount;
	};
}

class CPoolManager
{
	typedef std::map<std::string, tpoc::ObjectPoolBase*> PoolMap;
public:
	CPoolManager();
	~CPoolManager();

public:
	void Init();

public:
	template<typename T>
	T* pop()
	{
		T* pObj = NULL;
		std::string name = typeid(T).name();
		PoolMap::iterator iter = m_mPool.find( name );
		if ( iter != m_mPool.end() )
		{
			pObj = iter->second->pop<T>();
		}

		if ( NULL == pObj )
		{
			LOG_ERROR( "CPoolManager::pop() unregister type ( %s ) \n", name.c_str() );
			pObj = new T();
		}

		return pObj;
	}

	template<typename T>
	void push( T* pObj )
	{
		if ( NULL == pObj )
		{
			return;
		}

		std::string name = typeid(T).name();
		PoolMap::iterator iter = m_mPool.find( name );
		if ( iter != m_mPool.end() )
		{
			iter->second->push<T>( pObj );
			return;
		}

		LOG_ERROR( "CPoolManager::Push() unregister type ( %s ) \n", name.c_str() );
		delete pObj;
	}

private:
	template<typename T>
	void regPool( uint32_t nMinSize, uint32_t nMaxSize )
	{
		std::string name = typeid(T).name();
		tpoc::ObjectPoolBase* pStu = new tpoc::ObjectPool<T>( nMinSize, nMaxSize );
		if ( !m_mPool.insert( PoolMap::value_type( name, pStu ) ).second )
		{
			LOG_ERROR( "CPoolManager::regPool() has register type ( %s ) \n", name.c_str() );
		}
	}

private:
	PoolMap	m_mPool;
};

#define POOL_MANAGER Answer::Singleton<CPoolManager>::instance()


#endif	//__TPOC_POOL_MANAGER_H__
