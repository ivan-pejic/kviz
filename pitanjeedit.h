#ifndef PITANJEEDIT_H
#define PITANJEEDIT_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class pitanjeEdit;
}

class pitanjeEdit : public QDialog
{
    Q_OBJECT

public:
    explicit pitanjeEdit(QWidget *parent = nullptr, QString Pitanje_ID = "default", QString Pitanje = "default", QString Odgovor="default");
    QString pitanje, odgovor, pitanje_ID;
    QSqlQuery qry;
    int *nadjibroj(QString);
    void sacuvaj(QString, QString, QString);
    ~pitanjeEdit();

private slots:
    void on_c_btn_edit_clicked();

    void on_r_btn_edit_clicked();

    void on_k_btn_edit_clicked();

private:
    Ui::pitanjeEdit *ui;
};

#endif // PITANJEEDIT_H
