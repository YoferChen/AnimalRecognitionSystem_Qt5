#include "facts.h"
#include "string.h"
#include <QDebug>

Facts::Facts()
{

}

/*
void Facts::add(char* fact)
{
    strcpy(facts[n_facts],fact);
    n_facts++;
}

bool Facts::checkAndAdd(char* fact)
{
    int flag=true;  //是否加入事实库
    for(int i=0;i<n_facts;++i)
    {
        if(strcmp(fact,facts[i])==0)  //两个字符串相等，返回0
            flag=false;
    }
    if(flag==true)
    {
        add(fact);  //事实库不存在该事实，则加入事实库
    }
    return flag;  //返回是否添加到事实库
}*/

void Facts::add(QString fact)
{
    facts[n_facts]=fact;
    n_facts++;
}

int Facts::getFactsNum()
{
    return n_facts;
}

bool Facts::checkAndAdd(QString fact)  //检查事实库并添加不存在的事实
{
    int flag=true;  //是否加入事实库
    for(int i=0;i<n_facts;++i)
    {
        if(fact==facts[i])  //两个字符串相等，返回0
            flag=false;
    }
    if(flag==true)
    {
        add(fact);  //事实库不存在该事实，则加入事实库
    }
    return flag;  //返回是否添加到事实库
}

void Facts::showFacts()
{
    int index=1;
    for(int i=0;i<n_facts;++i)
    {
        qDebug()<<"事实"<<index++<<":"<<facts[i];
    }
}
