#ifndef INFOLABERINTO_H
#define INFOLABERINTO_H

#include <QDialog>
#include "common.h"

namespace Ui {
class infolaberinto;
}

class infolaberinto : public QDialog
{
	Q_OBJECT

public:
	explicit infolaberinto(QWidget *parent = 0);
	~infolaberinto();
	unsigned get_tam_x();
	unsigned get_tam_y();
	unsigned get_pos_copa_x();
	unsigned get_pos_copa_y();
	unsigned get_pos_harry_x();
	unsigned get_pos_harry_y();
public slots:

	void on_boton_ok_accepted();

private:
	bool prueba =false;
	Ui::infolaberinto *ui;

signals:
	void ok_clicked(void);

};

#endif // INFOLABERINTO_H
