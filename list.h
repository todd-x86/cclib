#ifndef __LIST_H
#define __LIST_H
#include <stdbool.h>
#include <string.h>
// List usage (as a percent) to force reallocation
#define CL_LIST_SIZE_THRESHOLD 0.75
// List expansion factor (new_size = current_size * list_expand_factor)
#define CL_LIST_EXPAND_FACTOR 1.5

// [List]
// Defines a list/vector of type T with name prefix name N
/// --------------------------------
/// N_list*		N_list_create(int size)
///		- Creates and allocates memory for a resizable array on the heap.
///		- @param size - Initial size of the array in terms of number of elements
///		- @return N_list allocated, NULL if heap memory exhausted
/// --------------------------------
/// N_list*		N_list_new(void)
///		- Creates a new N_list with an initial size of 4 elements
///		- @returns N_list allocated, NULL if heap memory exhausted
/// --------------------------------
/// int			N_list_count(N_list* list)
///		- Returns the number of items in the N_list.
///		- @param list The list struct to count
///		- @returns Number of elements stored in the list
/// --------------------------------
/// bool		N_list_expand(N_list* list, int size)
///		- Expands the list to a specific size.  If the size is less than the number 
///		  of elements in the list, expansion returns false.
///		- @param list List struct
///		- @param size New size of the list
///		- @returns true if reallocation succeeded, false if not
/// --------------------------------
/// T			N_list_get(N_list* list, int index)
///		- Retrieves one element from the list.  Memory access errors may occur if
///		  an element is not at the specified index.
///		- @param list The list to read
///		- @param index The index (0 <= index < count) to access
///		- @returns The element at the specified index
/// --------------------------------
/// T			N_list_delete(N_list* list, int index)
///		- Removes an element from the list at a specified index.
///		- @param list The list to access
///		- @param index The index (0 <= index < count) of the element to remove
///		- @returns Removed element from the specified index
/// --------------------------------
/// void 		N_list_resize(N_list* list)
///		- Resizes the list if the element count reaches the resize threshold
///		  (CL_LIST_SIZE_THRESHOLD * list->size).
///		- @param list The list to resize
/// --------------------------------
/// bool 		N_list_set(N_list* list, int index, T item)
///		- Sets the element at a specific index in the list.  If the element index
///		  does not exist, false is returned.
///		- @param list The list to access
///		- @param index The index of the element to modify
///		- @param item The replacement item
///		- @returns true if access and modification succeeded
/// --------------------------------
/// bool 		N_list_insert(N_list* list, int index, T item)
///		- Inserts an element at an arbitrary position in the list.  If the index
///		  is beyond the size of the list, the list is resized and memory is zeroed
///		  out for empty element space between the last insertion and the specified index.
///		  For indices specifying an existing element index, the previous element is shifted
///		  along with all successive elements forward to make room for the new element.
///		- @param list The list to access
///		- @param index The index to insert the new element
///		- @param item The new element to insert
///		- @returns true if insertion succeeded
/// --------------------------------
/// bool 		N_list_add(N_list* list, T item)
///		- Adds an element to the end of the list.  If the size is too small, the list is expanded.
///		- @param list The list to access
///		- @param item New item to insert
///		- @returns true if insertion succeeded
/// --------------------------------
#define DEFINE_LIST(T, N)	\
	typedef struct {	\
		T* items;	\
		int count;	\
		int size;	\
	} N##_list;	\
	\
	N##_list* N##_list_create(int size)	\
	{	\
		N##_list* result = (N##_list*)malloc(sizeof(N##_list));	\
		if(!result)	\
			return result;	\
		result->items = (T*)malloc(sizeof(T)*size);	\
		if (!result->items) {	\
			free(result);	\
			return NULL;	\
		}	\
		result->size = size;	\
		result->count = 0;	\
		return result;	\
	}	\
	\
	N##_list* N##_list_new(void) {	\
		return N##_list_create(4);	\
	}	\
	\
	int N##_list_count(N##_list* list)	\
	{	\
		return list->count;	\
	}	\
	\
	bool N##_list_expand(N##_list* list, int size)	\
	{	\
		if(size < list->count)	\
			return false;	\
		T* new_items = (T*)realloc(list->items, sizeof(T)*size);	\
		if (!new_items)	\
			return false;	\
		if(new_items != list->items){	\
			memmove(new_items, list->items, list->size*sizeof(T));	\
			free(list->items);	\
			list->items = new_items;	\
		}	\
		list->size = size;	\
		return true;	\
	}	\
	\
	T N##_list_get(N##_list* list, int index)	\
	{	\
		return list->items[index];	\
	}	\
	\
	T N##_list_delete(N##_list* list, int index)	\
	{	\
		T tmp = list->items[index];	\
		int size = (list->count-index-1)*sizeof(T);	\
		list->count--;	\
		if (size > 0) {	\
			memmove(list->items+index, list->items+index+1, size);	\
			memset(list->items+index+1, 0, sizeof(T));	\
		}	\
		return tmp;	\
	}	\
	\
	void N##_list_resize(N##_list* list)	\
	{	\
		while (list->count >= (double)list->size*CL_LIST_SIZE_THRESHOLD){	\
			N##_list_expand(list, (double)list->size*CL_LIST_EXPAND_FACTOR);	\
		}	\
	}	\
	\
	bool N##_list_set(N##_list* list, int index, T item)	\
	{	\
		if (index < 0 || index >= list->count)	\
			return false;	\
		list->items[index] = item;	\
		return true;	\
	}	\
	\
	bool N##_list_insert(N##_list* list, int index, T item)	\
	{	\
		if (index < 0)	\
			return false;	\
		\
		int before_count = list->count;	\
		if (index >= list->count) {	\
			list->count += (index-list->count)+1;	\
			N##_list_resize(list);	\
			memset(list->items + before_count, 0, (list->count-before_count-1)*sizeof(T));	\
		} else {	\
			list->count++;	\
			N##_list_resize(list);	\
			memmove(list->items + index+1, list->items + index, sizeof(T)*(list->count - index - 1));	\
		}	\
		return N##_list_set(list, index, item);	\
	}	\
	\
	bool N##_list_add(N##_list* list, T item)	\
	{	\
		return N##_list_insert(list, list->count, item);	\
	}

#endif
