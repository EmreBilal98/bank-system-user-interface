#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include<QtSql>
#include<QSqlDatabase>
#include<QMessageBox>



namespace Ui {
class Dialog;
}

class Dialog : public QDialog{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr,QString u=" ",QString v=" ");
    bool openDatabaseFile(void);
    double getBalance(QString,QString);
    QString username;
    QString password;
    double balance;
    QSqlQueryModel *qmodel;
    ~Dialog();

private slots:
    void on_Drawing_clicked();

    void on_Stick_in_clicked();

    void on_send_clicked();

private:
    Ui::Dialog *ui;
    QSqlDatabase db;


};

#endif // DIALOG_H
