#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <QTextCodec>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabWidget->setCurrentIndex(0);
    ui->labelConnexion->setStyleSheet("color : red;font: italic 16pt 'Courier 10 Pitch';");
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    ui->lineEditMdp->setEchoMode(QLineEdit::Password);
    ui->lineEditPort->setText("3306");
}
MainWindow::~MainWindow()
{
    CloseBase();
    delete ui;
}
void MainWindow::connctBase()
{
    base=QSqlDatabase::addDatabase("QMYSQL");
    base.setHostName(ui->lineEditAdresse->text());
    base.setUserName(ui->lineEditNomU->text());
    base.setPassword(ui->lineEditMdp->text());
    base.setPort(ui->lineEditPort->text().toInt());
}
void MainWindow::CloseBase()
{
    base.close();
}
void MainWindow::connectIfPossible()
{
    if(ui->lineEditAdresse->text().length()*ui->lineEditMdp->text().length()*ui->lineEditNomU->text().length()*ui->lineEditPort->text().length()>0)
    {
        connctBase();
        if(base.open())
        {
            ui->labelConnexion->setText("Connecté");
            ui->labelConnexion->setStyleSheet("color : green;font: italic 16pt 'Courier 10 Pitch';");
          QSqlQuery req("show databases");
          while(req.next())
            {
                ui->listWidgetConnexion->addItem(req.value(0).toString());
            }
        }
        ui->lineEditNomNouvelleBase->setEnabled(true);
    }
    else
    {
        ui->labelConnexion->setText("Pas de connexion");
        ui->labelConnexion->setStyleSheet("color : red;font: italic 16pt 'Courier 10 Pitch';");
    }
}
void MainWindow::chargerTables()
{
    ui->comboBoxTables->clear();
    ui->labelBaseName->setText(base.databaseName());
    QSqlQuery req("show tables");
    while(req.next())
    {
        ui->comboBoxTables->addItem(req.value(0).toString());
    }
}
void MainWindow::chargerRequette()
{

    ui->labelNomBase2->setText(base.databaseName());
    ui->textEditRequette->setStyleSheet("color:#999999");
    ui->textEditRequette->setText("Tapez votre requette : ");
}
void MainWindow::on_pushButton_clicked()
{
    connctBase();
}
bool MainWindow::connexionOK()
{
    return ui->lineEditAdresse->text().length()*
           ui->lineEditMdp->text().length()*
           ui->lineEditNomU->text().length()*
           ui->lineEditPort->text().length();
}
void MainWindow::on_lineEditAdresse_cursorPositionChanged()
{
    ui->pushButtonConnection->setEnabled(connexionOK());
}
void MainWindow::on_lineEditPort_cursorPositionChanged()
{
    ui->pushButtonConnection->setEnabled(connexionOK());

}
void MainWindow::on_lineEditNomU_cursorPositionChanged()
{
    ui->pushButtonConnection->setEnabled(connexionOK());

}
void MainWindow::on_lineEditMdp_cursorPositionChanged()
{
    ui->pushButtonConnection->setEnabled(connexionOK());

}
void MainWindow::on_listWidgetConnexion_itemClicked(QListWidgetItem *item)
{
    base.setDatabaseName(item->text());
    base.exec("use "+item->text());
    ui->tabWidget->setCurrentIndex(1);
}
void MainWindow::on_tabWidget_currentChanged(int index)
{
    if(index==1)
    {
        chargerTables();
    }
    if(index==2)
    {
        chargerRequette();
    }
}
void MainWindow::on_comboBoxTables_currentIndexChanged()
{
    modelTable= new QSqlTableModel(this);
    modelTable->setTable(ui->comboBoxTables->currentText());
    modelTable->setEditStrategy(QSqlTableModel::OnRowChange);
    modelTable->select();
    ui->tableViewCOntenuTables->setModel(modelTable);
}
void MainWindow::on_textEditRequette_selectionChanged()
{
    if(ui->textEditRequette->toPlainText()=="Tapez votre requette : ")
    {
        ui->textEditRequette->clear();
        ui->textEditRequette->setStyleSheet("color : black");
    }
}
void MainWindow::on_pushButtonEnvoyerRequette_clicked()
{
    modelReq=new QSqlQueryModel(this);
    modelReq->setQuery(ui->textEditRequette->toPlainText());
    ui->tableViewRequette->setModel(modelReq);
}
void MainWindow::on_pushButtonParcourirScipt_clicked()
{
    qDebug()<<QFileDialog::getOpenFileName(this,tr("Ajouter un script"), "/home/","*.sql");
}
void MainWindow::on_pushButtonConnection_clicked()
{
    ui->listWidgetConnexion->clear();
    if(ui->pushButtonConnection->text()=="Connexion")
    {
        ui->pushButtonConnection->setText("Deconnexion");
        this->connectIfPossible();
    }
    else
    {
        ui->pushButtonConnection->setText("Connexion");
        if(ui->checkBoxEnregistrer->isChecked()==false)
        {
            ui->lineEditMdp->clear();
            ui->lineEditNomU->clear();
        }
    }
}

void MainWindow::on_pushButtonNouvelleBase_clicked()
{
    QSqlQuery req("create database "+ui->lineEditNomNouvelleBase->text());
    this->connexionOK();
    ui->lineEditNomNouvelleBase->clear();
    ui->listWidgetConnexion->clear();
    QSqlQuery req1("show databases");
    while(req1.next())
      {
          ui->listWidgetConnexion->addItem(req1.value(0).toString());
      }
}

void MainWindow::on_lineEditNomNouvelleBase_textChanged()
{
    ui->pushButtonNouvelleBase->setEnabled(ui->lineEditNomNouvelleBase->text().length());
}
