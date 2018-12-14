
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
//#include "graph_represent.h"
//#include "queuey.h"
#include "pgtest_driver.h"

#ifdef PG_MODULE_MAGIC
PG_MODULE_MAGIC;
#endif


PGDLLEXPORT Datum test_add_fun(PG_FUNCTION_ARGS);
PG_FUNCTION_INFO_V1(test_add_fun);



Datum test_add_fun(PG_FUNCTION_ARGS)
{
	pgr_SPI_connect();
	char* edges_sql = text_to_cstring(PG_GETARG_TEXT_P(2));
	pgr_edge_t *edges = NULL;
	size_t total_edges = 0;
	pgr_get_edges(edges_sql, &edges, &total_edges);

    //do_connect(edges, total_edges);  //调用关阀分析函数

    pgr_edge_t c1 = edges[5];
    int c = edges[5].reverse_cost;
    //pgr_get_points(edges_sql, &edges, &total_edges);

    int sum, a, b;
	a = PG_GETARG_INT32(0);
	b = PG_GETARG_INT32(1);
	sum = a+b;
	PG_RETURN_INT32(sum);
    //FuncCallContext     *funcctx;
    //TupleDesc           tuple_desc;
    //HeapTuple    tuple;
    //bool*        nulls;
    //size_t numb = 8;
    //Datum        resulty;
  
    //nulls = palloc(numb * sizeof(bool));
    //funcctx = SRF_PERCALL_SETUP();
    //tuple_desc = funcctx->tuple_desc;
    //tuple = heap_form_tuple(tuple_desc, result, nulls);
    //resulty = HeapTupleGetDatum(tuple);
    //SRF_RETURN_NEXT(funcctx, result);

    //PG_RETURN_DATUM(result);
}
