#include "monster.h"

#ifndef BAT_H
#define BAT_H

#include <QObject>
#include <QString>

class Bat : public Monster {

Q_OBJECT

public:
   void growUP( void* cmd ) const;
   
private:
   QString className;
   
signals:
   void signalEmitCommand( void* , const Bat* ) const;
};

// the class factories
extern "C" Monster* createBat();
extern "C" void destroyBat( Monster* m );

#endif

// New line at end of me :)
