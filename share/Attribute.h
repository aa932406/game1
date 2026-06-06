#ifndef __TPOC_ATTRIBUTE__
#define __TPOC_ATTRIBUTE__
#include <stdint.h>
#include <strings.h>
#define ATTR_CUR_HP		31		//����buff��ʹ��
//INT����
class CObjAttrs
{
public:
	typedef enum
	{
		ATTR_INVALID			= -1,
		ATTR_HP					= 1,			// ����ֵ
		ATTR_MP					= 2,			// ����ֵ
		ATTR_PP					= 3,			// ����ֵ
		ATTR_XP					= 4,			// XPֵ
		ATTR_PHY_ATK_MIN		= 5,			// ��С��������
		ATTR_PHY_ATK_MAX		= 6,			// �����������
		ATTR_MAG_ATK_MIN		= 7,			// ��Сħ������
		ATTR_MAG_ATK_MAX		= 8,			// ���ħ������
		ATTR_PHY_DEF			= 9,			// ��������
		ATTR_MAG_DEF			= 10,			// ħ������
		ATTR_HITRATE			= 11,			// ����
		ATTR_DODGE				= 12,			// ����
		ATTR_CRITRATE			= 13,			// ����
		ATTR_TENACITY			= 14,			// ����
		ATTR_DMG_ADD			= 15,			// �����˺�
		ATTR_DMG_RDC			= 16,			// �����˺�
		ATTR_DMG_ADD_PEC		= 17,			// �˺��ӳɣ�%��
		ATTR_DMG_RDC_PEC		= 18,			// �˺����⣨%��
		ATTR_MOVE_SPEED			= 19,			// �ƶ��ٶ�
		ATTR_BATTLE				= 20,			// ս����
		ATTR_LUCKY				= 21,			// ����ֵ
//		ATTR_EXP
		MAX_INDEX,
	} Index_T;

	CObjAttrs()
	{
		CleanUp();
	}; 

	~CObjAttrs()
	{

	};

	void CleanUp(void)
	{
		bzero( m_vAttr, sizeof( m_vAttr ) );
	};

	int32_t GetAttr( Index_T const nIdx ) const 
	{
		if ( nIdx >= MAX_INDEX )
		{
			return 0;
		}
		return m_vAttr[nIdx];
	}

	void SetAttr( Index_T const nIdx, int32_t const nValue )
	{
		if ( nIdx >= MAX_INDEX )
		{
			return;
		}
		m_vAttr[nIdx] = nValue;
	};
private:
	int32_t	m_vAttr[MAX_INDEX];
};


//BOOL����
class CObjState
{
public:
	typedef enum
	{
		OBS_INVALID			= -1,
		OBS_YUNXUAN			= 0,			// ��ѣ
		OBS_MABI			= 1,			// ���
		OBS_SLOW			= 2,			// ����
		OBS_BINGDONG		= 3,			// ����
		OBS_WUDI			= 4,			// �޵�
		OBS_FREEDOM			= 5,			// ����
		OBS_MIANYI			= 6,			// ����
		OBS_CHENMO			= 7,			// ��Ĭ
		OBS_DIVIDE			= 8,			// �˺�ƽ�ָ�����״̬
		MAX_INDEX,
	} Index_T;

	CObjState()
	{
		CleanUp();
	}; 

	~CObjState()
	{

	};

	void CleanUp(void)
	{
		bzero( m_vState, sizeof( m_vState ) );
	};

	bool GetState( Index_T const nIdx ) const 
	{
		if ( nIdx >= MAX_INDEX )
		{
			return false;
		}
		return m_vState[nIdx] > 0;
	}

	void AddState( Index_T const nIdx )
	{
		if ( nIdx >= MAX_INDEX )
		{
			return;
		}
		++m_vState[nIdx];
	};

	void RemoveState( Index_T const nIdx )
	{
		if ( nIdx >= MAX_INDEX )
		{
			return;
		}
		--m_vState[nIdx];
	};
private:
	int8_t	m_vState[MAX_INDEX];
};


#endif	// __TPOC_ATTRIBUTE__
