#ifndef __VISION_H_
#define __VISION_H_
#include "c_types\pgr_edge_t.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>


    typedef struct {
        int64_t start_id;
        int64_t end_id;
    } multi_areas;

    void do_connect(pgr_edge_t *fields ,multi_areas **result_tuples);


#ifdef __cplusplus
}
#endif

#endif  
