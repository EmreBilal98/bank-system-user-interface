#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    db.close();
}

bool MainWindow::openDatabaseFile(){
    bool control=false;
    db=QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/db/mydb.sqlite");
    if(db.open())
        control=true;

    return control;
}

void MainWindow::on_log_in_button_clicked()
{
    QString username,password;
    username=ui->username->text();
    password=ui->password->text();

    if(openDatabaseFile()){
        QSqlQuery qry;


        qry.prepare("select * from bankUser where username='"+username+"' and password='"+password+"';");
        QSqlRecord rec=qry.record();
        if(qry.exec()){
            while(qry.next()){

                Dialog dialog(0,username,password);
                dialog.setModal(true);

                dialog.username=username;
                dialog.password=password;
                dialog.exec();
            }
        }

    }

}

