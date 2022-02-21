#ifndef DODAJUSER_H
#define DODAJUSER_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class dodajuser;
}

class dodajuser : public QDialog
{
    Q_OBJECT

public:
    explicit dodajuser(QWidget *parent = nullptr);
    QSqlQuery qry;
    ~dodajuser();

private slots:
    void on_btn_cncl_clicked();

    void on_btn_add_clicked();

private:
    Ui::dodajuser *ui;
};

#endif // DODAJUSER_H
