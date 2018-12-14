
#include<iostream>
#include<list>
#include<vector>
#include<queue>

#include "connectivity.h"

#include "postgres.h"
#include "fmgr.h"
#include "c_common/postgres_connection.h"
#include "utils/array.h"
#include "c_common/debug_macro.h"
#include "c_common/e_report.h"
#include "c_common/time_msg.h"
#include "c_common/edges_input.h"
#include "c_common/points_input.h"
#include "c_common/arrays_input.h"


using namespace std;

/* 图 */
class Graph
{
public:
    Graph(size_t V);                        // 构造函数
    void addEdge(int v, int w, int edgeName);          // 向图中添加边
    void DFS(int v);                     // 从v开始深度优先遍历图

private:
    //void DFSUtil(int v, bool visited[]); // 从顶点v深度优先遍历
    list<pair<int, int> > *adj;           // 邻接表
    int V;                               // 顶点数
};

/* 构造函数 */
Graph::Graph(size_t V)
{
	this->V = V;
	adj = new list<pair<int, int>>[V];
}

/* 添加边，构造邻接表 */
void Graph::addEdge(int v, int w, int edgeName)
{
	pair<int, int> pair;
	pair.first = w;
	pair.second = edgeName;
	adj[v].push_back(pair);                 // 将w添加到v的链表
}

/* 对图进行深度优先遍历，调用函数DFSUtil() */
void Graph::DFS(int v)
{
    //bool visited[14] = { 0 };
    bool *visited = new bool[V];
    for (int i = 0; i < V; ++i)
    {
        visited[i] = false;
    }
    queue<int> Q;
    queue<int> P;
    Q.push(v);
    // 访问顶点v并输出
    visited[v] = true;
    list<pair<int, int>>::iterator i;
    while (!Q.empty())  //if queue is not empty, then the bfs is not over
    {
        for (i = adj[Q.front()].begin(); i != adj[Q.front()].end(); ++i)
            if (!visited[(*i).first])
            {
                if ((*i).second == 1)
                {
                    P.push((*i).first);
                    cout << (*i).first << " ";
                    visited[(*i).first] = true;
                }
                else
                {
                    Q.push((*i).first);
                    visited[(*i).first] = true;
                }
            }
        Q.pop();
    }
}

/* 关阀分析调用函数 */
void do_connect(pgr_edge_t *edges, size_t total_edges)
{
    Graph g(total_edges);
    //pgr_edge_t c = edges[5];
	size_t num_edges = total_edges + 1;
    
	for (size_t j = 0; j < num_edges; ++j)
	{
		g.addEdge(edges[j].source, edges[j].target, edges[j].cost);
        g.addEdge(edges[j].target, edges[j].source , edges[j].reverse_cost);
	}
	//g.addEdge(1, 3, 1);
	//g.addEdge(3, 7, 0);
	//g.addEdge(2, 4, 1);
	//g.addEdge(4, 8, 0);
	//g.addEdge(5, 6, 1);
	//g.addEdge(6, 7, 0);
	//g.addEdge(7, 8, 0);
	//g.addEdge(8, 9, 1);
	//g.addEdge(9, 13, 1);
	//g.addEdge(7, 11, 1);
	//g.addEdge(11, 12, 0);
	//g.addEdge(8, 14, 0);
	//g.addEdge(13, 10, 0);
	//g.addEdge(3, 1, 0);
	//g.addEdge(7, 3, 1);
	//g.addEdge(4, 2, 0);
	//g.addEdge(8, 4, 1);
	//g.addEdge(6, 5, 0);
	//g.addEdge(7, 6, 1);
	//g.addEdge(8, 7, 0);
	//g.addEdge(9, 8, 0);
	//g.addEdge(13, 9, 1);
	//g.addEdge(11, 7, 0);
	//g.addEdge(12, 11, 1);
	//g.addEdge(14, 8, 0);
	//g.addEdge(10, 13, 1);

	g.DFS(8);
}
