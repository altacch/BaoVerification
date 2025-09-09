#include <mem.h>

struct addr_space * proof_as_allocate(void);
void proof_as_init(struct addr_space *as);
bool proof_as_is_valid(struct addr_space *as);

