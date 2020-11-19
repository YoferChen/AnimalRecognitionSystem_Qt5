#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <rules.h>
#include <facts.h>
#include <addrulesdialog.h>
#include <QGridLayout>
#include <QCheckBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
//    void createAddRuleDialog();
    void addRuleToList(Rule *rule);
    void addFactToList(QString fact);
    void reflashRulesList();  //清空规则库，根据rules重新把规则库中的所有规则添加到控件
    void indentify();  //识别动物类别
    Rule* strToRule(QString str);  //将QString类型的规则解析为Rule类型，用于推理过程或初始化规则库
    QString ruleTostr(Rule* rule,int index);  //rule转str
    void checkAndAddFactToList(Rule *rule);   //检查事实是否已存在事实库，否则添加

private:
    Ui::MainWindow *ui;

    Rules rules;  //规则库
    Facts facts;  //事实库
    QStringList classes;  //可以识别的类别
//    AddRulesDialog* addRulesDialog;  //添加规则窗口指针
    QGridLayout *pLayout;
    QCheckBox *pCheck[100];  //100个事实选项
    void initRules();  //初始化规则库和事实库（事实库根据规则库初始化）
public slots:
    void getAddedRule(Rule* rule);
};


#endif // MAINWINDOW_H
