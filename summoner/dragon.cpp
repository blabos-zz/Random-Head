#include "dragon.h"

void Dragon::growUP( void* cmd ) const {
   string* order = (string*)(cmd);
   cout << "Dragon growUP receiving order to " << *order << endl;
   cout << "Dragon " <<  *order << "..." << endl;
   
   emit( signalEmitCommand( cmd , this ) );
}

// the class factories
extern "C" Monster* createDragon() {
    return new Dragon;
}

extern "C" void destroyDragon( Monster* m ) {
    delete m;
}
