#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h> //包含了其它window头文件,为mmysql.h服务，且必须声明在mysql.h前面
#include <mysql.h> //mysql数据库头文件

#pragma warning( disable : 4996)

/*定义数据库相关操作变量*/
MYSQL mysql;          //定义mysql对象
MYSQL_RES *result;    //定义结果集变量
MYSQL_ROW row;        //定义行变量
char ch[2];

void ShowAll();       //显示所有的图书信息
void AddBook();       //添加图书信息
void ModifyBook();    //修改图书信息
void DeleteBook();    //删除图书信息
void QueryBook();     //查询图书信息


//显示菜单
void showmenu()
{
	printf("\n\n\n\n\n");
	printf("\t╔======================================================╗\n");
	printf("\t║            Welcome To ZhangYi Books System           ║\n");
	printf("\t╠======================================================╣\n");
	printf("\t║\t\t 1 - 显示所有图书信息                   ║\n");
	printf("\t║\t\t 2 - 添加图书信息                       ║\n");
	printf("\t║\t\t 3 - 修改图书信息                       ║\n");
	printf("\t║\t\t 4 - 删除图书信息                       ║\n");
	printf("\t║\t\t 5 - 查询图书信息                       ║\n");
	printf("\t║\t\t 6 - 退出                               ║\n");
	printf("\t╚======================================================╝\n");
	printf("\n              ENTER YOUR CHOICE(1-6):");

}

void inquire()  /*询问用户是否显示主菜单*/
{
	printf("\t 显示主菜单?(y/n):");
	scanf("%s", ch);
	if (strcmp(ch, "Y") == 0 || strcmp(ch, "y") == 0)/*判断是否要显示查找到的信息*/
	{
		showmenu();   /*显示菜单*/
	}
	else
	{
		exit(0);
	}
}

void initTable()
{
	if (!mysql_real_connect(&mysql, "localhost", "root", "1234", "db_books", 3306, NULL, 0))
	{
		printf("数据库连接失败");
	}
	mysql_query(&mysql, "create table db_books(id int, bookname varchar(20),author varchar(20),bookconcern varchar(20));");
}

/*显示主菜单，连接数据库*/
int main()
{
	int n;   //定义变量  存储用户输入的编号

	showmenu();   /*显示菜单*/
	mysql_init(&mysql);  //初始化mysql结构
	initTable();
	scanf("%d", &n);/*输入选择功能的编号*/

	while (n)
	{
		mysql_init(&mysql);  //初始化mysql结构

		switch (n)
		{
		case 1:
			ShowAll();    /*调用显示所有图书数据的过程*/
			break;
		case 2:
			AddBook();   /*添加图书信息*/
			break;
		case 3:
			ModifyBook();     /*修改图书信息*/
			break;
		case 4:
			DeleteBook();   /*删除图书信息*/
			break;
		case 5:
			QueryBook();   /*查询图书信息*/
			break;
		case 6:
			exit(0);       /*退出*/
		default:break;
		}
		system("PAUSE");
		system("CLS");
		//inquire();
		showmenu();
		scanf("%d", &n);
	}
}

//显示所有的图书信息
void ShowAll()
{
	//连接数据库
	if (!mysql_real_connect(&mysql, "localhost", "root", "1234", "db_books", 3306, NULL, 0)) //连接数据库成功,返回true
	{
		printf("连接数据库失败！\n");
	}
	else
	{
		//连接数据库成功
		if (mysql_query(&mysql, "select * from db_books")) //查询数据表tb_books中的所有字段 查询成功，返回false
		{
			printf("\n 查询 tb_books 失败!\n"); //连接数据库失败
		}
		else
		{
			result = mysql_store_result(&mysql); //获得结果集
			if (mysql_num_rows(result) != NULL) //获得结果集的行数，若行数不为0，则进入if
			{
				//有记录数据时，才显示记录数据
				printf("\t ════════════════════════════ \n");
				printf("\t                 显 示 所 有 图 书 信 息                  \n");
				printf("\t ════════════════════════════ \n");
				printf("\t  图书编号       图书名         作者        出版社      \n");
				printf("\t -------------------------------------------------------- \n");

				while (row = mysql_fetch_row(result)) //取出结果集中的下一行数据
				{
					//取出结果集中记录
					fprintf(stdout, "\t     %s             %s            %s         %s   \n", \
						row[0], row[1], row[2], row[3]);  //输出这行记录 [相当于从文件中取出数据，所以使用了fprintf]                    
				}
				printf("\t ════════════════════════════ \n");
			}
			else
			{
				printf("\n 没有记录数据! \n");
			}

			mysql_free_result(result); //释放结果集
		}

		mysql_close(&mysql); //释放连接
	}
}

void AddBook()    /*添加图书信息*/
{
	int rowcount;   /*结果集中的行数*/

	char id[10];       /*编号*/
	char *bookname; //图书名称
	char *author; //图书作者
	char *bookconcern;

	char *sql; //数据库字符串
	char dest[500] = { "  " };

	/*连接数据库*/
	if (!mysql_real_connect(&mysql, "localhost", "root", "1234", "db_books", 0, NULL, 0))
	{
		printf("\n\t 不能连接数据库!\n");
	}
	else
	{
		/*数据库连接成功，插入数据*/
		printf("\t ════════════════════════════ \n");
		printf("\t                     添 加 图 书 信 息                    \n");
		printf("\t ════════════════════════════ \n");
		if (mysql_query(&mysql, "select * from db_books"))
		{   //如果查询失败
			printf("\n\t 查询 db_books 数据表失败!\n");
		}
		else
		{
			result = mysql_store_result(&mysql); //获得结果集
			rowcount = (int)mysql_num_rows(result);  //获得行数
			row = mysql_fetch_row(result);       //获取结果集的行  

			printf("\t 图书编号:");
			scanf("%s", id);   /*输入图书编号*/

			if (mysql_num_rows(result) != NULL)
			{
				/*判断输入的编号是否存在*/
				do
				{   //存在相同编号
					if (!strcmp(id, row[0])) //row[0]为每行的第一个元素，即ID，则row[1]则为bookname
					{
						//  printf("%s",row[0]);
						printf("\n\t 记录存在，按任意键继续!\n");
						getch();
						mysql_free_result(result);   /*释放结果集*/
						mysql_close(&mysql);         /*释放连接*/
						return;
					}
				} while (row = mysql_fetch_row(result));
			}

			//给字符指针分配内存
			bookname = (char*)malloc(50);
			author = (char*)malloc(50);
			bookconcern = (char*)malloc(50);

			//不存在相同的编号            
			printf("\t 请输入图书名:");
			scanf("%s", bookname);   /*输入图书名*/

			//将要写入数据库的字符串添加到dest后
			sql = "insert into db_books (ID,bookname,author,bookconcern) values (";
			strcat(dest, sql);
			strcat(dest, "'");
			strcat(dest, id);
			strcat(dest, "', '");
			strcat(dest, bookname);    /*将图书编号追加到sql语句后面*/

			printf("\t 请输入作者:");
			scanf("%s", author);    /*输入作者*/
			strcat(dest, "', '");
			strcat(dest, author);

			printf("\t 请输入出版社:");
			scanf("%s", bookconcern);    /*输入出版社*/
			strcat(dest, "', '");
			strcat(dest, bookconcern);
			strcat(dest, "')");
			printf("%s", dest);

			if (mysql_query(&mysql, dest) != 0) //将dest插入到数据库中(db_books)
			{
				fprintf(stderr, "\t 不能插入记录!", mysql_error(&mysql));
			}
			else
			{
				printf("\t 插入成功!\n");
			}
			mysql_free_result(result);    //释放结果集
		}
		mysql_close(&mysql);          //释放连接
	}
}

void QueryBook()   /*查询图书信息*/
{
	char id[10];   /*结果集中的行数*/
	char *sql;
	char dest[100] = { "  " };

	if (!mysql_real_connect(&mysql, "127.0.0.1", "root", "1234", "db_books", 0, NULL, 0))
	{
		printf("\t 不能连接数据库!\n");
	}
	else
	{
		printf("\t 请输入您想要查询的图书编号:");
		scanf("%s", id);   /*输入图书编号*/
		sql = "select * from db_books where id="; //查询条件
		strcat(dest, sql);
		strcat(dest, id);    /*将图书编号追加到sql语句后面*/

		if (mysql_query(&mysql, dest))
		{   //如果查询失败
			printf("\n 查询 tb_book 数据表失败!\n");
		}
		else
		{
			result = mysql_store_result(&mysql); //获得结果集
			if (mysql_num_rows(result) != NULL)
			{  //有记录的情况,只有有记录取数据才有意义
				printf("\t ════════════════════════════ \n");
				printf("\t                          显示图书信息                      \n");
				printf("\t ════════════════════════════ \n");
				printf("\t图书编号       图书名         作者        出版社      \n");
				printf("\t -------------------------------------------------------- \n");
				while ((row = mysql_fetch_row(result)))
				{   //取出结果集中记录
					fprintf(stdout, "\t   %s             %s             %s          %s   \n", row[0], row[1], row[2], row[3]);  //输出这行记录
				}
				printf("\t ════════════════════════════ \n");
			}
			else
			{
				printf("\t 没有发现要查询的信息!\n");
			}
			mysql_free_result(result);    //释放结果集
		}
		mysql_close(&mysql);          //释放连接
	}
}

//修改图书信息
void ModifyBook()
{
	char id[10];   /*结果集中的行数*/
	char *sql;
	char dest[500] = { "  " };
	char dest1[500] = { "  " };

	char *bookname;
	char *author;
	char *bookconcern;

	if (!mysql_real_connect(&mysql, "127.0.0.1", "root", "1234", "db_books", 0, NULL, 0))
	{
		printf("\t 不能连接数据库!\n");
	}
	else
	{
		/*数据库连接成功*/
		// printf("连接成功");
		printf("\t 请输入您想要修改的图书编号.");

		scanf("%s", id);   /*输入图书编号*/
		sql = "select * from db_books where id=";
		strcat(dest, sql);
		strcat(dest, id);    /*将图书编号追加到sql语句后面*/

		//printf("%s\n",dest);

		/*查询该图书信息是否存在*/
		if (mysql_query(&mysql, dest))
		{   //如果查询失败
			printf("\n  查询 db_books 数据表失败! \n");
		}
		else
		{
			result = mysql_store_result(&mysql); //获得结果集
			if (mysql_num_rows(result) != NULL)
			{
				//有记录的情况,只有有记录取数据才有意义
				printf("\t 发现记录信息,是否显示?(y/n) ");
				scanf("%s", ch);
				if (strcmp(ch, "Y") == 0 || strcmp(ch, "y") == 0)/*判断是否要显示查找到的信息*/
				{
					printf("\t ════════════════════════════ \n");
					printf("\t               ***** 显示图书信息 *****                   \n");
					printf("\t ════════════════════════════ \n");
					printf("\t图书编号       图书名         作者        出版社      \n");
					printf("\t -------------------------------------------------------- \n");
					while ((row = mysql_fetch_row(result)))
					{   //取出结果集中记录
						fprintf(stdout, "\t   %s             %s             %s          %s   \n", row[0], row[1], row[2], row[3]);  //输出这行记录
					}
					printf("\t ════════════════════════════ \n");
				}


				printf("\t Modify?(y/n)");
				scanf("%s", ch);
				if (strcmp(ch, "Y") == 0 || strcmp(ch, "y") == 0)    /*判断是否需要录入*/
				{


					sql = "update db_books set bookname= '";
					strcat(dest1, sql);
					//   printf("%s",sql);
					bookname = (char*)malloc(20);
					author = (char*)malloc(20);
					bookconcern = (char*)malloc(20);

					printf("\t 图书名:");
					scanf("%s", bookname);   /*输入图书名*/

					strcat(dest1, bookname);
					//  printf("%s",&bookname);

					printf("\t 作者:");
					scanf("%s", author);    /*输入作者*/
					strcat(dest1, "', author= '");
					strcat(dest1, author);    /*追加sql语句*/

					printf("\t 出版社:");
					scanf("%s", bookconcern);    /*输入出版社*/
					strcat(dest1, "', bookconcern = '");
					strcat(dest1, bookconcern);    /*追加sql语句*/

					strcat(dest1, "' where id= ");
					strcat(dest1, id);

					//printf("%s",dest1);

					if (mysql_query(&mysql, dest1) != 0)
					{
						fprintf(stderr, "\t 不能修改记录!\n", mysql_error(&mysql));
					}
					else
					{
						printf("\t 修改成功!\n");
					}
				}

			}
			else
			{
				printf("\t 没有发现要修改的信息!\n");
			}
		}
		mysql_free_result(result);          //释放结果集
	}
	mysql_close(&mysql);     //释放连接
}

void DeleteBook()   /*删除图书信息*/
{
	char id[10];   /*结果集中的行数*/
	char *sql;
	char dest[100] = { "  " };
	char dest1[100] = { "  " };
	if (!mysql_real_connect(&mysql, "127.0.0.1", "root", "1234", "db_books", 0, NULL, 0))
	{
		printf("\t 不能连接数据库!\n");
	}
	else
	{
		printf("\t 请输入您想要删除的图书编号. ");
		scanf("%s", id);   /*输入图书编号*/
		sql = "select * from tb_book where id=";
		strcat(dest, sql);
		strcat(dest, id);    /*将图书编号追加到sql语句后面*/
		//printf("%s\n",dest);

		/*查询该图书信息是否存在*/
		if (mysql_query(&mysql, dest))
		{   //如果查询失败
			printf("\n 查询 tb_book 数据表失败! \n");
		}
		else
		{
			result = mysql_store_result(&mysql); //获得结果集
			if (mysql_num_rows(result) != NULL)
			{  //有记录的情况,只有有记录取数据才有意义
				printf("\t 发现记录信息,是否显示?(y/n) ");
				scanf("%s", ch);
				if (strcmp(ch, "Y") == 0 || strcmp(ch, "y") == 0)/*判断是否要显示查找到的信息*/
				{
					printf("\t ════════════════════════════ \n");
					printf("\t               ***** 显示图书信息 *****                   \n");
					printf("\t ════════════════════════════ \n");
					printf("\t图书编号       图书名         作者        出版社      \n");
					printf("\t -------------------------------------------------------- \n");
					while ((row = mysql_fetch_row(result)))
					{   //取出结果集中记录
						fprintf(stdout, "\t   %s             %s             %s          %s   \n", row[0], row[1], row[2], row[3]);  //输出这行记录
					}
					printf("\t ════════════════════════════ \n");
				}

				printf("\t 是否删除?(y/n) ");
				scanf("%s", ch);
				if (strcmp(ch, "Y") == 0 || strcmp(ch, "y") == 0)    /*判断是否需要录入*/
				{
					sql = "delete from tb_book where ID= ";
					printf("%s", dest1);
					strcat(dest1, sql);
					strcat(dest1, id);
					// printf("%s",dest1);

					if (mysql_query(&mysql, dest1) != 0)
					{
						fprintf(stderr, "\t 不能删除记录! \n", mysql_error(&mysql));
					}
					else
					{
						printf("\t 删除成功!\n");
					}
				}
			}
			else
			{
				printf("\t 没有发现要删除的信息!\n");
			}
		}
		mysql_free_result(result);    //释放结果集
	}
	mysql_close(&mysql);
}