#include "dialog.h"
#include "ui_dialog.h"
#include "mainwindow.h"

Dialog::Dialog(QWidget *parent,QString u,QString v) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    balance=getBalance(u,v);



}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_Drawing_clicked()
{
    QString drawingAmount=ui->Drawing_money->text();
    double amount=drawingAmount.toDouble();
    QSqlQuery qry;

    if(balance>=amount){


        //qry.prepare("select * from bankUser where username='"+username+"' and password='"+password+"';" );
            qry.prepare("update bankUser set balance=balance-"+drawingAmount+" where username='"+username+"' and password='"+password+"'; "  );

        if(qry.exec()){
            QMessageBox::information(this,"info","success ");
        }
        else
            QMessageBox::information(this,"info","unsuccess "+username+"   "+password);
    }
    else
        QMessageBox::information(this,"info","not enough money");
    balance=getBalance(username,password);
}

bool Dialog::openDatabaseFile(){
    bool control=false;
    db=QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/db/mydb.sqlite");
    if(db.open())
        control=true;

    return control;
}

double Dialog::getBalance(QString username,QString password)
{
    QString hold;
   QSqlQuery qry;
   qry.prepare("select balance from bankUser where username='"+username+"' and password='"+password+"';" );
   if(qry.exec()){
       while(qry.next())
           hold=qry.value(0).toString();
   }

   ui->balance->setText(hold);
   return hold.toDouble();
}

void Dialog::on_Stick_in_clicked()
{
    QString givingAmount=ui->stickInAmount->text();

    if(openDatabaseFile()){
        QSqlQuery qry;
            qry.prepare("update bankUser set balance=balance+"+givingAmount+" where username='"+username+"' and password='"+password+"'; "  );

        if(qry.exec()){
            QMessageBox::information(this,"info","success ");
        }
        else
            QMessageBox::information(this,"info","unsuccess "+username+"   "+password);
    }
    balance=getBalance(username,password);
}


void Dialog::on_send_clicked()
{
    QString r_name=ui->name_send->text();
    QString r_surname=ui->surname_send->text();
    QString c_number=ui->C_number_send->text();
    QString bank_sender,bank_receiver;
    double amount=ui->Send_amount->text().toDouble();
    double extra_drawing=4.12;

    //QString drawingAmount=ui->Drawing_money->text();
    //double amount=drawingAmount.toDouble();
    QSqlQuery qry;
    qry.prepare("select bank from bankUser where username='"+username+"' and password='"+password+"';" );
    if(qry.exec()){
        while(qry.next())
            bank_sender=qry.value(0).toString();
    }
    else
        QMessageBox::information(this,"info","unsuccess "+username+"   "+password);
    qry.clear();

    qry.prepare("select bank from bankUser where customerNumber='"+c_number+"'" );
    if(qry.exec()){
        while(qry.next())
            bank_receiver=qry.value(0).toString();
    }
    else
        QMessageBox::information(this,"info","unsuccess "+username+"   "+password);
    qry.clear();






    if(balance>=amount){


        //qry.prepare("select * from bankUser where username='"+username+"' and password='"+password+"';" );
            qry.prepare("update bankUser set balance=balance-"+QString::number(amount)+" where username='"+username+"' and password='"+password+"'; "  );

        if(qry.exec()){
            QMessageBox::information(this,"info","success ");
        }
        else
            QMessageBox::information(this,"info","unsuccess "+username+"   "+password);
    }
    else
        QMessageBox::information(this,"info","not enough money");
    balance=getBalance(username,password);
    qry.clear();

       if(bank_sender==bank_receiver){
        qry.prepare("update bankUser set balance=balance+"+QString::number(amount)+" where name='"+r_name+"' and surname='"+r_surname+"' and customerNumber='"+c_number+"'; "  );
       }else
        qry.prepare("update bankUser set balance=balance+"+QString::number(amount+extra_drawing)+" where name='"+r_name+"' and surname='"+r_surname+"' and customerNumber='"+c_number+"'; "  );

        if(qry.exec()){
            QMessageBox::information(this,"info","success ");
        }
        else
            QMessageBox::information(this,"info","unsuccess "+username+"   "+password);

}

