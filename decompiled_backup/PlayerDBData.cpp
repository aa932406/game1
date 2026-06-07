// Decompiled methods for class: PlayerDBData
// Source: gameserver.cc
// Total methods: 6

#####################################
void __cdecl PlayerDBData::~PlayerDBData(PlayerDBData *const this)
{
  PlayerDBData::~PlayerDBData(this);
  operator delete(this);
}


#####################################
void __cdecl PlayerDBData::CleanUp(PlayerDBData *const this)
{
  this->connid = 0;
  this->cgindex = 0;
  this->loadTime = 0;
  this->saveRefCount = 0;
  MemCharacterData::CleanUp(&this->chr);
  MemAttrData::CleanUp(&this->attrData);
  SysUserData::CleanUp(&this->sysUser);
  DailyActivityData::CleanUp(&this->signInfo);
  MemChrEquipData::CleanUp(&this->equipData);
  MemChrGemData::CleanUp(&this->gemData);
  MemChrBagData::CleanUp(&this->bagData);
  MemChrSkillData::CleanUp(&this->skillData);
  MemChrTaskData::CleanUp(&this->taskData);
  MemChrTaskCycleData::CleanUp(&this->taskCycleData);
  MemChrActionData::CleanUp(&this->actionData);
  MemChrAutoFightData::CleanUp(&this->autoFight);
  MemChrSystemSettingData::CleanUp(&this->systemSetting);
  MemChrBuffData::CleanUp(&this->buffData);
  MemChrDepotData::CleanUp(&this->gambleDepot);
  SysUserPreventWallowData::CleanUp(&this->sysUserPreventWallow);
  CurrencyDBData::CleanUp(&this->m_CurrencyData);
  OperateLimitDBData::CleanUp(&this->m_OperateLimit);
  PetDBData::CleanUp(&this->m_CharPets);
  FriendExpReward::CleanUp(&this->m_FriendExpReward);
  MailDBData::CleanUp(&this->m_MailDBData);
  ShangChengData::CleanUp(&this->m_ShangChengData);
  BossKilledRewardData::CleanUp(&this->m_BossKilledReward);
  CFaBaoData::CleanUp(&this->m_FaBaoData);
  CGoblinData::CleanUp(&this->m_CGoblinData);
  CharFamilyDBData::CleanUp(&this->m_FamilyData);
  WorshipDBData::CleanUp(&this->m_WorshipData);
  CJueWeiData::CleanUp(&this->m_JueWeiData);
  ScoreShopData::CleanUp(&this->m_ScoreShopData);
  TouZiData::CleanUp(&this->m_TouZiData);
  CHuoYueDuData::CleanUp(&this->m_HuoYueDuData);
  MysteryShopDBData::CleanUp(&this->m_MysteryShopDBData);
  ExchangeDBData::CleanUp(&this->m_ExchangeDBData);
  CharWishDBData::CleanUp(&this->m_WishDBData);
  CVplanData::CleanUp(&this->m_VplanData);
  CharWingDBData::CleanUp(&this->m_CharWingDBData);
  MagicBoxDBData::CleanUp(&this->m_MagicBoxDBData);
  VipData::CleanUp(&this->m_vipData);
  CShiZhuangData::CleanUp(&this->m_ShiZhuangData);
  CMonthlyChouJiangData::CleanUp(&this->m_CMonthlyChouJiangData);
  ChouJiangData::CleanUp(&this->m_ChouJinagData);
  MoneyRewardTaskData::CleanUp(&this->m_MoneyRewardTaskData);
  WuHunShopDBData::CleanUp(&this->m_WuHunShopDBData);
  CMingGeData::CleanUp(&this->m_CMingGeData);
  CKunData::CleanUp(&this->m_CKunData);
  CFlopDraw::CleanUp(&this->m_CFlopDraw);
  CSevenDayData::CleanUp(&this->m_CSevenDayData);
  PortalDBData::CleanUp(&this->m_PortalDBData);
  XinMoDBData::CleanUp(&this->m_XinMoDBData);
  CLittleHelperData::CleanUp(&this->m_CLittleHelper);
  NationalDayData::CleanUp(&this->m_NationalDayData);
  EquipRongHeData::CleanUp(&this->m_EquipRongHeData);
}


#####################################
void __cdecl PlayerDBData::SaveToSqlString(
        PlayerDBData *const this,
        SqlStringList *const sqls,
        char (*const szSQL)[4096],
        CharId_t nCid)
{
  MemCharacterData::SaveToSqlString(&this->chr, sqls, szSQL, nCid);
  MemAttrData::SaveToSqlString(&this->attrData, sqls, szSQL, nCid);
  SysUserData::SaveToSqlString(&this->sysUser, sqls, szSQL, nCid);
  SysUserPreventWallowData::SaveToSqlString(&this->sysUserPreventWallow, sqls, szSQL, nCid);
  DailyActivityData::SaveToSqlString(&this->signInfo, sqls, szSQL, nCid);
  MemChrEquipData::SaveToSqlString(&this->equipData, sqls, szSQL, nCid);
  MemChrGemData::SaveToSqlString(&this->gemData, sqls, szSQL, nCid);
  MemChrBagData::SaveToSqlString(&this->bagData, sqls, szSQL, nCid);
  MemChrDepotData::SaveToSqlString(&this->gambleDepot, sqls, szSQL, nCid);
  MemChrSkillData::SaveToSqlString(&this->skillData, sqls, szSQL, nCid);
  MemChrTaskData::SaveToSqlString(&this->taskData, sqls, szSQL, nCid);
  MemChrTaskCycleData::SaveToSqlString(&this->taskCycleData, sqls, szSQL, nCid);
  MemChrActionData::SaveToSqlString(&this->actionData, sqls, szSQL, nCid);
  MemChrAutoFightData::SaveToSqlString(&this->autoFight, sqls, szSQL, nCid);
  MemChrSystemSettingData::SaveToSqlString(&this->systemSetting, sqls, szSQL, nCid);
  MemChrBuffData::SaveToSqlString(&this->buffData, sqls, szSQL, nCid);
  CurrencyDBData::SaveToSqlString(&this->m_CurrencyData, sqls, szSQL, nCid);
  OperateLimitDBData::SaveToSqlString(&this->m_OperateLimit, sqls, szSQL, nCid);
  PetDBData::SaveToSqlString(&this->m_CharPets, sqls, szSQL, nCid);
  FriendExpReward::SaveToSqlString(&this->m_FriendExpReward, sqls, szSQL, nCid);
  MailDBData::SaveToSqlString(&this->m_MailDBData, sqls, szSQL, nCid);
  ShangChengData::SaveToSqlString(&this->m_ShangChengData, sqls, szSQL, nCid);
  BossKilledRewardData::SaveToSqlString(&this->m_BossKilledReward, sqls, szSQL, nCid);
  CFaBaoData::SaveToSqlString(&this->m_FaBaoData, sqls, szSQL, nCid);
  CGoblinData::SaveToSqlString(&this->m_CGoblinData, sqls, szSQL, nCid);
  CharFamilyDBData::SaveToSqlString(&this->m_FamilyData, sqls, szSQL, nCid);
  WorshipDBData::SaveToSqlString(&this->m_WorshipData, sqls, szSQL, nCid);
  CJueWeiData::SaveToSqlString(&this->m_JueWeiData, sqls, szSQL, nCid);
  ScoreShopData::SaveToSqlString(&this->m_ScoreShopData, sqls, szSQL, nCid);
  TouZiData::SaveToSqlString(&this->m_TouZiData, sqls, szSQL, nCid);
  CHuoYueDuData::SaveToSqlString(&this->m_HuoYueDuData, sqls, szSQL, nCid);
  MysteryShopDBData::SaveToSqlString(&this->m_MysteryShopDBData, sqls, szSQL, nCid);
  ExchangeDBData::SaveToSqlString(&this->m_ExchangeDBData, sqls, szSQL, nCid);
  CharWishDBData::SaveToSqlString(&this->m_WishDBData, sqls, szSQL, nCid);
  CharWingDBData::SaveToSqlString(&this->m_CharWingDBData, sqls, szSQL, nCid);
  MagicBoxDBData::SaveToSqlString(&this->m_MagicBoxDBData, sqls, szSQL, nCid);
  VipData::SaveToSqlString(&this->m_vipData, sqls, szSQL, nCid);
  CShiZhuangData::SaveToSqlString(&this->m_ShiZhuangData, sqls, szSQL, nCid);
  CMonthlyChouJiangData::SaveToSqlString(&this->m_CMonthlyChouJiangData, sqls, szSQL, nCid);
  ChouJiangData::SaveToSqlString(&this->m_ChouJinagData, sqls, szSQL, nCid);
  MoneyRewardTaskData::SaveToSqlString(&this->m_MoneyRewardTaskData, sqls, szSQL, nCid);
  WuHunShopDBData::SaveToSqlString(&this->m_WuHunShopDBData, sqls, szSQL, nCid);
  CMingGeData::SaveToSqlString(&this->m_CMingGeData, sqls, szSQL, nCid);
  CKunData::SaveToSqlString(&this->m_CKunData, sqls, szSQL, nCid);
  CFlopDraw::SaveToSqlString(&this->m_CFlopDraw, sqls, szSQL, nCid);
  CSevenDayData::SaveToSqlString(&this->m_CSevenDayData, sqls, szSQL, nCid);
  PortalDBData::SaveToSqlString(&this->m_PortalDBData, sqls, szSQL, nCid);
  XinMoDBData::SaveToSqlString(&this->m_XinMoDBData, sqls, szSQL, nCid);
  CLittleHelperData::SaveToSqlString(&this->m_CLittleHelper, sqls, szSQL, nCid);
  NationalDayData::SaveToSqlString(&this->m_NationalDayData, sqls, szSQL, nCid);
  EquipRongHeData::SaveToSqlString(&this->m_EquipRongHeData, sqls, szSQL, nCid);
}


#####################################
bool __cdecl PlayerDBData::LoadFromDB(
        PlayerDBData *const this,
        Answer::MySqlDBGuard *const db,
        char (*const szSQL)[4096],
        int64_t nUid,
        int32_t nSid,
        CharId_t nCid)
{
  CharId_t nCida; // [rsp+0h] [rbp-40h]

  this->loadTime = Answer::DayTime::now();
  if ( !MemCharacterData::LoadFromDB(&this->chr, db, szSQL, nUid, nSid, 0) )
    return 0;
  nCida = this->chr.data.cid;
  if ( SysUserData::LoadFromDB(&this->sysUser, db, szSQL, nUid, nSid, 0) )
    SysUserPreventWallowData::LoadFromDB(&this->sysUserPreventWallow, db, szSQL, nUid, nSid, 0);
  MemChrDepotData::LoadFromDB(&this->gambleDepot, db, szSQL, nUid, nSid, nCida);
  DailyActivityData::LoadFromDB(&this->signInfo, db, szSQL, nUid, nSid, nCida);
  MemChrEquipData::LoadFromDB(&this->equipData, db, szSQL, nUid, nSid, nCida);
  MemChrGemData::LoadFromDB(&this->gemData, db, szSQL, nUid, nSid, nCida);
  MemChrBagData::LoadFromDB(&this->bagData, db, szSQL, nUid, nSid, nCida);
  MemChrSkillData::LoadFromDB(&this->skillData, db, szSQL, nUid, nSid, nCida);
  MemChrTaskData::LoadFromDB(&this->taskData, db, szSQL, nUid, nSid, nCida);
  MemChrTaskCycleData::LoadFromDB(&this->taskCycleData, db, szSQL, nUid, nSid, nCida);
  MemChrActionData::LoadFromDB(&this->actionData, db, szSQL, nUid, nSid, nCida);
  MemChrAutoFightData::LoadFromDB(&this->autoFight, db, szSQL, nUid, nSid, nCida);
  MemChrSystemSettingData::LoadFromDB(&this->systemSetting, db, szSQL, nUid, nSid, nCida);
  MemChrBuffData::LoadFromDB(&this->buffData, db, szSQL, nUid, nSid, nCida);
  CurrencyDBData::LoadFromDB(&this->m_CurrencyData, db, szSQL, nUid, nSid, nCida);
  OperateLimitDBData::LoadFromDB(&this->m_OperateLimit, db, szSQL, nUid, nSid, nCida);
  PetDBData::LoadFromDB(&this->m_CharPets, db, szSQL, nUid, nSid, nCida);
  FriendExpReward::LoadFromDB(&this->m_FriendExpReward, db, szSQL, nUid, nSid, nCida);
  MailDBData::LoadFromDB(&this->m_MailDBData, db, szSQL, nUid, nSid, nCida);
  ShangChengData::LoadFromDB(&this->m_ShangChengData, db, szSQL, nUid, nSid, nCida);
  BossKilledRewardData::LoadFromDB(&this->m_BossKilledReward, db, szSQL, nUid, nSid, nCida);
  CFaBaoData::LoadFromDB(&this->m_FaBaoData, db, szSQL, nUid, nSid, nCida);
  CGoblinData::LoadFromDB(&this->m_CGoblinData, db, szSQL, nUid, nSid, nCida);
  CharFamilyDBData::LoadFromDB(&this->m_FamilyData, db, szSQL, nUid, nSid, nCida);
  WorshipDBData::LoadFromDB(&this->m_WorshipData, db, szSQL, nUid, nSid, nCida);
  CJueWeiData::LoadFromDB(&this->m_JueWeiData, db, szSQL, nUid, nSid, nCida);
  ScoreShopData::LoadFromDB(&this->m_ScoreShopData, db, szSQL, nUid, nSid, nCida);
  TouZiData::LoadFromDB(&this->m_TouZiData, db, szSQL, nUid, nSid, nCida);
  CHuoYueDuData::LoadFromDB(&this->m_HuoYueDuData, db, szSQL, nUid, nSid, nCida);
  MysteryShopDBData::LoadFromDB(&this->m_MysteryShopDBData, db, szSQL, nUid, nSid, nCida);
  ExchangeDBData::LoadFromDB(&this->m_ExchangeDBData, db, szSQL, nUid, nSid, nCida);
  CharWishDBData::LoadFromDB(&this->m_WishDBData, db, szSQL, nUid, nSid, nCida);
  CVplanData::LoadFromDB(&this->m_VplanData, db, szSQL, nUid, nSid, nCida);
  CharWingDBData::LoadFromDB(&this->m_CharWingDBData, db, szSQL, nUid, nSid, nCida);
  MagicBoxDBData::LoadFromDB(&this->m_MagicBoxDBData, db, szSQL, nUid, nSid, nCida);
  VipData::LoadFromDB(&this->m_vipData, db, szSQL, nUid, nSid, nCida);
  CShiZhuangData::LoadFromDB(&this->m_ShiZhuangData, db, szSQL, nUid, nSid, nCida);
  CMonthlyChouJiangData::LoadFromDB(&this->m_CMonthlyChouJiangData, db, szSQL, nUid, nSid, nCida);
  ChouJiangData::LoadFromDB(&this->m_ChouJinagData, db, szSQL, nUid, nSid, nCida);
  MoneyRewardTaskData::LoadFromDB(&this->m_MoneyRewardTaskData, db, szSQL, nUid, nSid, nCida);
  WuHunShopDBData::LoadFromDB(&this->m_WuHunShopDBData, db, szSQL, nUid, nSid, nCida);
  CMingGeData::LoadFromDB(&this->m_CMingGeData, db, szSQL, nUid, nSid, nCida);
  CKunData::LoadFromDB(&this->m_CKunData, db, szSQL, nUid, nSid, nCida);
  CFlopDraw::LoadFromDB(&this->m_CFlopDraw, db, szSQL, nUid, nSid, nCida);
  CSevenDayData::LoadFromDB(&this->m_CSevenDayData, db, szSQL, nUid, nSid, nCida);
  PortalDBData::LoadFromDB(&this->m_PortalDBData, db, szSQL, nUid, nSid, nCida);
  XinMoDBData::LoadFromDB(&this->m_XinMoDBData, db, szSQL, nUid, nSid, nCida);
  CLittleHelperData::LoadFromDB(&this->m_CLittleHelper, db, szSQL, nUid, nSid, nCida);
  NationalDayData::LoadFromDB(&this->m_NationalDayData, db, szSQL, nUid, nSid, nCida);
  EquipRongHeData::LoadFromDB(&this->m_EquipRongHeData, db, szSQL, nUid, nSid, nCida);
  return 1;
}


#####################################
void __cdecl PlayerDBData::PackageData(PlayerDBData *const this, Answer::NetPacket *packet)
{
  Answer::NetPacket::writeInt8(packet, this->connid);
  Answer::NetPacket::writeInt16(packet, this->cgindex);
  Answer::NetPacket::writeInt32(packet, this->loadTime);
  MemCharacterData::PackageData(&this->chr, packet);
  MemAttrData::PackageData(&this->attrData, packet);
  MemChrDepotData::PackageData(&this->gambleDepot, packet);
  SysUserData::PackageData(&this->sysUser, packet);
  SysUserPreventWallowData::PackageData(&this->sysUserPreventWallow, packet);
  DailyActivityData::PackageData(&this->signInfo, packet);
  MemChrEquipData::PackageData(&this->equipData, packet);
  MemChrGemData::PackageData(&this->gemData, packet);
  MemChrBagData::PackageData(&this->bagData, packet);
  MemChrSkillData::PackageData(&this->skillData, packet);
  MemChrTaskData::PackageData(&this->taskData, packet);
  MemChrTaskCycleData::PackageData(&this->taskCycleData, packet);
  MemChrActionData::PackageData(&this->actionData, packet);
  MemChrAutoFightData::PackageData(&this->autoFight, packet);
  MemChrSystemSettingData::PackageData(&this->systemSetting, packet);
  MemChrBuffData::PackageData(&this->buffData, packet);
  CurrencyDBData::PackageData(&this->m_CurrencyData, packet);
  OperateLimitDBData::PackageData(&this->m_OperateLimit, packet);
  PetDBData::PackageData(&this->m_CharPets, packet);
  FriendExpReward::PackageData(&this->m_FriendExpReward, packet);
  MailDBData::PackageData(&this->m_MailDBData, packet);
  ShangChengData::PackageData(&this->m_ShangChengData, packet);
  BossKilledRewardData::PackageData(&this->m_BossKilledReward, packet);
  CFaBaoData::PackageData(&this->m_FaBaoData, packet);
  CGoblinData::PackageData(&this->m_CGoblinData, packet);
  CharFamilyDBData::PackageData(&this->m_FamilyData, packet);
  WorshipDBData::PackageData(&this->m_WorshipData, packet);
  CJueWeiData::PackageData(&this->m_JueWeiData, packet);
  ScoreShopData::PackageData(&this->m_ScoreShopData, packet);
  TouZiData::PackageData(&this->m_TouZiData, packet);
  CHuoYueDuData::PackageData(&this->m_HuoYueDuData, packet);
  MysteryShopDBData::PackageData(&this->m_MysteryShopDBData, packet);
  ExchangeDBData::PackageData(&this->m_ExchangeDBData, packet);
  CharWishDBData::PackageData(&this->m_WishDBData, packet);
  CVplanData::PackageData(&this->m_VplanData, packet);
  CharWingDBData::PackageData(&this->m_CharWingDBData, packet);
  MagicBoxDBData::PackageData(&this->m_MagicBoxDBData, packet);
  VipData::PackageData(&this->m_vipData, packet);
  CShiZhuangData::PackageData(&this->m_ShiZhuangData, packet);
  CMonthlyChouJiangData::PackageData(&this->m_CMonthlyChouJiangData, packet);
  ChouJiangData::PackageData(&this->m_ChouJinagData, packet);
  MoneyRewardTaskData::PackageData(&this->m_MoneyRewardTaskData, packet);
  WuHunShopDBData::PackageData(&this->m_WuHunShopDBData, packet);
  CMingGeData::PackageData(&this->m_CMingGeData, packet);
  CKunData::PackageData(&this->m_CKunData, packet);
  CFlopDraw::PackageData(&this->m_CFlopDraw, packet);
  CSevenDayData::PackageData(&this->m_CSevenDayData, packet);
  PortalDBData::PackageData(&this->m_PortalDBData, packet);
  XinMoDBData::PackageData(&this->m_XinMoDBData, packet);
  CLittleHelperData::PackageData(&this->m_CLittleHelper, packet);
  NationalDayData::PackageData(&this->m_NationalDayData, packet);
  EquipRongHeData::PackageData(&this->m_EquipRongHeData, packet);
}


#####################################
void __cdecl PlayerDBData::UnPackageData(PlayerDBData *const this, Answer::NetPacket *inPacket, CharId_t nCid)
{
  CharId_t nCida; // [rsp+8h] [rbp-18h]

  this->connid = Answer::NetPacket::readInt8(inPacket);
  this->cgindex = Answer::NetPacket::readInt16(inPacket);
  this->loadTime = Answer::NetPacket::readInt32(inPacket);
  MemCharacterData::UnPackageData(&this->chr, inPacket, 0);
  nCida = this->chr.data.cid;
  MemAttrData::UnPackageData(&this->attrData, inPacket, nCida);
  MemChrDepotData::UnPackageData(&this->gambleDepot, inPacket, nCida);
  SysUserData::UnPackageData(&this->sysUser, inPacket, nCida);
  SysUserPreventWallowData::UnPackageData(&this->sysUserPreventWallow, inPacket, nCida);
  DailyActivityData::UnPackageData(&this->signInfo, inPacket, nCida);
  MemChrEquipData::UnPackageData(&this->equipData, inPacket, nCida);
  MemChrGemData::UnPackageData(&this->gemData, inPacket, nCida);
  MemChrBagData::UnPackageData(&this->bagData, inPacket, nCida);
  MemChrSkillData::UnPackageData(&this->skillData, inPacket, nCida);
  MemChrTaskData::UnPackageData(&this->taskData, inPacket, nCida);
  MemChrTaskCycleData::UnPackageData(&this->taskCycleData, inPacket, nCida);
  MemChrActionData::UnPackageData(&this->actionData, inPacket, nCida);
  MemChrAutoFightData::UnPackageData(&this->autoFight, inPacket, nCida);
  MemChrSystemSettingData::UnPackageData(&this->systemSetting, inPacket, nCida);
  MemChrBuffData::UnPackageData(&this->buffData, inPacket, nCida);
  CurrencyDBData::UnPackageData(&this->m_CurrencyData, inPacket, nCida);
  OperateLimitDBData::UnPackageData(&this->m_OperateLimit, inPacket, nCida);
  PetDBData::UnPackageData(&this->m_CharPets, inPacket, nCida);
  FriendExpReward::UnPackageData(&this->m_FriendExpReward, inPacket, nCida);
  MailDBData::UnPackageData(&this->m_MailDBData, inPacket, nCida);
  ShangChengData::UnPackageData(&this->m_ShangChengData, inPacket, nCida);
  BossKilledRewardData::UnPackageData(&this->m_BossKilledReward, inPacket, nCida);
  CFaBaoData::UnPackageData(&this->m_FaBaoData, inPacket, nCida);
  CGoblinData::UnPackageData(&this->m_CGoblinData, inPacket, nCida);
  CharFamilyDBData::UnPackageData(&this->m_FamilyData, inPacket, nCida);
  WorshipDBData::UnPackageData(&this->m_WorshipData, inPacket, nCida);
  CJueWeiData::UnPackageData(&this->m_JueWeiData, inPacket, nCida);
  ScoreShopData::UnPackageData(&this->m_ScoreShopData, inPacket, nCida);
  TouZiData::UnPackageData(&this->m_TouZiData, inPacket, nCida);
  CHuoYueDuData::UnPackageData(&this->m_HuoYueDuData, inPacket, nCida);
  MysteryShopDBData::UnPackageData(&this->m_MysteryShopDBData, inPacket, nCida);
  ExchangeDBData::UnPackageData(&this->m_ExchangeDBData, inPacket, nCida);
  CharWishDBData::UnPackageData(&this->m_WishDBData, inPacket, nCida);
  CVplanData::UnPackageData(&this->m_VplanData, inPacket, nCida);
  CharWingDBData::UnPackageData(&this->m_CharWingDBData, inPacket, nCida);
  MagicBoxDBData::UnPackageData(&this->m_MagicBoxDBData, inPacket, nCida);
  VipData::UnPackageData(&this->m_vipData, inPacket, nCida);
  CShiZhuangData::UnPackageData(&this->m_ShiZhuangData, inPacket, nCida);
  CMonthlyChouJiangData::UnPackageData(&this->m_CMonthlyChouJiangData, inPacket, nCida);
  ChouJiangData::UnPackageData(&this->m_ChouJinagData, inPacket, nCida);
  MoneyRewardTaskData::UnPackageData(&this->m_MoneyRewardTaskData, inPacket, nCida);
  WuHunShopDBData::UnPackageData(&this->m_WuHunShopDBData, inPacket, nCida);
  CMingGeData::UnPackageData(&this->m_CMingGeData, inPacket, nCida);
  CKunData::UnPackageData(&this->m_CKunData, inPacket, nCida);
  CFlopDraw::UnPackageData(&this->m_CFlopDraw, inPacket, nCida);
  CSevenDayData::UnPackageData(&this->m_CSevenDayData, inPacket, nCida);
  PortalDBData::UnPackageData(&this->m_PortalDBData, inPacket, nCida);
  XinMoDBData::UnPackageData(&this->m_XinMoDBData, inPacket, nCida);
  CLittleHelperData::UnPackageData(&this->m_CLittleHelper, inPacket, nCida);
  NationalDayData::UnPackageData(&this->m_NationalDayData, inPacket, nCida);
  EquipRongHeData::UnPackageData(&this->m_EquipRongHeData, inPacket, nCida);
}


