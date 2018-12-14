
#include "postgres.h"
#include "access\htup_details.h"
#include "fmgr.h"
#include "funcapi.h"
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
#include "vision.h"
//#include "build/pg_vision/vision.h"
//#include "pg_dfs/pgtest_driver.h"

#ifdef PG_MODULE_MAGIC
PG_MODULE_MAGIC;
#endif


PGDLLEXPORT Datum test_add_fun(PG_FUNCTION_ARGS);
PG_FUNCTION_INFO_V1(test_add_fun);


static
void
process(
    int a,
    int b,
    char* edges_sql,
    multi_areas **result_tuples)
{
    pgr_SPI_connect(); //连接数据库

    pgr_edge_t *edges = NULL;
    size_t total_edges = 0;

    int sum;
    sum = a - b;

    pgr_get_edges(edges_sql, &edges, &total_edges);   //数据读取函数
    do_connect(edges, result_tuples);  //调用关阀分析函数

    pgr_SPI_finish();//断开数据库

}




Datum test_add_fun(PG_FUNCTION_ARGS)
{
    FuncCallContext     *funcctx;
    TupleDesc            tuple_desc;

    multi_areas  *result_tuples = NULL;
    size_t result_count = 14;


	if (SRF_IS_FIRSTCALL()) {
		MemoryContext   oldcontext;
		funcctx = SRF_FIRSTCALL_INIT();
		oldcontext = MemoryContextSwitchTo(funcctx->multi_call_memory_ctx);



#if PGSQL_VERSION > 95
		funcctx->max_calls = result_count;
#else
		funcctx->max_calls = (uint32_t)result_count;
#endif

		
		if (get_call_result_type(fcinfo, NULL, &tuple_desc)
			!= TYPEFUNC_COMPOSITE) {
			ereport(ERROR,
				(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
					errmsg("function returning record called in context "
						"that cannot accept type record")));
		}


        process(

            PG_GETARG_INT32(0),
            PG_GETARG_INT32(1),
            text_to_cstring(PG_GETARG_TEXT_P(2)),
            &result_tuples);


		funcctx->user_fctx = result_tuples;
		funcctx->tuple_desc = tuple_desc;
		MemoryContextSwitchTo(oldcontext);
	}

	funcctx = SRF_PERCALL_SETUP();
	tuple_desc = funcctx->tuple_desc;
	result_tuples = (multi_areas*)funcctx->user_fctx;


	if (funcctx->call_cntr < funcctx->max_calls) {
		HeapTuple    tuple;
		Datum        result;
		Datum        *values;
		bool*        nulls;
		size_t       call_cntr = funcctx->call_cntr;

		size_t numb = 3;
		values = palloc(numb * sizeof(Datum));
		nulls = palloc(numb * sizeof(bool));

		size_t i;
		for (i = 0; i < numb; ++i) {
			nulls[i] = false;
		}

		values[0] = Int64GetDatum(call_cntr + 1);
		values[1] = Int64GetDatum(result_tuples[call_cntr].start_id);
		values[2] = Int64GetDatum(result_tuples[call_cntr].end_id);
		//values[3] = Int64GetDatum(result_tuples[call_cntr].target);
		//values[4] = Float8GetDatum(result_tuples[call_cntr].cost);
		//values[5] = Float8GetDatum(result_tuples[call_cntr].reverse_cost);
		/*values[6] = Float8GetDatum(result_tuples[call_cntr].cost);
		values[7] = Float8GetDatum(result_tuples[call_cntr].agg_cost);*/
		/**********************************************************************/

		tuple = heap_form_tuple(tuple_desc, values, nulls);
		result = HeapTupleGetDatum(tuple);
		SRF_RETURN_NEXT(funcctx, result);
	}
	else {
		SRF_RETURN_DONE(funcctx);
	}
    
}
