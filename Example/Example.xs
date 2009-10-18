#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"

#include <yatk/db/yadb.h>


MODULE = Example		PACKAGE = Example


void init(filename)
	char* filename
CODE:
	yadb_start(filename);


int load()
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


int add(key, val)
	char* key
	char* val
CODE:
	RETVAL = yadb_insert(key, val);
OUTPUT:
	RETVAL


int upd(key, val)
	char* key
	char* val
CODE:
	RETVAL = yadb_update(key, val);
OUTPUT:
	RETVAL


int del(key)
	char* key
CODE:
	RETVAL = yadb_delete(key);
OUTPUT:
	RETVAL


HV* get(key)
	char* key
PREINIT:
	record_t record;
	HV* data;
CODE:
	if (yadb_select(key, &record)) {
		data = (HV*)sv_2mortal((SV*)newHV());
		
		hv_store_ent(data, newSVpv(record.key, 0), newSVpv(record.val, 0), 0);
		
		RETVAL = data;
	}
	else {
		XSRETURN_UNDEF;
	}
OUTPUT:
	RETVAL
