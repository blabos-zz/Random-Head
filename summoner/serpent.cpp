#include "serpent.h"

void Serpent::growUP( void* cmd ) const {
   string* order = (string*)(cmd);
   cout << "Serpent growUP receiving order to " << *order << endl;
   cout << "Serpent " <<  *order << "..." << endl;
   
   emit( signalEmitCommand( cmd , this ) );
}

// the class factories
extern "C" Monster* createSerpent() {
    return new Serpent;
}

extern "C" void destroySerpent( Monster* m ) {
    delete m;
}
