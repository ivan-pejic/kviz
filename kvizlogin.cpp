#include "kvizlogin.h"
#include "ui_kvizlogin.h"

#define baza_path QDir::currentPath()+"/baza.sqlite"

KvizLogin::KvizLogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::KvizLogin)
{
    ui->setupUi(this);
    qApp->setStyleSheet("QPushButton{border-style: outset;"
                        "border-width: 1px;"
                        "background-color:lightgray;"
                        "border-radius: 10px;"
                        "border-color: black;"
                        "font:bold;"
                        "padding: 3px;}"
                        "QPushButton::hover{"
                        "background-color:gray;}"
                        "QLineEdit{border-style: outset;"
                        "border-width: 1px;"
                        "border-radius: 10px;"
                        "border-color: lightblack;"
                        "padding: 3px;}"
                        "QCheckBox{border-radius: 30px;}"
                        "QGroupBox{min-height: 110px;"
                        ""
                        "}");

    myDB=QSqlDatabase::addDatabase("QSQLITE");
    myDB.setDatabaseName(baza_path);
    QFileInfo checkFile(baza_path);
    if (checkFile.isFile())
    {
        if (myDB.open()){
            ui->lblResult->setText("Povezano na bazu..");
        }
        else{
            ui->lblResult->setText("Nije povezano na bazu..");
        }
    }
}

KvizLogin::~KvizLogin()
{
    delete ui;
    qDebug()<<"Zatvaranje konekcije na izlazu iz aplikacije";
    myDB.close();
}

void KvizLogin::on_btnLogin_clicked()
{
    QString Password, Username;
    Username=ui->txtUser->text();
    Password=ui->txtPass->text();

    if (!myDB.isOpen()){
        qDebug()<<"Nije povezano";
        return;
    }
    QSqlQuery qry;
    qry.prepare("SELECT korisnik, sifra, status, ID from korisnici WHERE korisnik=:username "
                "AND sifra=:pass");
    qry.bindValue(":username", Username);
    qry.bindValue(":pass", Password);
    if (qry.exec()){
        if (qry.next()){
            QString id=qry.value(3).toString();
            this->hide();
            if (qry.value(2)=="admin"){
            p1=new F_admin(this);
            p1->show();
            }
            if (qry.value(2)=="student"){
            p2=new F_student(this, id);
            p2->show();
            }

        }
        else{
            ui->lblResult->setText("Neuspjesan login");
        }
    }
}
