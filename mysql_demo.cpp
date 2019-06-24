#define _CRT_SECURE_NO_WARNINGS
#include"mysql.h"
#include<stdlib.h>

#if 0
int main(int argc, char **argv)
{
	char strSQL[1024];//保存sql语句
	char dbUrl[33]; //数据库ip
	char dbUser[256]; //数据库用户名
	char dbPass[256]; //数据库密码
	char dbName[256]; //数据库名称

	CMySQL theMySql; //CMySql的一个对象
	MYSQL_ROW m_row = NULL; //保存记录，MYSQL_ROW中自定义的类型,用于保存每一行的结果

	//初始化变量
	memset(strSQL, 0, sizeof(strSQL));
	memset(dbUrl, 0, sizeof(dbUrl));
	memset(dbUser, 0, sizeof(dbUser));
	memset(dbPass, 0, sizeof(dbPass));
	memset(dbName, 0, sizeof(dbName));


	strcpy(dbUrl, "localhost");
	strcpy(dbUser, "root");
	strcpy(dbPass, "1234");
	strcpy(dbName, "test");



	//连接数据库
	if (theMySql.ConnectDB(dbUrl, dbUser, dbPass, dbName) != true)
	{
		printf("can not connect server %s db\n", dbUrl);
		return -1;
	}
	printf("connect db success!\n");
	int i = 1;
	while (1)
	{
		memset(strSQL, 0, sizeof(strSQL));
		snprintf(strSQL, sizeof(strSQL), "select * from student");

		i++;
		//执行sql语句
		if (theMySql.ExecSql(strSQL) != true)  //执行不成功过5秒在执行
		{
			Sleep(5);
			continue;
		}
		break;
	}
	theMySql.PrintRows();

	{
		//保存结果集，此项用于执行sql语句有返回结果时
		if (theMySql.StoreResult() != true)
		{
			goto __RET;
		}

		printf("select m_num_count=%d m_num_field=%d\n", theMySql.m_num_count, theMySql.m_num_field);
		//printf ("mysql_error(&mysql)=%s\n", mysql_error(&theMySql));

		//获取结果集
		while ((m_row = theMySql.GetNextRow()) != NULL)
		{
			printf("vs_name:%s\n", m_row[57]);
		}

		//释放结果集,在有返回结果时，才释放，一般操作不需要释放
		theMySql.FreeResult();
	}

__RET:
	theMySql.DisConnectDB();
	return -1;

}
#endif