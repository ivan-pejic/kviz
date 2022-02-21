#ifndef LOGINEDIT_H
#define LOGINEDIT_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class loginedit;
}

class loginedit : public QDialog
{
    Q_OBJECT

public:
    explicit loginedit(QWidget *parent = nullptr, QString id="default", QString korisnik="default", QString sifra="default", QString status="default");
    QSqlQuery qry;
    QString idstari, korisnikstari, sifrastari, statusstari;
    ~loginedit();

private slots:
    void on_btn_edit_clicked();

    void on_btn_cncl_clicked();

private:
    Ui::loginedit *ui;
};

#endif // LOGINEDIT_H
