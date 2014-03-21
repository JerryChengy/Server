#ifndef CW_SQLSTATEMENT_H
#define CW_SQLSTATEMENT_H


const char* sqlSetSqlMode = "set session sql_mode=\"NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION\";";

const char* sqlSetIsolationLevel = "set session transaction isolation level repeatable read;";

const char* sqlFormatSetTimeout = "set session wait_timeout = 60*60*24*60*10;";

const char* sqlSetInnodbLockTimeout = "set session innodb_lock_wait_timeout = 60*2;";

const char* sqlSetCharacterSet = "set names utf8;";
#endif
