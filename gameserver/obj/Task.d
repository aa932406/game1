obj/Task.o: Task.cpp stdafx.h ../libanswer/include/libanswer.h \
 ../libanswer/include/stdafx.h ../libanswer/include/Application.h \
 ../libanswer/include/Logger.h ../libanswer/include/ArrayList.h \
 ../libanswer/include/SpinLock.h ../libanswer/include/SafeQueue.h \
 ../libanswer/include/Mutex.h ../libanswer/include/Condition.h \
 ../libanswer/include/Database.h /usr/include/mysql/mysql.h \
 /usr/include/mysql/mysql_version.h /usr/include/mysql/mysql_com.h \
 /usr/include/mysql/mysql_time.h /usr/include/mysql/my_list.h \
 /usr/include/mysql/typelib.h /usr/include/mysql/my_alloc.h \
 ../libanswer/include/DayTime.h ../libanswer/include/DBCFile.h \
 ../libanswer/include/DBPool.h ../libanswer/include/BlockingQueue.h \
 ../libanswer/include/InetAddress.h ../libanswer/include/Inifile.h \
 ../libanswer/include/MD5.h ../libanswer/include/NetPacket.h \
 ../libanswer/include/NetPacketPool.h ../libanswer/include/ObjectPool.h \
 ../libanswer/include/Random.h ../libanswer/include/RwLock.h \
 ../libanswer/include/Singleton.h ../libanswer/include/StringUtility.h \
 ../libanswer/include/TcpConnection.h ../libanswer/include/TcpServer.h \
 ../libanswer/include/TcpService.h ../libanswer/include/TcpClient.h \
 ../libanswer/include/Thread.h ../libanswer/include/Zip.h \
 ../share/Shared.h ../share/Attribute.h ../share/PDUDefine.h \
 ../share/Type.h DataStructs.h CfgData.h actStructs.h DBService.h \
 ../share/DataStruct.h GameService.h Player.h Bag.h ExtSystemBase.h \
 ExtSystemInterface.h Task.h TaskCycle.h Achievement.h Unit.h Buff.h \
 Entity.h ../share/Attribute.h Dungeon.h Map.h Tile.h DropItem.h ObjPet.h \
 Pet.h MapEvent.h MonsterBuff.h ExtSystemMgr.h OperateLimit.h Equip.h \
 FightChecker.h Currency.h CharTeam.h KillMonsterTongJi.h ChrDepot.h \
 CharPet.h PetEgg.h CharSkill.h Skill.h SkillBuff.h CharFamily.h \
 CharTeamDungeon.h CharInsidePet.h CharWorship.h CharAuction.h CharSoul.h \
 CharHallOfFame.h Trade.h PlayerMail.h FriendExpReward.h FaBao.h \
 Fighting.h JueWei.h ShangCheng.h ChouJiang.h QiFu.h DailyActivity.h \
 Vip.h ScoreShop.h FunctionOpen.h ExpBall.h YunYingHD.h TouZi.h \
 HuoYueDu.h GuanWei.h WarVictory.h User.h MapManager.h MapRunner.h
	g++ -c -g -O2 -Wall -I../share -I../libanswer/include -I/usr/include/mysql -DLIBANSWER_LINUX Task.cpp -o obj/Task.o
