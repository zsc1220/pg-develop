
//#include <sstream>
//#include <deque>
//#include <vector>
//#include <algorithm>
//#include <list>
//#include <vector>
//#include <queue>
//#include <iostream>
//#include "utils/palloc.h"
#include "vision.h"
#include "c_types\pgr_edge_t.h"
#include<iostream>
#include<list>
#include<queue>
using namespace std;

/* 图 */
class Graph
{
    int V;                               // 顶点数
    list<int> *adj;                      // 邻接表
    //void DFSUtil(int v, bool visited[], multi_areas  **result_tuples); // 从顶点v深度优先遍历
public:
    Graph(int V);                        // 构造函数
    void addEdge(int v, int w);          // 向图中添加节点
    void DFS(int v, multi_areas  **result_tuples);                     // 从v开始深度优先遍历图
};

/* 构造函数 */
Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
}

/* 添加边，构造邻接表 */
void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w);                 // 将w添加到v的链
}

/* 对图进行广度优先遍历，调用函数DFSUtil() */
void Graph::DFS(int v, multi_areas  **result_tuples)
{
    bool *visited = new bool[V];
    bool *color = new bool[V];
    for (int i = 1; i < V; ++i)
        visited[i] = false;
    //DFSUtil(v, visited);
    //cout << "**" << endl;
    multi_areas  resulty_tuples[14];
    int j = 0;
    // 对剩余顶点调用DFSUtil()，从0开始
    for (int i = 1; i < V; ++i)
    {
        if (!visited[i])
        {
            queue<int> Q;
            Q.push(i);
            int start = Q.front();
            // 访问顶点v并输出
            visited[i] = true; //通过指针传进来****

            int result[14][2] = { 0 };

            list<int>::iterator i;
            while (!Q.empty())  //if queue is not empty, then the bfs is not over
            {
                for (i = adj[Q.front()].begin(); i != adj[Q.front()].end(); ++i)
                    if (!visited[*i])
                    {
                        Q.push(*i);
                        visited[*i] = true;
                    }
                resulty_tuples[j].start_id = start;
                resulty_tuples[j].end_id = Q.front();
                result[j][0] = start;
                result[j][1] = Q.front();
               //cout << result[j][0] << "*" << result[j][1] << " ";
               //cout << start << "*" << Q.front() << " ";
                j++;

                //cout << Q.front() << " ";
                Q.pop();
            }

            //cout << "***" << endl;
        }
    }
    *result_tuples = resulty_tuples;
    //cout << "***" << endl;
}

///* 对图进行广度优先遍历，调用函数DFSUtil() */
//void Graph::DFS(int v, multi_areas  **result_tuples)
//{
//    bool *visited = new bool[V];
//    bool *color = new bool[V];
//    for (int i = 0; i < V; ++i)
//        visited[i] = false;
//    //DFSUtil(v, visited);
//    //cout << "**" << endl;
//
//    // 对剩余顶点调用DFSUtil()，从0开始
//    for (int i = 0; i < V; ++i)
//    {
//        if (!visited[i])
//        {
//            DFSUtil(i, visited, result_tuples);
//            cout << "***" << endl;
//        }
//    }
//}

/* 测试 */
void do_connect(pgr_edge_t *fields, multi_areas  **result_tuples)
{
    Graph g(15);
    for (int i = 0; i < 13; i++)
    {
        g.addEdge(fields[i].source, fields[i].target);
        g.addEdge(fields[i].target, fields[i].source);
    }


    //g.addEdge(1, 3);
    //g.addEdge(3, 7);
    //g.addEdge(2, 4);
    //g.addEdge(4, 8);
    //g.addEdge(5, 6);
    ////g.addEdge(6, 7);
    ////g.addEdge(7, 8);
    //g.addEdge(8, 9);
    //g.addEdge(9, 13);
    //g.addEdge(7, 11);
    //g.addEdge(11, 12);
    //g.addEdge(8, 14);
    //g.addEdge(13, 10);
    //g.addEdge(3, 1);
    //g.addEdge(7, 3);
    //g.addEdge(4, 2);
    //g.addEdge(8, 4);
    //g.addEdge(6, 5);
    ////g.addEdge(7, 6);
    ////g.addEdge(8, 7);
    //g.addEdge(9, 8);
    //g.addEdge(13, 9);
    //g.addEdge(11, 7);
    //g.addEdge(12, 11);
    //g.addEdge(14, 8);
    //g.addEdge(10, 13);

    g.DFS(0, result_tuples);

}



