#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QCheckBox>
#include <QPushButton>
#include <QMessageBox>
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

    //初始化可识别的类别
    classes<<"老虎"<<"金钱豹"<<"长颈鹿"<<"斑马"<<"企鹅"<<"鸵鸟"<<"海燕";

    //初始化手动设置的规则
    initRules();

    //显示所有信息（测试）
    connect(ui->pushButton_getRules,&QPushButton::clicked,[=](){
        QString meg=rules.showRules();
        QMessageBox::about(this,"显示所有规则",meg);
    });
    //显示所有事实
    connect(ui->pushButton_getfacts,&QPushButton::clicked,[=](){
        QString meg=facts.showFacts();
        QMessageBox::about(this,"显示所有事实",meg);
    });
    //测试字符串解析(测试)
//    connect(ui->pushButton_test,&QPushButton::clicked,[=](){
//        strToRule("有奶,哺乳动物");
//    });
    //动物识别
    connect(ui->btn_recognition,&QPushButton::clicked,[=](){
         indentify();
    });

    //删除规则
    connect(ui->btn_delete_rule,&QPushButton::clicked,[=](){
        deleteRuleFromList();
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
    QString text;  //显示规则信息
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

void MainWindow::addRuleToListByIndex(Rule *rule, int index)
{
    int n_pre=rule->n_pre;
    QString text;  //显示规则信息
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

void MainWindow::addFactToList(QString fact)   //添加事实选项到scrollArea控件中
{
    int index=facts.getFactsNum()-1;
    pCheck[index]=new QCheckBox();
    pCheck[index]->setText(fact);
    pCheck[index]->setMinimumSize(QSize(60,30));
//    int index=facts.getFactsNum()-1;
    if(index%2==0)
        pLayout->addWidget(pCheck[index],index/2,0);//把选项添加到布局控件中,第二个参数和第三个参数分别表示控件放置在第几行第几列
    else
        pLayout->addWidget(pCheck[index],index/2,1);
}

// 动物识别【思路：对每一条规则的前提进行遍历，判断规则是否满足，若满足，将规则的推论加入事实库，此规则标记为已使用】
void MainWindow::indentify()
{
    //系统状态初始化（避免上次识别过程产生的中间结果影响下一次识别
    //获取选取的事实项、规则标记置零
    QStringList getChoiceFacts;  //获取选择的事实项
    for(int i=0;i<facts.getFactsNum();++i)
    {
        //qDebug()<<i<<"  "<<pCheck[i]->text()<<"  "<<pCheck[i]->checkState();
        if(pCheck[i]->checkState()==Qt::Checked)
        {
            getChoiceFacts.append(pCheck[i]->text());
        }
    }
    qDebug()<<"选择的事实："<<getChoiceFacts;
    if(getChoiceFacts.size()==0)
    {
        QMessageBox::warning(this,"警告","请选择事实！");
        return;
    }
    //记录每条规则是否被使用
    int *state=new int(rules.getRulesNum());
    for(int i=0;i<rules.getRulesNum();++i) state[i]=0;  //全部初始化为0
    //是否匹配的规则
    bool isRecognized=false;
    QString recognizeResult=NULL;
    bool isMatch=true;
    //推理过程【以(xxx,xxx)==>XX的形式】
    QStringList reasoning_process;
    //保存现有规则的指针到数组，便于处理
    Rule ** rulePtr=new Rule*[rules.getRulesNum()];
    Rule* p=rules.front;
    for(int i=0;i<rules.getRulesNum();++i)
    {
        rulePtr[i]=p->next;
        p=p->next;
    }
    //遍历每条规则
    while(isMatch&&isRecognized==false)  //有规则匹配且还未识别出动物类别
    {
        isMatch=false;  //没有匹配的规则
        //遍历每条规则，判断是否规则的前提都满足，满足则状态标记为已使用，并将推理加入事实库
        for(int i=0;i<rules.getRulesNum();++i)
        {
//            qDebug()<<state[i];
            if(state[i]==0)  //该规则还未被使用
            {
                int preNum=rulePtr[i]->n_pre;  //获取前提数，每匹配一个前提，前提数-1，若最终前提数为0，则规则成立
                for(int k=0;k<rulePtr[i]->n_pre;++k)  //遍历每个前提
                {
                    for(int t=0;t<getChoiceFacts.size();++t)  //遍历每个事实
                    {
                        if(getChoiceFacts[t]==rulePtr[i]->premise[k])
                        {
                            preNum--;
                            break;
                        }
                    }
                }
                if(preNum==0)  //匹配成功，推论加入事实库
                {
                    getChoiceFacts.append(rulePtr[i]->interence);
                    state[i]=1;  //规则标记为已使用
                    isMatch=true;  //标记为存在规则匹配
                    //判断推论是否是可识别的动物类别
                    for(int j=0;j<classes.size();++j)
                    {
                        if(rulePtr[i]->interence==classes[j])
                        {
                            recognizeResult=rulePtr[i]->interence;  //识别出动物类别
                            isRecognized=true;
                        }
                    }
                    reasoning_process.append(ruleTostr(rulePtr[i],i+1));
                    break;  //进行下一轮规则遍历
                }
            }

        }

    }
    //识别结果弹出对话框显示
    if(isRecognized)  //成功识别
    {
        qDebug()<<"识别成功"<<"识别结果："+QString(recognizeResult);
        qDebug()<<"推理过程："<<reasoning_process;
        QString meg;
        for(int i=0;i<reasoning_process.size();++i)
        {
            if(i!=reasoning_process.size()-1)
                meg+=reasoning_process[i]+'\n';
            else
                meg+=reasoning_process[i];
        }
        qDebug()<<"meg="<<meg;
        QMessageBox::information(this,"识别成功","识别结果："+QString(recognizeResult)+'\n'+'\n'+"推理过程：\n"+meg);
    }
    else
    {
        qDebug()<<"识别失败"<<"抱歉，未能识别出动物类别！";
        QMessageBox::warning(this,"识别失败","抱歉，未能识别出动物类别！");
    }


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

QString MainWindow::ruleTostr(Rule *rule,int index)
{
    QString str;
    str+=(QString::number(index));
    str+=" ";
    for(int i=0;i<rule->n_pre;++i)
    {
        if(i!=rule->n_pre-1)
        {
            str+=rule->premise[i];
            str+=",";
        }
        else
            str+=rule->premise[i];
    }
    str+="->";
    str+=rule->interence;
    return str;
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

void MainWindow::deleteRuleFromList()
{

    QListWidgetItem* item=ui->listWidget_rules->currentItem();
    if(item==NULL)
    {
        QMessageBox::warning(this,"警告","请选择要删除的规则！");
        return;
    }
    int selectedIndex=ui->listWidget_rules->currentRow();
//    qDebug()<<"删除规则："<<item->text();
    qDebug()<<"删除第"<<selectedIndex+1<<"条规则："<<item->text();
    rules.rmRule(selectedIndex);  //从规则库中删除
    delete item;
    //更新规则list，修改序号
    refleshRulesList();
//    QMessageBox::warning(this,"警告","请选择要删除的规则！");

}

void MainWindow::refleshRulesList()
{
    ui->listWidget_rules->clear();
    Rule* p=rules.front;
    for(int i=0;i<rules.getRulesNum();++i)
    {
        addRuleToListByIndex(p->next,i+1);
        p=p->next;
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
    qDebug()<<"是否为具体动物："<<rule->isTarget;

    //将规则添加到规则库、事实库和UI控件中
    //添加到规则库
    rules.addRule(rule);

    //添加到规则UI控件
    addRuleToList(rule);  //添加到UI需在添加到规则库后面，否则UI中的序号会出错

    //添加到事实库和UI控件
    checkAndAddFactToList(rule);

    if(rule->isTarget==true)  //将推论加入到识别库中
    {
        classes.append(rule->interence);
    }

}

