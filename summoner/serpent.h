#ifndef SERPENT_H
#define SERPENT_H

#include "monster.h"

#include <QObject>
#include <QString>

class Serpent : public Monster {

Q_OBJECT

public:
   void growUP( void* cmd ) const;
   
private:
   QString className;
   
signals:
   void signalEmitCommand( void* , const Serpent* ) const;
};

// the class factories
extern "C" Monster* createSerpent();
extern "C" void destroySerpent( Monster* m );

#endif

// New line at end of me :)
