#ifndef PET_H
#define PET_H

#include <QObject>
#include <QString>

class Pet : public QObject {

Q_OBJECT

public:
    explicit Pet(QString name, QObject* parent = 0)
                : _name(name), QObject(parent) {}
    virtual ~Pet() {}

protected:
    QString _name;

public slots:
    virtual void say() = 0;
};

#endif

