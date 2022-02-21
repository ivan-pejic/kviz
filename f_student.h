#ifndef F_STUDENT_H
#define F_STUDENT_H

#include <QDialog>
#include <QtSql>
#include "izborkv.h"

namespace Ui {
class F_student;
}

class F_student : public QDialog
{
    Q_OBJECT

public:
    explicit F_student(QWidget *parent = nullptr, const QString id = "default");
    void izborPredmeta(QString, QString);
    ~F_student();

private slots:
    void on_btn_odjava_clicked();

private:
    Ui::F_student *ui;
    QSqlDatabase myDB;
    izborkv *p1;
};

#endif // F_STUDENT_H
