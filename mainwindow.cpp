#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QCheckBox>
#include <QPushButton>
#include "addrulesdialog.h"
#include <rules.h>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    QCheckBox *check1=new QCheckBox(ui->scrollArea);
//    check1->setText("test");
//    QCheckBox *check2=new QCheckBox(ui->scrollArea);
//    check1->setText("test");
//    QCheckBox *check3=new QCheckBox(ui->scrollArea);
//    check1->setText("test");
//    QCheckBox *check4=new QCheckBox(ui->scrollArea);
//    check1->setText("test");
//    QCheckBox *check5=new QCheckBox(ui->scrollArea);
//    check1->setText("test");
//    QCheckBox *check6=new QCheckBox(ui->scrollArea);
//    check1->setText("test");
//    ui->scrollArea->setAlignment(Qt::AlignVCenter);

    pLayout = new QGridLayout();//网格布局
    ui->scrollArea->widget()->setLayout(pLayout);//把布局放置到QScrollArea的内部QWidget中
    pLayout->setAlignment(Qt::AlignTop);

//    for(int i = 0; i < 5; i++)
//    {
////        QPushButton *pBtn = new QPushButton();
////        pBtn->setText(QString("按钮%1").arg(i));
////        pBtn->setMinimumSize(QSize(60,30));   //width height
////        pLayout->addWidget(pBtn);//把按钮添加到布局控件中
//        if(i%2==0)
//        {
//            QCheckBox *pCheck=new QCheckBox();
//            pCheck->setText(QString("选项%1").arg(i));
//            pCheck->setMinimumSize(QSize(60,30));
//            pLayout->addWidget(pCheck,i/2,0);//把选项添加到布局控件中,第二个参数和第三个参数分别表示控件放置在第几行第几列
//        }
//        else
//        {
//            QCheckBox *pCheck=new QCheckBox();
//            pCheck->setText(QString("选项%1").arg(i));
//            pCheck->setMinimumSize(QSize(60,30));
//            pLayout->addWidget(pCheck,i/2,1);//把选项添加到布局控件中
//        }

//    }

    //点击添加规则按钮弹出窗口
    connect(ui->btn_add_rule,&QPushButton::clicked,[=](){
        //弹出窗口
        qDebug()<<"弹出添加规则窗口！\n";
//        AddRulesDialog addRulesDialog;
//        addRulesDialog.exec();
        createAddRuleDialog();
    }
    );

    initRules();

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::createAddRuleDialog()
{
    addRulesDialog=new AddRulesDialog();
    addRulesDialog->exec();
}

void MainWindow::addRuleToList(Rule *rule,int index)  //添加规则到list控件中
{
    int n_pre=rule->n_pre;
    QString text;  //显示问信息
    text+=QString::number(index);
    text+="  ";
    for(int i=0;i<n_pre;++i)
    {
        if(i!=n_pre-1) text+=rule->premise[i]+"&";
        else text+=rule->premise[i];
    }
    text+=new QString("->");
    text+=rule->interence;
    QListWidgetItem *rule_item=new QListWidgetItem(text);
    ui->listWidget_rules->addItem(rule_item);
}

void MainWindow::addFactToList(QString fact,int index)   //添加事实选项到scrollArea控件中
{
    QCheckBox *pCheck=new QCheckBox();
    pCheck->setText(fact);
    pCheck->setMinimumSize(QSize(60,30));
    pLayout->addWidget(pCheck,index/2,0);//把选项添加到布局控件中,第二个参数和第三个参数分别表示控件放置在第几行第几列
}

void MainWindow::initRules()
{
    Rule rule;
    rule.n_pre=1;
    rule.premise[0]={"有奶"};
    rule.interence={"哺乳动物"};
    rules.addRule(&rule);
    addRuleToList(&rule,1);
    for(int i=0;i<rule.n_pre;++i)  //检查规则的前提是否在事实库中，若不在，则加入事实库
    {
        bool flag=facts.checkAndAdd(rule.premise[i]);  //判断是否需要添加到事实库
        if(flag==true)
        {
            addFactToList(rule.premise[i],0);  //添加到事实库控件
        }
    }

}
