/*
 * yadb.c
 *
 *  Created on: Oct 17, 2009
 *      Author: blabos
 */

#include "yadb.h"
#include "yadb_data.h"

#include <string.h>

yadb_t* yadb();

void yadb_start(char* filename) {
	memset(yadb()->filename, 0, sizeof(yadb()->filename));
	strncpy(yadb()->filename, filename, MAX_STR);
}

BOOLEAN yadb_load() {
	load(yadb());
}

BOOLEAN yadb_save() {
	save(yadb());
}

void yadb_dump() {
	dump_db(yadb());
}

BOOLEAN yadb_insert(char* key, char* val) {
	return ins_node(yadb(), key, val);
}

BOOLEAN yadb_update(char* key, char* val) {
	BOOLEAN ret = FALSE;
	
	node_t* node = find_node(yadb(), key);
	
	if (node) {
		upd_node(node, key, val);
		ret = TRUE;
	}
	
	return ret;
}

BOOLEAN yadb_delete(char* key) {
	BOOLEAN ret = FALSE;
	
	node_t* node = find_node(yadb(), key);
	
	if (node) {
		del_node(yadb(), node);
		ret = TRUE;
	}
	
	return ret;
}
BOOLEAN yadb_select(char* key, record_t* record) {
	BOOLEAN ret = FALSE;
	
	node_t* node = find_node(yadb(), key);
	
	if (node) {
		memcpy(record, &(node->data), sizeof(record_t));
		ret = TRUE;
	}
	
	return ret;
}

yadb_t* yadb() {
	static yadb_t _db;
	
	return &_db;
}
