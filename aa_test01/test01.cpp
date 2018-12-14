
#include<iostream>
#include<map>
#include<set>
#include<list>
#include<vector>
#include<queue>
#include<string>

using namespace std;





class Graph
{
public:
	Graph(int nodes);                                    // 构造函数
	void adj_list(string source, string target, string id);             // 向图中添加边
	void BFS_first(string v);                               // 从顶点v广度优先遍历
	void BFS_second();                                   // 从v开始广度优先遍历图
	void BFS_third();
	void affected_pipe();
public:
	queue<string> Qone;
	queue<string> Qfour;
	queue<string> Qsixth;
	queue<string> Qfive;
	queue<string> Qsevth;
	queue<string> Qeigth;
	queue<string> Qninth;
	map<string, bool> vtwo;
	map<string, bool> vfour;
	set<string> Spipe;  //自动进行排序 默认从小到大
	map<string, string> points;

	typedef struct adj_structure
	{

		string adj_up;
		string adj_edge;
	}adj_stru;

	multimap<string, adj_stru> adj_group;

private:
	int Total_nodes;                                     // 顶点数
	queue<string> Q;
	queue<string> Qtwo;
	queue<string> Qthere;

	map<string, bool> vone;
	map<string, bool> vthere;



};

/* 构造函数 */
Graph::Graph(int V)
{
	Total_nodes = V;
	//vone = new bool[V];
	//vtwo = new bool[V];
	//vthere = new bool[V];
	//vfour = new bool[V];
}

/* 创建邻接表 */
void Graph::adj_list(string source, string target, string id)
{
	adj_stru adj_strus;
	adj_strus.adj_up = target;

	adj_strus.adj_edge = id;
	adj_group.insert(make_pair(source, adj_strus));

}

/* 对图进行第一次遍历 */
void Graph::BFS_first(string v)
{
	for (map<string, string>::iterator it = points.begin(); it != points.end(); it++)
	{
		vone.insert(make_pair((*it).first, false));
		vtwo.insert(make_pair((*it).first, false));
		vfour.insert(make_pair((*it).first, false));
	}

	Q.push(v);
	vone[v] = true;
	while (!Q.empty())
	{
		multimap<string, adj_stru>::iterator it = adj_group.find(Q.front());
		int DepartCount = adj_group.count(Q.front());           //统计节点邻接数
		int num = 0;
		for (multimap<string, adj_stru>::iterator pos = it; it != adj_group.end() && num < DepartCount; pos++, num++) {
			points.find((*pos).second.adj_up)->second;
			if (!vone.find((*pos).second.adj_up)->second)
			{
				if (points.find((*pos).second.adj_up)->second == "1")
				{
					//cout << (*i).first << " ";
					vone[(*pos).second.adj_up] = true;
					vtwo[(*pos).second.adj_up] = true;
					Qone.push((*pos).second.adj_up);   //Qone 保存待关阀门
				}
				else if (points.find((*pos).second.adj_up)->second != "1" && points.find((*pos).second.adj_up)->second != "0")
				{
					Q.push((*pos).second.adj_up);
					vone[(*pos).second.adj_up] = true;
				}
			}


		}
		Q.pop();

	}
}

/* 对 待关 阀门进行第二次遍历 */
void Graph::BFS_second()
{
	while (!Qone.empty())
	{
		vthere = vtwo;
		//for (int k = 0; k < Total_nodes; k++)
		//{
		//    vthere[k] = vtwo[k];
		//}
		int j = 0;
		Qtwo.push(Qone.front());
		//cout << Qtwo.front() << " "; //输出队头元素
		Qone.pop();
		while (!Qtwo.empty())
		{
			multimap<string, adj_stru>::iterator it = adj_group.find(Qtwo.front());
			int DepartCount = adj_group.count(Qtwo.front());
			int num = 0;
			for (multimap<string, adj_stru>::iterator pos = it; it != adj_group.end() && num < DepartCount; pos++, num++)
			{
				if (!vthere.find((*pos).second.adj_up)->second)
				{
					vthere[(*pos).second.adj_up] = true;
					if (points.find((*pos).second.adj_up)->second == "0")
					{
						//cout << Qtwo.front() << " ";
						j = 1;
						break;
					}
					else
					{
						Qtwo.push((*pos).second.adj_up);

						//vtwo[(*i).first] = true;

					}
				}
			}
			Qthere.push(Qtwo.front());
			//Qtwo.pop();
			if (j == 1)
			{
				//cout << Qthere.front() << " ";
				Qfour.push(Qthere.front());         //Qfour 保存必须关闭阀门
				vfour[Qthere.front()] = true;
				//cout << vfour[Qthere.front()] <<endl;
				break;
			}
			Qtwo.pop();
		}
		//if (Qtwo.empty()) Qfive.push(Qthere.front());  //只有没有找到水源才会空，所以保存的是可关可不关的阀门
		while (!Qtwo.empty()) Qtwo.pop();      //把前n次的标记都清零，所以每次重新开始遍历时，只有待关阀门被标记了
		while (!Qthere.empty()) Qthere.pop();  //总之，不能遍历到其他待关闭阀门
											   //cout << "**" << endl;
	}

}



/* 对 非关 阀门进行第三次遍历 */
void Graph::BFS_third()
{

	while (!Qsixth.empty())
	{
		multimap<string, adj_stru>::iterator it = adj_group.find(Qsixth.front());
		int DepartCount = adj_group.count(Qsixth.front());
		int num = 0;
		for (multimap<string, adj_stru>::iterator pos = it; it != adj_group.end() && num < DepartCount; pos++, num++)
		{
			if (!vfour.find((*pos).second.adj_up)->second)
			{
				vfour[(*pos).second.adj_up] = true;
				if (points.find((*pos).second.adj_up)->second == "2")
				{
					//cout << Qtwo.front() << " ";
					Qsevth.push((*pos).second.adj_up);
					Qeigth.push((*pos).second.adj_up);
					/*	j = 1;
					break;*/
				}
				else
				{
					Qsixth.push((*pos).second.adj_up);
					Qeigth.push((*pos).second.adj_up);
					//vtwo[(*i).first] = true;

				}
			}
		}

		Qsixth.pop();
	}
}

void Graph::affected_pipe()
{
	while (!Qeigth.empty())
	{
		multimap<string, adj_stru>::iterator it = adj_group.find(Qeigth.front());
		int DepartCount = adj_group.count(Qeigth.front());
		int num = 0;
		for (multimap<string, adj_stru>::iterator pos = it; it != adj_group.end() && num < DepartCount; pos++, num++)
		{
			Spipe.insert((*pos).second.adj_edge);
		}
		Qeigth.pop();
	}
}

typedef struct {
	int pipe_id;
	int pipe_type;
} multi_datas;

typedef struct 
{
	string gid;
	string gid1;
	string gid2;
	string gid1_type;
	string gid2_type;
} pgr_edge_ts;

//typedef struct {
//	char *gid;
//	char *gid1;
//	char *gid2;
//	char *gid1_type;
//	char *gid2_type;
//} pgr_edge_ts;

int find_seq(pgr_edge_ts *array, int length, char *value)
{
	int i;
	for (i = 0; i < length; i++)
	{
	
		string v = array[i].gid;
		if (array[i].gid == value)
		{
			break;
		}
	}
	return i;
}

void do_close(
	pgr_edge_ts *fields,
	size_t total_edges,
	multi_datas **result_tuples,
	size_t *result_count,
	char *explode_e)
{

	int total_e = total_edges;   //总管段

	map<string, string> org_point;

	for (int i = 0; i < total_e; i++)
	{
		org_point.insert(make_pair(fields[i].gid1, fields[i].gid1_type));
		org_point.insert(make_pair(fields[i].gid2, fields[i].gid2_type));
	}

	int total_v = org_point.size();           //总节点


	Graph g(total_v);
	g.points = org_point;
	for (int i = 0; i < total_e; i++)
	{
		g.adj_list(fields[i].gid1, fields[i].gid2, fields[i].gid);
		g.adj_list(fields[i].gid2, fields[i].gid1, fields[i].gid);
	}
	//int select_edge = explode_e - 1;

	//char explode_e[] = "29";

	int j = find_seq(fields, total_e, explode_e);
	int select_edge = j;
	string left_type = g.points.find(fields[select_edge].gid1)->second;
	string right_type = g.points.find(fields[select_edge].gid2)->second;
	string headwaters = "0";
	string valve = "1";
	string user = "2";
	string node = "3";
	string pipe = "4";

	/*需关阀门搜索*/
	/*两点为节点 或者 左点为节点，右点为阀门*/
	if (((left_type != "1") && (right_type != "1")) || ((left_type != "1") && right_type == "1"))
	{

		g.BFS_first(fields[select_edge].gid1);
		g.BFS_second();
	}
	/*左点为阀门，右点为节点*/
	else if (left_type == "1" && (right_type != "1"))
	{
		g.BFS_first(fields[select_edge].gid2);
		g.BFS_second();
	}
	/*两点为阀门*/
	else
	{
		for (map<string, string>::iterator it = g.points.begin(); it != g.points.end(); it++)
		{
			g.vtwo.insert(make_pair((*it).first, false));
		}
		g.vtwo[fields[select_edge].gid1] = true;
		g.vtwo[fields[select_edge].gid2] = true;
		g.Qone.push(fields[select_edge].gid1);
		g.Qone.push(fields[select_edge].gid2);
		g.BFS_second();
	}

	/*受影响用户搜索*/
	if (g.vfour.find(fields[select_edge].gid1)->second == false)  //先确定不是必须关闭阀门
	{
		g.points.find(fields[select_edge].gid1)->second;
		if (g.points.find(fields[select_edge].gid1)->second == "2")             /*与下面对应的这两句话，导致不能合并*/
		{
			g.Qsevth.push(fields[select_edge].gid1);
		}
		g.Qsixth.push(fields[select_edge].gid1);
		g.Qeigth.push(fields[select_edge].gid1);
		g.BFS_third();
	}

	if (g.vfour.find(fields[select_edge].gid2)->second == false)   //先确定不是必须关闭阀门
	{
		if (g.points.find(fields[select_edge].gid2)->second == "2")
		{
			g.Qsevth.push(fields[select_edge].gid2);
		}
		g.Qsixth.push(fields[select_edge].gid2);
		g.Qeigth.push(fields[select_edge].gid2);
		g.BFS_third();
	}

	/*受影响管段*/
	g.affected_pipe();

	int res_count = g.Qfour.size() + g.Qsevth.size() + g.Spipe.size();

	(*result_tuples) = (multi_datas *)malloc(res_count);
	*result_count = res_count;
	int i = 0;
	while (g.Qfour.size() > 0)
	{
		cout << g.Qfour.front() << " ";       //输出必须关闭阀门
		(*result_tuples)[i].pipe_type = 1;

		(*result_tuples)[i].pipe_id = atoi(g.Qfour.front().c_str());
				
		g.Qfour.pop();
		i++;
	}
	cout << endl;
	//i = 0;
	while (!g.Qsevth.empty())
	{
		cout << g.Qsevth.front() << " ";      //输出受影响用户
		(*result_tuples)[i].pipe_id = atoi(g.Qsevth.front().c_str());

		(*result_tuples)[i].pipe_type = 2;
		g.Qsevth.pop();
		i++;
	}
	cout << endl;
	for (set<string>::iterator it = g.Spipe.begin(); it != g.Spipe.end(); it++)
	{
		cout << *it << " ";                   //输出受影响管段
		(*result_tuples)[i].pipe_id = atoi((*it).c_str());

		(*result_tuples)[i].pipe_type = 4;
		i++;
	}
	cout << endl;
	free(*result_tuples);
}

void processd(multi_datas **result_tuples,size_t *result_count)
{
	pgr_edge_ts fields[] =
	{
	{ "1","1","3","0","3" },
	{ "2","2","3","3","3" },
	{ "3","4","3","3","3" },
	{ "4","2","5","3","1" },
	{ "5","5","7","1","3" },
	{ "6","3","6","3","1" },
	{ "7","6","8","1","3" },
	{ "8","4","9","3","3" },
	{ "9","7","8","3","3" },
	{ "10","8","9","3","3" },
	{ "11","7","10","3","1" },
	{ "12","10","13","1","3" },
	{ "13","8","11","3","1" },
	{ "14","11","12","1","1" },
	{ "15","12","14","1","3" },
	{ "16","9","16","3","3" },
	{ "17","13","14","3","3" },
	{ "18","14","15","3","1" },
	{ "19","15","16","1","3" },
	{ "20","14","17","3","2" },
	{ "21","13","18","3","3" },
	{ "22","18","19","3","2" },
	{ "23","18","20","3","1" },
	{ "24","20","21","1","3" },
	{ "25","21","22","3","3" },
	{ "26","21","23","3","1" },
	{ "27","23","25","1","2" },
	{ "28","24","22","1","3" },
	{ "29","24","26","1","2" },
	};

	int total_edges = 29;
	char explode_e[] = "24";
	do_close(fields, total_edges, result_tuples, result_count, explode_e);  //调用关阀分析函数

	
}

int main()
{
	multi_datas  *result_tuples = NULL;
	size_t result_count = 0;
	processd(&result_tuples,&result_count);
	system("pause");
    return 0;
}
