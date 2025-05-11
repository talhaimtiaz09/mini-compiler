#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

void init_symbol_table();
int add_symbol(const char *name, const char *kind); // returns 1 if added, 0 if already exists
int lookup_symbol(const char *name);                // returns 1 if found
void push_scope();
void pop_scope();
void cleanup_symbol_table();

#endif
