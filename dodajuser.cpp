#include "dodajuser.h"
#include "ui_dodajuser.h"
#include <QMessageBox>
#include "useredit.h"

dodajuser::dodajuser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dodajuser)
{
    ui->setupUi(this);

}

dodajuser::~dodajuser()
{
    delete ui;
}

void dodajuser::on_btn_cncl_clicked()
{
    close();
}

void dodajuser::on_btn_add_clicked() //dodavanje usera
{
    QMessageBox messageBox;
    if(ui->txt_user->text()!="" && ui->txt_pass->text()!="")
    {
        qry.prepare("SELECT * FROM korisnici WHERE korisnik=:korisnik");
        qry.bindValue(":korisnik", ui->txt_user->text());
        qry.exec();
        if (!qry.next()){
        qry.prepare("INSERT INTO korisnici (korisnik, sifra, status) VALUES (:korisnik, :sifra, :status);");
        qry.bindValue(":korisnik", ui->txt_user->text());
        qry.bindValue(":sifra", ui->txt_pass->text());
        qry.bindValue(":status", ui->cmb_status->currentText());
        qry.exec();
        qry.next();
        messageBox.information(this, "Uspješno!", "Korisnik je dodan!");
        messageBox.setFixedSize(500,200);
        }
        else{
            messageBox.warning(this, "Greška!", "Korisnik već postoji!");
            messageBox.setFixedSize(500,200);
        }
    }
    else{
        messageBox.warning(this, "Greška!", "Korisničko ime/lozinka ne smiju biti prazni!");
        messageBox.setFixedSize(500,200);
    }
}
