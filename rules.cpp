#include "rules.h"
#include "facts.h"
#include "mainwindow.h"
#include <QDebug>

Rules::Rules()
{
    front=new Rule();
    front->next=NULL;
    rear=front;
}

int Rules::getRulesNum()
{
    return n_rules;
}

void Rules::addRule(Rule* rule)  //加入规则库
{
    rear->next=rule;  //加到链表尾部
    rear=rule;
    n_rules++;
}

void Rules::rmRule(int index)
{
    Rule* p=front;
    for(int i=0;i<index;++i)
    {
        p=p->next;
    }
    Rule* tmp=p->next;
    p->next=p->next->next;
    delete tmp;
    n_rules--;
}

void Rules::showRules()
{
    qDebug()<<"所有规则如下：";
    int index=1;
    Rule* p=front;
    while(p->next!=NULL)
    {
        qDebug()<<"规则"<<index++<<":\n"<<"前提：";
        for(int i=0;i<p->next->n_pre;++i)
        {
            qDebug()<<p->next->premise[i];
        }
        qDebug()<<"推论：\n"<<p->next->interence;

        p=p->next;
    }
}
