#include "izborkv.h"
#include "ui_izborkv.h"
#include <QVBoxLayout>
#include <QtWidgets>
#include <QString>
#include <QtDebug>
#include <QVector>
#include <QtSql>

izborkv::izborkv(QWidget *parent, QString pred, QString id) :
    QDialog(parent),
    ui(new Ui::izborkv)
{
    ui->setupUi(this);
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *vlay = new QVBoxLayout();
    if (qry.exec("SELECT kviz.naziv FROM kviz INNER JOIN predmeti ON predmeti.ID=kviz.predmet_ID WHERE predmeti.naziv=\'"+pred+"\'")){
        while (qry.next()){ //citanje predmeta usera
            QString kviz=qry.value(0).toString();
            QPushButton *btn1 = new QPushButton(kviz);
            connect(btn1, &QPushButton::clicked, [=]{
                pokreni(kviz, id);
            });
            vlay->addWidget(btn1);
            centralWidget->setLayout(vlay);
        }
    }
}

void izborkv::pokreni(QString kviz, QString id){ //pokretanje kviza
    if (qry.exec("SELECT * FROM odgovori INNER JOIN kviz ON odgovori.kviz_ID=kviz.ID WHERE odgovori.korisnik_ID=\'"+id+"\' AND kviz.naziv=\'"+kviz+"\'")){
        if (!qry.next()){
        this->hide();
        p1=new Kviz(this, kviz, id);
        p1->show();
        }
    else{
        this->hide();
    p2=new kvizPregled(this, kviz, id);
    p2->show();
    }
    }
}

izborkv::~izborkv()
{
    delete ui;
}

void izborkv::on_btn_nazad_clicked()
{
    parentWidget()->show();
    this->close();
}
