#include "rules.h"
#include "facts.h"
#include "mainwindow.h"
#include <QDebug>
#include <QMessageBox>

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

QString Rules::showRules()
{
    QString meg;
    qDebug()<<"所有规则如下：";
    meg+="所有规则如下：";
    meg+='\n';
    int index=1;
    Rule* p=front;
    while(p->next!=NULL)
    {
        meg+="规则"+QString::number(index)+":\n"+"\t";
        qDebug()<<"规则"<<index++<<":\n"<<"前提：";
        for(int i=0;i<p->next->n_pre;++i)
        {
            qDebug()<<p->next->premise[i];
            meg+=p->next->premise[i];
            if(i!=p->next->n_pre-1) meg+=",";
        }
        qDebug()<<"推论：\n"<<p->next->interence;
        meg+="==>"+p->next->interence;
        meg+='\n';

        p=p->next;
    }
    return meg;
}
