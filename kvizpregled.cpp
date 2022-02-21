#include "kvizpregled.h"
#include "ui_kvizpregled.h"
#include <QString>
#include <QVector>
#include <QDebug>
#include <QtWidgets>

kvizPregled::kvizPregled(QWidget *parent, QString kviz, QString id) :
    QMainWindow(parent),
    ui(new Ui::kvizPregled)
{
    ui->setupUi(this);
    static float bodovi_f=0;
    Q_ASSERT(qry.driver()->hasFeature(QSqlDriver::NamedPlaceholders));
    int z=0;
    qry.exec("SELECT odgovori.odgovor, pitanja.pitanje, pitanja.odgovor FROM odgovori INNER JOIN pitanja ON odgovori.pitanje_ID=pitanja.ID WHERE odgovori.korisnik_ID='"+id+"\' AND odgovori.kviz_ID=(SELECT ID FROM kviz WHERE naziv=\'"+kviz+"\');");
    if (qry.next()){
        for (int i=0; i<10; i++){
        QVBoxLayout *vertical = new QVBoxLayout;
        for (int j=0; j<5; j++){
            QStringList ponudjeni;
            QGroupBox *grp = new QGroupBox("Pitanje "+QString::number(z+1)+":");
            QVBoxLayout *grpLayout=new QVBoxLayout;
            QString pitanje=qry.value(1).toString();
            int r=0, c=0;
            r=pitanje.count("~");
            c=pitanje.count("ˇ");
            if (r!=0)
                ponudjeni<<pitanje.split("~");
            if (c!=0)
                ponudjeni<<pitanje.split("ˇ");

            QLabel *lbl = new QLabel();

            if (r==0 && c==0){
                lbl->setText(pitanje);
                QLineEdit *txt = new QLineEdit(qry.value(0).toString());
                txt->setDisabled(1);
                QLabel *lbl2 = new QLabel(bodovi(0, qry.value(0).toString(), qry.value(1).toString(), qry.value(2).toString(), bodovi_f));
                grpLayout->addWidget(lbl);
                grpLayout->addWidget(txt);
                grpLayout->addWidget(lbl2);
                grp->setLayout(grpLayout);
                vertical->addWidget(grp);
            }
            else if (c!=0){
                lbl->setText(ponudjeni.at(0));
                grpLayout->addWidget(lbl);
                int *cekiraj=nadjibroj(qry.value(0).toString());
                int y=1;
                for (int i=1; i<=c; i++){
                    QCheckBox *cbtn = new QCheckBox(ponudjeni[i]);
                    if (cekiraj[y]==i)
                    {
                        cbtn->setChecked(1);
                        y++;
                    }
                    cbtn->setDisabled(1);
                    grpLayout->addWidget(cbtn);
                }
                QLabel *lbl2 = new QLabel(bodovi(1, qry.value(0).toString(), qry.value(1).toString(), qry.value(2).toString(), bodovi_f));
                grpLayout->addWidget(lbl2);
                grp->setLayout(grpLayout);
                vertical->addWidget(grp);
            }
            else{
                lbl->setText(ponudjeni.at(0));
                grpLayout->addWidget(lbl);
                QButtonGroup *btn_grupa=new QButtonGroup();
                int *cekiraj=nadjibroj(qry.value(0).toString());
                for (int i=1; i<=r; i++){
                    QRadioButton *rbtn= new QRadioButton(ponudjeni[i]);
                    if (cekiraj[1]==i)
                        rbtn->setChecked(1);
                    grpLayout->addWidget(rbtn);
                    btn_grupa->addButton(rbtn);
                    rbtn->setAutoExclusive(false);
                    rbtn->setDisabled(1);
                }
                QLabel *lbl2 = new QLabel(bodovi(0, qry.value(0).toString(), qry.value(1).toString(), qry.value(2).toString(), bodovi_f));
                grpLayout->addWidget(lbl2);
                grp->setLayout(grpLayout);
                vertical->addWidget(grp);
            }
            z++;
            qry.next();
            }
        QWidget *page = new QWidget;
        page->setLayout(vertical);
        ui->stck->insertWidget(i, page);    
    }
    }
    ui->stck->setCurrentIndex(0);
    ui->lbl_brbodova->setText(QString::number(bodovi_f, 'f', 2)+"/100.00");
}

kvizPregled::~kvizPregled()
{
    delete ui;
}

int *kvizPregled::nadjibroj(QString string)
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

QString kvizPregled::bodovi(int vrsta, QString odgovor_k, QString pitanje, QString odgovor_t, float &bodovi_f){
    float bodovi=0.00;
    QString string="Bodovi: ";
    if (vrsta==0){
        if (odgovor_k.trimmed().toUpper()==odgovor_t.trimmed().toUpper())
            bodovi=2.00;
    }

    else if (vrsta==1){
        QStringList ponudjeni_p=pitanje.split("ˇ");
        QStringList ponudjeni_k=odgovor_k.split("ˇ");
        QStringList ponudjeni_t=odgovor_k.split("ˇ");
        for (int i=0; i<ponudjeni_t.length(); i++)
            for (int j=0; j<odgovor_k.count("ˇ"); j++)
                if (ponudjeni_p[i]==ponudjeni_k[j])
                    bodovi=bodovi+(float(2)/ponudjeni_t.length());
    }
    bodovi_f=bodovi_f+bodovi;
    string=string+QString::number(bodovi, 'f', 2)+"/2.00";
    return string;
}

void kvizPregled::on_btn_stranica1_clicked()
{
    ui->stck->setCurrentIndex(0);
}

void kvizPregled::on_btn_stranica2_clicked()
{
    ui->stck->setCurrentIndex(1);
}

void kvizPregled::on_btn_stranica3_clicked()
{
    ui->stck->setCurrentIndex(2);
}

void kvizPregled::on_btn_stranica4_clicked()
{
    ui->stck->setCurrentIndex(3);
}

void kvizPregled::on_btn_stranica5_clicked()
{
    ui->stck->setCurrentIndex(4);
}

void kvizPregled::on_btn_stranica6_clicked()
{
    ui->stck->setCurrentIndex(5);
}

void kvizPregled::on_btn_stranica7_clicked()
{
    ui->stck->setCurrentIndex(6);
}

void kvizPregled::on_btn_stranica8_clicked()
{
    ui->stck->setCurrentIndex(7);
}

void kvizPregled::on_btn_stranica9_clicked()
{
    ui->stck->setCurrentIndex(8);
}

void kvizPregled::on_btn_stranica10_clicked()
{
    ui->stck->setCurrentIndex(9);
}

void kvizPregled::on_btn_pocetna_clicked()
{
    ui->stck->setCurrentIndex(0);
}

void kvizPregled::on_btn_minus_clicked()
{
    if(ui->stck->currentIndex()>0)
        ui->stck->setCurrentIndex(ui->stck->currentIndex()-1);
}

void kvizPregled::on_btn_plus_clicked()
{
    if(ui->stck->currentIndex()<9)
        ui->stck->setCurrentIndex(ui->stck->currentIndex()+1);
}

void kvizPregled::on_btn_zadnja_clicked()
{
    ui->stck->setCurrentIndex(9);
}

void kvizPregled::on_btn_kraj_clicked()
{
    parentWidget()->show();
    this->close();
}
