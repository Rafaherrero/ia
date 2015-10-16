#ifndef VENTANAPRINCIPAL_H
#define VENTANAPRINCIPAL_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QtCore>
#include <QtGui>
#include <QImage>
#include <QGraphicsPixmapItem>
#include <QFileInfo>

#include "common.h"
#include "mapa.h"

#define RUTA_HARRY "img/Harry_Popotter_(definitivo).png"
#define RUTA_CESPED "img/Cesped_(definitivo).png"
#define RUTA_SETO "img/Seto_(definitivo).png"
#define RUTA_GRAGEA "img/Gragea_(definitivo).png"
#define RUTA_DEMENTOR "img/Dementor_(definitivo).png"
#define RUTA_COPA "img/Copa_(definitivo).png"

namespace Ui {
class VentanaPrincipal;
}

class VentanaPrincipal : public QMainWindow
{
	Q_OBJECT

public:
	explicit VentanaPrincipal(QWidget *parent = 0);
	~VentanaPrincipal();
	void set_texto_estado(QString estado_harry);

private:
	Ui::VentanaPrincipal *ui;
	QGraphicsScene *scene;
	QGraphicsEllipseItem *ellipse;
};

//SUPER IMPLEMENTACION DE AIRAM

#endif // VENTANAPRINCIPAL_H
