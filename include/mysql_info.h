#ifndef __MYSQL_H__
#define __MYSQL_H__

#define CONFIG 100

#include "/usr/local/Cellar/mysql/5.7.19/include/mysql/mysql.h"
//#include "mysql.h"

struct mysql_config{
	char database[CONFIG];
	char info_table[CONFIG];
	char user_register[CONFIG];
};

void insert_mysql_register(struct user *user_info, struct mysql_config *mysql_config_info);
void insert_mysql(struct mysql_config *insert_info, User *user_info);
struct mysql_config *read_mysqlconfig(struct mysql_config *info);
void select_mysql_sign_in(struct mysql_config *sign_in, const char *user_name, const char *user_password);
char *return_id(struct mysql_config *return_id);
void alter_table(struct mysql_config *alter, char *queue_name, char *queue_type);
//void mysql_operate(User *user_info);

#endif /* person_mysql_h */
