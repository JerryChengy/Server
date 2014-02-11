#ifndef CW_CONST_H
#define CW_CONST_H

const int SECONDS_PER_HOUR = 3600;
const int SERVER_TIME_ZONE = 8;

const int MAX_FILE_PATH = 128;	//文件路径最大长度
const int MAX_LOG_FILE_COUNT = 10;

const int MAX_FILE_NAME_LEN = 64;//所读文件名称最大长度
const int MAX_COLUMN_TYPE_TEXT_LEN = 16;//表格列类型字符串最大长度
const int MAX_COLUMN_COUNT = 300; //表格最大列数目
const int MAX_LINE_COUNT = 500;	  //表格最大行数目
const int MAX_NAME_LEN = 32;	  //名称最大长度
const int MAX_TITLE_LEN = 32;	  //称号最大长度
const int BUFF_LEN_16K = 1024*16; //局部buff长度
const int BUFF_LEN_1024 = 1024;	  //局部buff长度
const int BUFF_LEN_512  = 512;	  //局部buff长度
const int BUFF_LEN_256  = 256;
const int BUFF_LEN_128  = 128;
const int BUFF_LEN_32 = 32;
const int MAX_LINE_CHAR_COUNT = 1024;	//每行的最多字符个数
const int MAX_BLOCK_CHAR_COUNT = MAX_LINE_CHAR_COUNT;  //每块的最多字符个数（块与块之间用TAB键隔开）
const int HEAD_LINE_COUINT = 2;	   //表格文件中头行数（非有效数据行）

#endif
