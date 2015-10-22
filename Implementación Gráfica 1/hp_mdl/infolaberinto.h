#ifndef INFOLABERINTO_H
#define INFOLABERINTO_H

#include <QDialog>

namespace Ui {
class infolaberinto;
}

class infolaberinto : public QDialog
{
	Q_OBJECT

public:
	explicit infolaberinto(QWidget *parent = 0);
	~infolaberinto();
	bool on_buttonBox_accepted();
	unsigned get_tam_x();
	unsigned get_tam_y();
private slots:

private:
	bool prueba =false;
	Ui::infolaberinto *ui;
};

#endif // INFOLABERINTO_H
