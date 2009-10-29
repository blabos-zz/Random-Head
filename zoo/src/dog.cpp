#include "dog.h"

Dog::Dog(QString name, QObject parent)
    : Pet(name, parent) {
    // Nothing here...
}

void Dog::say() {
    qDebug() << _name << " says: auau!!!";
}

