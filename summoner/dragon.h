#ifndef DRAGON_H
#define DRAGON_H

#include "monster.h"

#include <QObject>
#include <QString>

class Dragon : public Monster {

Q_OBJECT

public:
   void growUP( void* cmd ) const;
   
private:
   QString className;
   
signals:
   void signalEmitCommand( void* , const Dragon* ) const;
};

// the class factories
extern "C" Monster* createDragon();
extern "C" void destroyDragon( Monster* m );

#endif

// New line at end of me :)
