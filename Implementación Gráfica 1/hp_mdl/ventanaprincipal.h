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
#include "mapa_t.h"
#include "harryPotter.h"
#include "infolaberinto.h"

#define RUTA_HARRY "img/Harry_Popotter_(definitivo).png"
#define RUTA_CESPED "img/Cesped_(definitivo).png"
#define RUTA_SETO "img/Seto_(definitivo).png"
#define RUTA_GRAGEA "img/Gragea_(definitivo).png"
#define RUTA_DEMENTOR "img/Dementor_(definitivo).png"
#define RUTA_COPA "img/Copa_(definitivo).png"
#define RUTA_CARGA "img/Loading_(definitivo).png"

namespace Ui {
class VentanaPrincipal;
}

class nodoMapa : public QGraphicsPixmapItem
{
public:
	bool hayseto_;
public:
	nodoMapa(bool);
	void mousePressEvent(QGraphicsSceneMouseEvent * event);
};

class VentanaPrincipal : public QMainWindow
{
	Q_OBJECT

public:
	explicit VentanaPrincipal(QWidget *parent = 0);
	~VentanaPrincipal();
	void set_texto_estado(QString estado_harry);
	infolaberinto *cuadrodialogo = new infolaberinto;
	void set_tam_x (unsigned tamano_x);
	void set_tam_y (unsigned tamano_y);

private slots:
	void on_boton_generar_clicked();
	void gen_lab();
	void gen_lab_setos(unsigned porcentaje);

	void on_play_lab_clicked();

	void sliderValueChanged(int value);

	void on_boton_aleatorio_clicked();

	void on_boton_modificar_clicked();
	void prueba();


private:
	Ui::VentanaPrincipal *ui;
	QGraphicsScene *scene;
	QGraphicsEllipseItem *ellipse;

	harryPotter* muneco_harry;
	mapa_t* el_mapa;
	unsigned tam_x=4;
	unsigned tam_y=4;
	unsigned tamano_icono=18;


};

//SUPER IMPLEMENTACION DE AIRAM

#endif // VENTANAPRINCIPAL_H
