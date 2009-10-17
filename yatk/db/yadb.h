/*
 * yadb.h
 *
 *  Created on: Oct 17, 2009
 *      Author: blabos
 */

#ifndef YADB_H_
#define YADB_H_

#include "pub_types.h"

void yadb_start(char*);
BOOLEAN yadb_load();
BOOLEAN yadb_save();

void yadb_dump();

BOOLEAN yadb_insert(char*, char*);
BOOLEAN yadb_update(char*, char*);
BOOLEAN yadb_delete(char*);
BOOLEAN yadb_select(char*, record_t*);


#endif /* YADB_H_ */
