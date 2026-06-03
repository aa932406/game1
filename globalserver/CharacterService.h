#pragma once

#include "CharacterUser.h"

#include <vector>

struct Position 
{
	explicit Position(int32_t x_ = 0, int32_t y_ = 0)
		: x(x_), y(y_)
	{

	}

	int32_t x;
	int32_t y;
};
typedef std::vector<Position> PositionVector;

struct CfgMapRegion 
{
	int32_t id;
	int32_t mapid;
	int32_t min_x;
	int32_t min_y;
	int32_t max_x;
	int32_t max_y;
	int32_t type;
};

struct AttrAddon
{
	int32_t index;
	int32_t addon;
};
typedef std::vector<AttrAddon> AttrAddonVector;

struct CfgBornAttr
{
	int32_t job;
	AttrAddonVector  attr;
};
typedef std::vector<CfgBornAttr>CfgBornAttrVector;
typedef std::map<int32_t,CfgBornAttr>CfgBornAttrTable;

class CharacterService
	: public Answer::TcpService
{
public:
	CharacterService();
	virtual ~CharacterService();

protected:
	virtual void onNetPacket(Answer::NetPacket *inPacket);

public:
	bool init(int32_t version);

private:
	void onAddUser(Answer::NetPacket *inPacket);
	void onRemoveUser(Answer::NetPacket *inPacket);

	void onGetCharacter(int16_t cgindex, Answer::NetPacket *inPacket);
	void onNewCharacter(int16_t cgindex, Answer::NetPacket *inPacket);
	//void onDelCharacter(int16_t cgindex, Answer::NetPacket *inPacket);

	void sendCharacterList(int16_t cgindex);
	void loadCharacterList(int16_t cgindex, int32_t uid, int32_t sid);

	//void sendDeleteCharacter( CharId_t cid, FamilyId_t family_id);

private:
	Position getRandomPositionInRegion(const CfgMapRegion &region);
	AttrAddonVector parseAttrEffect(int32_t id, const std::string &str);
	int32_t xAddHalfY(int32_t x, int32_t y);
	int32_t xSubHalfY(int32_t x, int32_t y);
	//int32_t calcBornAttr(int32_t job,SecondAttr &attr);
	CharId_t	GetNewCharId( int32_t nServerId );

private:
	CfgMapRegion m_bornRegion;
	int32_t m_version;
	CfgBornAttrTable  m_bornAttr;
	std::map<int8_t,int32_t> m_SkillDefault;
	User m_users[MAX_CONNECTION];
};
#define CHARACTER_SERVICE Answer::Singleton<CharacterService>::instance()

