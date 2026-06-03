/*
Navicat MySQL Data Transfer

Source Server         : localhost
Source Server Version : 50612
Source Host           : localhost:3306
Source Database       : liudao2

Target Server Type    : MYSQL
Target Server Version : 50612
File Encoding         : 65001

Date: 2015-08-28 22:38:21
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for `gmt_ban_chat`
-- ----------------------------
DROP TABLE IF EXISTS `gmt_ban_chat`;
CREATE TABLE `gmt_ban_chat` (
  `cid` bigint(20) NOT NULL DEFAULT '0' COMMENT '用户ID',
  `expire_time` int(11) NOT NULL DEFAULT '0' COMMENT '到期时间',
  `operator` varchar(20) NOT NULL,
  `reason` varchar(100) NOT NULL,
  `op_time` int(11) NOT NULL,
  `flag` tinyint(4) NOT NULL DEFAULT '0' COMMENT '标记',
  PRIMARY KEY (`cid`),
  KEY `cid` (`cid`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED;

-- ----------------------------
-- Records of gmt_ban_chat
-- ----------------------------

-- ----------------------------
-- Table structure for `gmt_broadcast`
-- ----------------------------
DROP TABLE IF EXISTS `gmt_broadcast`;
CREATE TABLE `gmt_broadcast` (
  `idx` int(11) NOT NULL AUTO_INCREMENT COMMENT '序列',
  `text` varchar(200) NOT NULL DEFAULT '' COMMENT '内容',
  `type` tinyint(4) NOT NULL DEFAULT '0' COMMENT '类型',
  `start_time` int(11) NOT NULL DEFAULT '0' COMMENT '发送时间',
  `interval` int(11) NOT NULL DEFAULT '0' COMMENT '时间（秒）',
  `times` int(11) NOT NULL DEFAULT '0' COMMENT '次数',
  `creater` varchar(20) NOT NULL DEFAULT '' COMMENT '创建者',
  `create_time` int(11) NOT NULL DEFAULT '0' COMMENT '创建时间',
  `flag` tinyint(4) NOT NULL DEFAULT '0' COMMENT '发送标记',
  PRIMARY KEY (`idx`),
  KEY `idx` (`idx`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED;

-- ----------------------------
-- Records of gmt_broadcast
-- ----------------------------

-- ----------------------------
-- Table structure for `gmt_seal`
-- ----------------------------
DROP TABLE IF EXISTS `gmt_seal`;
CREATE TABLE `gmt_seal` (
  `cid` bigint(20) NOT NULL DEFAULT '0' COMMENT '用户ID',
  `expire_time` int(11) NOT NULL DEFAULT '0' COMMENT '到期时间',
  `operator` varchar(20) NOT NULL,
  `reason` varchar(100) NOT NULL,
  `op_time` int(11) NOT NULL,
  `flag` tinyint(4) NOT NULL DEFAULT '0' COMMENT '标记',
  PRIMARY KEY (`cid`),
  KEY `cid` (`cid`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED;

-- ----------------------------
-- Records of gmt_seal
-- ----------------------------

-- ----------------------------
-- Table structure for `log_achievement`
-- ----------------------------
DROP TABLE IF EXISTS `log_achievement`;
CREATE TABLE `log_achievement` (
  `cid` bigint(20) NOT NULL DEFAULT '0',
  `name` char(8) NOT NULL DEFAULT '',
  `id` int(11) NOT NULL DEFAULT '0',
  `type` int(11) NOT NULL DEFAULT '0',
  `time` int(11) NOT NULL DEFAULT '0',
  KEY `cid` (`cid`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED;

-- ----------------------------
-- Records of log_achievement
-- ----------------------------

-- ----------------------------
-- Table structure for `log_activity`
-- ----------------------------
DROP TABLE IF EXISTS `log_activity`;
CREATE TABLE `log_activity` (
  `id` int(11) NOT NULL AUTO_INCREMENT COMMENT '序号',
  `cid` bigint(20) NOT NULL DEFAULT '0' COMMENT '玩家ID',
  `actid` int(11) NOT NULL DEFAULT '0' COMMENT '活动ID',
  `acttype` tinyint(4) NOT NULL DEFAULT '0' COMMENT '活动类型',
  `time` int(11) NOT NULL DEFAULT '0' COMMENT '参与时间',
  `param` bigint(20) NOT NULL DEFAULT '0' COMMENT '附加参数\r\n军团战 帮派ID\r\n答题 名次\r\nVIP挂机 地图ID',
  PRIMARY KEY (`id`),
  KEY `id` (`id`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED;

-- ----------------------------
-- Records of log_activity
-- ----------------------------

-- ----------------------------
-- Table structure for `log_boss`
-- ----------------------------
DROP TABLE IF EXISTS `log_boss`;
CREATE TABLE `log_boss` (
  `id` int(11) NOT NULL AUTO_INCREMENT COMMENT '自增长标记',
  `mid` int(11) NOT NULL DEFAULT '0' COMMENT '怪物表ID',
  `type` int(11) NOT NULL DEFAULT '0' COMMENT '类型',
  `killer` bigint(20) NOT NULL DEFAULT '0' COMMENT '击杀者',
  `time` int(11) NOT NULL DEFAULT '0' COMMENT '击杀时间',
  PRIMARY KEY (`id`),
  KEY `id` (`id`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED;

-- ----------------------------
-- Records of log_boss
-- ----------------------------

-- ----------------------------
-- Table structure for `log_civil_position_change`
-- ----------------------------
DROP TABLE IF EXISTS `log_civil_position_change`;
CREATE TABLE `log_civil_position_change` (
  `cid` bigint(20) NOT NULL DEFAULT '0',
  `name` char(20) NOT NULL DEFAULT '',
  `kcid` bigint(20) NOT NULL,
  `kname` char(20) NOT NULL,
  `kingdom` int(11) NOT NULL,
  `old_position` int(11) NOT NULL DEFAULT '0',
  `new_position` int(11) NOT NULL DEFAULT '0',
  `time` int(11) NOT NULL DEFAULT '0',
  KEY `cid` (`cid`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED;

-- ----------------------------
-- Records of log_civil_position_change
-- ----------------------------

-- ----------------------------
-- Table structure for `log_currency`
-- ----------------------------
DROP TABLE IF EXISTS `log_currency`;
CREATE TABLE `log_currency` (
  `id` int(11) NOT NULL AUTO_INCREMENT COMMENT '序列',
  `cid` bigint(20) NOT NULL DEFAULT '0' COMMENT '角色id',
  `name` char(12) NOT NULL DEFAULT '' COMMENT '角色名',
  `type` int(11) NOT NULL,
  `opway` int(11) NOT NULL DEFAULT '0' COMMENT '原因',
  `value` int(11) NOT NULL DEFAULT '0' COMMENT '变化值',
  `param` bigint(20) NOT NULL DEFAULT '0',
  `time` int(11) NOT NULL DEFAULT '0' COMMENT '时间',
  PRIMARY KEY (`id`),
  KEY `id` (`id`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED;

-- ----------------------------
-- Records of log_currency
-- ----------------------------

-- ----------------------------
-- Table structure for `log_cycle_task`
-- ----------------------------
DROP TABLE IF EXISTS `log_cycle_task`;
CREATE TABLE `log_cycle_task` (
  `cid` int(20) NOT NULL DEFAULT '0',
  `name` char(8) NOT NULL DEFAULT '',
  `taskID` int(11) NOT NULL DEFAULT '0',
  `task_name` char(8) NOT NULL DEFAULT '',
  `receive_time` int(11) NOT NULL DEFAULT '0',
  `submit_time` int(11) NOT NULL DEFAULT '0',
  `type` int(11) NOT NULL DEFAULT '0',
  KEY `cid` (`cid`) USING BTREE,
  KEY `cidtaskID` (`cid`,`taskID`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED;

-- ----------------------------
-- Records of log_cycle_task
-- ----------------------------

-- ----------------------------
-- Table structure for `log_daily_gift`
-- ----------------------------
DROP TABLE IF EXISTS `log_daily_gift`;
CREATE TABLE `log_daily_gift` (
  `id` int(11) NOT NULL AUTO_INCREMENT COMMENT '序号',
  `cid` bigint(20) NOT NULL DEFAULT '0' COMMENT '玩家ID',
  `giftid` int(11) NOT NULL DEFAULT '0' COMMENT '礼包ID',
  `type` tinyint(4) NOT NULL DEFAULT '0' COMMENT '礼包类型',
  `time` int(11) NOT NULL DEFAULT '0' COMMENT '领取时间',
  PRIMARY KEY (`id`),
  KEY `id` (`id`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED;

-- ----------------------------
-- Records of log_daily_gift
-- ----------------------------

-- ----------------------------
-- Table structure for `log_daily_report`
-- ----------------------------
DROP TABLE IF EXISTS `log_daily_report`;
CREATE TABLE `log_daily_report` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `time` int(11) NOT NULL DEFAULT '0' COMMENT '日期',
  `register` bigint(20) NOT NULL DEFAULT '0' COMMENT '注册（人）',
  `create` bigint(20) NOT NULL DEFAULT '0' COMMENT '创建（人）',
  `create_rate` int(11) NOT NULL DEFAULT '0' COMMENT '创建率',
  `lost` int(11) NOT NULL DEFAULT '0' COMMENT '流失（人）',
  `lost_rate` int(11) NOT NULL DEFAULT '0' COMMENT '流失率',
  `lost_new` int(11) NOT NULL DEFAULT '0' COMMENT '新手流失',
  `login` int(11) NOT NULL DEFAULT '0' COMMENT '登陆次数',
  `loginP` int(11) NOT NULL DEFAULT '0' COMMENT '登陆（人）',
  `online_max` int(11) NOT NULL DEFAULT '0' COMMENT '最高在线',
  `online_avg` int(11) NOT NULL DEFAULT '0' COMMENT '平均在线',
  `online_avg_active` int(11) NOT NULL DEFAULT '0' COMMENT '均活跃在线',
  `money` int(11) NOT NULL DEFAULT '0' COMMENT '充值',
  `money_people` int(11) NOT NULL DEFAULT '0' COMMENT '充值人数',
  `money_time` int(11) NOT NULL DEFAULT '0' COMMENT '充值次数',
  `arpu` int(11) NOT NULL DEFAULT '0' COMMENT 'ARPU',
  KEY `id` (`id`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED;

-- ----------------------------
-- Records of log_daily_report
-- ----------------------------

-- ----------------------------
-- Table structure for `log_day_report`
-- ----------------------------
DROP TABLE IF EXISTS `log_day_report`;
CREATE TABLE `log_day_report` (
  `id` int(11) NOT NULL AUTO_INCREMENT COMMENT '序列',
  `time` int(11) NOT NULL DEFAULT '0' COMMENT '日期',
  `type` int(11) NOT NULL DEFAULT '0' COMMENT '类型',
  `value` int(11) NOT NULL DEFAULT '0' COMMENT '值',
  `ratio` int(11) NOT NULL DEFAULT '0' COMMENT '比率',
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED;

-- ----------------------------
-- Records of log_day_report
-- ----------------------------

-- ----------------------------
-- Table structure for `log_dungeon`
-- ----------------------------
DROP TABLE IF EXISTS `log_dungeon`;
CREATE TABLE `log_dungeon` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `cid` bigint(20) NOT NULL DEFAULT '0' COMMENT '玩家ID',
  `did` int(11) NOT NULL DEFAULT '0' COMMENT '副本ID',
  `type` tinyint(4) NOT NULL DEFAULT '0' COMMENT '副本类型',
  `level` int(11) NOT NULL DEFAULT '0' COMMENT '等级',
  `state` tinyint(4) NOT NULL DEFAULT '0' COMMENT '状态\r\n0=未完成\r\n1=完成\r\n2=中途退出',
  `start_time` int(11) NOT NULL DEFAULT '0' COMMENT '开始时间',
  `finish_time` int(11) NOT NULL DEFAULT '0' COMMENT '完成时间',
  PRIMARY KEY (`id`),
  KEY `ciddidtime` (`cid`,`did`,`start_time`,`state`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED;

-- ----------------------------
-- Records of log_dungeon
-- ----------------------------

-- ----------------------------
-- Table structure for `log_equip_add_gem`
-- ----------------------------
DROP TABLE IF EXISTS `log_equip_add_gem`;
CREATE TABLE `log_equip_add_gem` (
  `id` int(11) NOT NULL AUTO_INCREMENT COMMENT '序列',
  `cid` bigint(20) NOT NULL DEFAULT '0' COMMENT '角色编号',
  `name` char(8) NOT NULL DEFAULT '' COMMENT '名字',
  `equip_name` char(16) NOT NULL DEFAULT '' COMMENT '装备名字',
  `equip_quality` int(11) NOT NULL DEFAULT '0' COMMENT '装备品质',
  `gem_name` char(12) NOT NULL DEFAULT '' COMMENT '宝石名字',
  `gem_level` int(11) NOT NULL DEFAULT '0' COMMENT '宝石等级',
  `time` int(11) NOT NULL DEFAULT '0' COMMENT '时间',
  KEY `id` (`id`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED;

-- ----------------------------
-- Records of log_equip_add_gem
-- ----------------------------

-- ----------------------------
-- Table structure for `log_equip_dismantle`
-- ----------------------------
DROP TABLE IF EXISTS `log_equip_dismantle`;
CREATE TABLE `log_equip_dismantle` (
  `id` int(11) NOT NULL AUTO_INCREMENT COMMENT '序列',
  `cid` bigint(20) NOT NULL DEFAULT '0' COMMENT '角色id',
  `name` char(8) NOT NULL DEFAULT '' COMMENT '角色名',
  `equip_id` bigint(20) NOT NULL DEFAULT '0' COMMENT '装备id',
  `base` int(11) NOT NULL DEFAULT '0' COMMENT '装备',
  `enhance` int(11) NOT NULL DEFAULT '0' COMMENT '装备强化等级',
  `item1_id` int(11) NOT NULL DEFAULT '0' COMMENT '分解道具1',
  `item1_count` int(11) NOT NULL DEFAULT '0' COMMENT '分解道具1数量',
  `item2_id` int(11) NOT NULL DEFAULT '0' COMMENT '分解道具2',
  `item2_count` int(11) NOT NULL DEFAULT '0' COMMENT '分解道具2数量',
  `item3_id` int(11) NOT NULL DEFAULT '0' COMMENT '分解道具3',
  `item3_count` int(11) NOT NULL DEFAULT '0' COMMENT '分解道具3数量',
  `item4_id` int(11) NOT NULL DEFAULT '0' COMMENT '分解道具4',
  `item4_count` int(11) NOT NULL DEFAULT '0' COMMENT '分解道具4数量',
  `time` int(11) NOT NULL DEFAULT '0' COMMENT '时间',
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED;

-- ----------------------------
-- Records of log_equip_dismantle
-- ----------------------------

-- ----------------------------
-- Table structure for `log_equip_enhance`
-- ----------------------------
DROP TABLE IF EXISTS `log_equip_enhance`;
CREATE TABLE `log_equip_enhance` (
  `id` int(11) NOT NULL AUTO_INCREMENT COMMENT '序列',
  `cid` bigint(20) NOT NULL DEFAULT '0' COMMENT '角色编号',
  `name` char(8) NOT NULL DEFAULT '' COMMENT '姓名',
  `equip_id` bigint(20) NOT NULL DEFAULT '0' COMMENT '装备id',
  `base_id` int(11) NOT NULL DEFAULT '0' COMMENT '装备基础id',
  `equip_quality` int(11) NOT NULL DEFAULT '0' COMMENT '装备品质',
  `old_level` int(11) NOT NULL DEFAULT '0' COMMENT '原强化等级',
  `new_level` int(11) NOT NULL DEFAULT '0' COMMENT '新强化等级',
  `money_cost` int(11) NOT NULL DEFAULT '0' COMMENT '铜币消耗',
  `sys_gold_cost` int(11) NOT NULL DEFAULT '0' COMMENT '绑定元宝消耗',
  `gold_cost` int(11) NOT NULL DEFAULT '0' COMMENT '元宝消耗',
  `time` int(11) NOT NULL DEFAULT '0' COMMENT '时间',
  KEY `id` (`id`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED;

-- ----------------------------
-- Records of log_equip_enhance
-- ----------------------------

-- ----------------------------
-- Table structure for `log_equip_life`
-- ----------------------------
DROP TABLE IF EXISTS `log_equip_life`;
CREATE TABLE `log_equip_life` (
  `id` int(11) NOT NULL AUTO_INCREMENT COMMENT '顺序id',
  `cid` bigint(20) NOT NULL DEFAULT '0' COMMENT '角色id',
  `name` char(8) NOT NULL DEFAULT '' COMMENT '角色名',
  `eid` bigint(20) NOT NULL DEFAULT '0' COMMENT '装备id',
  `baseid` int(11) NOT NULL DEFAULT '0' COMMENT '装备名',
  `type` int(11) NOT NULL DEFAULT '0' COMMENT '事件类型',
  `reason` int(11) NOT NULL DEFAULT '0' COMMENT '事件原因',
  `time` int(11) NOT NULL DEFAULT '0' COMMENT '记录时间',
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED;

-- ----------------------------
-- Records of log_equip_life
-- ----------------------------

-- ----------------------------
-- Table structure for `log_equip_magic_smith`
-- ----------------------------
DROP TABLE IF EXISTS `log_equip_magic_smith`;
CREATE TABLE `log_equip_magic_smith` (
  `id` int(11) NOT NULL AUTO_INCREMENT COMMENT '序列',
  `cid` bigint(20) NOT NULL DEFAULT '0' COMMENT '角色id',
  `name` char(8) NOT NULL DEFAULT '' COMMENT '角色名',
  `equip_id` bigint(20) NOT NULL DEFAULT '0' COMMENT '装备id',
  `old_base_id` int(11) NOT NULL DEFAULT '0' COMMENT '原装备',
  `new_base_id` int(11) NOT NULL DEFAULT '0' COMMENT '新装备',
  `time` int(11) NOT NULL DEFAULT '0' COMMENT '时间',
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED;

-- ----------------------------
-- Records of log_equip_magic_smith
-- ----------------------------

-- ----------------------------
-- Table structure for `log_equip_remove_gem`
-- ----------------------------
DROP TABLE IF EXISTS `log_equip_remove_gem`;
CREATE TABLE `log_equip_remove_gem` (
  `id` int(11) NOT NULL AUTO_INCREMENT COMMENT '序列',
  `cid` bigint(20) NOT NULL DEFAULT '0' COMMENT '角色id',
  `name` char(8) NOT NULL DEFAULT '' COMMENT '名字',
  `eid` bigint(20) NOT NULL DEFAULT '0' COMMENT '装备id',
  `baseid` int(11) NOT NULL DEFAULT '0' COMMENT '装备基础id',
  `slot_index` int(11) NOT NULL DEFAULT '0' COMMENT '孔位置',
  `stoneid` int(11) NOT NULL DEFAULT '0' COMMENT '宝石id',
  `time` int(11) NOT NULL DEFAULT '0' COMMENT '时间',
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED;

-- ----------------------------
-- Records of log_equip_remove_gem
-- ----------------------------

-- ----------------------------
-- Table structure for `log_equip_smithing`
-- ----------------------------
DROP TABLE IF EXISTS `log_equip_smithing`;
CREATE TABLE `log_equip_smithing` (
  `id` int(11) NOT NULL AUTO_INCREMENT COMMENT '序列',
  `cid` bigint(20) NOT NULL DEFAULT '0' COMMENT '角色编号',
  `name` char(8) NOT NULL DEFAULT '' COMMENT '名字',
  `equip_id` bigint(20) NOT NULL DEFAULT '0' COMMENT '装备id',
  `old_base_id` int(11) NOT NULL DEFAULT '0' COMMENT '原装备',
  `new_base_id` int(11) NOT NULL DEFAULT '0' COMMENT '新装备',
  `equip_quality` int(11) NOT NULL DEFAULT '0' COMMENT '装备品质',
  `blueprint_id` int(11) NOT NULL DEFAULT '0' COMMENT '图纸',
  `blueprint_quality` int(11) NOT NULL DEFAULT '0' COMMENT '图纸品质',
  `time` int(11) NOT NULL DEFAULT '0' COMMENT '时间',
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED;

-- ----------------------------
-- Records of log_equip_smithing
-- ----------------------------

-- ----------------------------
-- Table structure for `log_family_create`
-- ----------------------------
DROP TABLE IF EXISTS `log_family_create`;
CREATE TABLE `log_family_create` (
  `cid` bigint(20) NOT NULL DEFAULT '0',
  `name` char(8) NOT NULL DEFAULT '',
  `family_name` char(8) NOT NULL DEFAULT '',
  `create_time` int(11) NOT NULL DEFAULT '0',
  KEY `cid` (`cid`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED;

-- ----------------------------
-- Records of log_family_create
-- ----------------------------

-- ----------------------------
-- Table structure for `log_family_number`
-- ----------------------------
DROP TABLE IF EXISTS `log_family_number`;
CREATE TABLE `log_family_number` (
  `cid` bigint(20) NOT NULL DEFAULT '0',
  `name` char(8) NOT NULL DEFAULT '',
  `family_name` char(8) NOT NULL DEFAULT '',
  `join_time` int(11) NOT NULL DEFAULT '0',
  `out_time` int(11) NOT NULL DEFAULT '0',
  KEY `cid` (`cid`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED;

-- ----------------------------
-- Records of log_family_number
-- ----------------------------

-- ----------------------------
-- Table structure for `log_family_task`
-- ----------------------------
DROP TABLE IF EXISTS `log_family_task`;
CREATE TABLE `log_family_task` (
  `cid` bigint(20) NOT NULL DEFAULT '0',
  `name` char(8) NOT NULL DEFAULT '',
  `taskID` int(11) NOT NULL DEFAULT '0',
  `task_name` char(8) NOT NULL DEFAULT '',
  `receive_time` int(11) NOT NULL DEFAULT '0',
  `submit_time` int(11) NOT NULL DEFAULT '0',
  `type` int(11) NOT NULL DEFAULT '0' COMMENT '1.自己 2.快速',
  KEY `cid` (`cid`) USING BTREE,
  KEY `cidtaskID` (`cid`,`taskID`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED;

-- ----------------------------
-- Records of log_family_task
-- ----------------------------

-- ----------------------------
-- Table structure for `log_gm_gold_change`
-- ----------------------------
DROP TABLE IF EXISTS `log_gm_gold_change`;
CREATE TABLE `log_gm_gold_change` (
  `id` int(11) NOT NULL AUTO_INCREMENT COMMENT '序列',
  `cid` bigint(20) NOT NULL DEFAULT '0' COMMENT '角色id',
  `name` char(30) NOT NULL DEFAULT '' COMMENT '角色名',
  `level` int(11) NOT NULL DEFAULT '0' COMMENT '角色等级',
  `nindex` int(11) NOT NULL DEFAULT '0',
  `reason` int(11) NOT NULL DEFAULT '0' COMMENT '变动原因',
  `pid` int(11) NOT NULL DEFAULT '0' COMMENT '商品id',
  `count` int(11) NOT NULL DEFAULT '0' COMMENT '商品数量',
  `value` int(11) NOT NULL DEFAULT '0' COMMENT '元宝增减值',
  `time` int(11) NOT NULL DEFAULT '0' COMMENT '时间',
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED;

-- ----------------------------
-- Records of log_gm_gold_change
-- ----------------------------

-- ----------------------------
-- Table structure for `log_gold_change`
-- ----------------------------
DROP TABLE IF EXISTS `log_gold_change`;
CREATE TABLE `log_gold_change` (
  `id` int(11) NOT NULL AUTO_INCREMENT COMMENT '序列',
  `cid` bigint(20) NOT NULL DEFAULT '0' COMMENT '角色id',
  `name` char(30) NOT NULL DEFAULT '' COMMENT '角色名',
  `level` int(11) NOT NULL DEFAULT '0' COMMENT '角色等级',
  `nindex` int(11) NOT NULL DEFAULT '0' COMMENT '货币类型',
  `reason` int(11) NOT NULL DEFAULT '0' COMMENT '变动原因',
  `pid` int(11) NOT NULL DEFAULT '0' COMMENT '商品id',
  `count` int(11) NOT NULL DEFAULT '0' COMMENT '商品数量',
  `value` int(11) NOT NULL DEFAULT '0' COMMENT '元宝增减值',
  `time` int(11) NOT NULL DEFAULT '0' COMMENT '时间',
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED;

-- ----------------------------
-- Records of log_gold_change
-- ----------------------------

-- ----------------------------
-- Table structure for `log_hourly_report`
-- ----------------------------
DROP TABLE IF EXISTS `log_hourly_report`;
CREATE TABLE `log_hourly_report` (
  `id` int(11) NOT NULL AUTO_INCREMENT COMMENT '序列',
  `time` int(11) NOT NULL DEFAULT '0' COMMENT '日期',
  `register` bigint(20) NOT NULL DEFAULT '0' COMMENT '注册(人)',
  `create` bigint(20) NOT NULL DEFAULT '0' COMMENT '创建(人)',
  `create_rate` int(11) NOT NULL DEFAULT '0' COMMENT '创建率',
  `login` int(11) NOT NULL DEFAULT '0' COMMENT '登录(次)',
  `loginP` int(11) NOT NULL DEFAULT '0' COMMENT '登录(人)',
  `online_max` int(11) NOT NULL DEFAULT '0' COMMENT '最高在线',
  `online_avg` int(11) NOT NULL DEFAULT '0' COMMENT '平均在线',
  `online_avg_active` int(11) NOT NULL DEFAULT '0' COMMENT '平均活跃在线',
  `money` int(11) NOT NULL DEFAULT '0' COMMENT '充值',
  `money_people` int(11) NOT NULL DEFAULT '0' COMMENT '充值人数',
  `money_time` int(11) NOT NULL DEFAULT '0' COMMENT '充值次数',
  `arpu` int(11) NOT NULL DEFAULT '0' COMMENT 'ARPU',
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED;

-- ----------------------------
-- Records of log_hourly_report
-- ----------------------------

-- ----------------------------
-- Table structure for `log_item_change`
-- ----------------------------
DROP TABLE IF EXISTS `log_item_change`;
CREATE TABLE `log_item_change` (
  `cid` bigint(20) NOT NULL DEFAULT '0',
  `name` char(20) NOT NULL DEFAULT '',
  `flag` tinyint(4) NOT NULL DEFAULT '0',
  `reason` int(11) NOT NULL DEFAULT '0',
  `id` int(11) NOT NULL DEFAULT '0',
  `class` tinyint(4) NOT NULL DEFAULT '0',
  `count` int(11) NOT NULL DEFAULT '0',
  `time` int(11) NOT NULL DEFAULT '0',
  `srcid` bigint(20) NOT NULL DEFAULT '0' COMMENT '关联ID',
  KEY `cid` (`cid`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED;

-- ----------------------------
-- Records of log_item_change
-- ----------------------------

-- ----------------------------
-- Table structure for `log_item_combine`
-- ----------------------------
DROP TABLE IF EXISTS `log_item_combine`;
CREATE TABLE `log_item_combine` (
  `id` int(11) NOT NULL AUTO_INCREMENT COMMENT '序列',
  `cid` bigint(20) NOT NULL DEFAULT '0' COMMENT '角色id',
  `name` char(8) NOT NULL DEFAULT '' COMMENT '角色名',
  `old_item_id` int(11) NOT NULL DEFAULT '0' COMMENT '原道具',
  `old_item_num` int(11) NOT NULL DEFAULT '0' COMMENT '合成前道具数量',
  `new_item_id` int(11) NOT NULL DEFAULT '0' COMMENT '新道具',
  `new_item_num` int(11) NOT NULL DEFAULT '0' COMMENT '合成后道具数量',
  `money_cost` int(11) NOT NULL DEFAULT '0' COMMENT '消耗铜币',
  `sys_gold_cost` int(11) NOT NULL DEFAULT '0' COMMENT '消耗绑定元宝',
  `gold_cost` int(11) NOT NULL DEFAULT '0' COMMENT '消耗元宝',
  `time` int(11) NOT NULL DEFAULT '0' COMMENT '时间',
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED;

-- ----------------------------
-- Records of log_item_combine
-- ----------------------------

-- ----------------------------
-- Table structure for `log_month_report`
-- ----------------------------
DROP TABLE IF EXISTS `log_month_report`;
CREATE TABLE `log_month_report` (
  `id` int(11) NOT NULL AUTO_INCREMENT COMMENT '序列',
  `time` int(11) NOT NULL DEFAULT '0' COMMENT '月份检索',
  `minute_check` int(11) NOT NULL DEFAULT '0' COMMENT '天份检索',
  `login_count` int(11) NOT NULL DEFAULT '0' COMMENT '登陆次数',
  `login_ratio` int(11) NOT NULL DEFAULT '0' COMMENT '登陆比率',
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED;

-- ----------------------------
-- Records of log_month_report
-- ----------------------------

-- ----------------------------
-- Table structure for `log_online`
-- ----------------------------
DROP TABLE IF EXISTS `log_online`;
CREATE TABLE `log_online` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `login` int(11) NOT NULL DEFAULT '0',
  `active` int(11) NOT NULL DEFAULT '0',
  `inactive` int(11) NOT NULL DEFAULT '0',
  `online` int(11) NOT NULL DEFAULT '0',
  `time` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED;

-- ----------------------------
-- Records of log_online
-- ----------------------------

-- ----------------------------
-- Table structure for `log_player_level_distribution`
-- ----------------------------
DROP TABLE IF EXISTS `log_player_level_distribution`;
CREATE TABLE `log_player_level_distribution` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `level` int(11) NOT NULL DEFAULT '0',
  `kingdoms` varchar(500) NOT NULL DEFAULT '',
  `jobs` varchar(500) NOT NULL DEFAULT '',
  `total` int(11) NOT NULL DEFAULT '0',
  `time` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

-- ----------------------------
-- Records of log_player_level_distribution
-- ----------------------------

-- ----------------------------
-- Table structure for `log_player_login`
-- ----------------------------
DROP TABLE IF EXISTS `log_player_login`;
CREATE TABLE `log_player_login` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `cid` bigint(20) NOT NULL DEFAULT '0',
  `action` int(11) NOT NULL DEFAULT '0',
  `time` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED;

-- ----------------------------
-- Records of log_player_login
-- ----------------------------

-- ----------------------------
-- Table structure for `log_task`
-- ----------------------------
DROP TABLE IF EXISTS `log_task`;
CREATE TABLE `log_task` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `cid` bigint(20) NOT NULL DEFAULT '0' COMMENT '玩家ID',
  `tid` int(11) NOT NULL DEFAULT '0' COMMENT '任务ID',
  `type` tinyint(4) NOT NULL DEFAULT '0' COMMENT '任务类型',
  `receive_time` int(11) NOT NULL DEFAULT '0' COMMENT '接受时间',
  `submit_time` int(11) NOT NULL DEFAULT '0' COMMENT '完成时间',
  `state` int(11) NOT NULL DEFAULT '0' COMMENT '任务状态\r\n',
  PRIMARY KEY (`id`),
  KEY `cidtidstate` (`cid`,`tid`,`state`) USING BTREE,
  KEY `cidtid` (`cid`,`tid`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED;

-- ----------------------------
-- Records of log_task
-- ----------------------------

-- ----------------------------
-- Table structure for `log_user_liucun`
-- ----------------------------
DROP TABLE IF EXISTS `log_user_liucun`;
CREATE TABLE `log_user_liucun` (
  `id` int(11) NOT NULL AUTO_INCREMENT COMMENT '编号',
  `one` float NOT NULL COMMENT '第一天',
  `two` float NOT NULL COMMENT '第二天',
  `three` float NOT NULL COMMENT '第三天',
  `four` float NOT NULL COMMENT '第四天',
  `five` float NOT NULL COMMENT '第五天',
  `six` float NOT NULL COMMENT '第六天',
  `seven` float NOT NULL COMMENT '第七天',
  `fourtween` float NOT NULL COMMENT '第十四天',
  `thirty` float NOT NULL COMMENT '第三十天',
  `time` int(11) NOT NULL DEFAULT '0' COMMENT '时间',
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED;

-- ----------------------------
-- Records of log_user_liucun
-- ----------------------------

-- ----------------------------
-- Table structure for `log_user_retention`
-- ----------------------------
DROP TABLE IF EXISTS `log_user_retention`;
CREATE TABLE `log_user_retention` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `cid` bigint(20) NOT NULL DEFAULT '0',
  `monday` int(11) NOT NULL DEFAULT '0' COMMENT '星期一',
  `tuesday` int(11) NOT NULL DEFAULT '0' COMMENT '星期二',
  `wednesday` int(11) NOT NULL DEFAULT '0' COMMENT '星期三',
  `thursday` int(11) NOT NULL DEFAULT '0' COMMENT '星期四',
  `friday` int(11) NOT NULL DEFAULT '0' COMMENT '星期五',
  `saturday` int(11) NOT NULL DEFAULT '0' COMMENT '星期六',
  `sunday` int(11) NOT NULL DEFAULT '0' COMMENT '星期日',
  `fourtween` int(11) NOT NULL DEFAULT '0' COMMENT '14天',
  `January` int(11) NOT NULL DEFAULT '0' COMMENT '一个月',
  PRIMARY KEY (`cid`),
  KEY `id` (`id`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED;

-- ----------------------------
-- Records of log_user_retention
-- ----------------------------

-- ----------------------------
-- Table structure for `log_yellow_stone`
-- ----------------------------
DROP TABLE IF EXISTS `log_yellow_stone`;
CREATE TABLE `log_yellow_stone` (
  `cid` bigint(20) NOT NULL,
  `id` int(11) NOT NULL COMMENT 'cfg_yellow_stone 的 id',
  `get_time` int(11) NOT NULL COMMENT '领取时间'
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;

-- ----------------------------
-- Records of log_yellow_stone
-- ----------------------------

-- ----------------------------
-- Table structure for `mem_achievement`
-- ----------------------------
DROP TABLE IF EXISTS `mem_achievement`;
CREATE TABLE `mem_achievement` (
  `Cid` bigint(20) NOT NULL DEFAULT '0',
  `Id` int(11) DEFAULT NULL,
  `FinishCount` int(11) NOT NULL DEFAULT '0',
  `AcState` int(11) NOT NULL DEFAULT '0',
  `Time` int(11) NOT NULL DEFAULT '0',
  KEY `cid` (`Cid`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED;

-- ----------------------------
-- Records of mem_achievement
-- ----------------------------

-- ----------------------------
-- Table structure for `mem_character`
-- ----------------------------
DROP TABLE IF EXISTS `mem_character`;
CREATE TABLE `mem_character` (
  `cid` bigint(20) NOT NULL COMMENT '角色ID',
  `uid` int(11) NOT NULL DEFAULT '0' COMMENT '用户ID',
  `sid` int(11) NOT NULL DEFAULT '0' COMMENT '服务器id',
  `name` char(20) NOT NULL DEFAULT '' COMMENT '角色名',
  `sex` int(11) NOT NULL DEFAULT '0' COMMENT '性别',
  `job` int(11) NOT NULL DEFAULT '0' COMMENT '职业',
  `level` int(11) NOT NULL DEFAULT '0' COMMENT '等级',
  `exp` bigint(20) NOT NULL DEFAULT '0' COMMENT '拥有经验',
  `exp_minus` bigint(20) NOT NULL DEFAULT '0' COMMENT '经验减去值，主要用于pk惩罚',
  `vip` int(11) NOT NULL DEFAULT '0' COMMENT 'vip的id',
  `vip_end_time` int(11) NOT NULL DEFAULT '0' COMMENT 'vip结束时间',
  `battle` int(11) NOT NULL,
  `mapid` int(11) NOT NULL DEFAULT '0' COMMENT '所在地图ID',
  `x` int(11) NOT NULL DEFAULT '0' COMMENT '所在地图x',
  `y` int(11) NOT NULL DEFAULT '0' COMMENT '所在地图y',
  `hp` int(11) NOT NULL DEFAULT '0' COMMENT '血量',
  `mp` int(11) NOT NULL DEFAULT '0' COMMENT '蓝量',
  `pp` int(11) NOT NULL DEFAULT '0' COMMENT '体力值',
  `xp` int(11) NOT NULL DEFAULT '0' COMMENT 'xp值',
  `level_gift` int(11) NOT NULL DEFAULT '0' COMMENT '等级礼包',
  `level_gold` int(11) NOT NULL DEFAULT '0',
  `seven_login` int(11) NOT NULL DEFAULT '0',
  `head` int(11) NOT NULL DEFAULT '0',
  `create_time` int(11) NOT NULL DEFAULT '0' COMMENT '创建时间',
  `pk_mode` int(11) NOT NULL DEFAULT '0' COMMENT 'pk模式',
  `pk_value` int(11) NOT NULL DEFAULT '0' COMMENT 'pk值',
  `pk_killed_count` int(11) NOT NULL DEFAULT '0',
  `pk_time` int(11) NOT NULL DEFAULT '0',
  `kill_count` int(11) NOT NULL DEFAULT '0' COMMENT '杀死玩家数目',
  `bag_open_time` int(11) NOT NULL DEFAULT '0' COMMENT '背包开启时间',
  `bag_open_slot` int(11) NOT NULL DEFAULT '0' COMMENT '背包开启格数',
  `bag_can_open` int(11) NOT NULL DEFAULT '0' COMMENT '背包待开启',
  `last_task_id` int(11) NOT NULL DEFAULT '0',
  `logout_count` int(11) NOT NULL DEFAULT '0' COMMENT '登录次数',
  `pay_click_count` int(11) NOT NULL DEFAULT '0' COMMENT '充值按钮点击次数',
  `level_stay_time` int(11) NOT NULL DEFAULT '0',
  `last_login_time` int(11) NOT NULL DEFAULT '0' COMMENT '最后登录时间',
  `last_logout_time` int(11) NOT NULL DEFAULT '0' COMMENT '最后登出时间',
  `delete_time` int(11) NOT NULL DEFAULT '0' COMMENT '删除时间',
  `weapon` int(11) NOT NULL DEFAULT '0' COMMENT '当前武器',
  `cloth` int(11) NOT NULL DEFAULT '0' COMMENT '当前衣服',
  `start_game` tinyint(4) DEFAULT NULL,
  PRIMARY KEY (`cid`),
  UNIQUE KEY `name` (`name`) USING BTREE,
  KEY `uidsid` (`uid`,`sid`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED;

-- ----------------------------
-- Records of mem_character
-- ----------------------------

-- ----------------------------
-- Table structure for `mem_char_currency`
-- ----------------------------
DROP TABLE IF EXISTS `mem_char_currency`;
CREATE TABLE `mem_char_currency` (
  `cid` bigint(20) NOT NULL DEFAULT '0',
  `currency` varchar(200) DEFAULT '' COMMENT '货币',
  PRIMARY KEY (`cid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

-- ----------------------------
-- Records of mem_char_currency
-- ----------------------------

-- ----------------------------
-- Table structure for `mem_char_inside_pet`
-- ----------------------------
DROP TABLE IF EXISTS `mem_char_inside_pet`;
CREATE TABLE `mem_char_inside_pet` (
  `cid` bigint(20) NOT NULL DEFAULT '0' COMMENT '所有者ID',
  `pid` bigint(20) NOT NULL DEFAULT '0' COMMENT '经验',
  `start_flag` int(4) NOT NULL DEFAULT '0' COMMENT '初始属性修炼标记',
  `attr_type` int(4) NOT NULL DEFAULT '0' COMMENT '初始属性修炼增加属性',
  `attr_val` int(11) NOT NULL DEFAULT '0' COMMENT '初始属性修炼增加值',
  `online_time` int(11) NOT NULL DEFAULT '0' COMMENT '在线时间',
  `left_time` int(11) NOT NULL DEFAULT '0' COMMENT '初始属性修炼剩余时间',
  `buy_exp_times` int(11) NOT NULL DEFAULT '0' COMMENT '每日购买经验值次数',
  PRIMARY KEY (`cid`),
  KEY `cid` (`cid`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED;

-- ----------------------------
-- Records of mem_char_inside_pet
-- ----------------------------

-- ----------------------------
-- Table structure for `mem_char_operate_limit`
-- ----------------------------
DROP TABLE IF EXISTS `mem_char_operate_limit`;
CREATE TABLE `mem_char_operate_limit` (
  `cid` bigint(20) NOT NULL DEFAULT '0',
  `LimitId` int(11) NOT NULL DEFAULT '0' COMMENT '操作限制类型',
  `LimitCount` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`cid`,`LimitId`),
  KEY `cidtype` (`cid`,`LimitId`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED;

-- ----------------------------
-- Records of mem_char_operate_limit
-- ----------------------------

-- ----------------------------
-- Table structure for `mem_char_ransom`
-- ----------------------------
DROP TABLE IF EXISTS `mem_char_ransom`;
CREATE TABLE `mem_char_ransom` (
  `CharId` bigint(20) DEFAULT NULL COMMENT '装备拥有者id',
  `CharName` varchar(20) DEFAULT NULL COMMENT '装备拥有者姓名',
  `KillerId` bigint(20) DEFAULT NULL,
  `KillerName` varchar(20) DEFAULT NULL,
  `CanGetLastTime` int(11) DEFAULT NULL,
  `ItemId` int(11) DEFAULT NULL,
  `ItemClass` int(4) DEFAULT NULL,
  `ItemCount` int(11) DEFAULT NULL,
  `Bind` int(4) DEFAULT NULL,
  `EndTime` int(11) DEFAULT NULL,
  `SrcId` bigint(20) NOT NULL DEFAULT '0',
  `Mid` int(11) DEFAULT NULL,
  KEY `charid` (`CharId`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;

-- ----------------------------
-- Records of mem_char_ransom
-- ----------------------------

-- ----------------------------
-- Table structure for `mem_char_soul`
-- ----------------------------
DROP TABLE IF EXISTS `mem_char_soul`;
CREATE TABLE `mem_char_soul` (
  `cid` bigint(20) NOT NULL DEFAULT '0',
  `level` int(11) NOT NULL DEFAULT '0' COMMENT '等级',
  `soul` bigint(20) NOT NULL DEFAULT '0' COMMENT '魂力值',
  PRIMARY KEY (`cid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED;

-- ----------------------------
-- Records of mem_char_soul
-- ----------------------------

-- ----------------------------
-- Table structure for `mem_char_worship`
-- ----------------------------
DROP TABLE IF EXISTS `mem_char_worship`;
CREATE TABLE `mem_char_worship` (
  `cid` bigint(20) NOT NULL DEFAULT '0',
  `times` tinyint(4) NOT NULL DEFAULT '0' COMMENT '今日崇拜次数',
  `charlist` varchar(120) NOT NULL DEFAULT '' COMMENT '今日崇拜过的人列表',
  `record` int(11) NOT NULL DEFAULT '0' COMMENT '崇拜数',
  PRIMARY KEY (`cid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED;

-- ----------------------------
-- Records of mem_char_worship
-- ----------------------------

-- ----------------------------
-- Table structure for `mem_chr_action`
-- ----------------------------
DROP TABLE IF EXISTS `mem_chr_action`;
CREATE TABLE `mem_chr_action` (
  `cid` bigint(20) NOT NULL DEFAULT '0' COMMENT '角色id',
  `slot` int(11) NOT NULL DEFAULT '0' COMMENT '位置，1~12',
  `id` int(11) NOT NULL DEFAULT '0' COMMENT '道具或者技能id',
  `type` int(11) NOT NULL DEFAULT '0' COMMENT '类型，1道具，2技能',
  KEY `cid` (`cid`) USING BTREE,
  KEY `slot` (`slot`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED;

-- ----------------------------
-- Records of mem_chr_action
-- ----------------------------

-- ----------------------------
-- Table structure for `mem_chr_attr`
-- ----------------------------
DROP TABLE IF EXISTS `mem_chr_attr`;
CREATE TABLE `mem_chr_attr` (
  `cid` bigint(20) NOT NULL DEFAULT '0',
  `hp` int(11) NOT NULL DEFAULT '0' COMMENT '生命值',
  `mp` int(11) NOT NULL DEFAULT '0' COMMENT '法力值',
  `pp` int(11) NOT NULL DEFAULT '0' COMMENT '体力值',
  `xp` int(11) NOT NULL DEFAULT '0' COMMENT 'XP值',
  `phy_atk_min` int(11) NOT NULL DEFAULT '0' COMMENT '最小物理攻击力',
  `phy_atk_max` int(11) NOT NULL DEFAULT '0' COMMENT '最大物理攻击力',
  `mag_atk_min` int(11) NOT NULL DEFAULT '0' COMMENT '最小魔法攻击力',
  `mag_atk_max` int(11) NOT NULL DEFAULT '0' COMMENT '最大魔法攻击力',
  `phy_def` int(11) NOT NULL DEFAULT '0' COMMENT '物理防御力',
  `mag_def` int(11) NOT NULL DEFAULT '0' COMMENT '魔法防御力',
  `hitrate` int(11) NOT NULL DEFAULT '0' COMMENT '命中',
  `dodge` int(11) NOT NULL DEFAULT '0' COMMENT '闪避',
  `critrate` int(11) NOT NULL DEFAULT '0' COMMENT '暴击',
  `dmg_add` int(11) NOT NULL DEFAULT '0' COMMENT '额外伤害',
  `dmg_rdc` int(11) NOT NULL DEFAULT '0' COMMENT '忽视伤害',
  `dmg_add_pec` int(11) NOT NULL DEFAULT '0' COMMENT '伤害加成（%）',
  `dmg_rdc_pec` int(11) NOT NULL DEFAULT '0' COMMENT '伤害减免（%）',
  `movespeed` int(11) NOT NULL DEFAULT '0' COMMENT '移动速度',
  `battle` int(11) NOT NULL DEFAULT '0' COMMENT '战斗力',
  `lucky` int(11) NOT NULL DEFAULT '0' COMMENT '幸运值',
  PRIMARY KEY (`cid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED;

-- ----------------------------
-- Records of mem_chr_attr
-- ----------------------------

-- ----------------------------
-- Table structure for `mem_chr_auction`
-- ----------------------------
DROP TABLE IF EXISTS `mem_chr_auction`;
CREATE TABLE `mem_chr_auction` (
  `aid` int(11) NOT NULL DEFAULT '0' COMMENT '拍卖ID',
  `id` int(11) NOT NULL DEFAULT '0' COMMENT '物品ID',
  `class` tinyint(4) NOT NULL DEFAULT '0' COMMENT '物品类型',
  `count` int(11) NOT NULL DEFAULT '0' COMMENT '数量',
  `equipStar` int(11) NOT NULL COMMENT '装备星级',
  `srcid` bigint(20) NOT NULL DEFAULT '0' COMMENT '关联ID\r\n例如：装备ID',
  `price` int(11) NOT NULL DEFAULT '0' COMMENT '售价',
  `seller` bigint(20) NOT NULL DEFAULT '0' COMMENT '卖家',
  `buyer` bigint(20) NOT NULL DEFAULT '0' COMMENT '买家',
  `optime` int(11) NOT NULL DEFAULT '0' COMMENT '成交时间',
  PRIMARY KEY (`aid`),
  KEY `cidbagslot` (`aid`) USING BTREE,
  KEY `id` (`id`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED;

-- ----------------------------
-- Records of mem_chr_auction
-- ----------------------------

-- ----------------------------
-- Table structure for `mem_chr_auto_fight`
-- ----------------------------
DROP TABLE IF EXISTS `mem_chr_auto_fight`;
CREATE TABLE `mem_chr_auto_fight` (
  `cid` bigint(20) NOT NULL DEFAULT '0',
  `fight` char(150) NOT NULL DEFAULT '',
  `pick` char(1) NOT NULL DEFAULT '',
  PRIMARY KEY (`cid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED;

-- ----------------------------
-- Records of mem_chr_auto_fight
-- ----------------------------

-- ----------------------------
-- Table structure for `mem_chr_bag`
-- ----------------------------
DROP TABLE IF EXISTS `mem_chr_bag`;
CREATE TABLE `mem_chr_bag` (
  `cid` bigint(20) NOT NULL DEFAULT '0' COMMENT '玩家ID',
  `bag` tinyint(4) NOT NULL DEFAULT '0' COMMENT '包裹编号\r\n装备栏=0\r\n背包=1\r\n仓库=2\r\n',
  `slot` int(11) NOT NULL DEFAULT '0' COMMENT '格子',
  `id` int(11) NOT NULL DEFAULT '0' COMMENT '物品ID',
  `class` tinyint(4) NOT NULL DEFAULT '0' COMMENT '物品类型',
  `count` int(11) NOT NULL DEFAULT '0' COMMENT '数量',
  `bind` tinyint(4) NOT NULL DEFAULT '0' COMMENT '绑定状态',
  `endtime` int(11) NOT NULL DEFAULT '0' COMMENT '过期时间',
  `srcid` bigint(20) NOT NULL DEFAULT '0' COMMENT '关联ID\r\n例如：装备ID',
  PRIMARY KEY (`cid`,`bag`,`slot`),
  KEY `cidbagslot` (`cid`,`bag`,`slot`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED;

-- ----------------------------
-- Records of mem_chr_bag
-- ----------------------------

-- ----------------------------
-- Table structure for `mem_chr_buff`
-- ----------------------------
DROP TABLE IF EXISTS `mem_chr_buff`;
CREATE TABLE `mem_chr_buff` (
  `cid` bigint(20) NOT NULL DEFAULT '0',
  `item` int(11) NOT NULL DEFAULT '0',
  `time` int(11) NOT NULL DEFAULT '0',
  KEY `cid` (`cid`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED;

-- ----------------------------
-- Records of mem_chr_buff
-- ----------------------------

-- ----------------------------
-- Table structure for `mem_chr_chou_jiang_record`
-- ----------------------------
DROP TABLE IF EXISTS `mem_chr_chou_jiang_record`;
CREATE TABLE `mem_chr_chou_jiang_record` (
  `Cid` bigint(20) DEFAULT NULL,
  `ItemId` int(11) DEFAULT NULL,
  `ItemClass` int(4) DEFAULT NULL,
  `ItemCount` int(11) DEFAULT NULL,
  `Time` int(11) DEFAULT NULL,
  KEY `cid` (`Cid`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;

-- ----------------------------
-- Records of mem_chr_chou_jiang_record
-- ----------------------------

-- ----------------------------
-- Table structure for `mem_chr_chou_jiang_score`
-- ----------------------------
DROP TABLE IF EXISTS `mem_chr_chou_jiang_score`;
CREATE TABLE `mem_chr_chou_jiang_score` (
  `Cid` bigint(20) NOT NULL DEFAULT '0',
  `LuckPoint` int(11) DEFAULT NULL COMMENT '抽奖幸运值',
  `Score` int(11) DEFAULT NULL COMMENT '抽奖积分',
  PRIMARY KEY (`Cid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;

-- ----------------------------
-- Records of mem_chr_chou_jiang_score
-- ----------------------------

-- ----------------------------
-- Table structure for `mem_chr_depot`
-- ----------------------------
DROP TABLE IF EXISTS `mem_chr_depot`;
CREATE TABLE `mem_chr_depot` (
  `Cid` bigint(20) NOT NULL DEFAULT '0',
  `CurrencyString` varchar(150) DEFAULT NULL,
  `CanOpenSlots` int(11) DEFAULT NULL,
  `OpenedSlots` int(11) DEFAULT NULL,
  `LeftSeconds` int(11) DEFAULT NULL,
  PRIMARY KEY (`Cid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;

-- ----------------------------
-- Records of mem_chr_depot
-- ----------------------------

-- ----------------------------
-- Table structure for `mem_chr_equip`
-- ----------------------------
DROP TABLE IF EXISTS `mem_chr_equip`;
CREATE TABLE `mem_chr_equip` (
  `cid` bigint(20) NOT NULL DEFAULT '0' COMMENT '角色ID',
  `slot` int(11) NOT NULL DEFAULT '0' COMMENT '装备位置',
  `eid` bigint(20) NOT NULL DEFAULT '0' COMMENT '装备ID',
  KEY `cidslot` (`cid`,`slot`) USING BTREE,
  KEY `eid` (`eid`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED;

-- ----------------------------
-- Records of mem_chr_equip
-- ----------------------------

-- ----------------------------
-- Table structure for `mem_chr_exp_ball`
-- ----------------------------
DROP TABLE IF EXISTS `mem_chr_exp_ball`;
CREATE TABLE `mem_chr_exp_ball` (
  `Cid` bigint(20) NOT NULL DEFAULT '0',
  `ItemId` int(11) DEFAULT NULL,
  `CurExp` int(11) DEFAULT NULL,
  PRIMARY KEY (`Cid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;

-- ----------------------------
-- Records of mem_chr_exp_ball
-- ----------------------------

-- ----------------------------
-- Table structure for `mem_chr_fabao`
-- ----------------------------
DROP TABLE IF EXISTS `mem_chr_fabao`;
CREATE TABLE `mem_chr_fabao` (
  `Cid` bigint(20) NOT NULL DEFAULT '0',
  `FaBaoLevel` varchar(50) DEFAULT NULL,
  `FaBaoRes` varchar(50) DEFAULT NULL,
  `FaBaoDress` varchar(50) DEFAULT NULL,
  PRIMARY KEY (`Cid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;

-- ----------------------------
-- Records of mem_chr_fabao
-- ----------------------------

-- ----------------------------
-- Table structure for `mem_chr_family`
-- ----------------------------
DROP TABLE IF EXISTS `mem_chr_family`;
CREATE TABLE `mem_chr_family` (
  `cid` bigint(20) NOT NULL DEFAULT '0',
  `family_id` bigint(20) NOT NULL DEFAULT '0' COMMENT '家族id',
  `position` int(11) NOT NULL DEFAULT '0' COMMENT '职位',
  `contribute` int(11) NOT NULL DEFAULT '0' COMMENT '捐献贡献',
  `pet_contribute` int(11) NOT NULL DEFAULT '0' COMMENT '宠物贡献',
  `regflag` varchar(100) NOT NULL DEFAULT '' COMMENT '已登记标记',
  `Leave_family_time` int(11) DEFAULT NULL,
  PRIMARY KEY (`cid`),
  KEY `family_id` (`family_id`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED;

-- ----------------------------
-- Records of mem_chr_family
-- ----------------------------

-- ----------------------------
-- Table structure for `mem_chr_friend`
-- ----------------------------
DROP TABLE IF EXISTS `mem_chr_friend`;
CREATE TABLE `mem_chr_friend` (
  `cid` bigint(20) NOT NULL DEFAULT '0',
  `tcid` bigint(20) NOT NULL DEFAULT '0',
  `time` int(11) NOT NULL DEFAULT '0' COMMENT '记录时间',
  KEY `cid` (`cid`) USING BTREE,
  KEY `tcid` (`tcid`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED;

-- ----------------------------
-- Records of mem_chr_friend
-- ----------------------------

-- ----------------------------
-- Table structure for `mem_chr_friend_exp`
-- ----------------------------
DROP TABLE IF EXISTS `mem_chr_friend_exp`;
CREATE TABLE `mem_chr_friend_exp` (
  `Cid` bigint(20) DEFAULT NULL,
  `FriendId` bigint(20) DEFAULT NULL,
  `GetExp` int(11) DEFAULT NULL,
  `Level` int(11) DEFAULT NULL,
  `Name` varchar(20) DEFAULT NULL,
  KEY `cid` (`Cid`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;

-- ----------------------------
-- Records of mem_chr_friend_exp
-- ----------------------------

-- ----------------------------
-- Table structure for `mem_chr_gem`
-- ----------------------------
DROP TABLE IF EXISTS `mem_chr_gem`;
CREATE TABLE `mem_chr_gem` (
  `cid` bigint(20) NOT NULL DEFAULT '0' COMMENT '角色ID',
  `pos` int(11) NOT NULL DEFAULT '0' COMMENT '装备位置',
  `slot` int(11) NOT NULL DEFAULT '0' COMMENT '宝石位置',
  `gemid` int(11) NOT NULL DEFAULT '0' COMMENT '宝石',
  KEY `eid` (`gemid`) USING BTREE,
  KEY `cidposslot` (`cid`,`pos`,`slot`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED;

-- ----------------------------
-- Records of mem_chr_gem
-- ----------------------------

-- ----------------------------
-- Table structure for `mem_chr_huo_yue_du`
-- ----------------------------
DROP TABLE IF EXISTS `mem_chr_huo_yue_du`;
CREATE TABLE `mem_chr_huo_yue_du` (
  `Cid` bigint(20) NOT NULL DEFAULT '0',
  `HuoYueDuInfo` varchar(150) DEFAULT NULL,
  PRIMARY KEY (`Cid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;

-- ----------------------------
-- Records of mem_chr_huo_yue_du
-- ----------------------------

-- ----------------------------
-- Table structure for `mem_chr_jue_wei`
-- ----------------------------
DROP TABLE IF EXISTS `mem_chr_jue_wei`;
CREATE TABLE `mem_chr_jue_wei` (
  `CharId` bigint(20) NOT NULL DEFAULT '0' COMMENT '主角id',
  `DonateMoney` bigint(20) DEFAULT NULL COMMENT '捐款数量',
  PRIMARY KEY (`CharId`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;

-- ----------------------------
-- Records of mem_chr_jue_wei
-- ----------------------------

-- ----------------------------
-- Table structure for `mem_chr_kill_monster`
-- ----------------------------
DROP TABLE IF EXISTS `mem_chr_kill_monster`;
CREATE TABLE `mem_chr_kill_monster` (
  `Cid` bigint(20) DEFAULT NULL,
  `GroupId` int(11) DEFAULT NULL,
  `MonsterMid` int(11) DEFAULT NULL,
  `KillCount` int(11) DEFAULT NULL,
  `BossSign` int(11) DEFAULT NULL,
  KEY `cid` (`Cid`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;

-- ----------------------------
-- Records of mem_chr_kill_monster
-- ----------------------------

-- ----------------------------
-- Table structure for `mem_chr_mount`
-- ----------------------------
DROP TABLE IF EXISTS `mem_chr_mount`;
CREATE TABLE `mem_chr_mount` (
  `Cid` bigint(20) NOT NULL DEFAULT '0' COMMENT '角色id',
  `Quality` int(11) DEFAULT NULL COMMENT '坐骑等阶',
  `LuckyPoint` int(11) DEFAULT NULL COMMENT '当前幸运值',
  `SkillLatticeCount` int(11) DEFAULT NULL COMMENT '已经开启的技能格子数',
  `EatMountHeart` int(11) DEFAULT NULL COMMENT '已经服用坐骑之心的个数',
  `MountState` int(4) DEFAULT NULL COMMENT '是否在坐骑上',
  `CurRide` int(4) DEFAULT NULL COMMENT '当前乘骑的坐骑',
  `SkillMap` varchar(30) DEFAULT NULL COMMENT '坐骑技能等级信息',
  PRIMARY KEY (`Cid`),
  KEY `cid` (`Cid`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED;

-- ----------------------------
-- Records of mem_chr_mount
-- ----------------------------

-- ----------------------------
-- Table structure for `mem_chr_pet`
-- ----------------------------
DROP TABLE IF EXISTS `mem_chr_pet`;
CREATE TABLE `mem_chr_pet` (
  `cid` bigint(20) NOT NULL DEFAULT '0' COMMENT '角色ID',
  `pid` bigint(20) NOT NULL DEFAULT '0' COMMENT '宠物ID',
  `hp` int(11) NOT NULL DEFAULT '0' COMMENT '生命值',
  `alive` tinyint(4) NOT NULL DEFAULT '0' COMMENT '存活标记',
  `soul` int(11) NOT NULL DEFAULT '0' COMMENT '灵魂值',
  `state` tinyint(4) NOT NULL DEFAULT '0' COMMENT '状态',
  `bag` tinyint(4) NOT NULL DEFAULT '0' COMMENT '存放位置',
  `knight` tinyint(4) NOT NULL DEFAULT '0' COMMENT '骑士',
  `family_id` bigint(20) NOT NULL DEFAULT '0' COMMENT '注册帮派',
  `qi_shi` tinyint(4) DEFAULT NULL COMMENT '佩戴坐骑',
  PRIMARY KEY (`pid`),
  KEY `cidslot` (`cid`,`pid`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED;

-- ----------------------------
-- Records of mem_chr_pet
-- ----------------------------

-- ----------------------------
-- Table structure for `mem_chr_pet_egg`
-- ----------------------------
DROP TABLE IF EXISTS `mem_chr_pet_egg`;
CREATE TABLE `mem_chr_pet_egg` (
  `cid` bigint(20) NOT NULL DEFAULT '0' COMMENT '角色ID',
  `baseid` int(11) NOT NULL DEFAULT '0' COMMENT '宠物ID',
  `bag` tinyint(4) NOT NULL DEFAULT '0' COMMENT '存放位置',
  `slot` int(11) NOT NULL DEFAULT '0' COMMENT '存放格子',
  `state` tinyint(4) NOT NULL DEFAULT '0' COMMENT '状态',
  `starttime` int(11) NOT NULL DEFAULT '0' COMMENT '开始孵化时间',
  `pid` bigint(20) NOT NULL DEFAULT '0' COMMENT '宠物实体id',
  KEY `cidslot` (`cid`,`baseid`) USING BTREE,
  KEY `eid` (`bag`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED;

-- ----------------------------
-- Records of mem_chr_pet_egg
-- ----------------------------

-- ----------------------------
-- Table structure for `mem_chr_record`
-- ----------------------------
DROP TABLE IF EXISTS `mem_chr_record`;
CREATE TABLE `mem_chr_record` (
  `cid` bigint(20) NOT NULL DEFAULT '0',
  `type` int(11) NOT NULL DEFAULT '0',
  `param` int(11) NOT NULL DEFAULT '0',
  KEY `cidtype` (`cid`,`type`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED;

-- ----------------------------
-- Records of mem_chr_record
-- ----------------------------

-- ----------------------------
-- Table structure for `mem_chr_search_back`
-- ----------------------------
DROP TABLE IF EXISTS `mem_chr_search_back`;
CREATE TABLE `mem_chr_search_back` (
  `Cid` bigint(20) DEFAULT NULL,
  `ActivityType` int(11) DEFAULT NULL COMMENT '活动类型',
  `TodayRecord` varchar(20) DEFAULT NULL COMMENT '今天进入的记录',
  `YesterdayRecord` varchar(20) DEFAULT NULL COMMENT '昨天活动记录'
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;

-- ----------------------------
-- Records of mem_chr_search_back
-- ----------------------------

-- ----------------------------
-- Table structure for `mem_chr_shop_limit`
-- ----------------------------
DROP TABLE IF EXISTS `mem_chr_shop_limit`;
CREATE TABLE `mem_chr_shop_limit` (
  `Cid` bigint(20) NOT NULL,
  `ShopType` int(4) NOT NULL,
  `ShopId` int(11) NOT NULL DEFAULT '0',
  `LimitCount` int(11) NOT NULL,
  KEY `cid` (`Cid`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;

-- ----------------------------
-- Records of mem_chr_shop_limit
-- ----------------------------

-- ----------------------------
-- Table structure for `mem_chr_sign_info`
-- ----------------------------
DROP TABLE IF EXISTS `mem_chr_sign_info`;
CREATE TABLE `mem_chr_sign_info` (
  `cid` bigint(20) NOT NULL DEFAULT '0',
  `sign_record` int(11) NOT NULL,
  `sign_reward` varchar(70) NOT NULL DEFAULT '0',
  `refresh_time` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`cid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED;

-- ----------------------------
-- Records of mem_chr_sign_info
-- ----------------------------

-- ----------------------------
-- Table structure for `mem_chr_skill`
-- ----------------------------
DROP TABLE IF EXISTS `mem_chr_skill`;
CREATE TABLE `mem_chr_skill` (
  `cid` bigint(20) NOT NULL DEFAULT '0' COMMENT '角色id',
  `sid` int(11) NOT NULL DEFAULT '0' COMMENT '技能id',
  `level` int(11) NOT NULL DEFAULT '0' COMMENT '技能等级',
  KEY `cidsid` (`cid`,`sid`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED;

-- ----------------------------
-- Records of mem_chr_skill
-- ----------------------------

-- ----------------------------
-- Table structure for `mem_chr_system_setting`
-- ----------------------------
DROP TABLE IF EXISTS `mem_chr_system_setting`;
CREATE TABLE `mem_chr_system_setting` (
  `cid` bigint(20) NOT NULL DEFAULT '0',
  `setting` varchar(600) NOT NULL DEFAULT '',
  PRIMARY KEY (`cid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED;

-- ----------------------------
-- Records of mem_chr_system_setting
-- ----------------------------

-- ----------------------------
-- Table structure for `mem_chr_task`
-- ----------------------------
DROP TABLE IF EXISTS `mem_chr_task`;
CREATE TABLE `mem_chr_task` (
  `cid` bigint(20) NOT NULL DEFAULT '0' COMMENT '玩家id',
  `tid` int(11) NOT NULL DEFAULT '0' COMMENT '任务id',
  `state` int(11) NOT NULL DEFAULT '0' COMMENT '任务状态',
  `monster` int(11) NOT NULL DEFAULT '0',
  KEY `cidtid` (`cid`,`tid`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED;

-- ----------------------------
-- Records of mem_chr_task
-- ----------------------------

-- ----------------------------
-- Table structure for `mem_chr_tou_zi`
-- ----------------------------
DROP TABLE IF EXISTS `mem_chr_tou_zi`;
CREATE TABLE `mem_chr_tou_zi` (
  `cid` bigint(20) NOT NULL DEFAULT '0',
  `MoonCardStartTime` int(11) DEFAULT NULL,
  `TouZiValues` int(11) DEFAULT NULL,
  `MoonCardRecord` varchar(200) DEFAULT NULL,
  `LevelUpRecord` varchar(100) DEFAULT NULL,
  PRIMARY KEY (`cid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;

-- ----------------------------
-- Records of mem_chr_tou_zi
-- ----------------------------

-- ----------------------------
-- Table structure for `mem_cycle_task`
-- ----------------------------
DROP TABLE IF EXISTS `mem_cycle_task`;
CREATE TABLE `mem_cycle_task` (
  `cid` bigint(20) NOT NULL DEFAULT '0',
  `finishtimes` int(11) NOT NULL DEFAULT '0' COMMENT '完成次数',
  `taskid` int(11) NOT NULL DEFAULT '0' COMMENT '当前任务ID',
  `star` tinyint(4) NOT NULL DEFAULT '0' COMMENT '当前星数',
  `state` tinyint(4) NOT NULL DEFAULT '0' COMMENT '任务状态',
  `conds` int(11) NOT NULL DEFAULT '0' COMMENT '任务计数',
  `refstartimes` int(11) NOT NULL DEFAULT '0' COMMENT '刷新星级次数',
  PRIMARY KEY (`cid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED;

-- ----------------------------
-- Records of mem_cycle_task
-- ----------------------------

-- ----------------------------
-- Table structure for `mem_enemy`
-- ----------------------------
DROP TABLE IF EXISTS `mem_enemy`;
CREATE TABLE `mem_enemy` (
  `cid` bigint(20) NOT NULL DEFAULT '0',
  `ecid` bigint(20) NOT NULL DEFAULT '0',
  `friend_type` char(8) NOT NULL DEFAULT '',
  KEY `cid` (`cid`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED;

-- ----------------------------
-- Records of mem_enemy
-- ----------------------------

-- ----------------------------
-- Table structure for `mem_equip`
-- ----------------------------
DROP TABLE IF EXISTS `mem_equip`;
CREATE TABLE `mem_equip` (
  `id` bigint(20) NOT NULL DEFAULT '0' COMMENT '装备唯一ID',
  `base` int(11) NOT NULL DEFAULT '0' COMMENT '装备基础ID',
  `owner` bigint(20) NOT NULL DEFAULT '0',
  `star` int(11) NOT NULL DEFAULT '0' COMMENT '强化等级',
  `starLucky` int(11) NOT NULL DEFAULT '0' COMMENT '强化幸运值',
  `addAttr` int(11) NOT NULL DEFAULT '0' COMMENT '附加属性',
  `UpGradeLucky` int(11) DEFAULT NULL COMMENT '装备升级幸运值',
  `UpQuality` int(11) DEFAULT NULL COMMENT '装备升品幸运值',
  `EquipGem` varchar(50) DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `owner` (`owner`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED;

-- ----------------------------
-- Records of mem_equip
-- ----------------------------

-- ----------------------------
-- Table structure for `mem_exchange_code`
-- ----------------------------
DROP TABLE IF EXISTS `mem_exchange_code`;
CREATE TABLE `mem_exchange_code` (
  `id` int(11) NOT NULL AUTO_INCREMENT COMMENT '序列',
  `code` char(32) NOT NULL DEFAULT '' COMMENT '兑换码',
  `item_id` int(11) NOT NULL DEFAULT '0' COMMENT '兑换物品',
  `used` bigint(20) NOT NULL DEFAULT '0' COMMENT '使用情况',
  `name` char(8) NOT NULL DEFAULT '' COMMENT '使用者名',
  `time` int(11) NOT NULL DEFAULT '0' COMMENT '生成时间',
  PRIMARY KEY (`id`),
  UNIQUE KEY `code` (`code`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED;

-- ----------------------------
-- Records of mem_exchange_code
-- ----------------------------

-- ----------------------------
-- Table structure for `mem_family`
-- ----------------------------
DROP TABLE IF EXISTS `mem_family`;
CREATE TABLE `mem_family` (
  `id` bigint(20) NOT NULL DEFAULT '0' COMMENT '序列',
  `name` char(8) NOT NULL DEFAULT '' COMMENT '家族名',
  `leader_cid` bigint(20) NOT NULL DEFAULT '0' COMMENT '家族长',
  `creator_cid` bigint(20) NOT NULL DEFAULT '0' COMMENT '创建者',
  `create_time` int(11) NOT NULL DEFAULT '0' COMMENT '创建时间',
  `level` int(11) NOT NULL DEFAULT '0' COMMENT '等级',
  `money` int(11) NOT NULL DEFAULT '0' COMMENT '金钱',
  `notice` varchar(100) NOT NULL DEFAULT '' COMMENT '公告',
  `count` int(11) NOT NULL DEFAULT '0' COMMENT '人数',
  `delflag` tinyint(4) NOT NULL DEFAULT '0' COMMENT '删除标记',
  `del_time` int(11) NOT NULL DEFAULT '0' COMMENT '解散时间',
  `auto_agree` tinyint(4) DEFAULT NULL,
  `task_count` int(11) DEFAULT NULL,
  `task_time` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `name` (`name`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED;

-- ----------------------------
-- Records of mem_family
-- ----------------------------

-- ----------------------------
-- Table structure for `mem_family_log`
-- ----------------------------
DROP TABLE IF EXISTS `mem_family_log`;
CREATE TABLE `mem_family_log` (
  `id` bigint(20) NOT NULL COMMENT '序列',
  `type` tinyint(4) NOT NULL,
  `param1` bigint(20) NOT NULL DEFAULT '0' COMMENT '参数1',
  `param2` bigint(20) NOT NULL DEFAULT '0' COMMENT '参数2',
  `param3` bigint(20) NOT NULL DEFAULT '0' COMMENT '参数3',
  `param4` bigint(20) NOT NULL DEFAULT '0' COMMENT '参数4',
  `param5` bigint(20) NOT NULL DEFAULT '0' COMMENT '参数5',
  `time` int(11) NOT NULL DEFAULT '0' COMMENT '操作时间',
  KEY `time` (`time`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED;

-- ----------------------------
-- Records of mem_family_log
-- ----------------------------

-- ----------------------------
-- Table structure for `mem_family_totom`
-- ----------------------------
DROP TABLE IF EXISTS `mem_family_totom`;
CREATE TABLE `mem_family_totom` (
  `totom_id` int(11) NOT NULL DEFAULT '0' COMMENT '图腾ID',
  `family_id` bigint(20) NOT NULL DEFAULT '0' COMMENT '帮派ID',
  `battle` int(11) NOT NULL DEFAULT '0' COMMENT '增加战斗力',
  `start_time` int(11) NOT NULL DEFAULT '0' COMMENT '开始时间',
  PRIMARY KEY (`totom_id`,`family_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED;

-- ----------------------------
-- Records of mem_family_totom
-- ----------------------------

-- ----------------------------
-- Table structure for `mem_family_war`
-- ----------------------------
DROP TABLE IF EXISTS `mem_family_war`;
CREATE TABLE `mem_family_war` (
  `familyid` bigint(20) NOT NULL DEFAULT '0' COMMENT '胜利帮派',
  `wintimes` int(11) NOT NULL DEFAULT '0' COMMENT '胜利次数',
  `time` int(11) NOT NULL DEFAULT '0' COMMENT '军团战时间',
  `familyname` varchar(30) DEFAULT NULL,
  `leadyername` varchar(30) DEFAULT NULL,
  PRIMARY KEY (`time`),
  KEY `owner` (`time`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED;

-- ----------------------------
-- Records of mem_family_war
-- ----------------------------

-- ----------------------------
-- Table structure for `mem_gamble_depot`
-- ----------------------------
DROP TABLE IF EXISTS `mem_gamble_depot`;
CREATE TABLE `mem_gamble_depot` (
  `cid` bigint(20) NOT NULL DEFAULT '0',
  `slot` int(11) NOT NULL DEFAULT '0',
  `id` int(11) NOT NULL DEFAULT '0',
  `type` int(11) NOT NULL DEFAULT '0' COMMENT '类型',
  `count` int(11) NOT NULL DEFAULT '0',
  KEY `cid` (`cid`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED;

-- ----------------------------
-- Records of mem_gamble_depot
-- ----------------------------

-- ----------------------------
-- Table structure for `mem_global_chou_jiang_record`
-- ----------------------------
DROP TABLE IF EXISTS `mem_global_chou_jiang_record`;
CREATE TABLE `mem_global_chou_jiang_record` (
  `Cid` bigint(20) DEFAULT NULL,
  `Name` varchar(50) DEFAULT NULL,
  `ItemClass` int(4) DEFAULT NULL,
  `ItemId` int(11) DEFAULT NULL,
  `ItemCount` int(11) DEFAULT NULL,
  KEY `cid` (`Cid`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;

-- ----------------------------
-- Records of mem_global_chou_jiang_record
-- ----------------------------

-- ----------------------------
-- Table structure for `mem_global_luck_point`
-- ----------------------------
DROP TABLE IF EXISTS `mem_global_luck_point`;
CREATE TABLE `mem_global_luck_point` (
  `Id` int(11) NOT NULL DEFAULT '0',
  `GlobalLuckPint` int(11) unsigned zerofill NOT NULL DEFAULT '00000000000' COMMENT '抽奖全服幸运值',
  PRIMARY KEY (`Id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;

-- ----------------------------
-- Records of mem_global_luck_point
-- ----------------------------

-- ----------------------------
-- Table structure for `mem_hall_of_fame`
-- ----------------------------
DROP TABLE IF EXISTS `mem_hall_of_fame`;
CREATE TABLE `mem_hall_of_fame` (
  `fame_index` int(11) NOT NULL DEFAULT '0' COMMENT '名次',
  `cid` bigint(20) NOT NULL DEFAULT '0' COMMENT '玩家ID',
  `last_cid` bigint(20) NOT NULL DEFAULT '0' COMMENT '上次结算',
  `reward` tinyint(4) NOT NULL DEFAULT '0' COMMENT '领取标记',
  PRIMARY KEY (`fame_index`),
  KEY `fame_index` (`fame_index`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED;

-- ----------------------------
-- Records of mem_hall_of_fame
-- ----------------------------

-- ----------------------------
-- Table structure for `mem_item`
-- ----------------------------
DROP TABLE IF EXISTS `mem_item`;
CREATE TABLE `mem_item` (
  `id` int(11) NOT NULL DEFAULT '0',
  `base` int(11) NOT NULL DEFAULT '0',
  `owner` bigint(20) NOT NULL DEFAULT '0',
  `bind` int(11) NOT NULL DEFAULT '0',
  `expire` int(11) NOT NULL DEFAULT '0',
  `param1` int(11) NOT NULL DEFAULT '0',
  `param2` int(11) NOT NULL DEFAULT '0',
  `param3` int(11) NOT NULL DEFAULT '0',
  `param4` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`),
  KEY `owner` (`owner`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED;

-- ----------------------------
-- Records of mem_item
-- ----------------------------

-- ----------------------------
-- Table structure for `mem_kai_fu_huo_dong`
-- ----------------------------
DROP TABLE IF EXISTS `mem_kai_fu_huo_dong`;
CREATE TABLE `mem_kai_fu_huo_dong` (
  `Rank` int(11) DEFAULT NULL,
  `Type` tinyint(4) DEFAULT NULL,
  `CharId` bigint(20) DEFAULT NULL,
  `CharName` varchar(30) DEFAULT NULL,
  `CharJob` tinyint(4) DEFAULT NULL,
  `CharSex` tinyint(4) DEFAULT NULL,
  `Param` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;

-- ----------------------------
-- Records of mem_kai_fu_huo_dong
-- ----------------------------

-- ----------------------------
-- Table structure for `mem_limit_shop`
-- ----------------------------
DROP TABLE IF EXISTS `mem_limit_shop`;
CREATE TABLE `mem_limit_shop` (
  `ShopId` int(11) NOT NULL DEFAULT '0',
  `LimitCount` int(11) DEFAULT NULL,
  `RefreshTime` int(11) DEFAULT NULL,
  PRIMARY KEY (`ShopId`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;

-- ----------------------------
-- Records of mem_limit_shop
-- ----------------------------

-- ----------------------------
-- Table structure for `mem_mail`
-- ----------------------------
DROP TABLE IF EXISTS `mem_mail`;
CREATE TABLE `mem_mail` (
  `MailId` int(11) NOT NULL COMMENT '邮件id',
  `SysMailId` int(11) DEFAULT NULL,
  `SenderId` bigint(20) DEFAULT NULL,
  `SenderName` varchar(20) DEFAULT NULL,
  `ReceiveId` bigint(20) DEFAULT NULL,
  `ReceiveName` varchar(20) DEFAULT NULL,
  `SendTime` int(11) DEFAULT NULL,
  `HasRead` tinyint(4) DEFAULT NULL,
  `Extract` int(11) DEFAULT NULL,
  `MailTitle` varchar(30) DEFAULT NULL,
  `MailContent` varchar(150) DEFAULT NULL,
  `Item1` varchar(80) DEFAULT NULL,
  `Item2` varchar(80) DEFAULT NULL,
  `Item3` varchar(80) DEFAULT NULL,
  `Item4` varchar(80) DEFAULT NULL,
  `Item5` varchar(80) DEFAULT NULL,
  `Item6` varchar(80) DEFAULT NULL,
  `Param` varchar(80) DEFAULT NULL,
  PRIMARY KEY (`MailId`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;

-- ----------------------------
-- Records of mem_mail
-- ----------------------------

-- ----------------------------
-- Table structure for `mem_new_mail`
-- ----------------------------
DROP TABLE IF EXISTS `mem_new_mail`;
CREATE TABLE `mem_new_mail` (
  `MailId` int(11) NOT NULL AUTO_INCREMENT COMMENT '邮件id',
  `SysMailId` int(11) unsigned DEFAULT NULL,
  `SenderId` bigint(20) DEFAULT NULL,
  `SenderName` varchar(20) DEFAULT NULL,
  `ReceiveId` bigint(20) DEFAULT NULL,
  `ReceiveName` varchar(20) DEFAULT NULL,
  `SendTime` int(11) DEFAULT NULL,
  `HasRead` tinyint(4) DEFAULT NULL,
  `Extract` int(11) DEFAULT NULL,
  `MailTitle` varchar(30) DEFAULT NULL,
  `MailContent` varchar(150) DEFAULT NULL,
  `Item1` varchar(80) DEFAULT NULL,
  `Item2` varchar(80) DEFAULT NULL,
  `Item3` varchar(80) DEFAULT NULL,
  `Item4` varchar(80) DEFAULT NULL,
  `Item5` varchar(80) DEFAULT NULL,
  `Item6` varchar(80) DEFAULT NULL,
  `Param` varchar(80) DEFAULT NULL,
  PRIMARY KEY (`MailId`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

-- ----------------------------
-- Records of mem_new_mail
-- ----------------------------

-- ----------------------------
-- Table structure for `mem_pet`
-- ----------------------------
DROP TABLE IF EXISTS `mem_pet`;
CREATE TABLE `mem_pet` (
  `pid` bigint(20) NOT NULL DEFAULT '0' COMMENT '宠物ID',
  `owner` bigint(20) NOT NULL DEFAULT '0' COMMENT '所有者ID',
  `baseid` int(11) NOT NULL DEFAULT '0' COMMENT '宠物配置ID',
  `name` char(30) NOT NULL DEFAULT '' COMMENT '名称',
  `level` int(11) NOT NULL DEFAULT '0' COMMENT '等级',
  `exp` bigint(20) NOT NULL DEFAULT '0' COMMENT '经验',
  `points` int(11) NOT NULL DEFAULT '0' COMMENT '评分',
  `battle` int(11) NOT NULL DEFAULT '0' COMMENT '战斗力',
  `potential` int(11) NOT NULL DEFAULT '0' COMMENT '潜力值',
  `rein` int(11) NOT NULL DEFAULT '0' COMMENT '转生次数',
  `adj_rein` int(11) NOT NULL DEFAULT '0' COMMENT '最大转生次数',
  `growtimes` int(11) NOT NULL DEFAULT '0' COMMENT '成长率幻化次数',
  `number` int(11) NOT NULL DEFAULT '0' COMMENT '身份牌',
  `phase` tinyint(4) NOT NULL DEFAULT '0' COMMENT '相性',
  `lucky` int(11) NOT NULL DEFAULT '0' COMMENT '幸运值',
  `start_hp` int(11) NOT NULL DEFAULT '0',
  `start_phy_atk_min` int(11) NOT NULL DEFAULT '0',
  `start_phy_atk_max` int(11) NOT NULL DEFAULT '0',
  `start_phy_def` int(11) NOT NULL DEFAULT '0',
  `start_mag_atk_min` int(11) NOT NULL DEFAULT '0',
  `start_mag_atk_max` int(11) NOT NULL DEFAULT '0',
  `start_mag_def` int(11) NOT NULL DEFAULT '0',
  `start_dodge` int(11) NOT NULL DEFAULT '0',
  `start_hitrate` int(11) NOT NULL DEFAULT '0',
  `start_critrate` int(11) NOT NULL DEFAULT '0',
  `start_tenacity` int(11) NOT NULL DEFAULT '0',
  `grow_hp` int(11) NOT NULL DEFAULT '0',
  `grow_phy_atk_min` int(11) NOT NULL DEFAULT '0',
  `grow_phy_atk_max` int(11) NOT NULL DEFAULT '0',
  `grow_phy_def` int(11) NOT NULL DEFAULT '0',
  `grow_mag_atk_min` int(11) NOT NULL DEFAULT '0',
  `grow_mag_atk_max` int(11) NOT NULL DEFAULT '0',
  `grow_mag_def` int(11) NOT NULL DEFAULT '0',
  `grow_dodge` int(11) NOT NULL DEFAULT '0',
  `grow_hitrate` int(11) NOT NULL DEFAULT '0',
  `grow_critrate` int(11) NOT NULL DEFAULT '0',
  `grow_tenacity` int(11) NOT NULL DEFAULT '0',
  `records` varchar(120) NOT NULL DEFAULT '' COMMENT '记录',
  `skills` varchar(300) NOT NULL DEFAULT '' COMMENT '技能',
  `fromway` tinyint(4) NOT NULL DEFAULT '0' COMMENT '来源 0 普通 1 出生携带',
  `bornflag` tinyint(4) NOT NULL DEFAULT '0' COMMENT '出生标记',
  `delflag` tinyint(4) NOT NULL DEFAULT '0' COMMENT '删除标记',
  PRIMARY KEY (`pid`),
  KEY `pid` (`pid`) USING BTREE,
  KEY `cid` (`owner`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED;

-- ----------------------------
-- Records of mem_pet
-- ----------------------------

-- ----------------------------
-- Table structure for `mem_territory_war`
-- ----------------------------
DROP TABLE IF EXISTS `mem_territory_war`;
CREATE TABLE `mem_territory_war` (
  `actid` int(11) NOT NULL DEFAULT '0' COMMENT '活动ID',
  `time` int(11) NOT NULL DEFAULT '0' COMMENT '活动时间',
  `winners` varchar(160) NOT NULL DEFAULT '胜利者',
  PRIMARY KEY (`actid`,`time`),
  KEY `time` (`time`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED;

-- ----------------------------
-- Records of mem_territory_war
-- ----------------------------

-- ----------------------------
-- Table structure for `mem_tou_zi_record`
-- ----------------------------
DROP TABLE IF EXISTS `mem_tou_zi_record`;
CREATE TABLE `mem_tou_zi_record` (
  `Cid` bigint(20) DEFAULT NULL,
  `Name` varchar(20) DEFAULT NULL,
  `RecordType` tinyint(4) DEFAULT NULL,
  `MoneyType` tinyint(4) DEFAULT NULL,
  `MoneyValues` int(11) DEFAULT NULL,
  KEY `cid` (`Cid`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;

-- ----------------------------
-- Records of mem_tou_zi_record
-- ----------------------------

-- ----------------------------
-- Table structure for `mem_yellow_stone`
-- ----------------------------
DROP TABLE IF EXISTS `mem_yellow_stone`;
CREATE TABLE `mem_yellow_stone` (
  `cid` bigint(20) NOT NULL,
  `id` int(11) NOT NULL COMMENT 'cfg_yellow_stone 的 id',
  `get_time` int(11) NOT NULL COMMENT '领取时间'
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;

-- ----------------------------
-- Records of mem_yellow_stone
-- ----------------------------

-- ----------------------------
-- Table structure for `pay_key`
-- ----------------------------
DROP TABLE IF EXISTS `pay_key`;
CREATE TABLE `pay_key` (
  `ip` char(32) NOT NULL DEFAULT '',
  `key` char(32) NOT NULL DEFAULT '',
  PRIMARY KEY (`ip`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED;

-- ----------------------------
-- Records of pay_key
-- ----------------------------

-- ----------------------------
-- Table structure for `pay_log`
-- ----------------------------
DROP TABLE IF EXISTS `pay_log`;
CREATE TABLE `pay_log` (
  `id` int(11) NOT NULL AUTO_INCREMENT COMMENT '序列',
  `oid` char(64) NOT NULL DEFAULT '' COMMENT '订单号',
  `sid` int(11) NOT NULL DEFAULT '0' COMMENT '服务器id',
  `uid` int(11) NOT NULL DEFAULT '0' COMMENT '账户id',
  `passport` char(32) NOT NULL DEFAULT '' COMMENT '账户名',
  `cid` bigint(20) NOT NULL DEFAULT '0' COMMENT '角色id',
  `name` char(8) NOT NULL DEFAULT '' COMMENT '角色名',
  `amount` int(11) NOT NULL DEFAULT '0' COMMENT '充值金额',
  `time` int(11) NOT NULL DEFAULT '0' COMMENT '时间',
  `level` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`),
  UNIQUE KEY `oid` (`oid`) USING BTREE,
  KEY `cid` (`cid`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED;

-- ----------------------------
-- Records of pay_log
-- ----------------------------

-- ----------------------------
-- Table structure for `sys_annoucement_time`
-- ----------------------------
DROP TABLE IF EXISTS `sys_annoucement_time`;
CREATE TABLE `sys_annoucement_time` (
  `id` int(11) NOT NULL DEFAULT '0',
  `weekday` int(11) NOT NULL DEFAULT '0' COMMENT '对应的星期信息',
  `begin_date` int(11) NOT NULL DEFAULT '0',
  `end_date` int(11) NOT NULL DEFAULT '0',
  `hour` int(11) NOT NULL DEFAULT '0' COMMENT '发生的小时',
  `minute` int(11) NOT NULL DEFAULT '0' COMMENT '发生的分钟',
  `annoucement_id` int(11) NOT NULL DEFAULT '0' COMMENT '公告id',
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED;

-- ----------------------------
-- Records of sys_annoucement_time
-- ----------------------------

-- ----------------------------
-- Table structure for `sys_server_config`
-- ----------------------------
DROP TABLE IF EXISTS `sys_server_config`;
CREATE TABLE `sys_server_config` (
  `name` char(32) NOT NULL,
  `value` char(32) NOT NULL,
  `refresh_time` int(11) NOT NULL,
  PRIMARY KEY (`name`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED;

-- ----------------------------
-- Records of sys_server_config
-- ----------------------------

-- ----------------------------
-- Table structure for `sys_unique_id`
-- ----------------------------
DROP TABLE IF EXISTS `sys_unique_id`;
CREATE TABLE `sys_unique_id` (
  `sid` int(11) NOT NULL DEFAULT '0' COMMENT '服务器ID',
  `cid` int(11) NOT NULL DEFAULT '0' COMMENT '人物ID',
  `eid` int(11) NOT NULL DEFAULT '0' COMMENT '装备ID',
  `pid` int(11) NOT NULL DEFAULT '0' COMMENT '宠物ID',
  `fid` int(11) NOT NULL DEFAULT '0' COMMENT '军团ID',
  PRIMARY KEY (`sid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED;

-- ----------------------------
-- Records of sys_unique_id
-- ----------------------------

-- ----------------------------
-- Table structure for `sys_user`
-- ----------------------------
DROP TABLE IF EXISTS `sys_user`;
CREATE TABLE `sys_user` (
  `uid` int(11) NOT NULL DEFAULT '0' COMMENT '用户ID',
  `sid` int(11) NOT NULL DEFAULT '1',
  `passport` char(32) NOT NULL DEFAULT '' COMMENT '通行证，不区分大小写',
  `password` char(32) NOT NULL DEFAULT '' COMMENT '密码（测试使用）',
  `gold` int(11) NOT NULL DEFAULT '0' COMMENT '元宝',
  `sys_gold` int(11) NOT NULL DEFAULT '0' COMMENT '系统元宝',
  `gold_pay` int(11) NOT NULL DEFAULT '0',
  `gold_pay_total` int(11) NOT NULL DEFAULT '0' COMMENT '充值总数',
  `prepay_gold` int(11) NOT NULL DEFAULT '0' COMMENT '删档服换算到真实服的元宝',
  `gold_cost_total` int(11) NOT NULL DEFAULT '0' COMMENT '消费总数',
  `first_week_cost` int(11) NOT NULL DEFAULT '0',
  `second_week_pay` int(11) NOT NULL DEFAULT '0',
  `later_pay` int(11) NOT NULL DEFAULT '0',
  `last_pay_time` int(11) NOT NULL DEFAULT '0',
  `cash` int(11) NOT NULL DEFAULT '0' COMMENT '礼金',
  `create_time` int(11) NOT NULL DEFAULT '0' COMMENT '创建时间',
  `chr_list_time` int(11) NOT NULL DEFAULT '0',
  `chr_create_time` int(11) NOT NULL DEFAULT '0',
  `map_enter_time` int(11) NOT NULL DEFAULT '0',
  `last_login_time` int(11) NOT NULL DEFAULT '0' COMMENT '上次登陆时间',
  `first_login_ip` char(16) NOT NULL DEFAULT '' COMMENT '首次登陆IP',
  `last_login_ip` char(16) NOT NULL DEFAULT '' COMMENT '上次登陆IP',
  `adult` int(11) NOT NULL DEFAULT '1',
  `type` int(11) NOT NULL DEFAULT '0' COMMENT '0.普通.1.内部账号',
  `continue_login_count` int(11) NOT NULL DEFAULT '0' COMMENT '持续登陆天数',
  `total_login_count` int(11) NOT NULL DEFAULT '0' COMMENT '总登陆天数',
  `last_logout_time` int(11) NOT NULL DEFAULT '0',
  `total_online_time` int(11) NOT NULL DEFAULT '0',
  `total_offline_time` int(11) NOT NULL DEFAULT '0',
  `load_create_chr_ui` tinyint(4) DEFAULT '0' COMMENT '创角ui加载完成',
  KEY `uidsid` (`uid`) USING BTREE,
  KEY `passport` (`passport`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED;

-- ----------------------------
-- Records of sys_user
-- ----------------------------

-- ----------------------------
-- Table structure for `sys_user_prevent_wallow`
-- ----------------------------
DROP TABLE IF EXISTS `sys_user_prevent_wallow`;
CREATE TABLE `sys_user_prevent_wallow` (
  `uid` int(11) NOT NULL DEFAULT '0' COMMENT '用户id',
  `sid` int(11) NOT NULL DEFAULT '0' COMMENT '服务id',
  `name` char(31) NOT NULL DEFAULT '' COMMENT '姓名',
  `identitycard` char(19) NOT NULL DEFAULT '' COMMENT '身份证号码',
  `isGrowUp` int(11) NOT NULL DEFAULT '0' COMMENT '是否成年: 0未填写 1.成年 2.未成年人',
  PRIMARY KEY (`uid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;

-- ----------------------------
-- Records of sys_user_prevent_wallow
-- ----------------------------

-- ----------------------------
-- Table structure for `sys_user_token`
-- ----------------------------
DROP TABLE IF EXISTS `sys_user_token`;
CREATE TABLE `sys_user_token` (
  `uid` int(11) NOT NULL DEFAULT '0' COMMENT '用户id',
  `sid` int(11) NOT NULL DEFAULT '0' COMMENT '服务id',
  `token` char(32) NOT NULL DEFAULT '' COMMENT '随机生成的token',
  `create_time` int(11) NOT NULL DEFAULT '0' COMMENT '生成时间',
  `is_yellow_vip` int(11) NOT NULL DEFAULT '0' COMMENT '是否是黄钻用户',
  `is_yellow_year_vip` int(11) NOT NULL DEFAULT '0' COMMENT '是否是年费黄钻用户',
  `yellow_vip_level` int(11) NOT NULL DEFAULT '0' COMMENT '黄钻用户等级',
  `is_yellow_high_vip` int(11) NOT NULL DEFAULT '0' COMMENT '是否是豪华黄钻用户',
  PRIMARY KEY (`uid`)
) ENGINE=MEMORY DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED;

-- ----------------------------
-- Records of sys_user_token
-- ----------------------------

-- ----------------------------
-- Procedure structure for `NewCharId`
-- ----------------------------
DROP PROCEDURE IF EXISTS `NewCharId`;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `NewCharId`(in ServerId int, out OutCharId int)
begin
declare id int default 0;
declare lock_result int;
if get_lock('sp_critical_section_lock',60) then
select sys_unique_id.cid into id from sys_unique_id WHERE sys_unique_id.sid=ServerId LIMIT 1; 
if id>0 then
	set OutCharId = id;
	update sys_unique_id set sys_unique_id.cid = id+1 where sys_unique_id.sid=ServerId;
	select OutCharId;
ELSE
	set OutCharId = 1;
	INSERT INTO sys_unique_id(sid,cid,eid,pid,fid) VALUES (ServerId,2,1,1,1) ON DUPLICATE KEY UPDATE cid=2;
	SELECT OutCharId;
end if;
set lock_result=release_lock('sp_critical_section_lock'); 
else
set OutCharId = 0;
select OutCharId;
end if;	
end
;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `NewEquipId`
-- ----------------------------
DROP PROCEDURE IF EXISTS `NewEquipId`;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `NewEquipId`(in ServerId int, out OutEquipId int)
begin
declare id int default 0;
declare lock_result int;
if get_lock('sp_critical_section_lock',60) then
select sys_unique_id.eid into id from sys_unique_id WHERE sys_unique_id.sid=ServerId LIMIT 1; 
if id>0 then
	set OutEquipId = id;
	update sys_unique_id set sys_unique_id.eid = id+1 where sys_unique_id.sid=ServerId;
	select OutEquipId;
ELSE
	set OutEquipId = 1;
	INSERT INTO sys_unique_id(sid,cid,eid,pid,fid) VALUES (ServerId,1,2,1,1) ON DUPLICATE KEY UPDATE eid=2;
	SELECT OutEquipId;
end if;
set lock_result=release_lock('sp_critical_section_lock'); 
else
set OutEquipId = 0;
select OutEquipId;
end if;	
end
;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `NewFamilyId`
-- ----------------------------
DROP PROCEDURE IF EXISTS `NewFamilyId`;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `NewFamilyId`(in ServerId int, out OutFamilyId int)
begin
declare id int default 0;
declare lock_result int;
if get_lock('sp_critical_section_lock',60) then
select sys_unique_id.fid into id from sys_unique_id WHERE sys_unique_id.sid=ServerId LIMIT 1; 
if id>0 then
	set OutFamilyId = id;
	update sys_unique_id set sys_unique_id.fid = id+1 where sys_unique_id.sid=ServerId;
	select OutFamilyId;
ELSE
	set OutFamilyId = 1;
	INSERT INTO sys_unique_id(sid,cid,eid,pid,fid) VALUES (ServerId,1,1,1,2) ON DUPLICATE KEY UPDATE fid=2;
	SELECT OutFamilyId;
end if;
set lock_result=release_lock('sp_critical_section_lock'); 
else
set OutFamilyId = 0;
select OutFamilyId;
end if;	
end
;;
DELIMITER ;

-- ----------------------------
-- Procedure structure for `NewPetId`
-- ----------------------------
DROP PROCEDURE IF EXISTS `NewPetId`;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `NewPetId`(in ServerId int, out OutPetId int)
begin
declare id int default 0;
declare lock_result int;
if get_lock('sp_critical_section_lock',60) then
select sys_unique_id.pid into id from sys_unique_id WHERE sys_unique_id.sid=ServerId LIMIT 1; 
if id>0 then
	set OutPetId = id;
	update sys_unique_id set sys_unique_id.pid = id+1 where sys_unique_id.sid=ServerId;
	select OutPetId;
ELSE
	set OutPetId = 1;
	INSERT INTO sys_unique_id(sid,cid,eid,pid,fid) VALUES (ServerId,1,1,2,1) ON DUPLICATE KEY UPDATE pid=2;
	SELECT OutPetId;
end if;
set lock_result=release_lock('sp_critical_section_lock'); 
else
set OutPetId = 0;
select OutPetId;
end if;	
end
;;
DELIMITER ;
