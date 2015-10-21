#include "infolaberinto.h"
#include "ui_infolaberinto.h"

infolaberinto::infolaberinto(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::infolaberinto)
{
	ui->setupUi(this);
}

void infolaberinto::set_texto_laberinto(QString text_lab){
//	ui->
}

void infolaberinto::set_texto_harry(QString text_harry){

}

void infolaberinto::set_texto_copa(QString text_copa){

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
