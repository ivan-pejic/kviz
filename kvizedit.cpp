#include "kvizedit.h"
#include "ui_kvizedit.h"
#include <QInputDialog>

kvizEdit::kvizEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::kvizEdit)
{
    ui->setupUi(this);

    tabela("kviz", "");
}

void kvizEdit::tabela(QString var, QString kviz){
    QSqlQueryModel *model=new QSqlQueryModel();
    if (kviz=="")
    {
        qry.exec("SELECT * FROM "+var+";");
        ui->btn_back->hide();
        ui->btn_editPitanje->hide();
        ui->btn_addPitanje->hide();
        ui->btn_editKviz->show();
        ui->btn_addKviz->show();
        ui->lbl_ID->setText("ID: ");
        ui->lbl_na_pi->setText("Naziv kviza: ");
        ui->lbl_pr_od->setText("Predmet: ");
    }
    else{
        qry.exec("SELECT pitanja.ID, pitanja.pitanje, pitanja.odgovor, pitanja.kviz_ID FROM pitanja INNER JOIN kviz ON pitanja.kviz_ID=kviz.ID WHERE pitanja.kviz_ID="+kviz+";");
        ui->btn_editKviz->hide();
        ui->btn_addKviz->hide();
        ui->btn_back->show();
        ui->btn_editPitanje->show();
        ui->btn_addPitanje->show();
        ui->lbl_ID->setText("ID: ");
        ui->lbl_na_pi->setText("Pitanje: ");
        ui->lbl_pr_od->setText("Odgovor: ");
    }
    if (qry.next())
    model->setQuery(qry);    
    ui->tbl_kvizEdit->setModel(model);
    ui->tbl_kvizEdit->setColumnHidden(3, true);
    qry.exec("PRAGMA table_info("+var+");");
    qry.next();
}

void kvizEdit::on_tbl_kvizEdit_clicked(const QModelIndex &index)
{
    ui->btn_editKviz->setEnabled(true);
    ui->btn_editPitanje->setEnabled(true);
    ui->txt_ID->setText(ui->tbl_kvizEdit->model()->index(index.row(),0).data().toString());
    ui->txt_na_pi->setText(ui->tbl_kvizEdit->model()->index(index.row(),1).data().toString());
    ui->txt_pr_od->setText(ui->tbl_kvizEdit->model()->index(index.row(),2).data().toString());
    if (ui->tbl_kvizEdit->model()->index(index.row(),3).data().toString()=="")
        kviz_ID=ui->tbl_kvizEdit->model()->index(index.row(),0).data().toString();
    else
        kviz_ID=ui->tbl_kvizEdit->model()->index(index.row(),3).data().toString();
}

void kvizEdit::on_btn_editKviz_clicked()
{
    if (ui->txt_ID->text()!="")
    tabela("pitanja", ui->txt_ID->text());
    reset();
}

void kvizEdit::on_btn_addKviz_clicked()
{
    p1=new dodajkviz(this);
    p1->setModal(true);
    p1->show();
}

void kvizEdit::on_btn_editPitanje_clicked()
{
    p3=new pitanjeEdit(this, ui->txt_ID->text(), ui->txt_na_pi->text(), ui->txt_pr_od->text());
    p3->setModal(true);
    p3->show();

}

void kvizEdit::on_btn_addPitanje_clicked()
{
    p2=new dodajpitanje(this, kviz_ID);
    p2->setModal(true);
    p2->show();
}

kvizEdit::~kvizEdit()
{
    delete ui;
}

void kvizEdit::on_btn_back_clicked()
{
    tabela("kviz", "");
    reset();
}

void kvizEdit::reset()
{
    ui->txt_ID->setText("");
    ui->txt_na_pi->setText("");
    ui->txt_pr_od->setText("");
}



void kvizEdit::on_btn_nazad_clicked()
{
    parentWidget()->show();
    this->close();
}

void kvizEdit::on_btn_refresh_clicked()
{
    if (ui->tbl_kvizEdit->model()->columnCount()==3)
        tabela("kviz", "");
    else
        tabela("pitanja", ui->tbl_kvizEdit->model()->index(0, 3).data().toString());
}
