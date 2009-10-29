#ifndef DOG_H
#define DOG_H

#include "pet.h"

#include <QObject>
#include <QString>

class Dog : public Pet {

Q_OBJECT

public:
    explicit Dog(QString name, QObject* parent = 0);
    virtual ~Dog();

public slots:
    virtual void say();
    
};

#endif

