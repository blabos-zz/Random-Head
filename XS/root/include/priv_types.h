/*
 * priv_types.h
 *
 *  Created on: Oct 17, 2009
 *      Author: wesley
 */

#ifndef PRIV_TYPES_H_
#define PRIV_TYPES_H_

#include "pub_types.h"

struct node_st {
	record_t		data;
	struct node_st*	next;
	struct node_st*	prev;
};

typedef struct node_st node_t;

typedef struct {
	yastr_t	filename;
	int		size;
	node_t*	head;
	node_t* tail;
} yadb_t;


#endif /* PRIV_TYPES_H_ */
