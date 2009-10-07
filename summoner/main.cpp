#include <iostream>

#include "summoner.h"
#include "monster.h"

#include <dlfcn.h>

int main() {
    Summoner* summ = new Summoner();
    
    int i = 0;
    while ( i < 10 ){
      summ->getAction();
      summ->summons();
      i++;
    }
}

// New line at end of me :)
