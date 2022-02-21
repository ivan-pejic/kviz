#ifndef IZBORKV_H
#define IZBORKV_H
#include "kviz.h"
#include "kvizpregled.h"
#include <QDialog>

namespace Ui {
class izborkv;
}

class izborkv : public QDialog
{
    Q_OBJECT

public:
    explicit izborkv(QWidget *parent = nullptr, QString pred ="default", QString id="default");
    ~izborkv();
    void pokreni(QString, QString);
    QSqlQuery qry;

private slots:
    void on_btn_nazad_clicked();

private:
    Kviz *p1;
    kvizPregled *p2;
    Ui::izborkv *ui;
};

#endif // IZBORKV_H
