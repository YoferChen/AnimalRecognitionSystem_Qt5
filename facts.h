#include "mainwindow.h"
#ifndef FACTS_H
#define FACTS_H


class Facts
{
public:
    Facts();
//    void add(char* fact);  //添加事实
    void add(QString fact);  //添加事实到事实库
//    bool checkAndAdd(char *fact);  //检查事实库是否存在事实，若不存在，则将事实加入事实库
    bool checkAndAdd(QString fact);  //检查事实库是否存在事实，若不存在，则将事实加入事实库
private:
    int n_facts=0;
//    char facts[100][128];  //事实库
    QString facts[100];
};

#endif // FACTS_H
