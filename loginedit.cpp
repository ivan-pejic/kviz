#include "loginedit.h"
#include "ui_loginedit.h"
#include <QMessageBox>

loginedit::loginedit(QWidget *parent, QString id, QString korisnik, QString sifra, QString status) :
    QDialog(parent),
    ui(new Ui::loginedit)
{
    ui->setupUi(this);
    ui->txt_user->setText(korisnik);
    ui->txt_pass->setText(sifra);
    ui->cmb_status->setCurrentText(status);

    idstari=id;
    korisnikstari=korisnik;
    sifrastari=sifra;
    statusstari=status;
}

loginedit::~loginedit()
{
    delete ui;
}


void loginedit::on_btn_cncl_clicked()
{
    close();
}

void loginedit::on_btn_edit_clicked()
{
    QMessageBox messageBox;
    if(ui->txt_user->text()!="" && ui->txt_pass->text()!=""){
        qry.prepare("UPDATE korisnici SET korisnik=:korisniknovi, sifra=:sifranovi, status=:statusnovi WHERE id=:idstari AND korisnik=:korisnikstari AND sifra=:sifrastari AND status=:statusstari");
        qry.bindValue(":idstari", idstari);
        qry.bindValue(":korisnikstari", korisnikstari);
        qry.bindValue(":sifrastari", sifrastari);
        qry.bindValue(":statusstari", statusstari);

        qry.bindValue(":korisniknovi", ui->txt_user->text());
        qry.bindValue(":sifranovi", ui->txt_pass->text());
        qry.bindValue(":statusnovi", ui->cmb_status->currentText());
        qry.exec();
        if (qry.numRowsAffected()>0){
            messageBox.information(this, "Uspješno!", "Korisnik uređen!");
            messageBox.setFixedSize(500,200);
        }
        else{
            messageBox.warning(this, "Greška!", "Korisnik ne postoji!");
            messageBox.setFixedSize(500,200);
        }
    }
    else{
        messageBox.warning(this, "Greška!", "Korisničko ime/lozinka ne smiju biti prazni!");
        messageBox.setFixedSize(500,200);
    }
}
