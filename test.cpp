//#include "stdio.h"
//#include "mysql.h"
//#include <iostream>
////#pragma comment(lib, "libmysql.lib")
//using namespace std;
//
//int main()
//{
//	MYSQL * con; //= mysql_init((MYSQL*) 0); 
//	MYSQL_RES *res;
//	MYSQL_ROW row;
//	char tmp[400];
//	//database configuartion
//	char dbuser[30] = "root";
//	char dbpasswd[30] = "1234"; // it must be    changed
//	char dbip[30] = "localhost";
//	char dbname[50] = "test";
//	char tablename[50] = "student";
//	char *query = NULL;
//
//	int rt;//return value  
//	unsigned int t;
//
//	int count = 0;
//
//	con = mysql_init((MYSQL*)0);
//	std::cout << "1111111111111111111" << std::endl;
//	if (con != NULL && mysql_real_connect(con, dbip, dbuser, dbpasswd, dbname, 3306, NULL, 0)) {
//		std::cout << "H2222222222222222222" << std::endl;
//		if (!mysql_select_db(con, dbname)) {
//			std::cout << "3333333333333333" << std::endl;
//			printf("Select successfully the database!\n");
//			con->reconnect = 1;
//			query = (char*)"set names \'GBK\'";
//			rt = mysql_real_query(con, query, strlen(query));
//			if (rt) {
//				printf("Error making query: %s !!!\n", mysql_error(con));
//			}
//			else {
//				printf("query %s succeed!\n", query);
//			}
//		}
//	}
//	else {
//		MessageBoxA(NULL, "Unable to connect the database,check your configuration!", "", NULL);
//	}
//
//	//sprintf(tmp, "insert into %s values(%s,%d,%d)", tablename, "null", x, y); //注意如何向具有自增字段的数据库中插入记录
//	sprintf_s(tmp, "insert into bl values(null,'x','x','x','x')");
//
//
//	rt = mysql_real_query(con, tmp, strlen(tmp));
//	if (rt)
//	{
//	printf("Error making query: %s !!!\n", mysql_error(con));
//	}
//	else
//	{
//		printf("%s executed!!!\n", tmp);
//	}
//
//	sprintf_s(tmp, "select * from %s", tablename);
//	rt = mysql_real_query(con, tmp, strlen(tmp));
//	if (rt)
//	{
//		printf("Error making query: %s !!!\n", mysql_error(con));
//	}
//	else
//	{
//		printf("%s executed!!!\n", tmp);
//	}
//	res = mysql_store_result(con);//将结果保存在res结构体中
//
//	while (row = mysql_fetch_row(res)) {
//		for (t = 0; t < mysql_num_fields(res); t++) {
//			printf("%s  ", row[t]);
//		}
//		printf(".............\n");
//		count++;
//	}
//
//	printf("number of rows %d\n", count);
//	printf("mysql_free_result...\n");
//	mysql_free_result(res);
//	mysql_close(con);
//	system("pause");
//	return 0;
//}


