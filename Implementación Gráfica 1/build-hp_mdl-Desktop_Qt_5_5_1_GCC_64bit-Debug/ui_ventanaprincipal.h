/********************************************************************************
** Form generated from reading UI file 'ventanaprincipal.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VENTANAPRINCIPAL_H
#define UI_VENTANAPRINCIPAL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VentanaPrincipal
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QGraphicsView *grafico_mapa;
    QLabel *estado_harry;
    QHBoxLayout *horizontalLayout;
    QPushButton *boton_generar;
    QPushButton *boton_aleatorio;
    QPushButton *play_lab;
    QLabel *label;
    QHBoxLayout *horizontalLayout_2;
    QSlider *horizontalSlider;
    QLabel *porcentaje_seto;
    QPushButton *boton_modificar;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QComboBox *lista_temas;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *VentanaPrincipal)
    {
        if (VentanaPrincipal->objectName().isEmpty())
            VentanaPrincipal->setObjectName(QStringLiteral("VentanaPrincipal"));
        VentanaPrincipal->resize(471, 540);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(VentanaPrincipal->sizePolicy().hasHeightForWidth());
        VentanaPrincipal->setSizePolicy(sizePolicy);
        VentanaPrincipal->setMaximumSize(QSize(100000, 100000));
        centralWidget = new QWidget(VentanaPrincipal);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setEnabled(true);
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(50);
        sizePolicy1.setVerticalStretch(50);
        sizePolicy1.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy1);
        centralWidget->setAutoFillBackground(true);
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        grafico_mapa = new QGraphicsView(centralWidget);
        grafico_mapa->setObjectName(QStringLiteral("grafico_mapa"));
        QSizePolicy sizePolicy2(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(grafico_mapa->sizePolicy().hasHeightForWidth());
        grafico_mapa->setSizePolicy(sizePolicy2);
        grafico_mapa->setMaximumSize(QSize(10000, 10000));
        grafico_mapa->setSizeIncrement(QSize(0, 0));
        grafico_mapa->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        grafico_mapa->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        grafico_mapa->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);

        verticalLayout->addWidget(grafico_mapa);

        estado_harry = new QLabel(centralWidget);
        estado_harry->setObjectName(QStringLiteral("estado_harry"));

        verticalLayout->addWidget(estado_harry);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, 0, -1, -1);
        boton_generar = new QPushButton(centralWidget);
        boton_generar->setObjectName(QStringLiteral("boton_generar"));
        QSizePolicy sizePolicy3(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(boton_generar->sizePolicy().hasHeightForWidth());
        boton_generar->setSizePolicy(sizePolicy3);

        horizontalLayout->addWidget(boton_generar);

        boton_aleatorio = new QPushButton(centralWidget);
        boton_aleatorio->setObjectName(QStringLiteral("boton_aleatorio"));
        sizePolicy3.setHeightForWidth(boton_aleatorio->sizePolicy().hasHeightForWidth());
        boton_aleatorio->setSizePolicy(sizePolicy3);

        horizontalLayout->addWidget(boton_aleatorio);

        play_lab = new QPushButton(centralWidget);
        play_lab->setObjectName(QStringLiteral("play_lab"));
        sizePolicy3.setHeightForWidth(play_lab->sizePolicy().hasHeightForWidth());
        play_lab->setSizePolicy(sizePolicy3);

        horizontalLayout->addWidget(play_lab);


        verticalLayout->addLayout(horizontalLayout);

        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, 0, -1, -1);
        horizontalSlider = new QSlider(centralWidget);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setMaximum(90);
        horizontalSlider->setSingleStep(5);
        horizontalSlider->setOrientation(Qt::Horizontal);
        horizontalSlider->setTickPosition(QSlider::TicksBelow);
        horizontalSlider->setTickInterval(5);

        horizontalLayout_2->addWidget(horizontalSlider);

        porcentaje_seto = new QLabel(centralWidget);
        porcentaje_seto->setObjectName(QStringLiteral("porcentaje_seto"));
        QSizePolicy sizePolicy4(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(porcentaje_seto->sizePolicy().hasHeightForWidth());
        porcentaje_seto->setSizePolicy(sizePolicy4);
        porcentaje_seto->setMinimumSize(QSize(30, 0));
        porcentaje_seto->setLayoutDirection(Qt::LeftToRight);
        porcentaje_seto->setTextFormat(Qt::AutoText);
        porcentaje_seto->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(porcentaje_seto);


        verticalLayout->addLayout(horizontalLayout_2);

        boton_modificar = new QPushButton(centralWidget);
        boton_modificar->setObjectName(QStringLiteral("boton_modificar"));

        verticalLayout->addWidget(boton_modificar);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(-1, 0, -1, -1);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        QSizePolicy sizePolicy5(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy5);

        horizontalLayout_3->addWidget(label_2);

        lista_temas = new QComboBox(centralWidget);
        lista_temas->setObjectName(QStringLiteral("lista_temas"));
        sizePolicy3.setHeightForWidth(lista_temas->sizePolicy().hasHeightForWidth());
        lista_temas->setSizePolicy(sizePolicy3);
        lista_temas->setInsertPolicy(QComboBox::InsertAlphabetically);

        horizontalLayout_3->addWidget(lista_temas);


        verticalLayout->addLayout(horizontalLayout_3);

        VentanaPrincipal->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(VentanaPrincipal);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        VentanaPrincipal->setStatusBar(statusBar);

        retranslateUi(VentanaPrincipal);

        QMetaObject::connectSlotsByName(VentanaPrincipal);
    } // setupUi

    void retranslateUi(QMainWindow *VentanaPrincipal)
    {
        VentanaPrincipal->setWindowTitle(QApplication::translate("VentanaPrincipal", "Harry Potter y los Monstruos del Laberinto (v1.0.0.0.1)", 0));
        estado_harry->setText(QApplication::translate("VentanaPrincipal", "TextLabel", 0));
        boton_generar->setText(QApplication::translate("VentanaPrincipal", "Generar aleatorio", 0));
        boton_aleatorio->setText(QApplication::translate("VentanaPrincipal", "Aleatorio obst\303\241culos", 0));
        play_lab->setText(QApplication::translate("VentanaPrincipal", "Ejecutar b\303\272squeda", 0));
        label->setText(QApplication::translate("VentanaPrincipal", "Ajustar porcentaje de obst\303\241culos en laberinto aleatorio", 0));
        porcentaje_seto->setText(QApplication::translate("VentanaPrincipal", "0%", 0));
        boton_modificar->setText(QApplication::translate("VentanaPrincipal", "Modificar par\303\241metros", 0));
        label_2->setText(QApplication::translate("VentanaPrincipal", "Elige un tema:", 0));
    } // retranslateUi

};

namespace Ui {
    class VentanaPrincipal: public Ui_VentanaPrincipal {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VENTANAPRINCIPAL_H
