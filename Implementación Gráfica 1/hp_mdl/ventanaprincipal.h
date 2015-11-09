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
#include <QSound>

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

#define RUTA_PLAY "img/Comun/Icono_play.png"
#define RUTA_PAUSE "img/Comun/Icono_pause.png"
#define RUTA_TRANSPARENTE "img/Comun/Pause_transparente.png"
#define RUTA_STOP "img/Comun/Icono_stop.png"
#define RUTA_NEXT "img/Comun/Icono_siguiente.png"

namespace Ui {
class VentanaPrincipal;
class nodoMapa;
}

class nodoMapa : public QGraphicsPixmapItem
{
public:
	bool hayseto_;
	bool haycamino_;
	QPixmap* obstaculo_;
	QPixmap* suelo_;
public:
	/// \name Constructor
	///@{
	/*!
	 * \brief Constructor de cada uno de los objetos del mapa
	 * \param hayseto Define si ese objeto es un obstáculo o no
	 */
	
	nodoMapa(bool hayseto);
	///@}
	/// \name 
	void mousePressEvent(QGraphicsSceneMouseEvent * event);
	bool hay_seto();
	void hay_camino (bool camino);
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
	void ventana_aviso(QString nombre_ventana, QString texto_ventana);
	unsigned get_posicion (unsigned coord_i, unsigned coord_j);
	void ejecutar_algoritmo();

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
	void on_checkBox_3_clicked();
	void on_pause_lab_clicked();

	void on_next_lab_clicked();

private:
	Ui::VentanaPrincipal *ui;
	QGraphicsScene *scene;
	QGraphicsEllipseItem *ellipse;

	harryPotter* muneco_harry;
	mapa_t* el_mapa;
	unsigned tam_x;
	unsigned tam_y;
	unsigned tamano_icono;
	unsigned algoritmo;
	unsigned tamano_original_x;
	unsigned tamano_original_y;
	bool redimensionado;
	bool seguimiento_harry;
	bool mapa_generado;
	bool maxima_velocidad;
	bool nuevo;
	bool ejecutar_un_paso;
	bool un_paso;
	unsigned tema_actual;
	QPixmap suelo_tierra;
	QPixmap suelo_fuego;
	QPixmap suelo_aire;
	QPixmap suelo_agua;
	QPixmap obstaculo_tierra;
	QPixmap obstaculo_fuego;
	QPixmap obstaculo_aire;
	QPixmap obstaculo_agua;
	QPixmap* ruta_de_obstaculo=NULL;
	QPixmap* ruta_de_suelo=NULL;
	QGraphicsPixmapItem* harry_icono;
	QGraphicsPixmapItem* copa;
	QGraphicsPixmapItem* camino=NULL;
	std::vector<nodoMapa*> objetos_mapa;
	QString valor;
	QMessageBox ventana_error;
	QPoint posicion_harry_original;
	QPoint posicion_copa_original;
	unsigned contador_objeto=0;

};

//SUPER IMPLEMENTACION DE AIRAM

#endif // VENTANAPRINCIPAL_H
