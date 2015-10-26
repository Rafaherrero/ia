#include "ventanaprincipal.h"
#include "ui_ventanaprincipal.h"
#include "infolaberinto.h"
#include "ui_infolaberinto.h"

#include <iostream>

VentanaPrincipal::VentanaPrincipal(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::VentanaPrincipal)
{
	QImage image_carga(RUTA_CARGA);
	QGraphicsPixmapItem* carga = new QGraphicsPixmapItem(QPixmap::fromImage(image_carga));

	ui->setupUi(this);
	this->setMaximumSize((400)+100,(364)+250);
	this->setMinimumSize((400)+100,(364)+250);
	scene = new QGraphicsScene(this);
	ui->grafico_mapa->resize(400,364);
	ui->grafico_mapa->setScene(scene);
	scene->setSceneRect(0, 0, 400, 364);
	ui->grafico_mapa->setMaximumSize(500+30,455+80);
	set_texto_estado("No se ha creado ningún laberinto");
	scene->addItem(carga);

	connect(ui->horizontalSlider,SIGNAL(valueChanged(int)),this,SLOT(sliderValueChanged(int)));
//	connect(ui->play_lab,SIGNAL(clicked(bool)),this,SLOT(on_play_lab_clicked()));
	connect(ui->boton_aleatorio,SIGNAL(clicked(bool)),this,SLOT(on_boton_aleatorio_clicked()));
	connect(ui->boton_generar,SIGNAL(clicked(bool)),this,SLOT(on_boton_generar_clicked()));
	connect(cuadrodialogo,SIGNAL(ok_clicked(void)),this,SLOT(modificar_tamano()));
	connect(ui->lista_temas,SIGNAL(currentIndexChanged(int)),this,SLOT(on_lista_temas_currentIndexChanged(int)));
	connect(ui->checkBox,SIGNAL(clicked(bool)),this,SLOT(on_checkBox_clicked()));

	ui->lista_temas->addItem("Tierra");
	ui->lista_temas->addItem("Fuego");
	ui->lista_temas->addItem("Aire");
	ui->lista_temas->addItem("Agua");

	ejecutando=false;

	suelo_tierra = QPixmap::fromImage(QImage(RUTA_SUELO_TIERRA));
	suelo_fuego = QPixmap::fromImage(QImage(RUTA_SUELO_FUEGO));
	suelo_aire = QPixmap::fromImage(QImage(RUTA_SUELO_AIRE));
	suelo_agua = QPixmap::fromImage(QImage(RUTA_SUELO_AGUA));
	obstaculo_tierra = QPixmap::fromImage(QImage(RUTA_OBSTACULO_TIERRA));
	obstaculo_fuego = QPixmap::fromImage(QImage(RUTA_OBSTACULO_FUEGO));
	obstaculo_aire = QPixmap::fromImage(QImage(RUTA_OBSTACULO_AIRE));
	obstaculo_agua = QPixmap::fromImage(QImage(RUTA_OBSTACULO_AGUA));

	tam_x = cuadrodialogo->get_tam_x();
	tam_y = cuadrodialogo->get_tam_y();

	redimensionado=false;
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
	ejecutando=false;
	el_mapa = new mapa_t(tam_x,tam_y);
	muneco_harry = new harryPotter (*el_mapa);
	el_mapa->mover_copa(common::QP(cuadrodialogo->get_pos_copa_x(),cuadrodialogo->get_pos_copa_y()));
	muneco_harry->set_posicion_harry(common::QP(cuadrodialogo->get_pos_harry_x(),cuadrodialogo->get_pos_harry_y()));
	el_mapa->generar_laberinto();

	gen_lab_visual();
}

void VentanaPrincipal::gen_lab_visual(){

	scene = new QGraphicsScene(this);
	ui->grafico_mapa->resize(tam_x*tamano_icono,tam_y*tamano_icono);
	ui->grafico_mapa->setScene(scene);
	scene->setSceneRect(0, 0, tam_x*tamano_icono, tam_y*tamano_icono);
	if((((tam_x*tamano_icono)+20)>500)&&(((tam_y*tamano_icono)+20)<500)){
		this->setMinimumSize(500,0);
		this->setMaximumSize(730,(tam_y*tamano_icono)+100);
		ui->grafico_mapa->setMaximumSize(700,(tam_y*tamano_icono)+5);
	}
		else if((((tam_x*tamano_icono)+20)<500)&&(((tam_y*tamano_icono)+20)>500)){
			this->setMinimumSize(500,0);
			this->setMaximumSize(((tam_x*tamano_icono)+20),600);
			ui->grafico_mapa->setMaximumSize(((tam_x*tamano_icono)+5),500);
	}
			else if((((tam_x*tamano_icono)+20)<500)&&(((tam_y*tamano_icono)+20)<500)){
				this->setMinimumSize(500,0);
				this->setMaximumSize((tam_x*tamano_icono)+100,(tam_y*tamano_icono)+200);
				ui->grafico_mapa->setMaximumSize(((tam_x*tamano_icono)+5),((tam_y*tamano_icono)+5));
	}
				else if ((((tam_x*tamano_icono)+20)>500)&&(((tam_y*tamano_icono)+20)>500)){
					this->setMaximumSize(730,600);
					ui->grafico_mapa->setMaximumSize(700,500);
	}

	QImage image_harry(RUTA_HARRY);
	QImage image_copa(RUTA_COPA);
	QImage image_dementor(RUTA_DEMENTOR);
	QImage image_gragea(RUTA_GRAGEA);

	nodoMapa* objeto[tam_x][tam_y];

	unsigned conti=0;
	unsigned contj=0;
	QPoint posicion_objeto(0,0);

	for (unsigned j=0;(j<tam_y*tamano_icono);j=j+tamano_icono){
		conti=0;
		for (unsigned i=0;(i<tam_x*tamano_icono);i=i+tamano_icono){
			QPoint posicion_objeto(conti,contj);
			if (el_mapa->get_seto(posicion_objeto)){
				objeto[conti][contj] = new nodoMapa(true,get_obstaculo_actual(),get_suelo_actual());
				objeto[conti][contj]-> setOffset(i,j);
				scene->addItem(objeto[conti][contj]);
				conti++;
			}
			else{
				objeto[conti][contj] = new nodoMapa(false,get_obstaculo_actual(),get_suelo_actual());
				objeto[conti][contj]-> setOffset(i,j);
				scene->addItem(objeto[conti][contj]);
				conti++;
			}
		}
		contj++;
	}

	copa = new QGraphicsPixmapItem(QPixmap::fromImage(image_copa));
	copa ->setOffset(el_mapa->get_pos_copa().x()*tamano_icono, el_mapa->get_pos_copa().y()*tamano_icono);
	scene->addItem(copa);

	harry_icono = new QGraphicsPixmapItem(QPixmap::fromImage(image_harry));
	harry_icono->setOffset(muneco_harry->get_posicion_harry().x()*tamano_icono, muneco_harry->get_posicion_harry().y()*tamano_icono);
	scene->addItem(harry_icono);

	ui->estado_harry->setText("Harry ha entrado al laberinto");
	ui->estado_harry->adjustSize();
	qApp->processEvents();


}

void VentanaPrincipal::gen_lab_setos(unsigned porcentaje){

	ejecutando=false;
	el_mapa = new mapa_t(tam_x,tam_y);
	muneco_harry = new harryPotter (*el_mapa);
	muneco_harry->set_posicion_harry(common::QP(cuadrodialogo->get_pos_harry_x(),cuadrodialogo->get_pos_harry_y()));
	el_mapa->generar_aleatorio(porcentaje);

	gen_lab_visual();
}

nodoMapa::nodoMapa(bool hayseto, QPixmap& path_obstaculo, QPixmap& path_suelo):
hayseto_(hayseto)
{
	if(hayseto_)
		setPixmap(path_obstaculo);
	else
		setPixmap(path_suelo);
}

void nodoMapa::mousePressEvent(){
if(hayseto_)
	hayseto_ = false;
else
	hayseto_ = true;
}

void nodoMapa::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
//	bool prueba = VentanaPrincipal::get_estado_ejec(void);
	//if (!prueba){
	if(hayseto_)
		hayseto_ = false;
	else
		hayseto_ = true;

//	if(hayseto_)
//		setPixmap(QPixmap::fromImage(QImage(ruta_obstaculo)));
//	else
//		setPixmap(QPixmap::fromImage(QImage(ruta_suelo)));
//	//}
}

void VentanaPrincipal::on_play_lab_clicked()
{
	ejecutando=true;
	unsigned i=0;
	QPoint pos;
	QString texto;
	QGraphicsPixmapItem* camino[el_mapa->contar_cesped()];
	QImage image_camino(RUTA_CAMINO);

	while (muneco_harry->puedo_continuar()){
		camino[i] = new QGraphicsPixmapItem(QPixmap::fromImage(image_camino));
		camino[i]->setOffset(muneco_harry->get_posicion_harry().x()*tamano_icono,muneco_harry->get_posicion_harry().y()*tamano_icono);
		scene->addItem(camino[i]);
		pos = muneco_harry->movimiento();
		harry_icono->setOffset(pos.x()*tamano_icono,pos.y()*tamano_icono);
		usleep(100000);
		texto="Harry se ha movido a la posición ("+QString::number(pos.x())+","+QString::number(pos.y())+")";
		set_texto_estado(texto);
		qApp->processEvents();
		i++;
	}

	if (muneco_harry->get_posicion_harry()==el_mapa->get_pos_copa()){
	set_texto_estado("¡¡¡HARRY HA ENCONTRADO LA COPA!!!");
	ventana_aviso("¡¡¡FELICIDADES!!!","¡¡¡HARRY HA ENCONTRADO LA COPA!!!");
	}
	else{
	set_texto_estado("Harry no ha encontrado la salida");
	ventana_aviso("HARRY HA MUERTO","Harry no ha encontrado la salida y Voldemort lo ha matado :(");
	}
}

void VentanaPrincipal::sliderValueChanged(int value)
{
	QString valor = QString::number(value);
	ui->porcentaje_seto->setText(valor+"%");
}

void VentanaPrincipal::on_boton_aleatorio_clicked()
{
	gen_lab_setos(ui->horizontalSlider->value());
}

void VentanaPrincipal::on_boton_modificar_clicked()
{
	cuadrodialogo->show();
}

void VentanaPrincipal::set_tam_x (unsigned tamano_x){
	tam_x=tamano_x;
}

void VentanaPrincipal::set_tam_y (unsigned tamano_y){
	tam_y=tamano_y;
}

void VentanaPrincipal::modificar_tamano(){
	set_tam_x(cuadrodialogo->get_tam_x());
	set_tam_y(cuadrodialogo->get_tam_y());
}

bool VentanaPrincipal::get_estado_ejec(){
	return ejecutando;
}

void VentanaPrincipal::ventana_aviso(QString nombre_ventana, QString texto_ventana){
	QMessageBox probando;
	probando.setWindowTitle(nombre_ventana);
	probando.setText(texto_ventana);
	probando.exec();
}

QString VentanaPrincipal::get_ruta_suelo(){
return ruta_suelo;
}

QString VentanaPrincipal::get_ruta_obstaculo(){
return ruta_obstaculo;
}

void VentanaPrincipal::set_ruta_suelo(QString path_suelo){
ruta_suelo=path_suelo;
}

void VentanaPrincipal::set_ruta_obstaculo(QString path_obstaculo){
ruta_obstaculo=path_obstaculo;
}

void VentanaPrincipal::on_lista_temas_currentIndexChanged(int index)
{
	if (index==0){
		tema_actual=0;
	}
	else if (index==1){
		tema_actual=1;
	}
	else if (index==2){
		tema_actual=2;
	}
	else if (index==3){
		tema_actual=3;
	}
}

QPixmap& VentanaPrincipal::get_suelo_actual(){
	switch (tema_actual) {
	case 0:
		return suelo_tierra;
	break;
	case 1:
		return suelo_fuego;
	break;
	case 2:
		return suelo_aire;
	break;
	case 3:
		return suelo_agua;
	break;
	}
	return suelo_tierra;
}

QPixmap& VentanaPrincipal::get_obstaculo_actual(){
	switch (tema_actual) {
	case 0:
		return obstaculo_tierra;
	break;
	case 1:
		return obstaculo_fuego;
	break;
	case 2:
		return obstaculo_aire;
	break;
	case 3:
		return obstaculo_agua;
	break;
	}
	return obstaculo_tierra;
}

void VentanaPrincipal::on_checkBox_clicked()
{
	if(ui->checkBox->checkState())
	redimensionado=true;
}
