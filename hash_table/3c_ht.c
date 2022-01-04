//A simple hash table implemented in C.

#include "3c_ht.h"

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

//Hash table entry (slot may be filled or empty)
typedef struct{
	const char* key; //this key is NULL if the slot is empty
	void* value;
} ht_entry;

//Hash table structure: create with ht_create,free with ht_destroy 
struct ht{
	ht_entry* entries; // hash slots
	size_t capacity; // size of _entries array
	size_t length; //number of items in hash table.
};

#define INITIAL_CAPACITY 16 

ht* ht_create(void){
	//Allocate space for the hash table struct. 
	ht* table = malloc(sizeof(ht));
	if(table == NULL)
		return NULL;

	table->length = 0;
	table->capacity = INITIAL_CAPACITY; 

	//Allocate (zero'd) space for entry buckets 
	table->entries = calloc(table->capacity, sizeof(ht_entry));
	if(table->entries == NULL)
	{
		free(table); // error
		return NULL;
	}

	return table;
}

void ht_destroy(ht* table)
{
	//first free allocated keys. 
	for(size_t i = 0; i < table->capacity; i++)
	{
		if(table->entries[i].key != NULL)
			free((void*)table->entries[i].key);

	}

	//then free entries array and table itself.
	free(table->entries);
	free(table);
}

#define FNV_OFFSET 14695981039346656037UL
#define FNV_PRIME 1099511628211UL

//Return 64-Bit FNV-1a has for key (NULL-terminated).
static uint64_t hash_key(const char* key)
{
	uint64_t hash = FNV_OFFSET;
	for (const char* p = key; *p;p++)
	{
		hash ^=(uint64_t)(unsigned char)(*p);
		hash *= FNV_PRIME;
	}
	return hash;
}

void* ht_get(ht* table, const char* key)
{
	//AND hash with capacity-1 to ensure it is within entries array. 
	uint64_t hash = hash_key(key);
	size_t index = (size_t)(hash & (uint64_t)(table->capacity - 1));

	//Loop until we find an empty arary. 
	while(table->entries[index].key != NULL)
	{
		if(strcmp(key, table->entries[index].key) == 0) 
		{
			//Found key, return value.
			return table->entries[index].value;
		}

		//Key wasnt in this slot, move to the next slot (linear probing) 
		index++;
		if(index >= table->capacity)
		{
			//At end of entries array, wrap around. 
			index = 0;
		}
	}

	return NULL;
}

//Internal function to set an entry (without expanding table). 
static const char* ht_set_entry(ht_entry* entries, size_t capacity, 
		const char* key, void* value, size_t* plength)
{
	//And hash with capacity-1 to ensure its within entries array. 
	uint64_t hash = hash_key(key);
	size_t index = (size_t)(hash & (uint64_t)(capacity-1));

	//Loop till we find an empty entry. 
	while(entries[index].key != NULL)
	{
		if(strcmp(key, entries[index].key) == 0)
		{
		   //Found key (it already exists), update value. 
		   entries[index].value = value;
		   return entries[index].key;
		}
		//key wasnt in this slot, move to next (linear probing), 
		index++;
		if(index >= capacity)
		{
		   //At end of entries array, wrap around. 
		   index = 0;
		}
	}

	//didnt find any key, allocate+copy if needed, then insert it. 
	if(plength!=NULL){
	   key = strdup(key);
	   if( key == NULL)
		   return NULL;

	   (*plength)++;
	}
	
	entries[index].key = (char*)key;
	entries[index].value = value;
	return key;
}

//Expand hash table to twice its current size, Return true on success.

static bool ht_expand(ht* table)
{
	size_t new_capacity = table->capacity*2;
	if(new_capacity < table->capacity) 
		return false; //overflow (capacity would be too big)

	ht_entry* new_entries = calloc(new_capacity, sizeof(ht_entry));
	if(new_entries == NULL)
		return false;

	//Iterate entries, move all non-empty ones to new table's entries.
	
	for(size_t i =0; i< table->capacity; i++)
	{
		ht_entry entry = table->entries[i];
		if(entry.key != NULL)
			ht_set_entry(new_entries, new_capacity, entry.key, entry.value, NULL);
	}

	//Free old entries arary and update this table's details. 
	free(table->entries);
	table->entries = new_entries;
	table->capacity = new_capacity;
	return true;
}

const char* ht_set(ht* table, const char* key, void* value)
{
	assert(value != NULL);
	if(value == NULL)
		return NULL;

	// if the length exceeds half of current capacity, expand it
	if(table->length  >= table->capacity/2){
		if(!ht_expand(table))
			return NULL;
	}

	//set entry and update length.
	return ht_set_entry(table->entries, table->capacity, key, value, &table->length);
}

size_t ht_length(ht* table){
	return table->length;
}

hti ht_iterator(ht* table)
{
        hti it;
	it._table = table;
	it._index = 0;
	return it;
}

bool ht_next(hti* it)
{
	//loop till we have hit the end of entries array. 
	ht* table = it->_table;
	while(it->_index < table->capacity) 
	{
		size_t i = it->_index;
		it->_index++;
		if(table->entries[i].key != NULL)
		{
		     //found the next non-empty item, update iterator key and value 
		     ht_entry entry = table->entries[i];
		     it->key = entry.key;
		     it->value = entry.value;
		     return true;
		}
	}
	return false;
}
