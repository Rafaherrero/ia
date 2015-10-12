#include "ventanaprincipal.h"
#include "ui_ventanaprincipal.h"

#include <iostream>

VentanaPrincipal::VentanaPrincipal(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::VentanaPrincipal)
{
	ui->setupUi(this);

	scene = new QGraphicsScene(this);
	//scene->setSceneRect(0,0,64,64);
    //ui->grafico_mapa->resize(67,67);
	ui->grafico_mapa->resize(1800,1800);
	ui->grafico_mapa->setScene(scene);
	scene->setSceneRect(0, 0, 1800, 1800);

	QString filename = "img/pared.png";
	//QString pared = "recursos/img/Pared_(definitivo).png";

	//if (!fileExists(filename))
		//std::cerr << "No existe esa ruta" << std::endl;

	QImage image(filename);
	//QImage imagepared(pared);

	//QGraphicsPixmapItem* pared = new QGraphicsPixmapItem(QPixmap::fromImage(image));
	//QGraphicsPixmapItem* item2 = new QGraphicsPixmapItem(QPixmap::fromImage(imagepared));
	QGraphicsPixmapItem* pared1[10000];
	unsigned cont=0;

	for (int i=0;(i<1800);i=i+18){
		for (int j=0;(j<1800);j=j+18){
			pared1[cont] = new QGraphicsPixmapItem(QPixmap::fromImage(image));
			pared1[cont]->setOffset(i,j);
			scene->addItem(pared1[cont]);
			std::cout << cont << " ";
			cont++;
		}
	}
	//ui->grafico_mapa->fitInView(scene->itemsBoundingRect(), Qt::KeepAspectRatio );


	//scene->addItem(item2);

    //ui->grafico_mapa->setGeometry(10,0,tamanox*16,tamanoy*16);
	//ui->grafico_mapa->show();
	ui->estado_harry->setText("Harry ha entrado al laberinto");
	ui->estado_harry->adjustSize();

	mapa* el_mapa = new mapa(5,5);
	el_mapa->generar_laberinto();

}

void VentanaPrincipal::set_texto_estado(QString estado_harry){
	ui->estado_harry->setText(estado_harry);
}

VentanaPrincipal::~VentanaPrincipal()
{
	delete ui;
}
