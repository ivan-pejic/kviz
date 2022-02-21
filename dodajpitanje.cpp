#include "dodajpitanje.h"
#include "ui_dodajpitanje.h"
#include <QMessageBox>

dodajpitanje::dodajpitanje(QWidget *parent, QString kviz_ID) :
    QDialog(parent),
    ui(new Ui::dodajpitanje)
{
    ui->setupUi(this);
    Kviz_ID=kviz_ID;
    r_grupa->addButton(ui->r_chck1);
    r_grupa->addButton(ui->r_chck2);
    r_grupa->addButton(ui->r_chck3);
    r_grupa->addButton(ui->r_chck4);
    r_grupa->addButton(ui->r_chck5);

    c_grupa->setExclusive(false);
    c_grupa->addButton(ui->c_chck1);
    c_grupa->addButton(ui->c_chck2);
    c_grupa->addButton(ui->c_chck3);
    c_grupa->addButton(ui->c_chck4);
    c_grupa->addButton(ui->c_chck5);
}

dodajpitanje::~dodajpitanje()
{
    delete ui;
}

void dodajpitanje::on_k_btn_add_clicked() //ubacivanje klasicnog pitanja
{
    QMessageBox messageBox;
    QString nazivkviza;
    QSqlQuery qry2;
    qry2.exec("SELECT naziv FROM kviz WHERE ID=\'"+Kviz_ID+"\'");
    if (qry2.next())nazivkviza=qry2.value(0).toString();
    QString pitanje=ui->k_txt_pitanje->text();
    QString odgovor=ui->k_txt_odgovor->text();
    qry.exec("SELECT * FROM pitanja WHERE pitanje=\'"+pitanje+"\' AND odgovor=\'"+odgovor+"\' AND kviz_ID=\'"+Kviz_ID+"\'");
    if (qry.next()){
        messageBox.warning(this, "Greška!", "Kviz \""+nazivkviza+"\" već ima identično pitanje!");
        messageBox.setFixedSize(500,200);
        }
    else{
        pitanje.append("a");
        odgovor.append("a");
        sacuvaj(pitanje, odgovor, Kviz_ID);
    }

}

void dodajpitanje::on_r_btn_add_clicked() //ubacivanje radio pitanja
{
    QMessageBox messageBox;
    QString nazivkviza;
    QSqlQuery qry2;
    qry2.exec("SELECT naziv FROM kviz WHERE ID=\'"+Kviz_ID+"\'");
    if (qry2.next())nazivkviza=qry2.value(0).toString();
    if (ui->r_txt_pitanje->text()!=""){
        if (ui->r_txt_odg1->text()=="" && ui->r_txt_odg2->text()=="" && ui->r_txt_odg3->text()=="" && ui->r_txt_odg4->text()=="" && ui->r_txt_odg5->text()==""){
            messageBox.warning(this, "Greška!", "Niste unijeli nijedan odgovor!");
            messageBox.setFixedSize(500,200);
        }
        else{
            if (r_grupa->checkedId()!=-1){
                QString odgovor;
                QString pitanje;
                QList<QCheckBox *> lista_c=ui->tab_2->findChildren<QCheckBox *>();
                QList<QLineEdit *> lista_t=ui->tab_2->findChildren<QLineEdit *>();
                int istina=0;
                for (int i=0; i<5; i++){
                    if (lista_t[i+1]->text().size()>0)
                        pitanje=pitanje+lista_t[i+1]->text()+"~";
                    if (lista_t[i+1]->text().size()>0&&lista_c[i]->isChecked())
                        odgovor=lista_t[i+1]->text()+"~";
                    if (lista_t[i+1]->text().size()<1&&lista_c[i]->isChecked()){
                        messageBox.warning(this, "Greška!", "Odgovor je prazan!");
                        messageBox.setFixedSize(500,200);
                        istina=1;
                    }
                }
                if (istina==0){
                    sacuvaj(pitanje, odgovor, Kviz_ID);

                }
            }
            else{
                messageBox.warning(this, "Greška!", "Niste označili tačan odgovor!");
                messageBox.setFixedSize(500,200);
            }
        }
    }
    else{
        messageBox.warning(this, "Greška!", "Niste unijeli pitanje!");
        messageBox.setFixedSize(500,200);
    }
}

void dodajpitanje::on_c_btn_add_clicked() //ubacivanje checkbox pitanja
{
    QMessageBox messageBox;
    QString nazivkviza;
    QSqlQuery qry2;
    qry2.exec("SELECT naziv FROM kviz WHERE ID=\'"+Kviz_ID+"\'");
    if (qry2.next())nazivkviza=qry2.value(0).toString();
    if (ui->c_txt_pitanje->text()!=""){
        if (ui->c_txt_odg1->text()=="" && ui->c_txt_odg2->text()=="" && ui->c_txt_odg3->text()=="" && ui->c_txt_odg4->text()=="" && ui->c_txt_odg5->text()==""){
            messageBox.warning(this, "Greška!", "Niste unijeli nijedan odgovor!");
            messageBox.setFixedSize(500,200);
        }
        else{
            if (c_grupa->checkedId()!=-1){
            QString odgovor;
            QString pitanje;
            QList<QCheckBox *> lista_c=ui->tab_3->findChildren<QCheckBox *>();
            QList<QLineEdit *> lista_t=ui->tab_3->findChildren<QLineEdit *>();
            int istina=0;
            for (int i=0; i<5; i++){
                if (lista_t[i+1]->text().size()>0)
                    pitanje=pitanje+lista_t[i+1]->text()+"ˇ";
                if (lista_t[i+1]->text().size()>0&&lista_c[i]->isChecked())
                    odgovor=odgovor+lista_t[i+1]->text()+"ˇ";
                if (lista_t[i+1]->text().size()<1&&lista_c[i]->isChecked()){
                    messageBox.warning(this, "Greška!", "Jedan od odgovora je prazan!");
                    messageBox.setFixedSize(500,200);
                    istina=1;
                }
            }
            if (istina==0){
                sacuvaj(pitanje, odgovor, Kviz_ID);

            }
            }
            else{
                messageBox.warning(this, "Greška!", "Niste označili tačan odgovor!");
                messageBox.setFixedSize(500,200);
            }
        }


        }
    else{
        messageBox.warning(this, "Greška!", "Niste unijeli pitanje!");
        messageBox.setFixedSize(500,200);
    }
}


void dodajpitanje::on_k_btn_cncl_clicked()
{
    close();
}

void dodajpitanje::on_c_btn_cncl_clicked()
{
    close();
}

void dodajpitanje::on_r_btn_cncl_clicked()
{
    close();
}

void dodajpitanje::sacuvaj(QString pitanje, QString odgovor, QString Kviz_ID){
    QString nazivkviza;
    QSqlQuery qry2;
    qry2.exec("SELECT naziv FROM kviz WHERE ID=\'"+Kviz_ID+"\'");
    if (qry2.next())nazivkviza=qry2.value(0).toString();
    QMessageBox messageBox;
    pitanje.chop(1);
    odgovor.chop(1);
    qry.prepare("INSERT INTO pitanja (pitanje, odgovor, kviz_ID) VALUES (:pitanje, :odgovor, :kviz_ID);");
    qry.bindValue(":pitanje", pitanje);
    qry.bindValue(":odgovor", odgovor);
    qry.bindValue(":kviz_ID", Kviz_ID);
    qry.exec();
    qry.next();
    messageBox.information(this, "Uspješno!", "Pitanje je uspješno dodano u kviz \""+nazivkviza+"\"!");
    messageBox.setFixedSize(500,200);
    obrisi();
}

void dodajpitanje::obrisi()
{
    QList<QCheckBox *> lista_c=findChildren<QCheckBox *>();
    QList<QLineEdit *> lista_t=findChildren<QLineEdit *>();
    for (int i=0; i<lista_c.length(); i++)
        lista_c[i]->setChecked(0);
    for (int i=0; i<lista_t.length(); i++)
        lista_t[i]->setText("");
}
