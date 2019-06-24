#if 0
#include<stdio.h>
#include<mysql.h>
#include<iostream>

int main()
{
	MYSQL mysql; //数据库结构体
	MYSQL_RES* res;  //结果集结构体
	MYSQL_ROW row;  //char** 二维数组，存放一条条记录
	mysql_init(&mysql); //初始化数据库

	//mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk"); //设置编码方式

	if (mysql_real_connect(&mysql, "localhost", "root", "1234", "test", 3306, NULL, 0) == NULL)
	{
		printf("连接失败!\\n");
	}
	mysql_set_character_set(&mysql, "gbk");
	//res = mysql_list_dbs(&mysql, "%");
	//res = mysql_list_fields(&mysql, "student", "%");
	mysql_query(&mysql, "select * from student"); //查询数据
	//res = mysql_store_result(&mysql);  //获取结果集
	res = mysql_use_result(&mysql);
	//res = mysql_list_tables(&mysql, "%");
	//printf("New client character set : %s\n", mysql_character_set_name(&mysql));

	while (row = mysql_fetch_row(res))
	{
		printf("%s ", row[0]); //打印ID
		printf("%s ", row[1]); //打印姓名
		printf("%s ", row[2]); 
		printf("%s \n", row[3]); 
	}

	printf("%lu\n", mysql_field_count(&mysql));

	//MYSQL_FIELD* field;
	//while (field = mysql_fetch_field(res))
	//{
	//	std::cout << field << std::endl;
	//	///printf("field name %s\n", field->name);
	//}

	//printf("%ld student updated", (long)mysql_affected_rows(&mysql));

	unsigned long *lengths;
	unsigned int num_fields;
	unsigned int i;

	mysql_data_seek(res, 0);

	//num_fields = mysql_num_fields(res);
	//while (row = mysql_fetch_row(res))
	//{
	//	lengths = mysql_fetch_lengths(res);
	//	for (i = 0; i < num_fields; ++i)
	//		printf("[%.*s] ", (int)lengths[i], row[i] ? row[i] : "NULL");
	//	std::endl(std::cout);
	//	//num_fields = mysql_num_fields(res);
	//	//lengths = mysql_fetch_lengths(res);

	//	//for (i = 0; i < num_fields; ++i)
	//	//	printf("Column %u is %lu bytes in length.\n", i, lengths[i]);
	//}

	mysql_free_result(res);
	mysql_close(&mysql);
	system("pause");
	return 0;
}
#endif