#ifndef ADDRULESDIALOG_H
#define ADDRULESDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include "rules.h"

namespace Ui {
class AddRulesDialog;
}

class AddRulesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddRulesDialog(QWidget *parent = 0);
    ~AddRulesDialog();

public:
    Ui::AddRulesDialog *ui;
    int n_lineEdit=1;  //文本行数
    QLineEdit *editor[50];
signals:
    void sendAddedRule(Rule* rule);
};

#endif // ADDRULESDIALOG_H
