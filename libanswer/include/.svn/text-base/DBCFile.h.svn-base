#ifndef __TPOC_DB_FILE_H_
#define __TPOC_DB_FILE_H_

#include <vector>
#ifdef WIN32
#include <hash_map>
#define		tsnprintf		_snprintf
#else
#include <ext/hash_map>
#define		tsnprintf		snprintf
#endif

#define MAX_FILE_PATH  260
using namespace std;

class ANSWER_EXPORT_SYMBOL CDBCFile	
{
public:
	//文件头
	struct FILE_HEAD
	{
		unsigned int		m_Identify;				//标示	0XDDBBCC00
		int					m_nFieldsNum;			//列数
		int					m_nRecordsNum;			//行数
		int					m_nStringBlockSize;		//字符串区大小
	};

	//字段数据类型
	enum FIELD_TYPE
	{
		T_INT		= 0,	//整数
		T_FLOAT		= 1,	//浮点数
		T_STRING	= 2,	//字符串
	};

	//数据库格式描述
	typedef std::vector< FIELD_TYPE >	FILEDS_TYPE;

	//数据段
	union FIELD
	{
		float		fValue;
		int			iValue;
		const char*	pString;	// Just for runtime!

		//Construct
		FIELD() {}
		FIELD(int value) { iValue = value; }
		FIELD(float value) { fValue = value; }
		FIELD(const char* value) { pString = value; }
	};
	//数据区
	typedef vector< FIELD >		DATA_BUF;


public:
	CDBCFile(unsigned int id);
	virtual ~CDBCFile();

public:
	//打开文本文件，生成一个数据库
	bool					OpenFromTXT(const char* szFileName);
	//根据内存中的文件打开
	bool					OpenFromMemory(const char* pMemory, const char* pDeadEnd, const char* szFileName=0);
protected:
	//读取文本格式内容
	bool					OpenFromMemoryImpl_Text(const char* pMemory, const char* pDeadEnd, const char* szFileName=0);
	//读取二进制格式内容
	bool					OpenFromMemoryImpl_Binary(const char* pMemory, const char* pDeadEnd, const char* szFileName=0);

public:
	//按索引查找(第一列为索引)
	virtual const FIELD*	Search_Index_EQU(int nValue) const;
	//按照位置查找
	virtual const FIELD*	Search_Posistion(int nRecordLine, int nColumNum) const;
	//查找某列等于指定值的第一行
	virtual const FIELD*	Search_First_Column_Equ(int nColumnNum, const FIELD& value) const;

public:
	//取得ID
	unsigned int GetID() const				{ return m_ID; }
	//取得列数
	int	GetFieldsNum() const	    { return m_nFieldsNum; }
	//取得记录的条数
	int GetRecordsNum() const		{ return m_nRecordsNum; }
	//生成索引列
	void CreateIndex(int nColum = 0, const char* szFileName=0);

protected:
#ifdef __SGI_STL_PORT
	typedef std::hash_map< int, FIELD*>	FIELD_HASHMAP;
#else
#ifdef WIN32
	typedef stdext::hash_map< int, FIELD*>	FIELD_HASHMAP;
#else
	typedef __gnu_cxx::hash_map< int,FIELD*>    FIELD_HASHMAP;
	// hash_compare <INT, less<INT> > ,
	//allocator< pair<const INT, FIELD*> > >

#endif

#endif
	//数据库格式文件名
	unsigned int			m_ID;
	//数据库格式描述
	FILEDS_TYPE				m_theType;
	//行数
	int					m_nRecordsNum;
	//列数
	int					m_nFieldsNum;
	//数据区
	DATA_BUF				m_vDataBuf;		//size = m_nRecordsNum*m_nFieldsNum
	//字符串区
	char*					m_pStringBuf;
	//字符串区大小
	int					m_nStringBufSize;
	//索引表
	FIELD_HASHMAP			m_hashIndex;
	//索引列
	int					m_nIndexColum;

	FILE*					m_pf;

public:

	static int			_ConvertStringToVector(const char* strStrINTgSource, vector< std::string >& vRet, const char* szKey, bool bOneOfKey, bool bIgnoreEmpty);
	//从内存中字符串读取一行文本(按照换行符)
	static const char*	_GetLineFromMemory(char* pStringBuf, int nBufSize, const char* pMemory, const char* pDeadEnd);
	//比较两个值是否相等
	template < FIELD_TYPE T>	
	static bool				_FieldEqu(const FIELD& a, const FIELD& b);
};

#endif	// __TPOC_DB_FILE_H_
