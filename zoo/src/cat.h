#ifndef CAT_H
#define CAT_H

#include "pet.h"

#include <QObject>
#include <QString>

class Cat : public Pet {

Q_OBJECT

public:
    explicit Cat(QString name, QObject* parent = 0);
    virtual ~Cat();

public slots:
    virtual void say();
    
};

#endif

