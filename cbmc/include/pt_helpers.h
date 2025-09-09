#include <page_table.h>

struct page_table * proof_pt_allocate(void);
void proof_pt_init(struct page_table *pt);
bool proof_pt_is_valid(struct page_table *pt);
