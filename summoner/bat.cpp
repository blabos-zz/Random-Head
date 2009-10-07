#include "bat.h"

void Bat::growUP( void* cmd ) const {
   string* order = (string*)(cmd);
   cout << "Bat growUP receiving order to " << *order << endl;
   cout << "Bat " <<  *order << "..." << endl;
   
   emit( signalEmitCommand( cmd , this ) );
}

// the class factories
extern "C" Monster* createBat() {
    return new Bat;
}

extern "C" void destroyBat( Monster* m ) {
    delete m;
}
