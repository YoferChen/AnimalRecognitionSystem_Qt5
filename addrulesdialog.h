#ifndef ADDRULESDIALOG_H
#define ADDRULESDIALOG_H

#include <QDialog>
#include <QLineEdit>

namespace Ui {
class AddRulesDialog;
}

class AddRulesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddRulesDialog(QWidget *parent = 0);
    ~AddRulesDialog();

private:
    Ui::AddRulesDialog *ui;
    int n_lineEdit=1;  //文本行数
    QLineEdit *editor[50];

};

#endif // ADDRULESDIALOG_H
