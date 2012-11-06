#include <assert.h>

// libsolv
#include <solv/pool.h>
#include <solv/util.h>

// hawkey
#include "reldep_internal.h"

struct _HyReldep {
    Pool *pool;
    Id r_id;
};

struct _HyReldepList {
    Pool *pool;
    Queue queue;
};

HyReldep
reldep_create(Pool *pool, Id r_id)
{
    assert(ISRELDEP(r_id));
    HyReldep reldep = solv_calloc(1, sizeof(*reldep));
    reldep->pool = pool;
    reldep->r_id = r_id;
    return reldep;
}

Id
reldep_id(HyReldep reldep)
{
    return reldep->r_id;
}

HyReldepList
reldeplist_from_queue(Pool *pool, Queue h)
{
    HyReldepList reldeplist = solv_calloc(1, sizeof(*reldeplist));
    reldeplist->pool = pool;
    queue_init_clone(&reldeplist->queue, &h);
    return reldeplist;
}

void
hy_reldep_free(HyReldep reldep)
{
    solv_free(reldep);
}

HyReldep
hy_reldep_clone(HyReldep reldep)
{
    return reldep_create(reldep->pool, reldep->r_id);
}

char
*hy_reldep_str(HyReldep reldep)
{
    const char *str = pool_dep2str(reldep->pool, reldep->r_id);
    return solv_strdup(str);
}

void
hy_reldeplist_free(HyReldepList reldeplist)
{
    queue_free(&reldeplist->queue);
    solv_free(reldeplist);
}

int
hy_reldeplist_count(HyReldepList reldeplist)
{
    return reldeplist->queue.count;
}

HyReldep
hy_reldeplist_get_clone(HyReldepList reldeplist, int index)
{
    Id r_id = reldeplist->queue.elements[index];
    return reldep_create(reldeplist->pool, r_id);
}
