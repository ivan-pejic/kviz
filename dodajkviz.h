#ifndef DODAJKVIZ_H
#define DODAJKVIZ_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class dodajkviz;
}

class dodajkviz : public QDialog
{
    Q_OBJECT

public:
    explicit dodajkviz(QWidget *parent = nullptr);
    QSqlQuery qry;
    ~dodajkviz();

private slots:
    void on_btn_cncl_clicked();

    void on_btn_add_clicked();

private:
    Ui::dodajkviz *ui;
};

#endif // DODAJKVIZ_H
