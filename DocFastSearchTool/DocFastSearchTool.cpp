#include"Common.h"
#include"Sysutil.h"
#include"sqlite3.h"
#include"DataManager.h"
#include"ScanManager.h"
#include"Sysframe.h"
const char* title = "文档快速搜索工具";
int main(int argc, char* argv[])
{
	const string& path = "C:\\Users\\longkangJack\\Desktop\\pRO";
	//const string &path = "C:\\";
	//创建扫描实例
	ScanManager::CreateInstance(path).ScanDirectory(path);
	//创建搜索实例
	DataManager &dm = DataManager::GetInstance();
	vector<pair<string, string>> doc_path;
	string key;
	while (1)
	{
		DrawFrame(title);
		DrawMenu();
		cin >> key;
		if (key == "exit")
			break;
		dm.Search(key, doc_path);
		int init_row = 5; //由界面决定
		int count = 0;
		/*string prefix, highlight, suffix;*/
		for (const auto& e : doc_path)
		{
			//string doc_name = e.first;
			//string doc_path = e.second;
			//DataManager::SplitHighlight(doc_name, key, prefix, highlight, suffix);
			//SetCurPos(2, init_row + count++);
			////printf("%-31s", prefix.c_str());
			//cout << prefix;
			//ColourPrintf(highlight.c_str());
			//cout << suffix;
			SetCurPos(2,init_row+count++);
			//printf("%-50s", doc_path.c_str());
		printf("%-31s%-50s\n",e.first.c_str(), e.second.c_str());
		}
		SystemEnd();
		system("pause");
	}
	//SystemEnd();
	return 0;
}
/*void Test_DirectionList()
{
	const string& path = "C:\\Users\\longkangJack\\Desktop\\c++项目1\\DocFastSearchTool";
	vector<string> subfile, subdir;
	DirectionList(path, subfile, subdir);
	for (const auto& e : subfile)
		cout << e << endl;
	for (const auto& e : subdir)
		cout << e << endl;
}
void Test_Sqlite()
{
	//数据打开
	sqlite3* db;
	int rc = sqlite3_open("test.db", &db);
	if (rc != SQLITE_OK)
		printf("Open database failed.\n");
	else
		printf("Open database successed.\n");
	//操作数据库
	string sql = "select * from my_tb";
	char** result;
	int row;
	int col;
	char* zErrMsg = 0;
	//打印数据库
	sqlite3_get_table(db, sql.c_str(), &result, &row, &col, &zErrMsg);
	for (int i = 0; i <= row; ++i)
	{
		for (int j = 0; j < col; ++j)
		{
			//cout<<*((result+(i*col)+j))<<"  ";
			printf("%-5s", *(result + (i * col) + j));
		}
		cout << endl;
	}
	//cout<<endl;
	sqlite3_free_table(result);
	//关闭数据库
	sqlite3_close(db);
}
void Test_SqliteManager()
{
	SqliteManager sm;
	sm.Open("doc.db");
	/*string sql = "create table if not exists doc_tb(id integer primary key autoincrement, doc_name text, doc_path text)";
	sm.ExecuteSql(sql);*/
	//string sql1 = "insert into doc_tb values(null, 'stl.pdf', 'c:\\')";
	//sm.ExecuteSql(sql1);
//	string sql = "select * from doc_tb";
//	int row = 0, col = 0;
//	char** ppRet = 0;
//	sm.GetResultTable(sql, row, col, ppRet);
//	for (int i = 0; i <= row; ++i)
//	{
//	    for (int j = 0; j < col; ++j)
//		{
//			printf("%-10s", *(ppRet + (i * col) + j));
//		}
//		printf("\n");
//	}
//	sqlite3_free_table(ppRet);
//}
//void Test_Log()
//{
//	//char name[] = "hello world!\n";
//	FILE* fp = fopen("Test.txt","w");
//	if (fp == NULL)
//	{
//
//		TRACE_LOG("Open File Error.");
//		return;
//	}
//	else
//	    //fputs(name,fp);
//		TRACE_LOG("Open File Success.");
//	fclose(fp);
//}
//void Test_Map()
//{
	//映射
//	pair<int, string> p1 = { 1, "abc" };
//	pair<int, string> p2 = { 5, "xyz" };
//    pair<int, string> p3 = { 3, "lmn" };
//	pair<int, string> p4 = { 2, "opq" };
//	pair<int, string> p5 = { 9, "hjk" };
//	pair<int, string> p6 = { 7, "rty" };
//	//cout<<p1.first<<" : "<<p1.second<<endl;
//	map<int, string> mp;
//	mp.insert(p1);
//	mp.insert(p2);
//	mp.insert(p3);
//	mp.insert(p4);
//	mp.insert(p5);
//	mp.insert(p6);
//  for (const auto& e : mp)
//		cout << e.first << " : " << e.second << endl;
//}
//void Test_Scan()
//{
//	const string& path = "C:\\Users\\longkangJack\\Desktop\\pRO";
//	ScanManager sm;
//	sm.ScanDirectory(path);
//}
/*static int callback(void* data, int argc, char** argv, char** azColName)
{
	int i;
	fprintf(stderr, "%s: \n", (const char*)data);
	for (i = 0; i < argc; i++)
	{
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}
void Test_Sqlite()
{
	//数据打开
	sqlite3* db;
	int rc = sqlite3_open("test.db", &db);
	if (rc != SQLITE_OK)
		printf("Open database failed.\n");
	else
		printf("Open database successed.\n");
	//操作数据库
	char* zErrMsg = 0;
	const char* data = "Callback function called";
	//sqlite3_exec(sqlite3*, const char *sql, sqlite_callback, void *data, char **errmsg)；
	//string sql = "create table you_tb(id int, name varchar(20), path varchar(100))";
	//string sql = "insert into you_tb values(1, 'abc', 'c:\\')";
	string sql = "select id, name, path from my_tb where id=2";
	//rc = sqlite3_exec(db, sql.c_str(), 0, 0, &zErrMsg);
	rc = sqlite3_exec(db, sql.c_str(), callback, (void*)data, &zErrMsg);
	if (rc != SQLITE_OK)
	{
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else
	{
		//fprintf(stdout, "Table created successfully\n");
		//fprintf(stdout, "Insert Data successfully\n");
		fprintf(stdout, "Select Data successfully\n");
	}
	sqlite3_close(db);
}*/
/*void Test_Search()
{
	const string& path ="C:\\Users\\longkangJack\\Desktop\\pRO";
	//创建扫描实例
	ScanManager::CreateInstance(path).ScanDirectory(path);
	//sm.ScanDirectory(path);
	//创建搜索实例
	DataManager& dm = DataManager::GetInstance();
	string key;
	vector<pair<string, string>> doc_path;
	while (1)
	{
		cout << "请输入要搜索的关键字:>";
		cin >> key;
		dm.Search(key, doc_path);
		//显示结果
		printf("%-15s%-50s\n", "名称", "路径");
		for (const auto& e : doc_path)
		printf("%-15s%-50s\n", e.first.c_str(), e.second.c_str());
	}
}
void Test_ChineseConvert()
{
	string str = "熊立伟";
	string pinyin = ChineseConvertPinYinAllSpell(str);
	cout << "pinyin = " << pinyin << endl;
	string initials = ChineseConvertPinYinInitials(str);
	cout << "initials = " << initials << endl;
}
void Test_Frame()
{
	char*  title = "文件快速搜索工具";
	DrawFrame(title);
}
int main(int argc, char* argv[])
{
	//Test_DirectionList();
	//Test_Sqlite();
	//Test_SqliteManager();
	//Test_Log();
	//Test_Map();
	//Test_Scan();
	//Test_Search();
	//Test_ChineseConvert();
	Test_Frame();
	return 0;
}*/