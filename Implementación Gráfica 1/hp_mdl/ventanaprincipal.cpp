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
	this->setMaximumSize((400)+100,(364)+180);
	scene = new QGraphicsScene(this);
	ui->grafico_mapa->resize(400,364);
	ui->grafico_mapa->setScene(scene);
	scene->setSceneRect(0, 0, 400, 364);
	ui->grafico_mapa->setMaximumSize(500+30,455+30);
	ui->estado_harry->setText("No se ha creado ningún laberinto");
	scene->addItem(carga);

	connect(ui->horizontalSlider,SIGNAL(valueChanged(int)),this,SLOT(sliderValueChanged(int)));
	connect(ui->play_lab,SIGNAL(clicked(bool)),this,SLOT(on_play_lab_clicked()));
	connect(ui->boton_aleatorio,SIGNAL(clicked(bool)),this,SLOT(on_boton_aleatorio_clicked()));

	ui->lista_temas->addItem("Agua");
	ui->lista_temas->addItem("Fuego");
	ui->lista_temas->addItem("Tierra");
	ui->lista_temas->addItem("Aire");
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

}


void VentanaPrincipal::gen_lab(int tam_x, int tam_y){

	int tamano_x=tam_x;
	int tamano_y=tam_y;
	int tamano_icono=18;

	el_mapa = new mapa_t(tamano_x,tamano_y);
	el_mapa->generar_laberinto();

	muneco_harry = new harryPotter (*el_mapa);
	std::cout << ui->horizontalSlider->value() << std::endl;

	ui->setupUi(this);
	this->setMaximumSize((tamano_x*tamano_icono)+100,(tamano_y*tamano_icono)+200);
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

	nodoMapa* objeto[tamano_x][tamano_y];
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
				objeto[conti][contj] = new nodoMapa(true);
				objeto[conti][contj]-> setOffset(i,j);
				scene->addItem(objeto[conti][contj]);
				conti++;
			}
			else{
				objeto[conti][contj] = new nodoMapa(false);
				objeto[conti][contj]-> setOffset(i,j);
				scene->addItem(objeto[conti][contj]);
				conti++;
			}
		}
		contj++;
	}

	harry_icono = new QGraphicsPixmapItem(QPixmap::fromImage(image_harry));
	harry_icono->setOffset(muneco_harry->get_posicion_harry().x()*tamano_icono, muneco_harry->get_posicion_harry().y()*tamano_icono);
	scene->addItem(harry_icono);

	copa = new QGraphicsPixmapItem(QPixmap::fromImage(image_copa));

	copa ->setOffset(el_mapa->get_pos_copa().x()*tamano_icono, el_mapa->get_pos_copa().y()*tamano_icono);
	scene->addItem(copa);

	ui->estado_harry->setText("Harry ha entrado al laberinto");
	ui->estado_harry->adjustSize();

	connect(ui->horizontalSlider,SIGNAL(valueChanged(int)),this,SLOT(sliderValueChanged(int)));
	connect(ui->play_lab,SIGNAL(clicked(bool)),this,SLOT(on_play_lab_clicked()));
	connect(ui->boton_aleatorio,SIGNAL(clicked(bool)),this,SLOT(on_boton_aleatorio_clicked()));
}

void VentanaPrincipal::gen_lab_setos(int tam_x, int tam_y, unsigned porcentaje){

	int tamano_x=tam_x;
	int tamano_y=tam_y;
	int tamano_icono=18;

	el_mapa = new mapa_t(tamano_x,tamano_y);
	el_mapa->generar_aleatorio(porcentaje);

	muneco_harry = new harryPotter (*el_mapa);
	std::cout << ui->horizontalSlider->value() << std::endl;

	ui->setupUi(this);
	this->setMaximumSize((tamano_x*tamano_icono)+100,(tamano_y*tamano_icono)+200);
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

	nodoMapa* objeto[tamano_x][tamano_y];
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
				objeto[conti][contj] = new nodoMapa(true);
				objeto[conti][contj]-> setOffset(i,j);
				scene->addItem(objeto[conti][contj]);
				conti++;
			}
			else{
				objeto[conti][contj] = new nodoMapa(false);
				objeto[conti][contj]-> setOffset(i,j);
				scene->addItem(objeto[conti][contj]);
				conti++;
			}
		}
		contj++;
	}

	harry_icono = new QGraphicsPixmapItem(QPixmap::fromImage(image_harry));
	harry_icono->setOffset(muneco_harry->get_posicion_harry().x()*tamano_icono, muneco_harry->get_posicion_harry().y()*tamano_icono);
	scene->addItem(harry_icono);

	copa = new QGraphicsPixmapItem(QPixmap::fromImage(image_copa));

	copa ->setOffset(el_mapa->get_pos_copa().x()*tamano_icono, el_mapa->get_pos_copa().y()*tamano_icono);
	scene->addItem(copa);

	ui->estado_harry->setText("Harry ha entrado al laberinto");
	ui->estado_harry->adjustSize();

	connect(ui->horizontalSlider,SIGNAL(valueChanged(int)),this,SLOT(sliderValueChanged(int)));
	connect(ui->play_lab,SIGNAL(clicked(bool)),this,SLOT(on_play_lab_clicked()));
	connect(ui->boton_aleatorio,SIGNAL(clicked(bool)),this,SLOT(on_boton_aleatorio_clicked()));
	connect(ui->boton_modificar,SIGNAL(clicked(bool)),this,SLOT(on_boton_modificar_clicked()));


}

nodoMapa::nodoMapa(bool hayseto):
hayseto_(hayseto)
{
	if(hayseto_)
		setPixmap(QPixmap::fromImage(QImage(RUTA_SETO)));
	else
		setPixmap(QPixmap::fromImage(QImage(RUTA_CESPED)));
}

void nodoMapa::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	if(hayseto_)
		hayseto_ = false;
	else
		hayseto_ = true;

	if(hayseto_)
		setPixmap(QPixmap::fromImage(QImage(RUTA_SETO)));
	else
		setPixmap(QPixmap::fromImage(QImage(RUTA_CESPED)));
}

void VentanaPrincipal::on_play_lab_clicked()
{
//	while (muneco_harry->continuar()){
//	muneco_harry->movimiento();
//	scene->
//	}

}

void VentanaPrincipal::sliderValueChanged(int value)
{
	QString valor = QString::number(value);
	ui->porcentaje_seto->setText(valor+"%");
}

void VentanaPrincipal::on_boton_aleatorio_clicked()
{
	gen_lab_setos(22,22,ui->horizontalSlider->value());
}

void VentanaPrincipal::on_boton_modificar_clicked()
{
	infolaberinto *cuadrodialogo = new infolaberinto;
	cuadrodialogo->show();
}
