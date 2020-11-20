#include "addrulesdialog.h"
#include "ui_addrulesdialog.h"
#include <QGridLayout>
#include <QScrollArea>
#include <QCheckBox>
#include <QTextEdit>
#include <QLineEdit>
#include <QDebug>
#include <rules.h>
#include <facts.h>
#include <mainwindow.h>
#include <QMessageBox>

AddRulesDialog::AddRulesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddRulesDialog)
{
    ui->setupUi(this);


    QGridLayout *pLayout = new QGridLayout();//网格布局
    ui->scrollArea->widget()->setLayout(pLayout);//把布局放置到QScrollArea的内部QWidget中
    pLayout->setAlignment(Qt::AlignTop);  //设置垂直布局
//    for(int i = 0; i < 4; i++)
//    {
////        QPushButton *pBtn = new QPushButton();
////        pBtn->setText(QString("按钮%1").arg(i));
////        pBtn->setMinimumSize(QSize(60,30));   //width height
////        pLayout->addWidget(pBtn);//把按钮添加到布局控件中
//        QLineEdit *editor=new QLineEdit();
//        pLayout->addWidget((editor));
//    }
//    QLineEdit *editor=new QLineEdit();
//    pLayout->addWidget((editor));
    editor[0]=new QLineEdit();
    pLayout->addWidget(editor[0]);  //添加第一个文本栏

    connect(ui->toolButton_addLine,&QToolButton::clicked,[=](){  //点击添加按钮添加文本栏
        //n_lineEdit++;  //文本行数+1
        editor[n_lineEdit]=new QLineEdit();
        pLayout->addWidget((editor[n_lineEdit++]));
        qDebug()<<"文本栏数量："<<n_lineEdit<<endl;
    });

    connect(ui->toolButton_deleteLine,&QToolButton::clicked,[=](){
        //移除最后一个文本栏
        if(n_lineEdit>1)
        {
//            pLayout->removeWidget(editor[n_lineEdit-1]);
            delete editor[n_lineEdit-1];
            qDebug()<<"文本栏数量："<<n_lineEdit<<endl;
        }
        n_lineEdit--;
    });

    //点击确定按钮
    connect(ui->pushButton_accepted,&QPushButton::clicked,[=](){  //点击确定按钮检查输入内容，并保存信息到规则库，...
        qDebug()<<"点击确定按钮！\n";
        //获取窗口信息
        //添加信息到规则库
        //检查是否有文本栏为空
        bool close=true;
        for(int i=0;i<n_lineEdit;++i)
        {

            /*
            QString pre=editor[i]->text();
            qDebug()<<pre<<endl;
            QByteArray byteStr = pre.toLatin1();
            char *a=new char[100];
            a=byteStr.data();
            qDebug()<<a<<endl;*/
            QString pre=editor[i]->text();
            qDebug()<<pre<<endl;
            if(pre==NULL)
            {
                 close=false;
                 qDebug()<<n_lineEdit<<"  "<<"文本栏为空"<<endl;
                 //break;
            }
        }
        if(ui->lineEdit_interence->text()==NULL)
        {
            close=false;
        }
        if (close==false)
        {
            QMessageBox::warning(this,"文本栏不能为空！","警告！");
        }
        if(close==true)
        {
            Rule* rule=new Rule();
            rule->n_pre=n_lineEdit;
            for(int i=0;i<n_lineEdit;++i)
            {
                rule->premise[i]=editor[i]->text();
            }
            rule->interence=this->ui->lineEdit_interence->text();
            bool isAnimal=false;
            if(ui->checkBox_isAnimal->checkState()==Qt::Checked)
                isAnimal=true;
            rule->isTarget=isAnimal;
            emit sendAddedRule(rule);

            this->close();
        }
    });


}

AddRulesDialog::~AddRulesDialog()
{
    delete ui;
}

//Rule *AddRulesDialog::getAddedRule()
//{
//    qDebug()<<"获得添加的规则！"<<endl;
//}
