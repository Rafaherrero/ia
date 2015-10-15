#include "ventanaprincipal.h"
#include "ui_ventanaprincipal.h"

#include "harry_potter.h"

#include <iostream>

VentanaPrincipal::VentanaPrincipal(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::VentanaPrincipal)
{

	mapa* el_mapa = new mapa(TAMANO_Y,TAMANO_X);
	el_mapa->generar_laberinto();

	ui->setupUi(this);
	this->setMaximumSize((TAMANO_X*18)+40,(TAMANO_Y*18)+100);
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

	QGraphicsPixmapItem* objeto[TAMANO_X][TAMANO_Y];

	unsigned conti=0;
	unsigned contj=0;
	QPoint posicion_objeto(0,0);

	for (int j=0;(j<TAMANO_Y*18);j=j+18){
		conti=0;
		for (int i=0;(i<TAMANO_X*18);i=i+18){
			QPoint posicion_objeto(contj,conti);
			if (el_mapa->get_seto(posicion_objeto)){
				objeto[conti][contj] = new QGraphicsPixmapItem(QPixmap::fromImage(image_seto));
				objeto[conti][contj]-> setOffset(i,j);
				scene->addItem(objeto[conti][contj]);
				conti++;
			}
			else{
				objeto[conti][contj] = new QGraphicsPixmapItem(QPixmap::fromImage(image_cesped));
				objeto[conti][contj]-> setOffset(i,j);
				scene->addItem(objeto[conti][contj]);
				conti++;
			}
		}
		contj++;
	}

	ui->estado_harry->setText("Harry ha entrado al laberinto");
	ui->estado_harry->adjustSize();

}

void VentanaPrincipal::set_texto_estado(QString estado_harry){
	ui->estado_harry->setText(estado_harry);
	ui->estado_harry->adjustSize();
}

VentanaPrincipal::~VentanaPrincipal()
{
	delete ui;
}
