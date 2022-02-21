#include "userpredmet.h"
#include "ui_userpredmet.h"

userpredmet::userpredmet(QWidget *parent, QString Id, QString korisnik) :
    QDialog(parent),
    ui(new Ui::userpredmet)
{
    ui->setupUi(this);
    id=Id;

    ui->lbl_username->setText(korisnik);
    int pohadja[7];
    int k=0;
    qry.exec("SELECT predmet_ID FROM korisnik_predmet WHERE korisnik_ID=\'"+id+"\'");
    while (qry.next()){
            pohadja[k]=qry.value(0).toInt();
            k++;
    }
    postavi(&pohadja[0], id);
    connect(ui->btn_save, SIGNAL(clicked()), this, SLOT(sacuvaj()));
}

userpredmet::~userpredmet()
{
    delete ui;
}

void userpredmet::postavi(int predmet[7], QString id)
{
    QList<QCheckBox *> lista;
    lista=findChildren<QCheckBox *>();
    for (int i=0; i<velicina(id); i++)    
        for (int j=0; j<7; j++)
            if (predmet[i]==j)
                lista.at(i)->setChecked(true);
}

int userpredmet::velicina(QString id)
{
    qry.exec("SELECT COUNT (predmet_ID) FROM korisnik_predmet WHERE korisnik_ID=\'"+id+"\'");
    if (qry.next())return qry.value(0).toInt();
    else return  0;
}

void userpredmet::sacuvaj()
{
    QList<QCheckBox *> lista;
    lista=findChildren<QCheckBox *>();
    int predmeti[7];
    for (int i=0; i<7; i++)
    {
        if (lista[i]->isChecked())
            predmeti[i]=1;
        else
            predmeti[i]=0;
    }
    ubaci(&predmeti[0]);
}

void userpredmet::ubaci(int predmeti[7])
{
    for (int i=0; i<7; i++)
    {
        if (predmeti[i]==1){
            qry.exec("SELECT predmet_ID FROM korisnik_predmet WHERE korisnik_ID==\'"+id+"\' AND predmet_ID==\'"+QString::number(i+1)+"\'");
            if (!qry.next()){
                qry.exec("INSERT INTO korisnik_predmet (korisnik_ID, predmet_ID) VALUES (\'"+id+"\', \'"+QString::number(i+1)+"\')");

            }
        }
        else{
            qry.exec("DELETE FROM korisnik_predmet WHERE korisnik_ID=\'"+id+"\' AND predmet_ID=\'"+QString::number(i+1)+"\'");
        }
        qry.next();
    }
}

void userpredmet::on_btn_save_clicked()
{
    parentWidget()->show();
    this->close();
}
