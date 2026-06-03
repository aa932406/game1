/*
Navicat MySQL Data Transfer

Source Server         : localhost
Source Server Version : 50612
Source Host           : localhost:3306
Source Database       : gmuser

Target Server Type    : MYSQL
Target Server Version : 50612
File Encoding         : 65001

Date: 2015-08-12 11:42:23
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for `platform`
-- ----------------------------
DROP TABLE IF EXISTS `platform`;
CREATE TABLE `platform` (
  `id` int(11) NOT NULL,
  `name` varchar(20) NOT NULL,
  `group` int(11) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of platform
-- ----------------------------
INSERT INTO `platform` VALUES ('1', 'shengyou', '1');
INSERT INTO `platform` VALUES ('2', '37wan', '2');

-- ----------------------------
-- Table structure for `server`
-- ----------------------------
DROP TABLE IF EXISTS `server`;
CREATE TABLE `server` (
  `id` int(11) NOT NULL,
  `owner` int(11) NOT NULL,
  `name` varchar(20) NOT NULL,
  `adress` varchar(20) NOT NULL,
  `username` varchar(20) NOT NULL,
  `password` varchar(20) NOT NULL,
  `dbname` varchar(20) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of server
-- ----------------------------
INSERT INTO `server` VALUES ('1', '1', '本地1', 'localhost', 'root', '', 'zhcb');
INSERT INTO `server` VALUES ('2', '1', '本地2', 'localhost', 'root', '', 'zhcb');
INSERT INTO `server` VALUES ('3', '2', '37玩1', '192.168.0.200', 'root', '', 'moyu');
INSERT INTO `server` VALUES ('4', '2', '37玩2', '192.168.0.200', 'root', '', 'moyu');

-- ----------------------------
-- Table structure for `user`
-- ----------------------------
DROP TABLE IF EXISTS `user`;
CREATE TABLE `user` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(20) NOT NULL,
  `password` varchar(20) NOT NULL,
  `group` int(11) NOT NULL,
  `jurisdiction` int(11) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=10 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of user
-- ----------------------------
INSERT INTO `user` VALUES ('1', '123', '456', '1', '1');
INSERT INTO `user` VALUES ('2', 'abc', 'def', '2', '2');
INSERT INTO `user` VALUES ('3', 'admin', '123456', '0', '255');
INSERT INTO `user` VALUES ('4', 'zzz', '123456', '1', '2');
INSERT INTO `user` VALUES ('5', 'aaa', '123456', '2', '2');
INSERT INTO `user` VALUES ('6', 'bbb', '123456', '2', '2');
INSERT INTO `user` VALUES ('9', '333', '123456', '3', '33');
