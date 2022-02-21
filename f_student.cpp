#include "f_student.h"
#include "ui_f_student.h"
#include "kvizlogin.h"
#include <QVBoxLayout>
#include <QtWidgets>
#include <QString>
#include <QtDebug>
#include <QVector>


F_student::F_student(QWidget *parent, const QString id) :
    QDialog(parent),
    ui(new Ui::F_student)
{
    ui->setupUi(this);
    QVector<QString> predmeti(10);
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *vlay = new QVBoxLayout();
    int j=0;
    QSqlQuery qry;
    QString citaj[7];
    if (qry.exec("SELECT COUNT (predmeti.naziv) FROM predmeti INNER JOIN korisnik_predmet ON predmeti.ID=korisnik_predmet.predmet_ID INNER JOIN korisnici ON korisnik_predmet.korisnik_ID=korisnici.ID WHERE korisnici.ID=\'"+id+"\'")){
        if (qry.next()){
            citaj->resize(qry.value(0).toInt());
        }
    }
    if (qry.exec("SELECT predmeti.naziv FROM predmeti INNER JOIN korisnik_predmet ON predmeti.ID=korisnik_predmet.predmet_ID INNER JOIN korisnici ON korisnik_predmet.korisnik_ID=korisnici.ID WHERE korisnici.ID=\'"+id+"\'")){
            while (qry.next()){
                QString pred=qry.value(0).toString();
                QPushButton *btn1 = new QPushButton(pred);
                connect(btn1, &QPushButton::clicked, [=]{
                    izborPredmeta(pred, id);
                });
                btn1->setObjectName("btn_"+QString::number(j));
                j++;
                vlay->addWidget(btn1);
                centralWidget->setLayout(vlay);
                }
            }
    }

F_student::~F_student()
{
    delete ui;
}

void F_student::izborPredmeta(QString kup, QString id){
        this->hide();
        p1=new izborkv(this, kup, id);
        p1->show();
}


void F_student::on_btn_odjava_clicked()
{
    parentWidget()->show();
    this->close();
}
