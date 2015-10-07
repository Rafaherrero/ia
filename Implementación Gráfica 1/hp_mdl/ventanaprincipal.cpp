#include "ventanaprincipal.h"
#include "ui_ventanaprincipal.h"

#include <iostream>

bool fileExists(QString path) {
	QFileInfo checkFile(path);
	// check if file exists and if yes: Is it really a file and no directory?
	if (checkFile.exists() && checkFile.isFile()) {
		return true;
	} else {
		return false;
	}
}

VentanaPrincipal::VentanaPrincipal(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::VentanaPrincipal)
{
	ui->setupUi(this);

	scene = new QGraphicsScene(this);
	ui->grafico_mapa->setScene(scene);

	QString filename = "img/grass_wall.png";
	QString pared = "img/pared.png";

	if (!fileExists(filename))
			std::cerr << "No existe esa ruta" << std::endl;

	QImage image(filename);
	QImage imagepared(pared);

	QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(image));
	QGraphicsPixmapItem* itempared = new QGraphicsPixmapItem(QPixmap::fromImage(imagepared));

	qint32 tamanox = 100;
	qint32 tamanoy = 100;

	scene->addItem(item);
	scene->addItem(itempared);

	ui->grafico_mapa->setGeometry(10,0,tamanox*16,tamanoy*16);
	ui->grafico_mapa->show();
	ui->estado_harry->setText("Harry ha entrado al laberinto");
	ui->estado_harry->adjustSize();
}

VentanaPrincipal::~VentanaPrincipal()
{
	delete ui;
}
