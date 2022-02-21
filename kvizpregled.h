#ifndef KVIZPREGLED_H
#define KVIZPREGLED_H
#include <QtSql>

#include <QMainWindow>

namespace Ui {
class kvizPregled;
}

class kvizPregled : public QMainWindow
{
    Q_OBJECT

public:
    explicit kvizPregled(QWidget *parent = nullptr, QString kviz="default", QString id="default");
    QSqlQuery qry;
    QString bodovi(int, QString, QString, QString, float&);
    static float bodovi_f;
    int *nadjibroj(QString);
    ~kvizPregled();

private slots:
    void on_btn_stranica1_clicked();
    void on_btn_stranica2_clicked();
    void on_btn_stranica3_clicked();
    void on_btn_stranica4_clicked();
    void on_btn_stranica5_clicked();
    void on_btn_stranica6_clicked();
    void on_btn_stranica7_clicked();
    void on_btn_stranica8_clicked();
    void on_btn_stranica9_clicked();
    void on_btn_stranica10_clicked();

    void on_btn_pocetna_clicked();

    void on_btn_minus_clicked();

    void on_btn_plus_clicked();

    void on_btn_zadnja_clicked();

    void on_btn_kraj_clicked();

private:
    Ui::kvizPregled *ui;
};

#endif // KVIZPREGLED_H
