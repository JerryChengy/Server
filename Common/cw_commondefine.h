#ifndef CW_COMMONDEFINE_H
#define CW_COMMONDEFINE_H

#define FD_SETSIZE 1024
#include <WinSock2.h>
#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <direct.h>
#include <time.h>
#include <fstream>
#include <io.h>
#include <iostream>
#include <sys/stat.h>
#include <stdlib.h>
#include <map>
using namespace std;

#pragma warning(disable: 4996)


#define SAFE_DELETE(X) {delete X; X=0;}
//#define Assert(x) if(x) { Ass}
#endif