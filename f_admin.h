#ifndef F_ADMIN_H
#define F_ADMIN_H

#include <QDialog>
#include "useredit.h"
#include "kvizedit.h"

namespace Ui {
class F_admin;
}

class F_admin : public QDialog
{
    Q_OBJECT

public:
    explicit F_admin(QWidget *parent = nullptr);
    ~F_admin();

private slots:

    void on_btn_userEdit_clicked();

    void on_btn_kvizEdit_clicked();

    void on_btn_odjava_clicked();

private:
    Ui::F_admin *ui;
    userEdit *p1;
    kvizEdit *p2;
};

#endif // F_ADMIN_H
