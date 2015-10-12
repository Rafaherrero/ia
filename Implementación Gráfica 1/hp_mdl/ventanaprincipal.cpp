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

	QGraphicsPixmapItem* objeto[TAMANO_X][TAMANO_Y];

	unsigned conti=0;
	unsigned contj=0;
	QPoint posicion_objeto(0,0);
	id_t tipo_celda;

	for (int j=0;(j<TAMANO_X*18);j=j+18){
		conti=0;
		for (int i=0;(i<TAMANO_Y*18);i=i+18){
			QPoint posicion_objeto(conti,contj);
			tipo_celda = el_mapa->get_entidad(posicion_objeto);
			if (tipo_celda==)
		}
	}

		//			if (cont>99&&cont<200){
		//				if (cont==100){
		//					cesped[cont] = new QGraphicsPixmapItem(QPixmap::fromImage(image_cesped));
		//					cesped[cont]->setOffset(i,j);
		//					scene->addItem(cesped[cont]);
		//					harry->setOffset(i,j);
		//					scene->addItem(harry);
		//					cont++;
		//				}
		//				else{
		//				cesped[cont] = new QGraphicsPixmapItem(QPixmap::fromImage(image_cesped));
		//				cesped[cont]->setOffset(i,j);
		//				scene->addItem(cesped[cont]);
		//				cont++;
		//				}
		//			}
		//			else{
		//			seto[conti][contj] = new QGraphicsPixmapItem(QPixmap::fromImage(image_seto));
		//			seto[conti][contj]->setOffset(i,j);
		//			scene->addItem(seto[conti][contj]);
		//			cont++;
		//			}
		//			contj++;
		//		}
		//		conti++;

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
