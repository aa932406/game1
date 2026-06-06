#pragma once

#include "Entity.h"

class CDropItem
	: public Entity
{
public:
	CDropItem();
	virtual ~CDropItem();

public:
	void init(int32_t itemId, int8_t itemClass, int8_t bindType, int32_t itemCount, int32_t costType, int32_t costValue, CharId_t owner, Time_t endTime, int64_t srcId );
	void reset();

	int32_t getItemId() const;
	int8_t	getItemClass() const;
	int8_t	getBindType() const;
	int32_t getItemCount() const;
	int32_t getCostType() const;
	int32_t getCostValue() const;
	CharId_t getOwner() const;
	int32_t getItemEndTime() const;
	int64_t getItemSrcId() const;


private:
	int32_t m_itemId;
	int8_t	m_itemClass;
	int8_t	m_bindType;
	int32_t m_itemCount;
	Time_t	m_endTime;	
	int64_t	m_srcId;		
	CharId_t m_owner;

	int32_t m_costType;
	int32_t m_costValue;

};

class Map;
class CDropItemGroup
{
public:
	CDropItemGroup();
	~CDropItemGroup();

public:
	void init(Map *pMap, const Position &centerPos, Player *pOwner, int32_t droperType, int32_t droperMid, DropItem (&dropItems)[MAX_DROPITEM_SIZE], const std::string &dropper,int32_t broadcast, int32_t autoPick);
	void reset();
	void leaveMap();

	bool checkEnd();
	bool hasDropItem(EntityId_t dropid);
	int32_t getDropItem(EntityId_t dropid);
	int32_t pick(Player &player, EntityId_t dropid);

	void appendInfo(Answer::NetPacket *packet);
	int32_t getBroadCastItem();

	const Position& getCenterPos() const { return m_centerPos; }
	bool hasItems() const;
	EntityId_t getFirstDropItemId() const;

private:
	int16_t getDropItemCount();

	bool checkOwner(int32_t index, CharId_t cid);

	void broadcastRemoveDropItem(EntityId_t dropid);
	void broadcastRemoveFromMap();

private:
	Map *m_map;
	Position m_centerPos;
	int64_t m_freeTick;
	int64_t m_endTick;
	int32_t m_DropTime;
	CDropItem m_dropItems[MAX_DROPITEM_SIZE];

	int32_t m_broadcastItem;
	int32_t m_autoPick;
	std::string m_ownerName;
};

