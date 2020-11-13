#include "mainwindow.h"
#include "facts.h"
#ifndef RULES_H
#define RULES_H

//class Rule{
//public:
//    int n_pre;  //前提数量
//    char **premise;  //前提
//    char *inference;  //推论
//public:
//    Rule(){
//        premise=new char*(255);

//    }
//};

struct Rule{
    int n_pre;  //前提数量（只有所有前提同时满足，才得出推论）
//    char premise[10][255];  //前提（可能有多条）
    QString premise[10];  //前提（可能有多条）
//    /*char*/ inference[255];  //推论
    QString interence;  //推论
    Rule *next;

};

class Rules
{
private:
    int n_rules=0;  //规则数量
    Rule* front;  //最大100条规则（带头结点）
    Rule * rear;

public:
    Rules();
    int getRulesNum();
    void addRule(Rule* rule);
    void rmRule(int index);  //移除指定序号的规则（序号从0开始）
    void showRules();

};

#endif // RULES_H
