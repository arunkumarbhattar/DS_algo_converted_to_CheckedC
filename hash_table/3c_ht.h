//A simple Hash table implemented in C.

//header guards to prevent recursive inclusions and redeclaration of identifiers
#ifndef _HT_H
#define _HT_H

#include <stdbool.h>
#include <stddef.h>

//Hash table structure: create with ht_create, and free with ht_destroy
typedef struct ht ht;

//create hash table and return pointer to it, or NULL if out of memory. 
ht* ht_create(void);

//Free memory allocated for hash table, including allocated keys. 
void ht_destroy(ht* table);

//Get item with given key (NUL-terminated) from hash table. 
//Return the value (which was set with ht_set), or NULL if key not found. 
void* ht_get(ht* table, const char* key);

//Set item with given key (NUL-terminated to value (which must not be NULL). If not already present in table, 
//key is mostly copied to newly allocated memory (keys are freed automatically when ht_destroy is called). 
//Return address of copied key, or NULL if out of memory. 
const char* ht_set(ht* table, const char* key, void * value);

//Return the number of items in the hash table
size_t ht_length(ht*table);

//Hash table iterator: create with ht_terator, iterate with ht_next. 

typedef struct {
	const char* key; //current key
	void* value; //current value
	
	//dont use these fields directly
        ht* _table; //reference to the hash table being iterated
	size_t _index; //current index into ht. _entries
}hti;

//Return new Hash table iterator (for use with ht_next). 
hti ht_iterator(ht* table);

//Move the iterator to the next item in hash table. 
//update iterator's key and value to the current item and return true. 
//If ther are no more items, return false. Dont call ht_set during iteration. 

bool ht_next(hti* it);

#endif //_HT_H


