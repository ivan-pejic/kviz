#include "dodajkviz.h"
#include "ui_dodajkviz.h"
#include <QMessageBox>

dodajkviz::dodajkviz(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dodajkviz)
{
    ui->setupUi(this);
    qry.exec("SELECT * FROM predmeti;");
    while (qry.next()){ //ubacivanje predmeta u kombo
    ui->cmb_predmeti->addItem(qry.value(1).toString());
    }
}

dodajkviz::~dodajkviz()
{
    delete ui;
}

void dodajkviz::on_btn_cncl_clicked()
{
    close();
}

void dodajkviz::on_btn_add_clicked() //ubacivanje kviza
{
    QMessageBox messageBox;
    QString ime=ui->txt_ime->text();
    QString predmet=ui->cmb_predmeti->currentText();
    qry.exec("SELECT * FROM kviz INNER JOIN predmeti ON predmeti.ID=kviz.predmet_ID WHERE predmeti.naziv=\'"+predmet+"\' AND kviz.naziv=\'"+ime+"\'");
    if (qry.next()){
        messageBox.warning(this, "Greška!", "Predmet \""+predmet+"\" već ima kviz sa nazivom \""+ime+"\"!");
        messageBox.setFixedSize(500,200);
    }
    else{
        qry.exec("INSERT INTO kviz (naziv, predmet_ID) VALUES (\'"+ime+"\', (SELECT ID from predmeti WHERE naziv=\'"+predmet+"\'))");
        qry.next();
        messageBox.information(this, "Uspješno!", "Kviz \""+ime+"\" je uspješno dodan u predmet \""+predmet+"\"!");
        messageBox.setFixedSize(500,200);
        close();
    }
}
