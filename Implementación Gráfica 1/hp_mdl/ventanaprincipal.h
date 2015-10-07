#ifndef VENTANAPRINCIPAL_H
#define VENTANAPRINCIPAL_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QtCore>
#include <QtGui>
#include <QImage>
#include <QGraphicsPixmapItem>
#include <QFileInfo>

namespace Ui {
class VentanaPrincipal;
}

class VentanaPrincipal : public QMainWindow
{
	Q_OBJECT

public:
	explicit VentanaPrincipal(QWidget *parent = 0);
	~VentanaPrincipal();

private:
	Ui::VentanaPrincipal *ui;
	QGraphicsScene *scene;
	QGraphicsEllipseItem *ellipse;
};

#endif // VENTANAPRINCIPAL_H
