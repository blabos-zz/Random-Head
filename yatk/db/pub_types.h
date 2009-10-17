/*
 * pub_types.h
 *
 *  Created on: Oct 17, 2009
 *      Author: wesley
 */

#ifndef PUB_TYPES_H_
#define PUB_TYPES_H_

#define MAX_STR		20
#define BOOLEAN		int
#define TRUE		1
#define	FALSE		0

typedef char yastr_t[MAX_STR + 1];

typedef struct {
	yastr_t	key;
	yastr_t val;
} record_t;

#endif /* PUB_TYPES_H_ */
