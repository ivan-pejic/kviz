#ifndef USEREDIT_H
#define USEREDIT_H

#include <QDialog>
#include <QtSql>
#include "dodajuser.h"
#include "loginedit.h"
#include "userpredmet.h"

namespace Ui {
class userEdit;
}

class userEdit : public QDialog
{
    Q_OBJECT

public:
    explicit userEdit(QWidget *parent = nullptr);
    QSqlQuery qry;
    QString id, korisnik, sifra, status;
    void tabela();
    ~userEdit();

private slots:
    void on_btn_userAdd_clicked();

    void on_btn_edit_user_clicked();

    void on_btn_edit_predmet_clicked();

    void on_tbl_userEdit_clicked(const QModelIndex &index);

    void on_btn_nazad_clicked();

    void on_btn_refresh_clicked();

private:
    dodajuser *p1;
    loginedit *p2;
    userpredmet *p3;
    Ui::userEdit *ui;
};

#endif // USEREDIT_H
