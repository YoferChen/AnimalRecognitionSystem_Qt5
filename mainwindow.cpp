#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QCheckBox>
#include <QPushButton>

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

    QGridLayout *pLayout = new QGridLayout();//网格布局
    ui->scrollArea->widget()->setLayout(pLayout);//把布局放置到QScrollArea的内部QWidget中
    for(int i = 0; i < 100; i++)
    {
//        QPushButton *pBtn = new QPushButton();
//        pBtn->setText(QString("按钮%1").arg(i));
//        pBtn->setMinimumSize(QSize(60,30));   //width height
//        pLayout->addWidget(pBtn);//把按钮添加到布局控件中
        if(i%2==0)
        {
            QCheckBox *pCheck=new QCheckBox();
            pCheck->setText(QString("选项%1").arg(i));
            pCheck->setMinimumSize(QSize(60,30));
            pLayout->addWidget(pCheck,i/2,0);//把选项添加到布局控件中,第二个参数和第三个参数分别表示控件放置在第几行第几列
        }
        else
        {
            QCheckBox *pCheck=new QCheckBox();
            pCheck->setText(QString("选项%1").arg(i));
            pCheck->setMinimumSize(QSize(60,30));
            pLayout->addWidget(pCheck,i/2,1);//把选项添加到布局控件中
        }

    }

}

MainWindow::~MainWindow()
{
    delete ui;
}
