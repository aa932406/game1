#!/bin/sh

MXMLC=/root/flex_sdk_4.0.0/bin/mxmlc
PROJECT=/root/kunlun_src_trunk_client_ZhuShen
SRC=$PROJECT/src
OUTPUT=$PROJECT/ouput
SVN=svn://127.0.0.1/kunlun/src/trunk/client/ZhuShen
WWW=/web/www

svn co $SVN --username louhuang --password louhuang $PROJECT

$MXMLC -load-config $PROJECT/compile-config.xml --incremental --source-path=$SRC $SRC/Main.mxml --output=$OUTPUT/Main.swf

\cp $OUTPUT/Main.swf $WWW/kunlun -rf

svn co $SVN/res $WWW/res


