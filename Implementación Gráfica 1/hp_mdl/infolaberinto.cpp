#include "infolaberinto.h"
#include "ui_infolaberinto.h"

infolaberinto::infolaberinto(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::infolaberinto)
{
	ui->setupUi(this);

}

infolaberinto::~infolaberinto()
{
	delete ui;
}

unsigned infolaberinto::get_tam_x(){
	return ui->tam_mapa_x->value();
}

unsigned infolaberinto::get_tam_y(){
	return ui->tam_mapa_y->value();
}

unsigned infolaberinto::get_pos_copa_x(){
	return ui->pos_copa_x->value();
}

unsigned infolaberinto::get_pos_copa_y(){
	return ui->pos_copa_y->value();
}

unsigned infolaberinto::get_pos_harry_x(){
	return ui->pos_harry_x->value();
}

unsigned infolaberinto::get_pos_harry_y(){
	return ui->pos_harry_y->value();
}

void infolaberinto::on_boton_ok_accepted()
{
 emit ok_clicked();
}

//void infolaberinto::ok_clicked(){
//	emit ok_clicked();
//}

void infolaberinto::on_tam_mapa_x_valueChanged(int arg1)
{
	ui->pos_harry_x->setMaximum(get_tam_x()-2);
	ui->pos_copa_x->setMaximum(get_tam_x()-2);
}

void infolaberinto::on_tam_mapa_y_valueChanged(int arg1)
{
	ui->pos_harry_y->setMaximum(get_tam_y()-2);
	ui->pos_copa_y->setMaximum(get_tam_y()-2);
}
