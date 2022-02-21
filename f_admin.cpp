#include "f_admin.h"
#include "ui_f_admin.h"

F_admin::F_admin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::F_admin)
{
    ui->setupUi(this);
}

F_admin::~F_admin()
{
    delete ui;
}

void F_admin::on_btn_userEdit_clicked()
{
    this->hide();
    p1=new userEdit(this);
    p1->show();
}

void F_admin::on_btn_kvizEdit_clicked()
{
    this->hide();
    p2=new kvizEdit(this);
    p2->show();
}

void F_admin::on_btn_odjava_clicked()
{
    parentWidget()->show();
    this->close();
}
