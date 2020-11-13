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
        AddRulesDialog* addRulesDialog=new AddRulesDialog();
//        addRulesDialog->exec();


        //如果有重载函数，需要使用函数指针指明使用哪个重载函数
//        void (AddRulesDialog::*sendAddedRule)(Rule)=&AddRulesDialog::sendAddedRule;
//        void (MainWindow::*getAddedRule)(Rule)=&MainWindow::getAddedRule;
//        connect(addRulesDialog,sendAddedRule,this,getAddedRule);

        connect(addRulesDialog,&AddRulesDialog::sendAddedRule,this,&MainWindow::getAddedRule);


        addRulesDialog->exec();  //必须放在信号连接之后，否则接收不到信号！！！


//        connect(addRulesDialog,&AddRulesDialog::sendSignal,[=](){
//            qDebug()<<"Received signal！\n";
//        });
    }
    );


    //初始化手动设置的规则
    initRules();

    //显示所有信息（测试）
    connect(ui->pushButton_getRules,&QPushButton::clicked,[=](){
        rules.showRules();
    });

    connect(ui->pushButton_getfacts,&QPushButton::clicked,[=](){
        facts.showFacts();
    });

    connect(ui->pushButton_test,&QPushButton::clicked,[=](){
        strToRule("123");
    });

}

MainWindow::~MainWindow()
{
    delete ui;
}


//void MainWindow::createAddRuleDialog()
//{
//    addRulesDialog=new AddRulesDialog();
//    addRulesDialog->exec();
//}

void MainWindow::addRuleToList(Rule *rule)  //添加规则到list控件中
{
    int n_pre=rule->n_pre;
    QString text;  //显示问信息
    text+=QString::number(rules.getRulesNum());
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

void MainWindow::addFactToList(QString fact)   //添加事实选项到scrollArea控件中
{
    QCheckBox *pCheck=new QCheckBox();
    pCheck->setText(fact);
    pCheck->setMinimumSize(QSize(60,30));
    int index=facts.getFactsNum()-1;
    if(index%2==0)
        pLayout->addWidget(pCheck,index/2,0);//把选项添加到布局控件中,第二个参数和第三个参数分别表示控件放置在第几行第几列
    else
        pLayout->addWidget(pCheck,index/2,1);
}

Rule* MainWindow::strToRule(QString str)  //将string类型规则解析成Rule类型，用于推理过程或初始化规则库
{
//    QString test="有奶&胎生&有毛,哺乳动物";
    QStringList strList=str.split(',');  //划分成事实和推论
    QStringList factList=strList[0].split('&');
    qDebug()<<"事实集："<<factList;  //事实集： ("有奶", "胎生", "有毛")
    qDebug()<<"推论："<<strList[1];  //推论： "哺乳动物"
    Rule *rule=new Rule();
    qDebug()<<"事实数量："<<factList.size();
    for(int i=0;i<factList.size();++i)
    {
        rule->premise[i]=factList[i];
        rule->n_pre++;
    }
    rule->interence=strList[1];
    return rule;
}

void MainWindow::checkAndAddFactToList(Rule *rule)  //检查事实是否已存在事实库，否则添加
{
    for(int i=0;i<rule->n_pre;++i)  //检查规则的前提是否在事实库中，若不在，则加入事实库
    {
        bool flag=facts.checkAndAdd(rule->premise[i]);  //判断是否需要添加到事实库
        if(flag==true)
        {
            addFactToList(rule->premise[i]);  //添加到事实库控件
        }
    }
}

void MainWindow::initRules()
{
//    QString initRules[15];
//    initRules[0]="有奶,哺乳动物";  //注意逗号是英文逗号
//    initRules[1]="有毛发,哺乳动物";

    QStringList initRules;
    initRules<<"有奶,哺乳动物"<<"有毛发,哺乳动物"<<"有羽毛,鸟"<<"会飞&生蛋,鸟"<<"哺乳动物&有爪&有犬齿&目盯前方,食肉动物"
            <<"哺乳动物&吃肉,食肉动物"<<"哺乳动物&有蹄,有蹄动物"<<"有蹄动物&反刍食物,偶蹄动物"<<"食肉动物&黄褐色&有黑色条纹,老虎"
           <<"食肉动物&黄褐色&有黑色斑点,金钱豹"<<"有蹄动物&长腿&长脖子&黄褐色&有暗斑点,长颈鹿"<<"有蹄动物&白色&有黑色条纹,斑马"
          <<"鸟&不会飞&长腿&长脖子&黑白色,鸵鸟"<<"鸟&不会飞&会游泳&黑白色,企鹅"<<"鸟&善飞&不怕风浪,海燕";
    for(int i=0;i<initRules.size();++i)
    {
        Rule* rule=strToRule(initRules[i]);
        rules.addRule(rule);
        addRuleToList(rule);
        checkAndAddFactToList(rule);
    }

//    Rule* rule=new Rule();
//    rule->n_pre=1;
//    rule->premise[0]={"有奶"};
//    rule->interence={"哺乳动物"};
//    rules.addRule(rule);
//    addRuleToList(rule);
//    checkAndAddFactToList(rule);

//    Rule* rule1=strToRule(initRules[1]);
//    rules.addRule(rule1);
//    addRuleToList(rule1);
//    checkAndAddFactToList(rule1);

}

void MainWindow::getAddedRule(Rule* rule)
{
    qDebug()<<"接收到信号！"<<endl;
    qDebug()<<"新增规则：";
    qDebug()<<"前提：";
    for(int i=0;i<rule->n_pre;++i)
    {
        qDebug()<<rule->premise[i];
    }
    qDebug()<<"推论：\n"<<rule->interence;

    //将规则添加到规则库、事实库和UI控件中
    //添加到规则库
    rules.addRule(rule);

    //添加到规则UI控件
    addRuleToList(rule);  //添加到UI需在添加到规则库后面，否则UI中的序号会出错

    //添加到事实库和UI控件
    checkAndAddFactToList(rule);

}

