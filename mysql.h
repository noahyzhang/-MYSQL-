#pragma once
#include<stdio.h>
#include<string.h>
#include<string>
#include<iostream>
#include<mysql.h>
#include<mysqld_error.h>

class CMySQL
{
public:
	CMySQL();
	~CMySQL();

	bool ConnectDB(char* mysqlHost, char* user, char* passwd, char* db); //连接数据库
	void DisConnectDB();  //关闭数据库
	bool ExecSql(char* sqlStr); //执行sql 语句
	bool StoreResult();  //返回查找  select、show、describe、explain 等语句执行的结果
	MYSQL_ROW GetNextRow(); //获取查询结果集中的下一条记录
	void GotoRowsFirst();  // 移动到数据集的开始
	void PrintRows(); //打印记录
	void FreeResult(); //释放查询的数据集的内存资源

public:
	MYSQL m_mysql;
	MYSQL_RES *m_query;
	MYSQL_ROW m_row;

	bool m_bConnect;
	int m_num_field;
	int m_num_count;

};
