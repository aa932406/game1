#pragma once
typedef struct MYSQL {} MYSQL;
typedef struct MYSQL_RES {} MYSQL_RES;
typedef struct MYSQL_ROW { char** data; } MYSQL_ROW;
typedef struct MYSQL_FIELD { const char* name; } MYSQL_FIELD;
typedef int my_ulonglong;