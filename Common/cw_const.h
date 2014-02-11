#ifndef CW_CONST_H
#define CW_CONST_H

const int SECONDS_PER_HOUR = 3600;
const int SERVER_TIME_ZONE = 8;

const int MAX_FILE_PATH = 128;	//�ļ�·����󳤶�
const int MAX_LOG_FILE_COUNT = 10;

const int MAX_FILE_NAME_LEN = 64;//�����ļ�������󳤶�
const int MAX_COLUMN_TYPE_TEXT_LEN = 16;//����������ַ�����󳤶�
const int MAX_COLUMN_COUNT = 300; //����������Ŀ
const int MAX_LINE_COUNT = 500;	  //����������Ŀ
const int MAX_NAME_LEN = 32;	  //������󳤶�
const int MAX_TITLE_LEN = 32;	  //�ƺ���󳤶�
const int BUFF_LEN_16K = 1024*16; //�ֲ�buff����
const int BUFF_LEN_1024 = 1024;	  //�ֲ�buff����
const int BUFF_LEN_512  = 512;	  //�ֲ�buff����
const int BUFF_LEN_256  = 256;
const int BUFF_LEN_128  = 128;
const int BUFF_LEN_32 = 32;
const int MAX_LINE_CHAR_COUNT = 1024;	//ÿ�е�����ַ�����
const int MAX_BLOCK_CHAR_COUNT = MAX_LINE_CHAR_COUNT;  //ÿ�������ַ������������֮����TAB��������
const int HEAD_LINE_COUINT = 2;	   //����ļ���ͷ����������Ч�����У�

#endif
