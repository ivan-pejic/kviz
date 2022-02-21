#ifndef USERPREDMET_H
#define USERPREDMET_H

#include <QDialog>
#include <QtSql>
#include <QVector>
#include <QtWidgets>

namespace Ui {
class userpredmet;
}

class userpredmet : public QDialog
{
    Q_OBJECT

public:
    explicit userpredmet(QWidget *parent = nullptr, QString Id="default", QString korisnik="default");
    QSqlQuery qry;
    void postavi(int[7], QString);
    int velicina(QString);
    QString id;
    void ubaci(int [7]);
    ~userpredmet();

private slots:
    void sacuvaj();

    void on_btn_save_clicked();

private:
    Ui::userpredmet *ui;
};

#endif // USERPREDMET_H
