#ifndef TEST_ENVIRONMENT_H
#define TEST_ENVIRONMENT_H

#include <QObject>

class Test_Environment : public QObject
{
    Q_OBJECT
public:
    explicit Test_Environment(QObject *parent = 0);

private slots:
    void Test_VisionField();
};

#endif // TEST_ENVIRONMENT_H