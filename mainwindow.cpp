#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QAction *openAct = new QAction(tr("&Otworz..."), this);
    openAct->setShortcut(tr("Ctrl+O"));
    openAct->setStatusTip(tr("Otworz plik."));
    connect(openAct, SIGNAL(triggered()), this, SLOT(wyswietl()));

    QAction *aboutAct = new QAction(tr("&O programie..."), this);
    aboutAct->setStatusTip(tr("O programie..."));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    QAction *closeAct = new QAction(tr("&Koniec..."), this);
    closeAct->setShortcut(tr("Ctrl+X"));
    closeAct->setStatusTip(tr("Zamknij program"));
    connect(closeAct, SIGNAL(triggered()), this, SLOT(close()));


    QAction *powiekszAct = new QAction(tr("&Powieksz..."), this);
    powiekszAct->setShortcut(tr("Ctrl++"));
    powiekszAct->setStatusTip(tr("Powieksz zdjecie"));
    connect(powiekszAct, SIGNAL(triggered()), this, SLOT(powieksz()));

    QAction *pomniejszAct = new QAction(tr("&Pomniejsz..."), this);
    pomniejszAct->setShortcut(tr("Ctrl+-"));
    pomniejszAct->setStatusTip(tr("Pomniejsz zdjecie"));
    connect(pomniejszAct, SIGNAL(triggered()), this, SLOT(pomniejsz()));

    QAction *resetAct = new QAction(tr("&1:1..."), this);
    resetAct->setShortcut(tr("Ctrl+0"));
    resetAct->setStatusTip(tr("Rozmiar oryginalny"));
    connect(resetAct, SIGNAL(triggered()), this, SLOT(reset()));

    ui->menuPlik->addAction(openAct);
    ui->menuPlik->addAction(closeAct);
    ui->menuPomoc->addAction(aboutAct);

    ui->menuWidok->addAction(powiekszAct);
    ui->menuWidok->addAction(pomniejszAct);
    ui->menuWidok->addAction(resetAct);
    this->image_resize_ratio=1.0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}


void MainWindow::wyswietl(){


    //QString image_name= ui->plik->text();
    QFileDialog *f = new QFileDialog();
    this->image_name=f->getOpenFileName(this,"Wybierz plik",".","*.jpg");
    this->image_resize_ratio=1.0;
    this->RedrawImage();

}


void MainWindow::RedrawImage(){
    QGraphicsScene *scene = new QGraphicsScene();
    QImage *image = new QImage();
    image->load(this->image_name);
    int width=image->width();
    width=width*this->image_resize_ratio;
    *image=image->scaledToWidth(width);
    scene->addPixmap(QPixmap::fromImage(*image));
    ui->v->setScene(scene);
}


void MainWindow::powieksz(){
    this->image_resize_ratio=this->image_resize_ratio+0.1;
    this->RedrawImage();
}


void MainWindow::pomniejsz(){
    if (this->image_resize_ratio>=0.2){
        this->image_resize_ratio=this->image_resize_ratio-0.1;
    }
    this->RedrawImage();
}

void MainWindow::reset(){
    this->image_resize_ratio=1.0;
    this->RedrawImage();
}

void MainWindow::about(){
    QMessageBox::information(this,"O programie","\"PIC\"  to bardzo prosta przegladarka plikow jpg.");
}

