#include "summoner.h"
#include <stdlib.h>


Summoner::Summoner(){
   cout << "\n--------------------------------------------\n";
   cout << "A Summoner was born..." << endl;
   
   libmonster = dlopen("./lib/libmonster.so", RTLD_LAZY );
   if (!libmonster) {
      cerr << "Cannot load library: " << dlerror() << '\n';
      exit(1);
   }
   
   // reset errors
   dlerror();
}

Summoner::~Summoner(){
   cout << "An Summoner was killed..." << endl;
   
   // unload the triangle library
   dlclose(libmonster);
}
   
void Summoner::getAction(){
   cout << "--------------------------------------------" << endl;
   cout << "Get-me a Monster to summons: ";
   cin >> monster;
   cout << endl;
   cout << "Get-me a Command to Monster: ";
   cin >> command;
   cout << endl;
   
   string symbols;
   create_monster = NULL;
   destroy_monster= NULL;
   
   // load the symbols
   symbols = "create" + monster;
   create_monster = (create_t*) dlsym(libmonster, symbols.c_str() );
   const char* dlsym_error = dlerror();
   if (dlsym_error) {
      cerr << "Cannot load symbol create: " << dlsym_error << '\n';
      return;
   }
   
   symbols = "destroy" + monster;
   destroy_monster = (destroy_t*) dlsym(libmonster, symbols.c_str() );
   dlsym_error = dlerror();
   if (dlsym_error) {
      cerr << "Cannot load symbol destroy: " << dlsym_error << '\n';
      return;
   }
}

void Summoner::summons(){

   if ( create_monster == NULL ) return;

   cout << "Summoner: \"Call monster: " << monster << "\"...\n";
   cout << "Summoner: \"Ordering: " << command << "\"...\n";
   
   // create an instance of the class
   m = create_monster();
   connect( m , SIGNAL( signalEmitCommand( void* , const Bat* ) ) , this , SLOT( slotReceiveMonster( void* , const Bat* ) ) );
   connect( m , SIGNAL( signalEmitCommand( void* , const Dragon* ) ) , this , SLOT( slotReceiveMonster( void* , const Dragon* ) ) );
   connect( m , SIGNAL( signalEmitCommand( void* , const Serpent* ) ) , this , SLOT( slotReceiveMonster( void* , const Serpent* ) ) );

   // use the class
   std::string* str = new string();
   str->insert(0,command);
   m->growUP((void*)(str));

   // destroy the class
   destroy_monster(m);
   disconnect ( this , SLOT(slotReceiveMonster(void*,const Bat*)) );
   disconnect ( this , SLOT(slotReceiveMonster(void*,const Dragon*)) );
   disconnect ( this , SLOT(slotReceiveMonster(void*,const Serpent*)) );
}


void Summoner::slotReceiveMonster( void* v , const Bat* b ){
   string* st = (string*)(v);
   cout << "I wait for Bat" << endl;
   cout << "I received a Monster: " << typeid(b).name() << endl;
   cout << "I received a Message: " << st->c_str()  << endl;
}

void Summoner::slotReceiveMonster( void* v , const Dragon* d ){
   string* st = (string*)(v);
   cout << "I wait for Dragon" << endl;
   cout << "I received a Monster: " << typeid(d).name() << endl;
   cout << "I received a Message: " << st->c_str()  << endl;
}

void Summoner::slotReceiveMonster( void* v , const Serpent* s ){
   string* st = (string*)(v);
   cout << "I wait for Dragon" << endl;
   cout << "I received a Monster: " << typeid(s).name() << endl;
   cout << "I received a Message: " << st->c_str()  << endl;
}


// New line at end of me :)
