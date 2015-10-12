#include "ventanaprincipal.h"
#include "ui_ventanaprincipal.h"

#include <iostream>

VentanaPrincipal::VentanaPrincipal(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::VentanaPrincipal)
{
	mapa* el_mapa = new mapa(5,5);
	el_mapa->generar_laberinto();

	ui->setupUi(this);
	this->setMaximumSize((TAMANO_X*18)+29,(TAMANO_Y*18)+84);
	scene = new QGraphicsScene(this);
	//scene->setSceneRect(0,0,64,64);
    //ui->grafico_mapa->resize(67,67);
	ui->grafico_mapa->resize(TAMANO_X*18,TAMANO_Y*18);
	ui->grafico_mapa->setScene(scene);
	scene->setSceneRect(0, 0, TAMANO_X*18, TAMANO_Y*18);
	ui->grafico_mapa->setMaximumSize((TAMANO_X*18)+3,(TAMANO_Y*18)+3);

	QImage image_seto(RUTA_SETO);
	QImage image_cesped(RUTA_CESPED);
	QImage image_harry(RUTA_HARRY);
	QImage image_copa(RUTA_COPA);
	QImage image_dementor(RUTA_DEMENTOR);
	QImage image_gragea(RUTA_GRAGEA);

	QGraphicsPixmapItem* harry = new QGraphicsPixmapItem(QPixmap::fromImage(image_harry));
	QGraphicsPixmapItem* copa = new QGraphicsPixmapItem(QPixmap::fromImage(image_copa));
	//QImage imagepared(pared);

	//QGraphicsPixmapItem* pared = new QGraphicsPixmapItem(QPixmap::fromImage(image));
	//QGraphicsPixmapItem* item2 = new QGraphicsPixmapItem(QPixmap::fromImage(imagepared));
	QGraphicsPixmapItem* seto[10000];
	QGraphicsPixmapItem* cesped[10000];
	QGraphicsPixmapItem* gragea[10000];
	QGraphicsPixmapItem* dementor[10000];

	unsigned cont=0;

	for (int i=0;(i<1800);i=i+18){
		for (int j=0;(j<1800);j=j+18){
			if (cont>99&&cont<200){
				if (cont==100){
					cesped[cont] = new QGraphicsPixmapItem(QPixmap::fromImage(image_cesped));
					cesped[cont]->setOffset(i,j);
					scene->addItem(cesped[cont]);
					harry->setOffset(i,j);
					scene->addItem(harry);
					cont++;
				}
				else{
				cesped[cont] = new QGraphicsPixmapItem(QPixmap::fromImage(image_cesped));
				cesped[cont]->setOffset(i,j);
				scene->addItem(cesped[cont]);
				cont++;
				}
			}
			else{
			seto[cont] = new QGraphicsPixmapItem(QPixmap::fromImage(image_seto));
			seto[cont]->setOffset(i,j);
			scene->addItem(seto[cont]);
			cont++;
			}
		}
	}
	//ui->grafico_mapa->fitInView(scene->itemsBoundingRect(), Qt::KeepAspectRatio );


	//scene->addItem(item2);

    //ui->grafico_mapa->setGeometry(10,0,tamanox*16,tamanoy*16);
	//ui->grafico_mapa->show();
	ui->estado_harry->setText("Harry ha entrado al laberinto");
	ui->estado_harry->adjustSize();


}

void VentanaPrincipal::set_texto_estado(QString estado_harry){
	ui->estado_harry->setText(estado_harry);
}

VentanaPrincipal::~VentanaPrincipal()
{
	delete ui;
}
