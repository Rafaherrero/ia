#include "ventanaprincipal.h"
#include "ui_ventanaprincipal.h"

#include <iostream>

VentanaPrincipal::VentanaPrincipal(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::VentanaPrincipal)
{
	ui->setupUi(this);

	scene = new QGraphicsScene(this);
    scene->setSceneRect(0,0,64,64);
    //ui->grafico_mapa->resize(67,67);
    ui->grafico_mapa->resize(4000,4000);
	ui->grafico_mapa->setScene(scene);

	QString filename = "recursos/img/grass_wall.png";
	QString pared = "recursos/img/pared.png";

//	if (!fileExistsHola(filename))
	//		std::cerr << "No existe esa ruta" << std::endl;

	QImage image(filename);
	QImage imagepared(pared);

	QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(image));
    QGraphicsPixmapItem* item2 = new QGraphicsPixmapItem(QPixmap::fromImage(image));
    item2->setPos(0,16);

	scene->addItem(item);
    scene->addItem(item2);

    //ui->grafico_mapa->setGeometry(10,0,tamanox*16,tamanoy*16);
	ui->grafico_mapa->show();
	ui->estado_harry->setText("Harry ha entrado al laberinto");
	ui->estado_harry->adjustSize();

	mapa* el_mapa = new mapa(5,5);
	el_mapa->generar_laberinto();

	harry_potter harry_popotter;
	harry_popotter.movimiento();
}

void VentanaPrincipal::set_texto_estado(QString estado_harry){
	ui->estado_harry->setText(estado_harry);
}

VentanaPrincipal::~VentanaPrincipal()
{
	delete ui;
}
