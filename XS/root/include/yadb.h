/*
 * yadb.h
 *
 *  Created on: Oct 17, 2009
 *      Author: blabos
 */

#ifndef YADB_H_
#define YADB_H_

#include "pub_types.h"

void		yadb_start(char*);
int			yadb_load();
int			yadb_save();

void		yadb_dump();
status_t	yadb_status();

int			yadb_insert(record_t*);
int			yadb_update(record_t*);
int			yadb_delete(char*);
int			yadb_select(char*, record_t*);


#endif /* YADB_H_ */
