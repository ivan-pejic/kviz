#ifndef DODAJPITANJE_H
#define DODAJPITANJE_H

#include <QDialog>
#include <QtSql>
#include <QtWidgets>

namespace Ui {
class dodajpitanje;
}

class dodajpitanje : public QDialog
{
    Q_OBJECT

public:
    explicit dodajpitanje(QWidget *parent = nullptr, QString kviz_ID="default");
    QString Kviz_ID;
    QButtonGroup *r_grupa=new QButtonGroup();
    QButtonGroup *c_grupa=new QButtonGroup();
    void sacuvaj(QString, QString, QString);
    void obrisi();
    QSqlQuery qry;
    ~dodajpitanje();

private slots:
    void on_k_btn_add_clicked();

    void on_k_btn_cncl_clicked();

    void on_c_btn_cncl_clicked();

    void on_r_btn_cncl_clicked();

    void on_r_btn_add_clicked();

    void on_c_btn_add_clicked();

private:
    Ui::dodajpitanje *ui;
};

#endif // DODAJPITANJE_H
