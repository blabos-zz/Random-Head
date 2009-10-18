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

int yadb_load() {
	load(yadb());
}

int yadb_save() {
	save(yadb());
}

void yadb_dump() {
	dump_db(yadb());
}

int yadb_insert(char* key, char* val) {
	return ins_node(yadb(), key, val);
}

int yadb_update(char* key, char* val) {
	int ret = 0;
	
	node_t* node = find_node(yadb(), key);
	
	if (node) {
		upd_node(node, key, val);
		ret = 1;
	}
	
	return ret;
}

int yadb_delete(char* key) {
	int ret = 0;
	
	node_t* node = find_node(yadb(), key);
	
	if (node) {
		del_node(yadb(), node);
		ret = 1;
	}
	
	return ret;
}
int yadb_select(char* key, record_t* record) {
	int ret = 0;
	
	node_t* node = find_node(yadb(), key);
	
	if (node) {
		memcpy(record, &(node->data), sizeof(record_t));
		ret = 1;
	}
	
	return ret;
}

yadb_t* yadb() {
	static yadb_t _db;
	
	return &_db;
}
