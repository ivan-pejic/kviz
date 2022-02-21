#include "useredit.h"
#include "ui_useredit.h"
#include <QMessageBox>

userEdit::userEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::userEdit)
{
    ui->setupUi(this);
    tabela();
}

userEdit::~userEdit()
{
    delete ui;
}

void userEdit::tabela(){
    qry.exec("SELECT ID, korisnik, sifra, status FROM korisnici;");
    QSqlQueryModel *model=new QSqlQueryModel();
    if (qry.next()){
    model->setQuery(qry);
    }
    ui->tbl_userEdit->setModel(model);
    ui->tbl_userEdit->setColumnHidden(2, true);
}

void userEdit::on_btn_userAdd_clicked()
{
    p1=new dodajuser(this);
    p1->setModal(true);
    p1->show();
}

void userEdit::on_btn_edit_user_clicked()
{
    p2=new loginedit(this, id, korisnik, sifra, status);
    p2->setModal(true);
    p2->show();
}


void userEdit::on_btn_edit_predmet_clicked()
{
    p3=new userpredmet(this, id, korisnik);
    p3->setModal(true);
    p3->show();
}

void userEdit::on_tbl_userEdit_clicked(const QModelIndex &index)
{
    ui->btn_edit_predmet->setEnabled(true);
    ui->btn_edit_user->setEnabled(true);
    id=ui->tbl_userEdit->model()->index(index.row(),0).data().toString();
    korisnik=ui->tbl_userEdit->model()->index(index.row(),1).data().toString();
    sifra=ui->tbl_userEdit->model()->index(index.row(),2).data().toString();
    status=ui->tbl_userEdit->model()->index(index.row(),3).data().toString();
}

void userEdit::on_btn_nazad_clicked()
{
    parentWidget()->show();
    this->close();
}

void userEdit::on_btn_refresh_clicked()
{
    tabela();
}
