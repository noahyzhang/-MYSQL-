#define _CRT_SECURE_NO_WARNINGS
#include"mysql.h"
#include<stdlib.h>

#if 0
int main(int argc, char **argv)
{
	char strSQL[1024];//����sql���
	char dbUrl[33]; //���ݿ�ip
	char dbUser[256]; //���ݿ��û���
	char dbPass[256]; //���ݿ�����
	char dbName[256]; //���ݿ�����

	CMySQL theMySql; //CMySql��һ������
	MYSQL_ROW m_row = NULL; //�����¼��MYSQL_ROW���Զ��������,���ڱ���ÿһ�еĽ��

	//��ʼ������
	memset(strSQL, 0, sizeof(strSQL));
	memset(dbUrl, 0, sizeof(dbUrl));
	memset(dbUser, 0, sizeof(dbUser));
	memset(dbPass, 0, sizeof(dbPass));
	memset(dbName, 0, sizeof(dbName));


	strcpy(dbUrl, "localhost");
	strcpy(dbUser, "root");
	strcpy(dbPass, "1234");
	strcpy(dbName, "test");



	//�������ݿ�
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
		//ִ��sql���
		if (theMySql.ExecSql(strSQL) != true)  //ִ�в��ɹ���5����ִ��
		{
			Sleep(5);
			continue;
		}
		break;
	}
	theMySql.PrintRows();

	{
		//������������������ִ��sql����з��ؽ��ʱ
		if (theMySql.StoreResult() != true)
		{
			goto __RET;
		}

		printf("select m_num_count=%d m_num_field=%d\n", theMySql.m_num_count, theMySql.m_num_field);
		//printf ("mysql_error(&mysql)=%s\n", mysql_error(&theMySql));

		//��ȡ�����
		while ((m_row = theMySql.GetNextRow()) != NULL)
		{
			printf("vs_name:%s\n", m_row[57]);
		}

		//�ͷŽ����,���з��ؽ��ʱ�����ͷţ�һ���������Ҫ�ͷ�
		theMySql.FreeResult();
	}

__RET:
	theMySql.DisConnectDB();
	return -1;

}
#endif