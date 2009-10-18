/*
 * main.cpp
 *
 *  Created on: Oct 17, 2009
 *      Author: wesley
 */
#include <yatk/db/yadb.h>

#include <cstdlib>

int main(int argc, char** argv) {
	if (argc != 2) {
		return EXIT_FAILURE;
	}
	
	yatk::db::yadb* db = yatk::db::yadb::instance();
	
	db->load(argv[1]);
	
	yatk::db::yadb::destroy();
	
	return EXIT_SUCCESS;
}
