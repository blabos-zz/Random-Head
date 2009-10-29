#include "cat.h"

Cat::Cat(QString name, QObject parent)
    : Pet(name, parent) {
    // Nothing here...
}

void Cat::say() {
    qDebug() << _name << " says: meow!!!";
}

