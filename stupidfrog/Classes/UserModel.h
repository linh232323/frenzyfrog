#ifndef __USER_MODEL_H__
#define __USER_MODEL_H__

#include "cocos2d.h"
#include "lib/sqlite/sqlite3.h"
#include <iostream>
#include "Utils.h"


using namespace std;
using namespace cocos2d;

class User{
private:
	int temp;
	
public:	
	User();
	~User();
	void				init();
	void			SaveData();
	void			LoadData();	
	
	
	static User			&Instance();

	CC_SYNTHESIZE(std::string, id , ID);
	CC_SYNTHESIZE(int, crt_score , CrtScore);
	CC_SYNTHESIZE(int, best_score , BestScore);
	
	double				lastTimeCharge;
	
	static int callback(void *data, int argc, char **argv, char **azColName);


};
#endif