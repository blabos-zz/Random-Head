/*
 * yadb_data.c
 *
 *  Created on: Oct 17, 2009
 *      Author: wesley
 */
#include "yadb_data.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

node_t*	_new_node();
void	_del_node(node_t*);

node_t*	_db_begin(yadb_t*);
node_t* _db_end(yadb_t*);
void	_db_clear(yadb_t*);

void 	_set_record(record_t*, char*, char*);


yadb_t* new_db() {
	yadb_t* db = (yadb_t*)malloc(sizeof(yadb_t));
	
	db->head = db->tail = (void*)(db->size = 0);
	
	return db;
}

void del_db(yadb_t* db) {
	_db_clear(db);
	free(db);
}

int	ins_node(yadb_t* db, char* key, char* val) {
	int ret = 0;
	
	node_t* node = _new_node();
	
	if (node) {
		record_t rec;
		strncpy(rec.key, key, MAX_STR);
		strncpy(rec.val, val, MAX_STR);
		upd_node(node, &rec);
		
		if (db->tail == NULL) {
			db->tail = node;
		}
		
		if (db->head == NULL) {
			db->head = node;
		}
		else {
			node->next		= db->head;
			db->head->prev	= node;
			db->head		= node;
		}
		
		db->size++;
		
		ret = 1;
	}
	
	return ret;
}

void upd_node(node_t* node, record_t* record) {
	memcpy(&(node->data), record, sizeof(record_t));
}

void del_node(yadb_t* db , node_t* node) {
	if (db->head == db->tail) {
		db->head = db->tail = NULL;
	}
	else if (node == db->head) {
		db->head = node->next;
		if (db->head) db->head->prev = NULL;
	}
	else if (node == db->tail) {
		db->tail = node->prev;
		if (db->tail) db->tail->next = NULL;
	}
	else {
		node->prev->next = node->next;
		node->next->prev = node->prev;
	}
	
	_del_node(node);
}

node_t* find_node(yadb_t* db, char* key) {
	node_t* it;
	for (it = _db_begin(db); it != _db_end(db); it = it->next) {
		if (strncmp(key, it->data.key, MAX_STR) == 0) return it;
	}
	
	return NULL;
}

void node_dump(node_t* node) {
	printf("%10p <- %10p -> %10p: {%15s -> %15s}\n",
				node->prev, node, node->next,
				node->data.key,
				node->data.val);
}

void db_dump(yadb_t* db) {
	printf("File: '%s'\n", db->filename);
	printf("Head: %10p\n", db->head);
	printf("Tail: %10p\n", db->tail);
	printf("Size: %10d\n", db->size);
	
	node_t* it = _db_begin(db);
	
	if (it) {
		printf("Data: \n\n");
	}
	
	for (it = _db_begin(db); it != _db_end(db); it = it->next) {
		node_dump(it);
	}
}

status_t db_status(yadb_t* db) {
	status_t status;
	
	snprintf(status.filename, MAX_STR, "%s", db->filename);
	
	status.elements		= db->size;
	status.header_bytes	= sizeof(yadb_t);
	status.body_bytes	= db->size * sizeof(node_t);
	status.total_bytes	= status.header_bytes + status.body_bytes;
	
	return status;
}

int	load(yadb_t* db) {
	int ret = 0;
	FILE* fp;
	size_t count;
	int rows;
	
	if ((fp = fopen(db->filename, "rb")) != NULL) {
		{
			count = fread((void*)(&rows), sizeof(int), 1, fp);
			if (count != 1) {
				fclose(fp);
				return ret;
			}
		}
		
		{
			int i;
			record_t record;
			int status;
			
			for (i = 0; i < rows; i++) {
				count = fread((void*)(&record), sizeof(record_t), 1, fp);
				if (count == 1) {
					status = ins_node(db, record.key, record.val);
					if (status != 1) {
						fclose(fp);
						return ret;
					}
				}
				else {
					fclose(fp);
					return ret;
				}
			}
			
			ret = 1;
		}
		
		fclose(fp);
	}
	
	return ret;
}
int	save(yadb_t* db) {
	int ret = 0;
	FILE* fp;
	size_t count;
	
	if ((fp = fopen(db->filename, "wb")) != NULL) {
		{
			count = fwrite((void*)(&(db->size)), sizeof(int), 1, fp);
			if (count != 1) {
				fclose(fp);
				return ret;
			}
		}
		
		{
			node_t* it;
			
			for (it = _db_begin(db); it != _db_end(db); it = it->next) {
				count = fwrite((void*)(&(it->data)), sizeof(record_t), 1, fp);
				if (count != 1) {
					fclose(fp);
					return ret;
				}
			}
			
			ret = 1;
		}
		
		fclose(fp);
	}
	
	return ret;
}

node_t*	_new_node() {
	node_t* node = (node_t*)malloc(sizeof(node_t));
	
	if (node != NULL) {
		node->next = node->prev = NULL;
	}
	
	return node;
}

void _del_node(node_t* node) {
	free(node);
}

node_t*	_db_begin(yadb_t* db) {
	return db->head;
}

node_t* _db_end(yadb_t* db) {
	return NULL;
}

void _db_clear(yadb_t* db) {
	node_t* it;
	for (it = _db_begin(db); it != _db_end(db); it = it->next) {
		del_node(db, it);
	}
}
