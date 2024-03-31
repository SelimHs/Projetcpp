#include "produit.h"
#include <QStandardItemModel>
#include <QIntValidator>
#include <QTableView>
#include <QMessageBox>
Produit::Produit()
{
 ID=NULL;
 Nom="";
 Type="";
 Poids="";
 Prix="";
 Qte="";

}
Produit::Produit(int ID,QString Nom,QString Type,QString Poids,QString Prix,QString Qte){
   this->ID=ID;
   this->Nom=Nom;
   this->Type=Type;
   this->Poids=Poids;
   this->Prix=Prix;
   this->Qte=Qte;
}

void Produit::setID(int n){ID=n;}
void Produit::setNom(QString n){Nom=n;}
void Produit::setType(QString n){Type=n;}
void Produit::setPoids(QString n){Poids=n;}
void Produit::setPrix(QString n){Prix=n;}
void Produit::setQte(QString n){Qte=n;}

int Produit::getID(){return ID;}
QString Produit::getNom(){return Nom;}
QString Produit::getType(){return Type;}
QString Produit::getPoids(){return Poids;}
QString Produit::getPrix(){return Prix;}
QString Produit::getQte(){return Qte;}

bool Produit::ajouter(){
    Produit p;
 QSqlQuery query;
 QIntValidator* intValidator= new QIntValidator();
 intValidator->setRange(0,9);
 query.prepare("insert into Produit (ID, Nom, Type, Poids, Prix, Qte)" "values(:ID, :Nom, :Type ,:Poids, :Prix, :Qte)");

 query.bindValue(":ID",ID);
 query.bindValue(":Nom",Nom);
 query.bindValue(":Type",Type);
 query.bindValue(":Poids",Poids);
 query.bindValue(":Prix",Prix);
 query.bindValue(":Qte",Qte);

 return query.exec();

}

bool Produit::supprimer(int IDx){
    QSqlQuery query;
    query.prepare("Delete from Produit where ID=:ID");
    query.bindValue(":ID",IDx);
    return query.exec();
}

/*QSqlQueryModel * Produit::afficher(){
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from Produit");
    model->setHeaderData(0,Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2,Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(3,Qt::Horizontal, QObject::tr("Poids"));
    model->setHeaderData(4,Qt::Horizontal, QObject::tr("Prix"));
    model->setHeaderData(5,Qt::Horizontal, QObject::tr("Qte"));

    return model;
}*/
QSqlTableModel * Produit::afficher()
{

    QSqlTableModel *mmodel = new QSqlTableModel();
    mmodel->setTable("PRODUIT");
    mmodel->select();
    return mmodel;
}

bool Produit::modifier(){
    QSqlQuery query;
    query.prepare("UPDATE Produit SET Nom =:Nom, Type =:Type, Poids =:Poids, Prix =:Prix, Qte =:Qte WHERE ID =:ID");

    query.bindValue(":ID",ID);
    query.bindValue(":Nom",Nom);
    query.bindValue(":Type",Type);
    query.bindValue(":Poids",Poids);
    query.bindValue(":Prix",Prix);
    query.bindValue(":Qte",Qte);

    return query.exec();

}



QSqlQueryModel * Produit::triPrix(){
    QSqlQueryModel * model = new QSqlQueryModel;
    model->setQuery("Select * from Produit order by Prix");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Poids"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Prix"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Qte"));
    return model;

}
QSqlQueryModel * Produit::triQte(){
    QSqlQueryModel * model = new QSqlQueryModel;
    model->setQuery("Select * from Produit order by Qte");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Poids"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Prix"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Qte"));
    return model;

}

void Produit::rechercher(QTableView *tableView, QString nomx){
    QSqlQueryModel *model= new QSqlQueryModel();
    QSqlQuery *query=new QSqlQuery;

    query->prepare("select * from Produit where (Nom like '%"+nomx+"%' )");
    query->exec();
    model->setQuery(*query);
    tableView->setModel(model);
    tableView->show();

}
/*void Produit::rechercherT(QTableView *tableView, QString Typex){
    QSqlQueryModel *model= new QSqlQueryModel();
    QSqlQuery *query=new QSqlQuery;

    query->prepare("select * from Produit where (Type like '%"+Typex+"%' )");
    query->exec();
    model->setQuery(*query);
    tableView->setModel(model);
    tableView->show();

}*/
<<<<<<< HEAD





=======
>>>>>>> 288da9dbd02a8bde5bf884f4635e6cbe134f6078
