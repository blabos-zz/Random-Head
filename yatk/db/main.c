/*
 * main.c
 *
 *  Created on: Oct 17, 2009
 *      Author: blabos
 */
#include "yadb.h"
#include "yadb_data.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv) {
	record_t record;
	
	yadb_start(argv[1] ? argv[1] : "foo.bin");
	
	int ret = yadb_load();
	printf("RET: %d\n", ret);
	
	yadb_dump();
	
	/*yadb_select("7", &record);
	
	printf("KEY: %s\n", record.key);
	
	yadb_dump();*/
	
	return EXIT_SUCCESS;
}
