#include "dialog.h"
#include "ui_Interface.h"
#include "produit.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connection.h"
#include <QMessageBox>
#include <QIntValidator>
#include <QTextStream>
#include <QFileDialog>
#include <QFileInfo>
#include <QPrinter>
#include <QPrintDialog>
#include <QTextDocument>
#include <QSqlQueryModel>
<<<<<<< HEAD
#include <QBarSet>
#include <QtCharts>
#include <QChartView>
#include <QBarSet>
#include <QBarSeries>
#include <QChartView>
#include <QImage>
#include <QImageWriter>
#include <QSystemTrayIcon>
#include <exportexcelobject.h>

=======


>>>>>>> 288da9dbd02a8bde5bf884f4635e6cbe134f6078
Produit temp;
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    mSystemTrayIcon=new QSystemTrayIcon(this);
    ui->tableView->setModel(Ptemp.afficher());
    ui->lineEdit_ID->setValidator(new QRegExpValidator(QRegExp("\\d+"), this));
    ui->lineEdit_Nom->setValidator(new QRegExpValidator(QRegExp("[A-Za-z]+"), this));
    ui->lineEdit_Type->setValidator(new QRegExpValidator(QRegExp("[A-Za-z]+"), this));
    ui->lineEdit_Poids->setValidator(new QRegExpValidator(QRegExp("\\d+"), this));
    ui->lineEdit_Prix->setValidator(new QRegExpValidator(QRegExp("\\d+"), this));
    ui->lineEdit_Qte->setValidator(new QRegExpValidator(QRegExp("\\d+"), this));

}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::setProduit(Produit p){
    ui->lineEdit_Nom->setText(p.getNom());
    ui->lineEdit_Type->setText(p.getType());
    ui->lineEdit_Poids->setText(p.getPoids());
    ui->lineEdit_Prix->setText(p.getPrix());
    ui->lineEdit_Qte->setText(p.getQte());
}


void Dialog::on_pushButton_Add_clicked(){
    int ID=ui->lineEdit_ID->text().toInt();
    QString Nom=ui->lineEdit_Nom->text();
    QString Type=ui->lineEdit_Type->text();
    QString Poids=ui->lineEdit_Poids->text();
    QString Prix=ui->lineEdit_Prix->text();
    QString Qte=ui->lineEdit_Qte->text();

   Produit P(ID,Nom,Type,Poids,Prix,Qte);
   if(ui->lineEdit_Nom->text().isEmpty()||ui->lineEdit_Type->text().isEmpty()||ui->lineEdit_Poids->text().isEmpty()||ui->lineEdit_Prix->text().isEmpty()||ui->lineEdit_Qte->text().isEmpty()) {
           QMessageBox::critical(nullptr, QObject::tr("Erreur"),
           QObject::tr("Information manquante.\n""Achevez la complétion."), QMessageBox::Cancel);}
   else{
   bool test=P.ajouter();
   if (test){
       ui->tableView->setModel(Ptemp.afficher());
       QMessageBox::information(nullptr,QObject::tr("OK"),QObject::tr("Ajout effectué \n"),QMessageBox::Cancel);
   }
   else QMessageBox::critical(nullptr,QObject::tr("Not OK"), QObject::tr("Ajout non effectué\n"),QMessageBox::Cancel);
}}

void Dialog::on_pushButton_Delete_clicked(){
    int ID=ui->lineEdit_3->text().toInt();

    int existe=0;
    QSqlQuery query;
    query.prepare("select * from Produit where ID=:ID");
    if (query.exec())
        while (query.next()){existe++;}
    if (existe!=0){
    bool test=Ptemp.supprimer(ID);
    if (test){
        ui->tableView->setModel(Ptemp.afficher());
        QMessageBox::information(nullptr,QObject::tr("OK"),QObject::tr("Supression effectuée \n"),QMessageBox::Cancel);
    }
    else QMessageBox::critical(nullptr,QObject::tr("Not OK"), QObject::tr("Suppression non effectuée\n"),QMessageBox::Cancel);
    }
    else if(existe==0){QMessageBox::critical(nullptr, QObject::tr("Erreur"), QObject::tr("Ce produit n'existe pas.\n"), QMessageBox::Cancel);}
}






void Dialog::on_pushButton_Edit_clicked()
{
    int ID=ui->lineEdit_ID->text().toInt();
    QString Nom=ui->lineEdit_Nom->text();
    QString Type=ui->lineEdit_Type->text();
    QString Poids=ui->lineEdit_Poids->text();
    QString Prix=ui->lineEdit_Prix->text();
    QString Qte=ui->lineEdit_Qte->text();

   Produit P(ID,Nom,Type,Poids,Prix,Qte);
   bool test=P.modifier();
   if (test){
       ui->tableView->setModel(Ptemp.afficher());
       QMessageBox::information(nullptr,QObject::tr("OK"),QObject::tr("Modification effectuée \n"),QMessageBox::Cancel);
   }
   else QMessageBox::critical(nullptr,QObject::tr("Not OK"), QObject::tr("Modification non effectuée\n"),QMessageBox::Cancel);
}







void Dialog::on_pushButton_PDF_clicked()
{
    QString strStream;
    QTextStream out(&strStream);
    const int rowC=ui->tableView->model()->rowCount();
    const int columnC=ui->tableView->model()->columnCount();
    out <<  "<html>\n"
            "<head>\n"
            "<meta Content=\"Text/html; charset=Windows-1251\">\n"
            <<  QString("<title>%1</title>\n").arg("strTitle")
            <<  "</head>\n"
            "<body bgcolor=#ffffff link=#5000A0>\n"

            //     "<align='right'> " << datefich << "</align>"
            "<center> <H1>Liste des Produits</H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";
    //headers
    out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
        for (int column = 0; column < columnC; column++)
            if (!ui->tableView->isColumnHidden(column))
                out << QString("<th>%1</th>").arg(ui->tableView->model()->headerData(column, Qt::Horizontal).toString());
        out << "</tr></thead>\n";
    //data
        for (int row = 0; row < rowC; row++)
            {
                out << "<tr> <td bkcolor=0>" << row + 1 << "</td>";
                for (int column = 0; column < columnC; column++)
                {
                    if (!ui->tableView->isColumnHidden(column))
                    {
                        QString data = ui->tableView->model()->data(ui->tableView->model()->index(row, column)).toString().simplified();
                        out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                    }
                }
                out << "</tr>\n";
            }
        out <<  "</table> </center>\n"
                "</body>\n"
                "</html>\n";
        //getting file name
        QString fileName = QFileDialog::getSaveFileName((QWidget * )0, "Sauvegarder en PDF", QString(), "*.pdf");
            if (QFileInfo(fileName).suffix().isEmpty())
            {
                fileName.append(".pdf");
            }

            QPrinter printer (QPrinter::PrinterResolution);
                printer.setOutputFormat(QPrinter::PdfFormat);
                printer.setPaperSize(QPrinter::A4);
                printer.setOutputFileName(fileName);

                QTextDocument doc;
                doc.setHtml(strStream);
                doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
                doc.print(&printer);

}

void Dialog::on_pushButton_TPrix_clicked()
{
    ui->tableView->setModel(temp.triPrix());
}



void Dialog::on_lineEdit_recherche_textChanged(QString Nom)
{
    Produit p;
    Nom=ui->lineEdit_recherche->text();
    p.rechercher(ui->tableView,Nom);

}
/*void Dialog::on_lineEdit_recherche_textChanged(QString Nom,QString Type)
{
    Produit p;
    if(ui->comboBox->currentText()=="Nom"){
    Nom=ui->lineEdit_recherche->text();
    p.rechercherN(ui->tableView,Nom);}
    else if (ui->comboBox->currentText()=="Type");
    Type=ui->lineEdit_recherche->text();
    p.rechercherT(ui->tableView,Type);)

<<<<<<< HEAD
=======
}*/
>>>>>>> 288da9dbd02a8bde5bf884f4635e6cbe134f6078


void Dialog::on_pushButton_TQte_clicked()
{
    ui->tableView->setModel(temp.triQte());
}
<<<<<<< HEAD



void Dialog::produitOOS()
{
    QSqlQuery query;
    query.prepare("SELECT ID, Nom FROM Produit WHERE Qte = 0");
    if (!query.exec())
    {
        QMessageBox::critical(this, "Error", "Failed to execute the query.");
        return;
    }

    if (query.next())
    {
        QString message = "Produits Hors-stock:\n\n";
        do
        {
            int id = query.value("ID").toInt();
            QString name = query.value("Nom").toString();
            message += QString("ID: %1, Nom: %2\n").arg(id).arg(name);
        } while (query.next());

        QMessageBox *infoBox = new QMessageBox(this);
        infoBox->setWindowTitle("Search Result");
        infoBox->setText(message);
        infoBox->setIcon(QMessageBox::Information);
        QTimer::singleShot(10000, infoBox, &QMessageBox::close); // Close after 5000 milliseconds (5 seconds)
        infoBox->exec();
    }
    else
    {
        QMessageBox *infoBox = new QMessageBox(QMessageBox::Information, "Search Result", "Pas de produits Hors-stock.", QMessageBox::Ok, this);
        QTimer::singleShot(5000, infoBox, &QMessageBox::close); // Close after 5000 milliseconds (5 seconds)
        infoBox->exec();
    }
}


void Dialog::on_pushButton_OOS_clicked()
{
    produitOOS();
}

void Dialog::afficherStatistiques() {
    QBarSeries *series = new QBarSeries();

    // Récupérer les données d'absence depuis la base de données
    QSqlQuery query;
    query.prepare("SELECT Qte, Nom FROM Produit");
    if (query.exec()) {
        while (query.next()) {
            QString nom = query.value("Nom").toString();
            int Qte = query.value("Qte").toInt();

            QBarSet *QteSet = new QBarSet(nom);
            *QteSet << Qte;

            series->append(QteSet);
        }
    } else {
        qDebug() << "Erreur lors de l'exécution de la requête SQL : " << query.lastError().text();
        return;
    }


    QChart *chart = new QChart();
    chart->addSeries(series);

    // Créer l'axe X et définir le titre
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);


    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Quantité");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);


    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QMainWindow *statsWindow = new QMainWindow();
    statsWindow->setCentralWidget(chartView);


    QPushButton *closeButton = new QPushButton("Fermer", statsWindow);
    QObject::connect(closeButton, &QPushButton::clicked, statsWindow, &QMainWindow::close);


    statsWindow->resize(800, 600);

    statsWindow->show();
}

void Dialog::on_pushButton_stats_clicked()
{
    afficherStatistiques();
}



/*void Dialog::on_pushButton_QR_clicked()
{
    QDesktopServices::openUrl(QUrl("https://app.qr-code-generator.com/manage/?aftercreate=1&count=1"));
        QString filename = QFileDialog::getSaveFileName(this,tr("choose"),"",tr("Image(*.png )"));
        if (QString::compare(filename,QString()) !=0)
        {
            QImage image;
            bool valid = image.load(filename);
            if(valid)
            {
                image=image.scaledToWidth(ui->label_24->width(), Qt::SmoothTransformation);
                        ui->label_24->setPixmap(QPixmap::fromImage(image));
            }
            else
            {
                //ERROR HANDLING
            }
}
}*/
//METIER QR (VOIDED BUT WORKS)


void Dialog::on_pushButton_Excel_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),
                                                       tr("Excel Files (*.xls)"));
       if (fileName.isEmpty())
           return;

       ExportExcelObject obj(fileName, "Produit", ui->tableView);

       //colums to export
       obj.addField(0, "ID", "char(20)");
       obj.addField(1, "Nom", "char(20)");
       obj.addField(2, "Type", "char(20)");
       obj.addField(3, "Poids", "char(20)");
       obj.addField(4, "Prix", "char(20)");
       obj.addField(5, "Qte", "char(20)");



       int retVal = obj.export2Excel();
       if( retVal > 0)
       {
           QMessageBox::information(this, tr("Done"),
                                    QString(tr("%1 records exported!")).arg(retVal)
                                    );
       }
}
=======
>>>>>>> 288da9dbd02a8bde5bf884f4635e6cbe134f6078
