#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QJsonObject>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->countryText->setText("");

    QNetworkAccessManager* netManager = new QNetworkAccessManager();
    connect(netManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(parseOutput(QNetworkReply*)));
    connect(netManager, SIGNAL(finished(QNetworkReply*)), netManager, SLOT(deleteLater()));

    netManager->get(QNetworkRequest(QUrl("http://www.ip-api.com/json")));
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::parseOutput(QNetworkReply* reply)
{
    QByteArray b  = reply->readAll();
    QString s(b);

    QJsonDocument json = QJsonDocument::fromJson(b);
    QJsonObject json_obj = json.object();
    if(json_obj.isEmpty()){
        ui->countryText->setText("Error parsing");
    }
    else {
        ui->countryText->setText(json_obj.value("country").toString());
        //QVariantMap m = json_obj.toVariantMap();
        ui->cityText->setText(json_obj.value("city").toString());
        ui->regionText->setText(json_obj.value("regionName").toString());
        ui->ipText->setText(json_obj.value("query").toString());
        QVariantMap qmap = json_obj.toVariantMap();
        ui->latText->setText(qmap["lat"].toString());
        ui->lonText->setText(qmap["lon"].toString());


    }



}
