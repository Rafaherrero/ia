#include "ventanaprincipal.h"
#include "ui_ventanaprincipal.h"

#include <iostream>

QPixmap* path_obstaculo=NULL;
QPixmap* path_suelo=NULL;
bool ejecutando=false;
bool terminado_ejecucion=false;
bool pausa=false;

VentanaPrincipal::VentanaPrincipal(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::VentanaPrincipal)
{
	QImage image_carga(RUTA_CARGA);
	QGraphicsPixmapItem* carga = new QGraphicsPixmapItem(QPixmap::fromImage(image_carga));

	ui->setupUi(this);
	this->setMaximumSize(580,614);
	this->setMinimumSize(580,614);
	scene = new QGraphicsScene(this);
	ui->grafico_mapa->resize(580,535);
	ui->grafico_mapa->setScene(scene);
	scene->setSceneRect(-55, 0, 520, 364);
	ui->grafico_mapa->setMaximumSize(580,535);
	set_texto_estado("No se ha creado ningún laberinto");
	scene->addItem(carga);
	nuevo=true;

	connect(ui->horizontalSlider,SIGNAL(valueChanged(int)),this,SLOT(sliderValueChanged(int)));
	connect(ui->boton_aleatorio,SIGNAL(clicked(bool)),this,SLOT(on_boton_aleatorio_clicked()));
	connect(ui->lista_temas,SIGNAL(currentIndexChanged(int)),this,SLOT(on_lista_temas_currentIndexChanged(int)));

	ui->lista_temas->addItem("Tierra");
	ui->lista_temas->addItem("Fuego");
	ui->lista_temas->addItem("Aire");
	ui->lista_temas->addItem("Agua");

	ui->lista_algoritmos->addItem("DFS");
	ui->lista_algoritmos->addItem("A*");
	ui->lista_algoritmos->addItem("LRTA*");
	ui->lista_algoritmos->addItem("RTA*");

	redimensionado=false;
	seguimiento_harry=false;
	mapa_generado=false;
	maxima_velocidad=false;
	finalizado=true;
	tema_actual=0;
	tamano_icono=18;

	suelo_tierra = QPixmap::fromImage(QImage(RUTA_SUELO_TIERRA));
	suelo_fuego = QPixmap::fromImage(QImage(RUTA_SUELO_FUEGO));
	suelo_aire = QPixmap::fromImage(QImage(RUTA_SUELO_AIRE));
	suelo_agua = QPixmap::fromImage(QImage(RUTA_SUELO_AGUA));
	obstaculo_tierra = QPixmap::fromImage(QImage(RUTA_OBSTACULO_TIERRA));
	obstaculo_fuego = QPixmap::fromImage(QImage(RUTA_OBSTACULO_FUEGO));
	obstaculo_aire = QPixmap::fromImage(QImage(RUTA_OBSTACULO_AIRE));
	obstaculo_agua = QPixmap::fromImage(QImage(RUTA_OBSTACULO_AGUA));

	tam_x = ui->tam_mapa_x->value();
	tam_y = ui->tam_mapa_y->value();

	QPixmap icon_play(RUTA_PLAY);
	QPixmap icon_pause(RUTA_PAUSE);
	QPixmap icon_stop(RUTA_STOP);
	QPixmap icon_next(RUTA_NEXT);

	QIcon icon_play_button(icon_play);
	QIcon icon_pause_button(icon_pause);
	QIcon icon_stop_button(icon_stop);
	QIcon icon_next_button(icon_next);

	ui->play_lab->setIcon(icon_play_button);
	ui->pause_lab->setIcon(icon_pause_button);
	ui->stop_lab->setIcon(icon_stop_button);
	ui->next_lab->setIcon(icon_next_button);

	el_mapa = new mapa_t(tam_x,tam_y);
	muneco_harry = new harryPotter(*el_mapa);

	ruta_de_obstaculo=&obstaculo_tierra;
	ruta_de_suelo=&suelo_tierra;

	posicion_harry_original=muneco_harry->get_posicion_harry();
	posicion_copa_original=el_mapa->get_pos_copa();

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
	terminado_ejecucion=false;
	if(!ejecutando){
		on_tam_mapa_x_valueChanged(0);
		on_tam_mapa_y_valueChanged(0);
		nuevo=true;
		el_mapa->resize(tam_x,tam_y);
		el_mapa->mover_copa(common::QP(ui->pos_copa_x->value(),ui->pos_copa_y->value()));
		muneco_harry->set_posicion_harry_nuevo(common::QP(ui->pos_harry_x->value(),ui->pos_harry_y->value()));
		el_mapa->generar_laberinto();
		posicion_harry_original=muneco_harry->get_posicion_harry();
		posicion_copa_original=el_mapa->get_pos_copa();
		path_obstaculo=ruta_de_obstaculo;
		path_suelo=ruta_de_suelo;
		gen_lab_visual();
	}
}

void VentanaPrincipal::gen_lab_visual(){

	objetos_mapa.clear();
	objetos_mapa.resize(tam_x*tam_y);
	scene->clear();
	ui->grafico_mapa->setScene(scene);
	scene->setSceneRect(0, 0, tam_x*tamano_icono, tam_y*tamano_icono);

	QImage image_harry(RUTA_HARRY);
	QImage image_copa(RUTA_COPA);

	for (unsigned j=0;(j<tam_y);j++){
		for (unsigned i=0;(i<tam_x);i++){
			if (el_mapa->get_seto(common::QP(i,j))){
				objetos_mapa[contador_objeto] = (new nodoMapa(true));
				objetos_mapa[contador_objeto] -> setOffset(i*tamano_icono,j*tamano_icono);
				scene->addItem(objetos_mapa[contador_objeto]);
				contador_objeto++;
			}
			else{
				objetos_mapa[contador_objeto] = (new nodoMapa(false));
				objetos_mapa[contador_objeto] -> setOffset(i*tamano_icono,j*tamano_icono);
				scene->addItem(objetos_mapa[contador_objeto]);
				contador_objeto++;
			}
		}
	}

	copa = new QGraphicsPixmapItem(QPixmap::fromImage(image_copa));
	copa ->setOffset(el_mapa->get_pos_copa().x()*tamano_icono, el_mapa->get_pos_copa().y()*tamano_icono);
	scene->addItem(copa);
	objetos_mapa[get_posicion(el_mapa->get_pos_copa().x(), el_mapa->get_pos_copa().y())]->hay_camino (true);

	harry_icono = new QGraphicsPixmapItem(QPixmap::fromImage(image_harry));
	harry_icono->setOffset(muneco_harry->get_posicion_harry().x()*tamano_icono, muneco_harry->get_posicion_harry().y()*tamano_icono);
	scene->addItem(harry_icono);
	objetos_mapa[get_posicion(muneco_harry->get_posicion_harry().x(), muneco_harry->get_posicion_harry().y())]->hay_camino (true);

	ui->estado_harry->setText("Harry ha entrado al laberinto");
	ui->estado_harry->adjustSize();
	qApp->processEvents();
	contador_objeto=0;
	mapa_generado=true;
	on_checkBox_clicked();
	tamano_original_x=tam_x;
	tamano_original_y=tam_y;
}

void VentanaPrincipal::gen_lab_setos(unsigned porcentaje){

	terminado_ejecucion=false;
	if(!ejecutando){
		nuevo=true;
		el_mapa->resize(tam_x,tam_y);
		el_mapa->mover_copa(common::QP(ui->pos_copa_x->value(),ui->pos_copa_y->value()));
		muneco_harry->set_posicion_harry_nuevo(common::QP(ui->pos_harry_x->value(),ui->pos_harry_y->value()));
		el_mapa->generar_aleatorio(porcentaje);
		posicion_harry_original=muneco_harry->get_posicion_harry();
		posicion_copa_original=el_mapa->get_pos_copa();
		path_obstaculo=ruta_de_obstaculo;
		path_suelo=ruta_de_suelo;
		gen_lab_visual();
	}
}

nodoMapa::nodoMapa(bool hayseto):
hayseto_(hayseto),
haycamino_(false)
{
	if(hayseto_)
		setPixmap(*path_obstaculo);
	else
		setPixmap(*path_suelo);
}

void nodoMapa::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	if((!ejecutando&&!terminado_ejecucion)||(!ejecutando&&pausa)){
		if(!haycamino_){
			if(hayseto_)
				hayseto_ = false;
			else
				hayseto_ = true;

			if(hayseto_)
				setPixmap(*path_obstaculo);
			else
				setPixmap(*path_suelo);
		}
	}
}

bool nodoMapa::hay_seto(){
	return hayseto_;
}

void nodoMapa::hay_camino (bool camino){
	haycamino_=camino;
}

void VentanaPrincipal::on_play_lab_clicked(){
	ejecutar_un_paso = false;
	un_paso = false;
	if (nuevo)
		ejecutar_algoritmo();
	else{
		if (!finalizado)
			ventana_aviso("ERROR CAMBIANDO TAMAÑOS", "Ha cambiado el valor de los datos mientras una búsqueda se estaba ejecutando. Genere un nuevo laberinto.");
		else
			ventana_aviso("OPCION NO VALIDA", "Genere un nuevo laberinto.");
	}
}

void VentanaPrincipal::ejecutar_algoritmo()
{
	if(mapa_generado){
		finalizado=false;
		ejecutando=true;
		pausa=false;
		QPoint pos;
		QImage image_camino(RUTA_CAMINO);

	for (unsigned j=0;(j<tam_y);j++){
		for (unsigned i=0;(i<tam_x);i++){
			if(el_mapa->get_seto(common::QP(i,j))!=objetos_mapa[contador_objeto]->hay_seto()){
				el_mapa->get_seto(common::QP(i,j))=objetos_mapa[contador_objeto]->hay_seto();
			}
			contador_objeto++;
		}
	}
	contador_objeto=0;

	if(algoritmo==0){
	while (muneco_harry->puedo_continuar_DFS()&&ejecutando&&!un_paso){
		camino = new QGraphicsPixmapItem(QPixmap::fromImage(image_camino));
		camino->setOffset(muneco_harry->get_posicion_harry().x()*tamano_icono,muneco_harry->get_posicion_harry().y()*tamano_icono);
		scene->addItem(camino);
		pos = muneco_harry->movimiento_DFS();
		scene->removeItem(harry_icono);
		harry_icono->setOffset(pos.x()*tamano_icono,pos.y()*tamano_icono);
		scene->addItem(harry_icono);
		if ((common::QP(pos.x(),pos.y()))!=(common::QP(el_mapa->get_pos_copa().x(),el_mapa->get_pos_copa().y())))
			objetos_mapa[get_posicion(pos.x(),pos.y())]->hay_camino (true);
		if (!maxima_velocidad){
			if (!redimensionado&&seguimiento_harry)
				ui->grafico_mapa->centerOn(muneco_harry->get_posicion_harry().x()*tamano_icono,muneco_harry->get_posicion_harry().y()*tamano_icono);
			usleep((ui->horizontalSlider_2->maximum()*100)-(ui->horizontalSlider_2->value()*100));
			set_texto_estado("Harry se ha movido a la posición ("+QString::number(pos.x())+","+QString::number(pos.y())+")");
			qApp->processEvents();
		}
		if (ejecutar_un_paso)
			un_paso=true;
	}
	qApp->processEvents();
	}
	else if (algoritmo==1){

		ejecucion_A_estrella();

	}
	else if (algoritmo==2){
		while (muneco_harry->puedo_continuar_LRTA()&&ejecutando&&!un_paso){
			camino = new QGraphicsPixmapItem(QPixmap::fromImage(image_camino));
			camino->setOffset(muneco_harry->get_posicion_harry().x()*tamano_icono,muneco_harry->get_posicion_harry().y()*tamano_icono);
			scene->addItem(camino);
			pos = muneco_harry->movimiento_LRTA();
			scene->removeItem(harry_icono);
			harry_icono->setOffset(pos.x()*tamano_icono,pos.y()*tamano_icono);
			scene->addItem(harry_icono);
			if ((common::QP(pos.x(),pos.y()))!=(common::QP(el_mapa->get_pos_copa().x(),el_mapa->get_pos_copa().y())))
				objetos_mapa[get_posicion(pos.x(),pos.y())]->hay_camino (true);
			if (!maxima_velocidad){
				if (!redimensionado&&seguimiento_harry)
					ui->grafico_mapa->centerOn(muneco_harry->get_posicion_harry().x()*tamano_icono,muneco_harry->get_posicion_harry().y()*tamano_icono);
				usleep((ui->horizontalSlider_2->maximum()*100)-(ui->horizontalSlider_2->value()*100));
				set_texto_estado("Harry se ha movido a la posición ("+QString::number(pos.x())+","+QString::number(pos.y())+")");
				qApp->processEvents();
			}
			if (ejecutar_un_paso)
				un_paso=true;
		}
		qApp->processEvents();
	}

	else if (algoritmo==3){
		while (muneco_harry->puedo_continuar_RTA()&&ejecutando&&!un_paso){
			camino = new QGraphicsPixmapItem(QPixmap::fromImage(image_camino));
			camino->setOffset(muneco_harry->get_posicion_harry().x()*tamano_icono,muneco_harry->get_posicion_harry().y()*tamano_icono);
			scene->addItem(camino);
			pos = muneco_harry->movimiento_RTA();
			scene->removeItem(harry_icono);
			harry_icono->setOffset(pos.x()*tamano_icono,pos.y()*tamano_icono);
			scene->addItem(harry_icono);
			if ((common::QP(pos.x(),pos.y()))!=(common::QP(el_mapa->get_pos_copa().x(),el_mapa->get_pos_copa().y())))
				objetos_mapa[get_posicion(pos.x(),pos.y())]->hay_camino (true);
			if (!maxima_velocidad){
				if (!redimensionado&&seguimiento_harry)
					ui->grafico_mapa->centerOn(muneco_harry->get_posicion_harry().x()*tamano_icono,muneco_harry->get_posicion_harry().y()*tamano_icono);
				usleep((ui->horizontalSlider_2->maximum()*100)-(ui->horizontalSlider_2->value()*100));
				set_texto_estado("Harry se ha movido a la posición ("+QString::number(pos.x())+","+QString::number(pos.y())+")");
				qApp->processEvents();
			}
			if (ejecutar_un_paso)
				un_paso=true;
		}
		qApp->processEvents();
	}


	if (ejecutando&&!un_paso){
		if (muneco_harry->get_posicion_harry()==el_mapa->get_pos_copa()){
			set_texto_estado("¡¡¡HARRY HA ENCONTRADO LA COPA!!!");
			QSound::play("sounds/Trompeta_ganador.wav");
			ventana_aviso("¡¡¡FELICIDADES!!!","¡¡¡HARRY HA ENCONTRADO LA COPA!!!");
			finalizado=true;
		}
		else{
			set_texto_estado("Harry no ha encontrado la salida");
			QSound::play("sounds/Trompeta_perdedor.wav");
			ventana_aviso("HARRY HA MUERTO","Harry no ha encontrado la salida y Voldemort lo ha matado :(");
			finalizado=true;
		}
	}
}
	ejecutando=false;
	terminado_ejecucion=true;
}

void VentanaPrincipal::ejecucion_A_estrella (void){

	QStack<QPoint> camino_estrella;
	QStack<QPoint> copia_al_derecho;
	QPoint pos;
	QImage image_camino(RUTA_CAMINO);

	set_texto_estado("Se está calculando el algoritmo A*");
	qApp->processEvents();
	camino_estrella = muneco_harry->movimiento_estrella();
	set_texto_estado("Se ha calculado el algoritmo A*");
	qApp->processEvents();

	pos = camino_estrella.top();

	if(pos!=(common::QP(-1,-1))){
		while (!camino_estrella.empty()){
			copia_al_derecho.push(camino_estrella.pop());
		}
		while (!copia_al_derecho.empty()&&!pausa&&ejecutando){
			pos = copia_al_derecho.pop();
			camino = new QGraphicsPixmapItem(QPixmap::fromImage(image_camino));
			camino->setOffset(muneco_harry->get_posicion_harry().x()*tamano_icono,muneco_harry->get_posicion_harry().y()*tamano_icono);
			scene->addItem(camino);
			muneco_harry->set_posicion_harry(pos);
			scene->removeItem(harry_icono);
			harry_icono->setOffset(pos.x()*tamano_icono,pos.y()*tamano_icono);
			scene->addItem(harry_icono);
			if (!maxima_velocidad){
				if (!redimensionado&&seguimiento_harry)
					ui->grafico_mapa->centerOn(muneco_harry->get_posicion_harry().x()*tamano_icono,muneco_harry->get_posicion_harry().y()*tamano_icono);
				usleep((ui->horizontalSlider_2->maximum()*100)-(ui->horizontalSlider_2->value()*100));
				set_texto_estado("Harry se ha movido a la posición ("+QString::number(pos.x())+","+QString::number(pos.y())+")");
				qApp->processEvents();
			}
			if (ejecutar_un_paso)
				un_paso=true;
		qApp->processEvents();
		}
	}
	qApp->processEvents();

}

void VentanaPrincipal::sliderValueChanged(int value)
{
	valor = QString::number(value);
	ui->porcentaje_seto->setText(valor+"%");
}

void VentanaPrincipal::on_boton_aleatorio_clicked()
{
	gen_lab_setos(ui->horizontalSlider->value());
}

void VentanaPrincipal::set_tam_x (unsigned tamano_x){
	tam_x=tamano_x;
}

void VentanaPrincipal::set_tam_y (unsigned tamano_y){
	tam_y=tamano_y;
}

void VentanaPrincipal::modificar_tamano(){
	set_tam_x(ui->tam_mapa_x->value());
	set_tam_y(ui->tam_mapa_y->value());
	nuevo=false;
}

void VentanaPrincipal::ventana_aviso(QString nombre_ventana, QString texto_ventana){
	ventana_error.setWindowTitle(nombre_ventana);
	ventana_error.setText(texto_ventana);
	ventana_error.exec();
}

void VentanaPrincipal::on_lista_temas_currentIndexChanged(int index)
{
	if (nuevo){
	if (index==0){
		ruta_de_obstaculo=&obstaculo_tierra;
		ruta_de_suelo=&suelo_tierra;
	}
	else if (index==1){
		ruta_de_obstaculo=&obstaculo_fuego;
		ruta_de_suelo=&suelo_fuego;
	}
	else if (index==2){
		ruta_de_obstaculo=&obstaculo_aire;
		ruta_de_suelo=&suelo_aire;
	}
	else if (index==3){
		ruta_de_obstaculo=&obstaculo_agua;
		ruta_de_suelo=&suelo_agua;
	}
	}
	else
		ventana_aviso("ERROR CAMBIANDO ALGORITMOS", "Ha cambiado el valor de los datos mientras una búsqueda se estaba ejecutando. Genere un nuevo laberinto.");
}

void VentanaPrincipal::on_checkBox_clicked()
{
	if (ui->checkBox_3->checkState()){
		ui->checkBox->setChecked(true);
		if(mapa_generado){
			ui->grafico_mapa->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
			redimensionado=true;
		}
	}
	else if(ui->checkBox->checkState()){
		if(mapa_generado){
			ui->grafico_mapa->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
			redimensionado=true;
		}
		ui->checkBox_2->setChecked(false);
		ui->checkBox_2->setCheckable(false);
	}
	else{
		ui->checkBox_2->setCheckable(true);
		if (mapa_generado){
			ui->grafico_mapa->setTransform(QTransform());
			ui->grafico_mapa->centerOn(muneco_harry->get_posicion_harry().x()*tamano_icono,muneco_harry->get_posicion_harry().y()*tamano_icono);
			redimensionado=false;
		}
	}

}

void VentanaPrincipal::on_horizontalSlider_2_valueChanged(int value)
{
	ui->texto_velocidad->setText(QString::number(value));
}

void VentanaPrincipal::on_stop_lab_clicked()
{
	if(nuevo){
		if(mapa_generado){
			ejecutando=false;
			pausa=true;
			ejecutar_un_paso = false;
			muneco_harry->set_posicion_harry_nuevo(posicion_harry_original);
			gen_lab_visual();
		}
	}
	else{
	if (!finalizado)
		ventana_aviso("ERROR CAMBIANDO TAMAÑOS", "Ha cambiado el valor de los datos mientras una búsqueda se estaba ejecutando. Genere un nuevo laberinto.");
	else
		ventana_aviso("OPCION NO VALIDA", "Genere un nuevo laberinto.");
	}
}

void VentanaPrincipal::on_checkBox_2_clicked()
{
	if(ui->checkBox_2->checkState())
		seguimiento_harry=true;
	else
		seguimiento_harry=false;
}

void VentanaPrincipal::on_tam_mapa_x_valueChanged(int arg1)
{
	if(!ejecutando){
		modificar_tamano();
	}
	ui->pos_harry_x->setMaximum(ui->tam_mapa_x->value()-2);
	ui->pos_copa_x->setMaximum(ui->tam_mapa_x->value()-2);
}

void VentanaPrincipal::on_tam_mapa_y_valueChanged(int arg1)
{
	if(!ejecutando){
		modificar_tamano();
	}
	ui->pos_harry_y->setMaximum(ui->tam_mapa_y->value()-2);
	ui->pos_copa_y->setMaximum(ui->tam_mapa_y->value()-2);
}

void VentanaPrincipal::on_lista_algoritmos_currentIndexChanged(int index)
{
	if (index==0){
		algoritmo=0;
	}
	else if (index==1){
		algoritmo=1;
	}
	else if (index==2){
		algoritmo=2;
	}
	else if (index==3){
		algoritmo=3;
	}
}

void VentanaPrincipal::on_checkBox_3_clicked()
{

	if(ui->checkBox_3->checkState()){
		on_checkBox_clicked();
		ui->checkBox_2->setChecked(false);
		ui->checkBox_2->setCheckable(false);
		maxima_velocidad=true;
	}
	else{
		maxima_velocidad=false;
		ui->checkBox->setCheckable(true);
		ui->checkBox_2->setCheckable(true);
	}
}

void VentanaPrincipal::on_pause_lab_clicked()
{
	if(nuevo){
		pausa=true;
		ejecutando=false;
		ejecutar_un_paso = false;
	}
	else{
		if (!finalizado)
			ventana_aviso("ERROR CAMBIANDO TAMAÑOS", "Ha cambiado el valor de los datos mientras una búsqueda se estaba ejecutando. Genere un nuevo laberinto.");
		else
			ventana_aviso("OPCION NO VALIDA", "Genere un nuevo laberinto.");
	}
}

unsigned VentanaPrincipal::get_posicion (unsigned coord_i, unsigned coord_j){
	return coord_i+coord_j*tam_x;
}

void VentanaPrincipal::on_next_lab_clicked()
{
	if (algoritmo==1)
		ventana_aviso("OPCION NO VALIDA", "Esta opción no está disponible para el algoritmo A*.");
	else{
	if (nuevo&&!finalizado){
		un_paso = false;
		ejecutar_un_paso = true;
		ejecutar_algoritmo();
		on_pause_lab_clicked();
	}
	else{
		if (!finalizado)
			ventana_aviso("ERROR CAMBIANDO TAMAÑOS", "Ha cambiado el valor de los datos mientras una búsqueda se estaba ejecutando. Genere un nuevo laberinto.");
		else
			ventana_aviso("OPCION NO VALIDA", "Genere un nuevo laberinto.");
	}
}
}
