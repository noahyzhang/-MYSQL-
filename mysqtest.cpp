#if 0
#include<stdio.h>
#include<mysql.h>
#include<iostream>

int main()
{
	MYSQL mysql; //���ݿ�ṹ��
	MYSQL_RES* res;  //������ṹ��
	MYSQL_ROW row;  //char** ��ά���飬���һ������¼
	mysql_init(&mysql); //��ʼ�����ݿ�

	//mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk"); //���ñ��뷽ʽ

	if (mysql_real_connect(&mysql, "localhost", "root", "1234", "test", 3306, NULL, 0) == NULL)
	{
		printf("����ʧ��!\\n");
	}
	mysql_set_character_set(&mysql, "gbk");
	//res = mysql_list_dbs(&mysql, "%");
	//res = mysql_list_fields(&mysql, "student", "%");
	mysql_query(&mysql, "select * from student"); //��ѯ����
	//res = mysql_store_result(&mysql);  //��ȡ�����
	res = mysql_use_result(&mysql);
	//res = mysql_list_tables(&mysql, "%");
	//printf("New client character set : %s\n", mysql_character_set_name(&mysql));

	while (row = mysql_fetch_row(res))
	{
		printf("%s ", row[0]); //��ӡID
		printf("%s ", row[1]); //��ӡ����
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