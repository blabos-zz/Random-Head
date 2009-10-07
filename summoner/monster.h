#ifndef MONSTER_H
#define MONSTER_H

#include <iostream>
#include <QObject>

using namespace std;

class Monster : public QObject {

Q_OBJECT

public:
    Monster();
    virtual ~Monster(){}
    virtual void growUP( void* ) const = 0;
};

// the types of the class factories
typedef Monster* create_t();
typedef void destroy_t(Monster*);

#endif
