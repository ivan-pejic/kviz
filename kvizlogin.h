#ifndef KVIZLOGIN_H
#define KVIZLOGIN_H

#include <QDialog>
#include <QDebug>
#include <QtSql>
#include <QFileInfo>
#include <QMessageBox>
#include "f_admin.h"
#include "f_student.h"

namespace Ui {
class KvizLogin;
}

class KvizLogin : public QDialog
{
    Q_OBJECT

public:
    explicit KvizLogin(QWidget *parent = nullptr);
    ~KvizLogin();

private slots:
    void on_btnLogin_clicked();

private:
    Ui::KvizLogin *ui;
    F_admin *p1;
    F_student *p2;

    QSqlDatabase myDB;
};

#endif // KVIZLOGIN_H
