#ifndef __TPOC_ATTRIBUTE__
#define __TPOC_ATTRIBUTE__
#define ATTR_CUR_HP		31		//技能buff中使用
//INT属性
class CObjAttrs
{
public:
	typedef enum
	{
		ATTR_INVALID			= -1,
		ATTR_HP					= 1,			// 生命值
		ATTR_MP					= 2,			// 法力值
		ATTR_PP					= 3,			// 体力值
		ATTR_XP					= 4,			// XP值
		ATTR_PHY_ATK_MIN		= 5,			// 最小物理攻击
		ATTR_PHY_ATK_MAX		= 6,			// 最大物理攻击
		ATTR_MAG_ATK_MIN		= 7,			// 最小魔法攻击
		ATTR_MAG_ATK_MAX		= 8,			// 最大魔法攻击
		ATTR_PHY_DEF			= 9,			// 物理防御
		ATTR_MAG_DEF			= 10,			// 魔法防御
		ATTR_HITRATE			= 11,			// 命中
		ATTR_DODGE				= 12,			// 闪避
		ATTR_CRITRATE			= 13,			// 暴击
		ATTR_TENACITY			= 14,			// 韧性
		ATTR_DMG_ADD			= 15,			// 额外伤害
		ATTR_DMG_RDC			= 16,			// 忽视伤害
		ATTR_DMG_ADD_PEC		= 17,			// 伤害加成（%）
		ATTR_DMG_RDC_PEC		= 18,			// 伤害减免（%）
		ATTR_MOVE_SPEED			= 19,			// 移动速度
		ATTR_BATTLE				= 20,			// 战斗力
		ATTR_LUCKY				= 21,			// 幸运值
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


//BOOL属性
class CObjState
{
public:
	typedef enum
	{
		OBS_INVALID			= -1,
		OBS_YUNXUAN			= 0,			// 晕眩
		OBS_MABI			= 1,			// 麻痹
		OBS_SLOW			= 2,			// 减速
		OBS_BINGDONG		= 3,			// 冰冻
		OBS_WUDI			= 4,			// 无敌
		OBS_FREEDOM			= 5,			// 自由
		OBS_MIANYI			= 6,			// 免疫
		OBS_CHENMO			= 7,			// 沉默
		OBS_DIVIDE			= 8,			// 伤害平分给宠物状态
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
