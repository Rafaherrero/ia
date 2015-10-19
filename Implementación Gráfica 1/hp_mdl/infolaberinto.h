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
	void set_texto_laberinto(QString text_lab);
	void set_texto_copa(QString text_copa);
	void set_texto_harry(QString text_harry);
private:
	Ui::infolaberinto *ui;
};

#endif // INFOLABERINTO_H
