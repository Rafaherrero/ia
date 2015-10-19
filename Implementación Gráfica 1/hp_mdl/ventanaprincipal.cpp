#include "ventanaprincipal.h"
#include "ui_ventanaprincipal.h"
#include "harryPotter.h"
#include "infolaberinto.h"
#include "ui_infolaberinto.h"

#include <iostream>

VentanaPrincipal::VentanaPrincipal(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::VentanaPrincipal)
{
	
	int tamano_x=10;
	int tamano_y=10;
	int tamano_icono=18;

	QImage image_carga(RUTA_CARGA);
	QGraphicsPixmapItem* carga = new QGraphicsPixmapItem(QPixmap::fromImage(image_carga));

	ui->setupUi(this);
	this->setMaximumSize((500)+50,(455)+140);
	scene = new QGraphicsScene(this);
	ui->grafico_mapa->resize(500,455);
	ui->grafico_mapa->setScene(scene);
	scene->setSceneRect(0, 0, 500, 455);
	ui->grafico_mapa->setMaximumSize(500+3,455+3);
	ui->estado_harry->setText("No se ha creado ningún laberinto");
	scene->addItem(carga);

}

void VentanaPrincipal::set_texto_estado(QString estado_harry){
	ui->estado_harry->setText(estado_harry);
	ui->estado_harry->adjustSize();
}

VentanaPrincipal::~VentanaPrincipal()
{
	delete ui;
}

void VentanaPrincipal::on_boton_generar_clicked()
{
	//infolaberinto *cuadrodialogo = new infolaberinto;
	//cuadrodialogo->show();
}

void VentanaPrincipal::gen_lab(){

	int tamano_x=10;
	int tamano_y=10;
	int tamano_icono=18;

	mapa_t* el_mapa = new mapa_t(tamano_x,tamano_y);
	el_mapa->generar_laberinto();

	harryPotter harry_potter(*el_mapa);

	ui->setupUi(this);
	this->setMaximumSize((tamano_x*tamano_icono)+40,(tamano_y*tamano_icono)+140);
	scene = new QGraphicsScene(this);
	ui->grafico_mapa->resize(tamano_x*tamano_icono,tamano_y*tamano_icono);
	ui->grafico_mapa->setScene(scene);
	scene->setSceneRect(0, 0, tamano_x*tamano_icono, tamano_y*tamano_icono);
	ui->grafico_mapa->setMaximumSize((tamano_x*tamano_icono)+3,(tamano_y*tamano_icono)+3);

	QImage image_seto(RUTA_SETO);
	QImage image_cesped(RUTA_CESPED);
	QImage image_harry(RUTA_HARRY);
	QImage image_copa(RUTA_COPA);
	QImage image_dementor(RUTA_DEMENTOR);
	QImage image_gragea(RUTA_GRAGEA);

	QGraphicsPixmapItem* objeto[tamano_x][tamano_y];
	QGraphicsPixmapItem* harry_icono;
	QGraphicsPixmapItem* copa;

	unsigned conti=0;
	unsigned contj=0;
	QPoint posicion_objeto(0,0);

	for (int j=0;(j<tamano_y*tamano_icono);j=j+tamano_icono){
		conti=0;
		for (int i=0;(i<tamano_x*tamano_icono);i=i+tamano_icono){
			QPoint posicion_objeto(conti,contj);
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

	harry_icono = new QGraphicsPixmapItem(QPixmap::fromImage(image_harry));
	harry_icono->setOffset(harry_potter.get_posicion_harry().x()*tamano_icono, harry_potter.get_posicion_harry().y()*tamano_icono);
	scene->addItem(harry_icono);

	copa = new QGraphicsPixmapItem(QPixmap::fromImage(image_copa));

	copa ->setOffset(el_mapa->get_pos_copa().x()*tamano_icono, el_mapa->get_pos_copa().y()*tamano_icono);
	scene->addItem(copa);

	ui->estado_harry->setText("Harry ha entrado al laberinto");
	ui->estado_harry->adjustSize();
}
