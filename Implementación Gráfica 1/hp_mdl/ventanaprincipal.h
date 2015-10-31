#ifndef VENTANAPRINCIPAL_H
#define VENTANAPRINCIPAL_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QtCore>
#include <QtGui>
#include <QImage>
#include <QGraphicsPixmapItem>
#include <QFileInfo>
#include <QMessageBox>

#include "common.h"
#include "mapa_t.h"
#include "harryPotter.h"

#define RUTA_HARRY "img/Comun/Harry_Popotter.png"
#define RUTA_GRAGEA "img/Comun/Gragea.png"
#define RUTA_DEMENTOR "img/Comun/Dementor.png"
#define RUTA_COPA "img/Comun/Copa.png"
#define RUTA_CARGA "img/Comun/Loading.png"
#define RUTA_CAMINO "img/Comun/Camino.png"

#define RUTA_SUELO_TIERRA "img/Tierra/Suelo.png"
#define RUTA_OBSTACULO_TIERRA "img/Tierra/Obstaculo.png"

#define RUTA_SUELO_AGUA "img/Agua/Suelo.png"
#define RUTA_OBSTACULO_AGUA "img/Agua/Obstaculo.png"

#define RUTA_SUELO_AIRE "img/Aire/Suelo.png"
#define RUTA_OBSTACULO_AIRE "img/Aire/Obstaculo.png"

#define RUTA_SUELO_FUEGO "img/Fuego/Suelo.png"
#define RUTA_OBSTACULO_FUEGO "img/Fuego/Obstaculo.png"

#define RUTA_PLAY "img/Icono_play.png"
#define RUTA_STOP "img/Icono_stop.png"

namespace Ui {
class VentanaPrincipal;
class nodoMapa;
}

class nodoMapa : public QGraphicsPixmapItem
{
public:
	bool hayseto_;
	QPixmap* obstaculo_;
	QPixmap* suelo_;
public:
	nodoMapa(bool);
	void cambiar_tema(unsigned tm);
	void mousePressEvent(QGraphicsSceneMouseEvent * event);
	bool hay_seto();
};

class VentanaPrincipal : public QMainWindow
{
	Q_OBJECT

public:
	explicit VentanaPrincipal(QWidget *parent = 0);
	~VentanaPrincipal();
	void set_texto_estado(QString estado_harry);
	void set_tam_x (unsigned tamano_x);
	void set_tam_y (unsigned tamano_y);
	bool get_estado_ejec();
	void ventana_aviso(QString nombre_ventana, QString texto_ventana);

private slots:
	void on_boton_generar_clicked();
	void gen_lab_visual();
	void gen_lab_setos(unsigned porcentaje);
	void on_play_lab_clicked();
	void sliderValueChanged(int value);
	void on_boton_aleatorio_clicked();
	void modificar_tamano();
	void on_lista_temas_currentIndexChanged(int index);
	void on_checkBox_clicked();
	void on_horizontalSlider_2_valueChanged(int value);
	void on_stop_lab_clicked();
	void on_checkBox_2_clicked();
	void on_tam_mapa_x_valueChanged(int arg1);
	void on_tam_mapa_y_valueChanged(int arg1);

	void on_lista_algoritmos_currentIndexChanged(int index);

private:
	Ui::VentanaPrincipal *ui;
	QGraphicsScene *scene;
	QGraphicsEllipseItem *ellipse;

	harryPotter* muneco_harry;
	mapa_t* el_mapa;
	unsigned tam_x;
	unsigned tam_y;
	unsigned tamano_icono=18;
	unsigned algoritmo;
	bool redimensionado;
	bool seguimiento_harry;
	unsigned tema_actual=0;
	unsigned velocidad=0;
	QString ruta_suelo=RUTA_SUELO_TIERRA;
	QString ruta_obstaculo=RUTA_OBSTACULO_TIERRA;
	QPixmap suelo_tierra;
	QPixmap suelo_fuego;
	QPixmap suelo_aire;
	QPixmap suelo_agua;
	QPixmap obstaculo_tierra;
	QPixmap obstaculo_fuego;
	QPixmap obstaculo_aire;
	QPixmap obstaculo_agua;
	QGraphicsPixmapItem* harry_icono;
	QGraphicsPixmapItem* copa;
	std::vector<nodoMapa*> objetos_mapa;
	QString valor;
	QMessageBox ventana_error;
	unsigned contador_objeto=0;

};

//SUPER IMPLEMENTACION DE AIRAM

#endif // VENTANAPRINCIPAL_H
