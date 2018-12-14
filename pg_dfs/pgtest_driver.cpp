/*PGR-GNU*****************************************************************
File: many_to_many_dijkstra_driver.cpp

Generated with Template by:
Copyright (c) 2015 pgRouting developers
Mail: project@pgrouting.org

Function's developer: 
Copyright (c) 2015 Celia Virginia Vergara Castillo
Mail: vicky_vergara@hotmail.com

------

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

********************************************************************PGR-GNU*/

//#include "pgtest_driver.h"

#include <sstream>
#include <deque>
#include <vector>
#include <algorithm>
#include <list>
#include <vector>
#include <queue>
#include <iostream>
#include "pg_dfs/pgtest_driver.h"
#include "dijkstra/pgr_dijkstra.hpp"

#include "cpp_common/pgr_alloc.hpp"
#include "cpp_common/pgr_assert.h"

using namespace std;

template < class G >
std::deque< Path >
pgr_dijkstra(
        G &graph,
        std::vector < int64_t > sources,
        std::vector < int64_t > targets,
        bool only_cost,
        bool normal) {
    std::sort(sources.begin(), sources.end());
    sources.erase(
            std::unique(sources.begin(), sources.end()),
            sources.end());

    std::sort(targets.begin(), targets.end());
    targets.erase(
            std::unique(targets.begin(), targets.end()),
            targets.end());

    Pgr_dijkstra< G > fn_dijkstra;
    auto paths = fn_dijkstra.dijkstra(graph, sources, targets, only_cost);

    if (!normal) {
        for (auto &path : paths) {
            path.reverse();
        }
    }
    return paths;
}



// CREATE OR REPLACE FUNCTION pgr_dijkstra(
// sql text,
// start_vids anyarray,
// end_vids anyarray,
// directed boolean default true,
void
do_pgr_many_to_many_dijkstra(
        pgr_edge_t  *data_edges,
        size_t total_edges,
        int64_t  *start_vidsArr,
        size_t size_start_vidsArr,
        int64_t  *end_vidsArr,
        size_t size_end_vidsArr,
        bool directed,
        bool only_cost,
        bool normal,
        General_path_element_t **return_tuples,
        size_t *return_count,
        char ** log_msg,
        char ** notice_msg,
        char ** err_msg) {
    std::ostringstream log;
    std::ostringstream err;
    std::ostringstream notice;

    try {
        pgassert(total_edges != 0);
        pgassert(!(*log_msg));
        pgassert(!(*notice_msg));
        pgassert(!(*err_msg));
        pgassert(!(*return_tuples));
        pgassert(*return_count == 0);

        graphType gType = directed? DIRECTED: UNDIRECTED;

        log << "Inserting vertices into a c++ vector structure";
        std::vector<int64_t>
            start_vertices(start_vidsArr, start_vidsArr + size_start_vidsArr);
        std::vector< int64_t >
            end_vertices(end_vidsArr, end_vidsArr + size_end_vidsArr);

        std::deque< Path >paths;
        if (directed) {
            log << "\nWorking with directed Graph";
            pgrouting::DirectedGraph digraph(gType);
            digraph.insert_edges(data_edges, total_edges);
            paths = pgr_dijkstra(
                    digraph,
                    start_vertices, end_vertices,
                    only_cost, normal);
        } else {
            log << "\nWorking with Undirected Graph";
            pgrouting::UndirectedGraph undigraph(gType);
            undigraph.insert_edges(data_edges, total_edges);
            paths = pgr_dijkstra(
                    undigraph,
                    start_vertices, end_vertices,
                    only_cost, normal);
        }

        size_t count(0);
        count = count_tuples(paths);

        if (count == 0) {
            (*return_tuples) = NULL;
            (*return_count) = 0;
            notice <<
                "No paths found";
            *log_msg = pgr_msg(notice.str().c_str());
            return;
        }

        (*return_tuples) = pgr_alloc(count, (*return_tuples));
        log << "\nConverting a set of paths into the tuples";
        (*return_count) = (collapse_paths(return_tuples, paths));

        *log_msg = log.str().empty()?
            *log_msg :
            pgr_msg(log.str().c_str());
        *notice_msg = notice.str().empty()?
            *notice_msg :
            pgr_msg(notice.str().c_str());
    } catch (AssertFailedException &except) {
        (*return_tuples) = pgr_free(*return_tuples);
        (*return_count) = 0;
        err << except.what();
        *err_msg = pgr_msg(err.str().c_str());
        *log_msg = pgr_msg(log.str().c_str());
    } catch (std::exception &except) {
        (*return_tuples) = pgr_free(*return_tuples);
        (*return_count) = 0;
        err << except.what();
        *err_msg = pgr_msg(err.str().c_str());
        *log_msg = pgr_msg(log.str().c_str());
    } catch(...) {
        (*return_tuples) = pgr_free(*return_tuples);
        (*return_count) = 0;
        err << "Caught unknown exception!";
        *err_msg = pgr_msg(err.str().c_str());
        *log_msg = pgr_msg(log.str().c_str());
    }
}

/* 图 */
class Graph
{
public:
	Graph(size_t V);                        // 构造函数
	void addEdge(int v, int w, int edgeName);          // 向图中添加边
	void DFS(int v);                     // 从v开始深度优先遍历图

private:
	list<pair<int, int>> *adj;           // 邻接表
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

/* 对图进行广度优先遍历，调用函数DFS() */
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
					//cout << (*i).first << " ";
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
void do_connect()
{
	/*Graph g(total_edges);
	pgr_edge_t c = edges[5];
	size_t num_edges = total_edges + 1;

	for (size_t j = 0; j < num_edges; ++j)
	{
		g.addEdge(edges[j].source, edges[j].target, edges[j].reverse_cost);
		g.addEdge(edges[j].target, edges[j].source, edges[j].cost);
	}*/
	Graph g(14);
	g.addEdge(1, 3, 1);
	g.addEdge(3, 7, 0);
	g.addEdge(2, 4, 1);
	g.addEdge(4, 8, 0);
	g.addEdge(5, 6, 1);
	g.addEdge(6, 7, 0);
	g.addEdge(7, 8, 0);
	g.addEdge(8, 9, 1);
	g.addEdge(9, 13, 1);
	g.addEdge(7, 11, 1);
	g.addEdge(11, 12, 0);
	g.addEdge(8, 14, 0);
	g.addEdge(13, 10, 0);
	g.addEdge(3, 1, 0);
	g.addEdge(7, 3, 1);
	g.addEdge(4, 2, 0);
	g.addEdge(8, 4, 1);
	g.addEdge(6, 5, 0);
	g.addEdge(7, 6, 1);
	g.addEdge(8, 7, 0);
	g.addEdge(9, 8, 0);
	g.addEdge(13, 9, 1);
	g.addEdge(11, 7, 0);
	g.addEdge(12, 11, 1);
	g.addEdge(14, 8, 0);
	g.addEdge(10, 13, 1);

	g.DFS(8);
	
	
}

