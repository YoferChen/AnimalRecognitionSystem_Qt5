#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <rules.h>
#include <facts.h>
#include <addrulesdialog.h>
#include <QGridLayout>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void createAddRuleDialog();
    void addRuleToList(Rule *rule,int index);
    void addFactToList(QString fact,int index);
    void reflashRulesList();  //清空规则库，根据rules重新把规则库中的所有规则添加到控件
    void indentify();  //识别动物类别
    void strToRule(QString str);  //将QString类型的规则解析为Rule类型

private:
    Ui::MainWindow *ui;

    Rules rules;  //规则库
    Facts facts;  //事实库
    AddRulesDialog* addRulesDialog;  //添加规则窗口指针
    QGridLayout *pLayout;
    void initRules();  //初始化规则库和事实库（事实库根据规则库初始化）
};


#endif // MAINWINDOW_H
