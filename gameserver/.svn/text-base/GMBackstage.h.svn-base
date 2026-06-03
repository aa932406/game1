//////////////////////////////////////////////////////////////////////////
// 后台支持
//////////////////////////////////////////////////////////////////////////

#ifndef __TPOC_GM_BACKSTAGE_H__
#define __TPOC_GM_BACKSTAGE_H__

class CGMBackstate
{
public:
	CGMBackstate();
	virtual ~CGMBackstate();

public:
	void Init();
	void OnUpdate();

	int32_t GetBanChatLeftTime( CharId_t cid );
	int32_t GetSealLeftTime( CharId_t cid );

public:
	void onUpdateGMBroadcast( Answer::NetPacket *inPacket );		// 公告
	void onUpdateGMBanChat( Answer::NetPacket *inPacket );			// 禁言
	void onUpdateGMSeal( Answer::NetPacket *inPacket );				// 封号

private:
	void initBroadcast();
	void initBanChat();
	void checkBroadcast();
	void sendGMBroadcast( const std::string& text, int8_t type );

private:
	GMBroadcastMap	m_mBroadcasts;
	GMBanChatMap	m_mBanChat;
	GMSealMap		m_mSeal;

	Answer::Mutex	m_mutex;
	int64_t			m_nLastTick;
};
#define GM_BACKSTAGE Answer::Singleton<CGMBackstate>::instance()

#endif	//__TPOC_ACTIVITY_MANAGER_H__
