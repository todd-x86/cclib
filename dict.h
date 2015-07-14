#ifndef __DICT_H
#define __DICT_H
#include <stdbool.h>

/// Required definitions: N_hash_equals, unsigned long N_hash_compute
#define DEFINE_DICT(T1, T2, N) \
	typedef struct {	\
		T1 key;	\
		T2 value;	\
		int next_index;	\
		unsigned long hash;	\
	} N##_dict_item;	\
	\
	typedef struct {	\
		N##_dict_item* items;	\
		int size;	\
		int count;	\
	} N##_dict;	\
	\
	/* Forward declarations */	\
	unsigned long	N##_hash_compute(T1 key);	\
	bool 			N##_hash_equals(T1 key1, T2 key2);	\
	\
	N##_dict* N##_dict_create(int size)	\
	{	\
		N##_dict* result = (N##_dict*)malloc(sizeof(N##_dict));	\
		if (!result) return NULL;	\
		result->items = (N##_dict_item*)malloc(sizeof(N##_dict_item)*size);	\
		if (!result->items) {	\
			free(result);	\
			return NULL;	\
		}	\
		result->size = size;	\
		result->count = 0;	\
		return result;	\
	}	\
	\
	N##_dict* N##_dict_new()	\
	{	\
		return N##_dict_create(7);	\
	}	\
	\
	T2 N##_dict_get(N##_dict* dict, T1 key)	\
	{	\
		unsigned long index = N##_dict_indexof(key);
		
	}

	unsigned long N##_dict_indexof(T1 key)
	{
		
	}

	unsigned long idx = N##_hash_compute(key) % dict->size;	\
		while (dict->items[idx] == NULL || !N##_hash_equals(key, dict->items[idx]->key))	\
		{	\
			return dict->items[idx]->value;	\
		}	\

// [Common dictionary Hash Functions]
/// (char*) str_hash_func [DJB2]
unsigned long djb2_hash(char* str)
{
	unsigned long hash = 5381;
	char c;

	while (c = *str++)
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

	return hash;
}

#endif
