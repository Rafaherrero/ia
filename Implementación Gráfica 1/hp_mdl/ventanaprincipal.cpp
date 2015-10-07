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

	QString filename = ":/img/grass_wall.png";

	if (!fileExists(filename))
			std::cerr << "No existe esa ruta" << std::endl;

	QImage image(filename);

	QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(image));

	scene->addItem(item);

	ui->grafico_mapa->show();
}

VentanaPrincipal::~VentanaPrincipal()
{
	delete ui;
}
