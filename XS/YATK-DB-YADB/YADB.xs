#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"

#include "ppport.h"

#include <yadb.h>


MODULE = YATK::DB::YADB		PACKAGE = YATK::DB::YADB		


void init(filename)
	char* filename
CODE:
	yadb_start(filename);


int load();
CODE:
	RETVAL = yadb_load();
OUTPUT:
	RETVAL


int save()
CODE:
	RETVAL = yadb_save();
OUTPUT:
	RETVAL


void dump()
CODE:
	yadb_dump();


status_t status()
CODE:
	RETVAL = yadb_status();
OUTPUT:
	RETVAL


int add(record)
	record_t record;
CODE:
	RETVAL = yadb_insert(&record);
OUTPUT:
	RETVAL


int upd(record)
	record_t record
CODE:
	RETVAL = yadb_update(&record);
OUTPUT:
	RETVAL


int del(key)
	char* key
CODE:
	RETVAL = yadb_delete(key);
OUTPUT:
	RETVAL


record_t get(key)
	char* key
CODE:
	if (!yadb_select(key, &RETVAL)) {
		XSRETURN_UNDEF;
	}
OUTPUT:
	RETVAL

