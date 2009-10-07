#ifndef SUMMONER_H
#define SUMMONER_H

#include <iostream>
#include <typeinfo>

#include <QObject>

#include "monster.h"
#include "bat.h"
#include "dragon.h"
#include "serpent.h"

#include <dlfcn.h>

using namespace std;

class Summoner : public QObject{
   Q_OBJECT
   
public:
   Summoner();
   ~Summoner();
   
   void getAction();
   void summons();
   
public slots:
   void slotReceiveMonster( void* , const Bat* );
   void slotReceiveMonster( void* , const Dragon* );
   void slotReceiveMonster( void* , const Serpent* );
private:
   string command;
   string monster;
   
   
   void* libmonster;
   
   create_t* create_monster;
   destroy_t* destroy_monster;
   Monster* m;
};

#endif

// New line at end of me :)
