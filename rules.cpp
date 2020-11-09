#include "rules.h"
#include "facts.h"
#include "mainwindow.h"

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
