#!/bin/sh

OUTPUT=/root/kunlun_src_trunk_client_ZhuShen/res/config/
SVN=svn://127.0.0.1/kunlun/src/trunk/client/ZhuShen
XMLCONVERTER=/root/xmlconverter/xmlconverter

function dump_cfg_data_as_xml()
{
	mysqldump -ukunlun -pkunlun kunlun $1 -X | $XMLCONVERTER > $OUTPUT$1".xml"
}

dump_cfg_data_as_xml cfg_skill_effect
dump_cfg_data_as_xml cfg_skill_info
dump_cfg_data_as_xml cfg_skill_result

svn commit --username louhuang --password louhuang -m "更新配置文件" $OUTPUT

