#ifndef KVIZEDIT_H
#define KVIZEDIT_H

#include <QDialog>
#include <QtSql>
#include "dodajkviz.h"
#include "dodajpitanje.h"
#include "pitanjeedit.h"

namespace Ui {
class kvizEdit;
}

class kvizEdit : public QDialog
{
    Q_OBJECT

public:
    explicit kvizEdit(QWidget *parent = nullptr);
    ~kvizEdit();
    QSqlQuery qry;
    QString kviz_ID;
    void tabela(QString, QString);
    void reset();

private slots:
    void on_btn_addKviz_clicked();

    void on_tbl_kvizEdit_clicked(const QModelIndex &index);

    void on_btn_editKviz_clicked();

    void on_btn_editPitanje_clicked();

    void on_btn_back_clicked();

    void on_btn_addPitanje_clicked();

    void on_btn_nazad_clicked();

    void on_btn_refresh_clicked();

private:
    dodajkviz *p1;
    dodajpitanje *p2;
    pitanjeEdit *p3;
    Ui::kvizEdit *ui;
};

#endif // KVIZEDIT_H
