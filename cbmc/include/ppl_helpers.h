#include <mem.h>

struct page_pool root_pool;

struct page_pool *proof_ppl_init(void);
bool proof_ppl_is_valid(struct page_pool *pp);
