/*
 * yadb_data.h
 *
 *  Created on: Oct 17, 2009
 *      Author: blabos
 */

#ifndef YADB_DATA_H_
#define YADB_DATA_H_

#include "priv_types.h"

yadb_t*		new_db();
void		del_db(yadb_t*);

int			ins_node(yadb_t*, char*, char*);
void		upd_node(node_t*, record_t*);
void	 	del_node(yadb_t*, node_t*);
node_t* 	find_node(yadb_t*, char*);

void		node_dump(node_t*);
void		db_dump(yadb_t*);
status_t	db_status(yadb_t*);

int			load(yadb_t*);
int			save(yadb_t*);

#endif /* YADB_DATA_H_ */
