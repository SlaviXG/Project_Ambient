#include "test_environment.h"

#include <QTest>

#include "Environment.h"
#include "cell.h"

Test_Environment::Test_Environment(QObject *parent) :
    QObject(parent)
{

}

void Test_Environment::Test_VisionField()
{
    Environment env(10, 10);
    env.AddCell(new Cell({1,1})); env.AddCell(new Cell({5,5})); env.AddCell(new Cell({9,9}));
    env.AddCell(new Cell({9,1})); env.AddCell(new Cell({2,9}));

    QVector<bool> field1 = env.getVisionField({1,0});
    QVector<bool> checkVec1 = {0,0,0,0,0,
                              0,0,0,0,0,
                              0,0,  1,0,
                              0,0,0,0,0,
                              0,0,0,0,0};
    for(int i = 0; i < 24; i++){
        qDebug() << field1[i] <<" " << checkVec1[i];
        QCOMPARE(field1[i], checkVec1[i]);
    }

    QVector<bool> field2 = env.getVisionField({8,8});
    QVector<bool> checkVec2 = {0,0,0,0,0,
               0,0,0,0,0,
               0,0,  0,0,
               0,0,0,1,0,
               0,0,0,0,0};  
    for(int i = 0; i < 24; i++){
        QCOMPARE(field2[i], checkVec2[i]);
    }

    QVector<bool> field3 = env.getVisionField({9,0});
    QVector<bool> checkVec3 = {0,0,0,0,0,
               0,0,0,0,0,
               0,0,  1,0,
               0,0,0,0,0,
               0,0,0,0,0};  
    for(int i = 0; i < 24; i++){
        QCOMPARE(field3[i], checkVec3[i]);
    }

    QVector<bool> field4 = env.getVisionField({1,9});
    QVector<bool> checkVec4 = {0,0,0,0,0,
               0,0,0,0,0,
               0,0,  0,0,
               0,0,1,0,0,
               0,0,0,0,0};  
    for(int i = 0; i < 24; i++){
        QCOMPARE(field4[i], checkVec4[i]);
    }
}
