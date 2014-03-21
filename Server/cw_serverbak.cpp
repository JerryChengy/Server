
//
//#include <assert.h>  
//#include <string.h>  
//#include <leveldb/db.h>  
//#include <iostream>  
//#include "cw_testdata.h"
//
//int main(){  
//	leveldb::DB* db;  
//	leveldb::Options options;  
//	options.create_if_missing = true;  
//	leveldb::Status status = leveldb::DB::Open(options,"/tmp/testdb", &db);  
//	assert(status.ok());  
//
//	//write key1,value1  
//	std::string key="key";  
//	/*HumanData data;
//	data.m_ID = 999;
//	leveldb::Slice slice((char*)(void*)&data, sizeof(data));
//
//	status = db->Put(leveldb::WriteOptions(), key,slice);  
//	assert(status.ok());  */
//
//	std::string value;
//	status = db->Get(leveldb::ReadOptions(), key, &value);  
//	assert(status.ok());  
//
//	HumanData data1;
//	memcpy(&data1, value.c_str(), sizeof(data1));
//	std::cout<<data1.m_ID<<std::endl;  
//	//std::string key2 = "key2";  
//
//	////move the value under key to key2  
//
//	//status = db->Put(leveldb::WriteOptions(),key2,value);  
//	//assert(status.ok());  
//	//status = db->Delete(leveldb::WriteOptions(), key);  
//
//	//assert(status.ok());  
//
//	//status = db->Get(leveldb::ReadOptions(),key2, &value);  
//
//	//assert(status.ok());  
//	//std::cout<<key2<<"==="<<value<<std::endl;  
//
//	//status = db->Get(leveldb::ReadOptions(),key, &value);  
//
//	//if(!status.ok()) std::cerr<<key<<"  "<<status.ToString()<<std::endl;  
//	//else std::cout<<key<<"==="<<value<<std::endl;  
//
//	delete db;  
//	getchar();
//	return 0;  
//}  
