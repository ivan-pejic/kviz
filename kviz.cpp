#include "kviz.h"
#include "ui_kviz.h"
#include <QString>
#include <QVector>
#include <QDebug>
#include <QRandomGenerator64>
#include <QtWidgets>

Kviz::Kviz(QWidget *parent, QString kviz, QString id) :
    QMainWindow(parent),
    ui(new Ui::Kviz)
{
    ui->setupUi(this);
    QVector<int> brpitanja(50);
    Q_ASSERT(qry.driver()->hasFeature(QSqlDriver::NamedPlaceholders));
    int brojac=0, z=0;
    if (qry.exec("SELECT COUNT (pitanja.ID) FROM pitanja INNER JOIN kviz ON kviz.ID=pitanja.kviz_ID WHERE kviz.naziv=\'"+kviz+"\';")){
        if (qry.next()){
            brojac=qry.value(0).toInt();
        }
    }
    std::uniform_int_distribution<int> distribution(1, brojac); //generisanje 50 random pitanja
    for (int i=0; i<50; i++){
        int val=distribution(*QRandomGenerator::global());
        int istina=0;
        for (int j=0; j<i+1; j++){
            if (brpitanja[j]==val)istina=1;
                if (qry.exec("SELECT pitanja.pitanje, pitanja.odgovor FROM pitanja INNER JOIN kviz ON pitanja.kviz_ID=kviz.ID WHERE kviz.naziv=\'"+kviz+"\' AND pitanja.id=\'"+QString::number(val)+"\'"))
                    if (!qry.next())istina=1;
            }
        if (istina==0){
            brpitanja[i]=val;
            QString c="";
            //ubacivanje praznih vrijednosti u bazu u slucaju da user ne odgovori nista
            qry.exec("INSERT INTO odgovori (korisnik_ID, pitanje_ID, odgovor, kviz_ID) VALUES (\'"+id+"\', \'"+QString::number(val)+"\', \'"+c+"\', (SELECT ID FROM kviz WHERE naziv=\'"+kviz+"\'));");
            qry.next();
        }
        else i--;
        }

    for (int i=0; i<10; i++){ //postavljanje kviza
        QVBoxLayout *vertical = new QVBoxLayout;
        for (int j=0; j<5; j++){
    if (qry.exec("SELECT pitanje FROM pitanja WHERE ID=\'"+QString::number(brpitanja[z])+"\' ")){
        if (qry.next()){
            QStringList ponudjeni;
            QGroupBox *grp = new QGroupBox("Pitanje "+QString::number(z+1)+":");
            QVBoxLayout *grpLayout=new QVBoxLayout;
            QString pitanje=qry.value(0).toString();
            int r=0, c=0;
            r=pitanje.count("~");
            c=pitanje.count("ˇ");
            if (r!=0) //~ je stavljen kao znak za radio button
                ponudjeni<<pitanje.split("~");
            if (c!=0) //ˇ je stavljen kao znak za checkbox
                ponudjeni<<pitanje.split("ˇ");

            QLabel *lbl = new QLabel();

            if (r==0 && c==0){ //klasicno
                lbl->setText(pitanje);
                QLineEdit *txt = new QLineEdit();
                grpLayout->addWidget(lbl);
                grpLayout->addWidget(txt);
                grp->setLayout(grpLayout);
                vertical->addWidget(grp);
                connect(txt, &QLineEdit::textChanged, this, [=](){provjera(txt->text(), brpitanja[z], id, kviz);});
            }
            else if (c!=0){ //checkbox
                lbl->setText(ponudjeni.at(0));
                grpLayout->addWidget(lbl);
                for (int i=1; i<=c; i++){
                    QCheckBox *cbtn = new QCheckBox(ponudjeni[i]);
                    connect(cbtn, &QCheckBox::clicked, this, [=](){provjera(cbtn->text(), brpitanja[z], id, kviz);});
                    cbtn->setChecked(false);
                    grpLayout->addWidget(cbtn);
                }
                grp->setLayout(grpLayout);
                vertical->addWidget(grp);
            }
            else{ //radio
                lbl->setText(ponudjeni.at(0));
                grpLayout->addWidget(lbl);
                QButtonGroup *btn_grupa=new QButtonGroup;
                for (int i=1; i<=r; i++){
                    QRadioButton *rbtn= new QRadioButton(ponudjeni.at(i), grp);
                    connect(rbtn, &QRadioButton::clicked, this, [=](){provjera(rbtn->text(), brpitanja[z], id, kviz);});
                    rbtn->setChecked(false);
                    grpLayout->addWidget(rbtn);
                    btn_grupa->addButton(rbtn);
                    rbtn->setAutoExclusive(false);
                }
                grp->setLayout(grpLayout);
                vertical->addWidget(grp);
            }
        }
    }
    z++;
    }
        QWidget *page = new QWidget;
        page->setLayout(vertical);
        ui->stck->insertWidget(i, page);
    }
    ui->stck->setCurrentIndex(0);
    ui->pb_statuskomplet->setValue(0);
    ui->lbl_statuskomplet->setText("Procenat završetka: ");
    ui->statusbar->addPermanentWidget(ui->lbl_statuskomplet);
    ui->statusbar->addPermanentWidget(ui->pb_statuskomplet, 3);
}


void Kviz::provjera(QString odgovor, int pitanjeid, QString id, QString kviz){ //lambda za pohranjivanje promijene vrijednosti
    if (QCheckBox *checkbox = qobject_cast<QCheckBox *>(QObject::sender())){
            if (checkbox->isChecked()){
                qry.prepare("UPDATE odgovori SET odgovor=(odgovor||:odgovor||'ˇ') WHERE korisnik_ID=:korisnik_ID AND pitanje_ID=:pitanje_ID AND kviz_ID=(SELECT ID FROM kviz WHERE naziv=\'"+kviz+"\');");
                qry.bindValue(":odgovor", odgovor);
                qry.bindValue(":korisnik_ID", id);
                qry.bindValue(":pitanje_ID", QString::number(pitanjeid));
                qry.exec();
                qry.next();
            }
            else{
                qry.prepare("UPDATE odgovori SET odgovor=REPLACE(odgovor, :odgovor||'ˇ', '') WHERE korisnik_ID=:korisnik_ID AND pitanje_ID=:pitanje_ID AND kviz_ID=(SELECT ID FROM kviz WHERE naziv=\'"+kviz+"\');");
                qry.bindValue(":odgovor", odgovor);
                qry.bindValue(":korisnik_ID", id);
                qry.bindValue(":pitanje_ID", QString::number(pitanjeid));
                qry.exec();
                qry.next();
            }
    }
    else{
    qry.prepare("UPDATE odgovori SET odgovor=:odgovor WHERE korisnik_ID=:korisnik_ID AND pitanje_ID=:pitanje_ID AND kviz_ID=(SELECT ID FROM kviz WHERE naziv=\'"+kviz+"\');");
    qry.bindValue(":odgovor", odgovor);
    qry.bindValue(":korisnik_ID", id);
    qry.bindValue(":pitanje_ID", QString::number(pitanjeid));
    qry.exec();
    qry.next();
    }
    qry.prepare("SELECT COUNT (odgovor) FROM odgovori WHERE korisnik_ID=:korisnik_ID AND odgovor!='' AND kviz_ID=(SELECT ID FROM kviz WHERE naziv=\'"+kviz+"\');");
    qry.bindValue(":korisnik_ID", id);
    qry.bindValue(":pitanje_ID", QString::number(pitanjeid));
    qry.exec();
    qry.next();
    ui->pb_statuskomplet->setValue(qry.value(0).toInt()*2);
}

Kviz::~Kviz()
{
    delete ui;
}

//ostatak interfacea
void Kviz::on_btn_stranica1_clicked()
{
    ui->stck->setCurrentIndex(0);
}

void Kviz::on_btn_stranica2_clicked()
{
    ui->stck->setCurrentIndex(1);
}

void Kviz::on_btn_stranica3_clicked()
{
    ui->stck->setCurrentIndex(2);
}

void Kviz::on_btn_stranica4_clicked()
{
    ui->stck->setCurrentIndex(3);
}

void Kviz::on_btn_stranica5_clicked()
{
    ui->stck->setCurrentIndex(4);
}

void Kviz::on_btn_stranica6_clicked()
{
    ui->stck->setCurrentIndex(5);
}

void Kviz::on_btn_stranica7_clicked()
{
    ui->stck->setCurrentIndex(6);
}

void Kviz::on_btn_stranica8_clicked()
{
    ui->stck->setCurrentIndex(7);
}

void Kviz::on_btn_stranica9_clicked()
{
    ui->stck->setCurrentIndex(8);
}

void Kviz::on_btn_stranica10_clicked()
{
    ui->stck->setCurrentIndex(9);
}

void Kviz::on_btn_pocetna_clicked()
{
    ui->stck->setCurrentIndex(0);
}

void Kviz::on_btn_minus_clicked()
{
    if(ui->stck->currentIndex()>0)
        ui->stck->setCurrentIndex(ui->stck->currentIndex()-1);
}

void Kviz::on_btn_plus_clicked()
{
    if(ui->stck->currentIndex()<9)
        ui->stck->setCurrentIndex(ui->stck->currentIndex()+1);
}

void Kviz::on_btn_zadnja_clicked()
{
    ui->stck->setCurrentIndex(9);
}

void Kviz::on_btn_kraj_clicked()
{
    parentWidget()->show();
    this->close();
}
