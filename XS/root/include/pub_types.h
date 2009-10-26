/*
 * pub_types.h
 *
 *  Created on: Oct 17, 2009
 *      Author: wesley
 */

#ifndef PUB_TYPES_H_
#define PUB_TYPES_H_

#define MAX_STR		15

typedef char yastr_t[MAX_STR + 1];

typedef struct {
	yastr_t	key;
	yastr_t val;
} record_t;

typedef struct {
	yastr_t	filename;
	int		elements;
	int		header_bytes;
	int		body_bytes;
	int		total_bytes;
} status_t;

#endif /* PUB_TYPES_H_ */
