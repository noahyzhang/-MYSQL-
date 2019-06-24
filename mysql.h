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

	bool ConnectDB(char* mysqlHost, char* user, char* passwd, char* db); //�������ݿ�
	void DisConnectDB();  //�ر����ݿ�
	bool ExecSql(char* sqlStr); //ִ��sql ���
	bool StoreResult();  //���ز���  select��show��describe��explain �����ִ�еĽ��
	MYSQL_ROW GetNextRow(); //��ȡ��ѯ������е���һ����¼
	void GotoRowsFirst();  // �ƶ������ݼ��Ŀ�ʼ
	void PrintRows(); //��ӡ��¼
	void FreeResult(); //�ͷŲ�ѯ�����ݼ����ڴ���Դ

public:
	MYSQL m_mysql;
	MYSQL_RES *m_query;
	MYSQL_ROW m_row;

	bool m_bConnect;
	int m_num_field;
	int m_num_count;

};
