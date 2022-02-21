#include "pitanjeedit.h"
#include "ui_pitanjeedit.h"
#include <QtWidgets>

pitanjeEdit::pitanjeEdit(QWidget *parent, QString Pitanje_ID, QString Pitanje, QString Odgovor) :
    QDialog(parent),
    ui(new Ui::pitanjeEdit)
{
    ui->setupUi(this);
    Q_ASSERT(qry.driver()->hasFeature(QSqlDriver::NamedPlaceholders));
    pitanje=Pitanje;
    odgovor=Odgovor;
    pitanje_ID=Pitanje_ID;
    QButtonGroup *r_grupa=new QButtonGroup();
    r_grupa->addButton(ui->r_chck1);
    r_grupa->addButton(ui->r_chck2);
    r_grupa->addButton(ui->r_chck3);
    r_grupa->addButton(ui->r_chck4);
    r_grupa->addButton(ui->r_chck5);
    for (int i=0; i<3; i++)
        ui->tabWidget->setTabEnabled(i, false);


    QStringList ponudjeni;
    int r=0, c=0;
    r=pitanje.count("~");
    c=pitanje.count("ˇ");
    if (r!=0)
        ponudjeni<<pitanje.split("~");
    if (c!=0)
        ponudjeni<<pitanje.split("ˇ");

    if (r==0 && c==0){
        ui->tabWidget->setTabEnabled(0, true);
    ui->tabWidget->setCurrentIndex(0);
    ui->k_txt_pitanje->setText(pitanje);
    ui->k_txt_odgovor->setText(odgovor);
    }
    else if (c!=0){
        QList<QCheckBox *> lista_c=ui->tab_3->findChildren<QCheckBox *>();
        QList<QLineEdit *> lista_t=ui->tab_3->findChildren<QLineEdit *>();
        ui->c_txt_pitanje->setText(ponudjeni[0]);
        ui->tabWidget->setTabEnabled(2, true);
        ui->tabWidget->setCurrentIndex(2);
        ui->c_txt_pitanje->setText(ponudjeni[0]);
        int *cekiraj=nadjibroj(odgovor);
        int y=1;
        for (int i=1; i<=c; i++){
            lista_t[i]->setText(ponudjeni[i]);
            if (cekiraj[y]==i)
            {
                lista_c[i-1]->setChecked(1);
                y++;
            }
        }
    }
    else{
        QList<QCheckBox *> lista_c=ui->tab_2->findChildren<QCheckBox *>();
        QList<QLineEdit *> lista_t=ui->tab_2->findChildren<QLineEdit *>();
        ui->tabWidget->setTabEnabled(1, true);
        ui->tabWidget->setCurrentIndex(1);
        ui->r_txt_pitanje->setText(ponudjeni[0]);
        int *cekiraj=nadjibroj(odgovor);
        for (int i=1; i<=r; i++){
            lista_t[i]->setText(ponudjeni[i]);
            if (cekiraj[1]==i)
                lista_c[i-1]->setChecked(1);
        }
    }
}

pitanjeEdit::~pitanjeEdit()
{
    delete ui;
}

int *pitanjeEdit::nadjibroj(QString string)
{
    QRegularExpression rx("[0-9]");
    QRegularExpressionMatchIterator i = rx.globalMatch(string);
    int z=1;
    static int brojevi[6]={0, 0, 0, 0, 0, 0};
    while (i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        brojevi[z++] = match.captured(0).toInt();
    }
    return brojevi;
}

void pitanjeEdit::sacuvaj(QString pitanje, QString odgovor, QString pitanje_ID){
    QMessageBox messageBox;
    qry.prepare("UPDATE pitanja SET pitanje=:pitanje, odgovor=:odgovor WHERE ID=:pitanje_ID;");
    qry.bindValue(":pitanje", pitanje);
    qry.bindValue(":odgovor", odgovor);
    qry.bindValue(":pitanje_ID", pitanje_ID);
    qry.exec();
    qry.next();
    messageBox.information(this, "Uspješno!", "Pitanje je uspješno uređeno!");
    messageBox.setFixedSize(500,200);
}

void pitanjeEdit::on_c_btn_edit_clicked()
{
    QMessageBox messageBox;
    if (ui->c_txt_pitanje->text()!=""){
        if (ui->c_txt_odg1->text()=="" && ui->c_txt_odg2->text()=="" && ui->c_txt_odg3->text()=="" && ui->c_txt_odg4->text()=="" && ui->c_txt_odg5->text()==""){
            messageBox.warning(this, "Greška!", "Niste unijeli nijedan odgovor!");
            messageBox.setFixedSize(500,200);
        }
        else{
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
                sacuvaj(ui->c_txt_pitanje->text()+"ˇ"+pitanje.chopped(1), odgovor.chopped(1), pitanje_ID);

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

void pitanjeEdit::on_r_btn_edit_clicked()
{
    QMessageBox messageBox;
    if (ui->r_txt_pitanje->text()!=""){
        if (ui->r_txt_odg1->text()=="" && ui->r_txt_odg2->text()=="" && ui->r_txt_odg3->text()=="" && ui->r_txt_odg4->text()=="" && ui->r_txt_odg5->text()==""){
            messageBox.warning(this, "Greška!", "Niste unijeli nijedan odgovor!");
            messageBox.setFixedSize(500,200);
        }
        else{
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
                    sacuvaj(ui->r_txt_pitanje->text()+"~"+pitanje.chopped(1), odgovor.chopped(1), pitanje_ID);

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

void pitanjeEdit::on_k_btn_edit_clicked()
{
    sacuvaj(ui->k_txt_pitanje->text(), ui->k_txt_odgovor->text(), pitanje_ID);
}
