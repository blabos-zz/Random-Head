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
void		upd_node(node_t*, char*, char*);
void	 	del_node(yadb_t*, node_t*);
node_t* 	find_node(yadb_t*, char*);

void		dump_node(node_t*);
void		dump_db(yadb_t*);
int			load(yadb_t*);
int			save(yadb_t*);

#endif /* YADB_DATA_H_ */
