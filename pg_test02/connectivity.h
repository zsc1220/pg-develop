#pragma once


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

#ifndef INCLUDE_DRIVERS_DIJKSTRA_DIJKSTRA_DRIVER_H_
#define INCLUDE_DRIVERS_DIJKSTRA_DIJKSTRA_DRIVER_H_

#include "c_types/pgr_edge_t.h"
#include "c_types/general_path_element_t.h"

#ifdef __cplusplus
extern "C" {
#endif

	void do_connect(pgr_edge_t *edges, size_t total_edges);

#ifdef __cplusplus
    }
#endif

#endif  // INCLUDE_DRIVERS_DIJKSTRA_DIJKSTRA_DRIVER_H_


