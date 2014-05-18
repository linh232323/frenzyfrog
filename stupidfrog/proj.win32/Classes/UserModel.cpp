#include "UserModel.h"


User::User(){
	
}
User::~User(){	

}
User& User::Instance(){
	static User _instance;
	return _instance;
}
void User::init(){
	
}

void User::SaveData(){		
	char* errMsg = NULL;
	CCString *sqlstr;
	int result;
	sqlite3* pDB;
	std::string dbPath = CCFileUtils::sharedFileUtils()->getWritablePath();
	dbPath.append("data.db");
	
	result = sqlite3_open(dbPath.c_str(),&pDB);
	if (result != SQLITE_OK){		
		CCLOG("OPENING WRONG, %d, MSG:%s",result,errMsg);
		return;
	}

	sqlstr = CCString::createWithFormat("UPDATE `users` SET best_score=%d,crt_score=%d,best_score2=%d,crt_score2=%d WHERE id='%s'",
		User::Instance().getBestScore(),
		User::Instance().getCrtScore(),
		User::Instance().getBestScore2(),
		User::Instance().getCrtScore2(),
		User::Instance().getID().c_str());			 	

	result = sqlite3_exec(pDB,(char*)sqlstr->getCString(),NULL,NULL,&errMsg);
	if( result != SQLITE_OK ){
		 CCLOG("SQL error: %s\n", errMsg);
		sqlite3_free(errMsg);
	}else{
		CCLOG( "Update record successfully\n");
	}

	sqlite3_close(pDB);
	
}
void User::LoadData(){
    char* errMsg = NULL;
	const char* data = "Callback function called";
	CCString *sqlstr;
	int result;
	sqlite3* pDB;
	std::string dbPath = CCFileUtils::sharedFileUtils()->getWritablePath();	
	dbPath.append("Settings.db");
	
	result = sqlite3_open(dbPath.c_str(),&pDB);
	if (result != SQLITE_OK){		
		CCLOG("OPENING WRONG, %d, MSG:%s",result,errMsg);
		return;
	}

	sqlstr = CCString::createWithFormat("CREATE TABLE `users` (id varchar(32) primary key,crt_score INT,best_score INT,crt_score2 INT,best_score2 INT)");
	result = sqlite3_exec(pDB,(char*)sqlstr->getCString(),NULL,NULL,&errMsg);
	if( result != SQLITE_OK ){
		CCLOG("SQL: error: %s\n", errMsg);	
		sqlite3_free(errMsg);
	}
	

	sqlstr = CCString::create("select * from `users`");	
	result = sqlite3_exec(pDB,(char*)sqlstr->getCString() , User::callback, (void*)data,&errMsg);
	if(result != SQLITE_OK)
	{	
		CCLOG("SQL: error: %s\n", errMsg);
		sqlite3_free(errMsg);				
	}

	if(User::Instance().getBestScore() == 0){
		User::Instance().setID(Utils::getUniqueId());
		sqlstr = CCString::createWithFormat("INSERT INTO `users` VALUES ('%s',%d,%d,%d,%d)", getID().c_str(), 0,0,999999,99999);						
		result = sqlite3_exec(pDB,(char*)sqlstr->getCString(),NULL,NULL,&errMsg);
		if( result != SQLITE_OK ){
			CCLOG("SQL error: %s\n", errMsg);
			sqlite3_free(errMsg);
		}	
	}
	sqlite3_close(pDB);
}
int User::callback(void *data, int argc, char **argv, char **azColName){  
   for(int i=0; i<argc; i++){
      if(strcmp(azColName[i] , "id") == 0){
		  User::Instance().id = argv[i];
	  }else if (strcmp(azColName[i] , "crt_score") == 0){
		  User::Instance().setCrtScore(atoi(argv[i]));
	  }else if(strcmp(azColName[i] , "best_score") ==0){
		  User::Instance().setBestScore(atoi(argv[i]));
	  }else if(strcmp(azColName[i] , "crt_score2") ==0){
		  User::Instance().setCrtScore2(atoi(argv[i]));
	  }else if(strcmp(azColName[i] , "best_score2") ==0){
		  User::Instance().setBestScore2(atoi(argv[i]));
	  }	   
   }   
   return 0;
}

