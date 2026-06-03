#pragma once

#include "DataStruct.h"
#include <map>
#include <vector>

struct CfgTask;
class Player;

enum EspeciallyTaskID
{

};

class ChrTask
{
public:
	ChrTask();
	~ChrTask();

public:
	void init(Player *player, const MemChrTaskVector &tasks);
	void reset();

	int32_t receive(int32_t tid , int8_t TaskType );
	int32_t submit(int32_t tid);
	int32_t giveUp(int32_t tid);
	int32_t quickDone(int32_t tid);
	int32_t GetTypeTask( int8_t Type );
	int8_t  GetTaskType( int32_t TaskId );
	void checkTaskCanSubmit(int32_t dungenID);
	bool receivePreCheck(int32_t tid, const CfgTask &cfgTask);
	bool submitPreCheck(int32_t tid,  const CfgTask &cfgTask);

	void updateTaskUseItem( int32_t id ,int32_t Count);
	void updateTaskTypeCount( int32_t taskType );
	void updateTaskMonster(int32_t mid, int32_t level);
	void updateTaskCount( int32_t Condition );
	void updateTaskSkill(int32_t skillID);
	void updateTaskDrop(int32_t tid, int32_t itemid);

	void cmdResetTrunkTask(int32_t trunkTaskId);
	bool isDoingTaskType(int32_t type);
	void setTaskCanSubmit(int32_t tid);

	void sendTaskList();
	void sendTaskKilledMonster();

	void saveToDB(Answer::NetPacket *packet);
	void SaveDBData( PlayerDBData& dbData );

	bool ForceSubmit( int32_t tid );

private:
	bool	CheckTaskCondition( int32_t taskCondition );
	int32_t getMonster(int32_t tid);

	void	sendTaskReceived(int32_t tid);
	void	sendTaskSubmitted(int32_t tid, int32_t exp);
	void	sendTaskGiveUped(int32_t tid);
	TaskRequest GetTaskCfgRequest( int32_t Tid );

private:
	Player *m_player;

	typedef std::map<int32_t, MemChrTask> Int32MemChrTaskMap;
	Int32MemChrTaskMap m_tasks;
	int32_t m_trunkTaskId;

	typedef std::vector<TaskMonster> TaskMonsterVector;
	TaskMonsterVector m_taskMonsters;

};

