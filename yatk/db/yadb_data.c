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

BOOLEAN	ins_node(yadb_t* db, char* key, char* val) {
	BOOLEAN ret = FALSE;
	
	node_t* node = _new_node();
	
	if (node) {
		upd_node(node, key, val);
		
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
		
		ret = TRUE;
	}
	
	return ret;
}

void upd_node(node_t* node, char* key, char* val) {
	memset(&(node->data), 0, sizeof(record_t));
	
	strncpy(node->data.key, key, MAX_STR);
	strncpy(node->data.val, val, MAX_STR);
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

void dump_node(node_t* node) {
	printf("%10p <- %10p -> %10p: {%20s -> %20s}\n",
				node->prev, node, node->next,
				node->data.key,
				node->data.val);
}

void dump_db(yadb_t* db) {
	printf("File: '%s'\n", db->filename);
	printf("Head: %10p\n", db->head);
	printf("Tail: %10p\n", db->tail);
	printf("Size: %10d\n", db->size);
	
	node_t* it = _db_begin(db);
	
	if (it) {
		printf("Data: \n\n");
	}
	
	for (it = _db_begin(db); it != _db_end(db); it = it->next) {
		dump_node(it);
	}
}

BOOLEAN	load(yadb_t* db) {
	BOOLEAN ret = FALSE;
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
			BOOLEAN status;
			
			for (i = 0; i < rows; i++) {
				count = fread((void*)(&record), sizeof(record_t), 1, fp);
				if (count == 1) {
					status = ins_node(db, record.key, record.val);
					if (status != TRUE) {
						fclose(fp);
						return ret;
					}
				}
				else {
					fclose(fp);
					return ret;
				}
			}
			
			ret = TRUE;
		}
		
		fclose(fp);
	}
	
	return ret;
}
BOOLEAN	save(yadb_t* db) {
	BOOLEAN ret = FALSE;
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
			
			ret = TRUE;
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
