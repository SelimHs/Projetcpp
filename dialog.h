#ifndef DIALOG_H
#define DIALOG_H
#include <QTableView>
#include <QDialog>
#include "produit.h"

namespace Ui {
class Dialog;
}
class QSystemTrayIcon;

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    void setProduit(Produit p);
    ~Dialog();
    void produitOOS();
    void afficherStatistiques();

private slots:
    void on_pushButton_Add_clicked();
    void on_pushButton_Delete_clicked();
    void on_pushButton_Edit_clicked();

    void on_pushButton_PDF_clicked();
    void on_pushButton_TPrix_clicked();
    void on_pushButton_TQte_clicked();
<<<<<<< HEAD
    void on_pushButton_stats_clicked();
    void on_lineEdit_recherche_textChanged(QString);


    void on_pushButton_OOS_clicked();



    //void on_pushButton_QR_clicked(); VOIDED BUT WORKS


    void on_pushButton_Excel_clicked();
=======

    void on_lineEdit_recherche_textChanged(QString);


>>>>>>> 288da9dbd02a8bde5bf884f4635e6cbe134f6078

private:
    Ui::Dialog *ui;
    QSystemTrayIcon *mSystemTrayIcon;
    Produit Ptemp;
};

#endif // DIALOG_H
