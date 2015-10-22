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

bool infolaberinto::on_buttonBox_accepted()
{
	prueba = true;
	if (prueba)
		return true;
	else
		return false;
}

unsigned infolaberinto::get_tam_x(){
	return ui->tam_mapa_x->value();
}

unsigned infolaberinto::get_tam_y(){
	return ui->tam_mapa_y->value();
}
