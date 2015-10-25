/********************************************************************************
** Form generated from reading UI file 'infolaberinto.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INFOLABERINTO_H
#define UI_INFOLABERINTO_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_infolaberinto
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout;
    QLabel *texto_tamano;
    QHBoxLayout *horizontalLayout;
    QLabel *texto_tamano_2;
    QSpinBox *tam_mapa_x;
    QLabel *texto_tamano_3;
    QSpinBox *tam_mapa_y;
    QVBoxLayout *verticalLayout_3;
    QLabel *texto_tamano_8;
    QHBoxLayout *horizontalLayout_4;
    QLabel *texto_tamano_9;
    QSpinBox *pos_harry_x;
    QLabel *texto_tamano_7;
    QSpinBox *pos_harry_y;
    QVBoxLayout *verticalLayout_2;
    QLabel *texto_tamano_4;
    QHBoxLayout *horizontalLayout_2;
    QLabel *texto_tamano_6;
    QSpinBox *pos_copa_x;
    QLabel *texto_tamano_5;
    QSpinBox *pos_copa_y;
    QDialogButtonBox *boton_ok;

    void setupUi(QDialog *infolaberinto)
    {
        if (infolaberinto->objectName().isEmpty())
            infolaberinto->setObjectName(QStringLiteral("infolaberinto"));
        infolaberinto->resize(355, 253);
        infolaberinto->setMinimumSize(QSize(355, 253));
        infolaberinto->setMaximumSize(QSize(355, 253));
        gridLayout = new QGridLayout(infolaberinto);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        texto_tamano = new QLabel(infolaberinto);
        texto_tamano->setObjectName(QStringLiteral("texto_tamano"));

        verticalLayout->addWidget(texto_tamano);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        texto_tamano_2 = new QLabel(infolaberinto);
        texto_tamano_2->setObjectName(QStringLiteral("texto_tamano_2"));

        horizontalLayout->addWidget(texto_tamano_2);

        tam_mapa_x = new QSpinBox(infolaberinto);
        tam_mapa_x->setObjectName(QStringLiteral("tam_mapa_x"));
        tam_mapa_x->setMinimum(6);
        tam_mapa_x->setMaximum(150);

        horizontalLayout->addWidget(tam_mapa_x);

        texto_tamano_3 = new QLabel(infolaberinto);
        texto_tamano_3->setObjectName(QStringLiteral("texto_tamano_3"));

        horizontalLayout->addWidget(texto_tamano_3);

        tam_mapa_y = new QSpinBox(infolaberinto);
        tam_mapa_y->setObjectName(QStringLiteral("tam_mapa_y"));
        tam_mapa_y->setMinimum(6);
        tam_mapa_y->setMaximum(150);

        horizontalLayout->addWidget(tam_mapa_y);


        verticalLayout->addLayout(horizontalLayout);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(-1, 10, -1, -1);
        texto_tamano_8 = new QLabel(infolaberinto);
        texto_tamano_8->setObjectName(QStringLiteral("texto_tamano_8"));

        verticalLayout_3->addWidget(texto_tamano_8);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(-1, 10, -1, -1);
        texto_tamano_9 = new QLabel(infolaberinto);
        texto_tamano_9->setObjectName(QStringLiteral("texto_tamano_9"));

        horizontalLayout_4->addWidget(texto_tamano_9);

        pos_harry_x = new QSpinBox(infolaberinto);
        pos_harry_x->setObjectName(QStringLiteral("pos_harry_x"));
        pos_harry_x->setMinimum(1);
        pos_harry_x->setMaximum(4);
        pos_harry_x->setValue(1);

        horizontalLayout_4->addWidget(pos_harry_x);

        texto_tamano_7 = new QLabel(infolaberinto);
        texto_tamano_7->setObjectName(QStringLiteral("texto_tamano_7"));

        horizontalLayout_4->addWidget(texto_tamano_7);

        pos_harry_y = new QSpinBox(infolaberinto);
        pos_harry_y->setObjectName(QStringLiteral("pos_harry_y"));
        pos_harry_y->setMinimum(1);
        pos_harry_y->setMaximum(4);
        pos_harry_y->setValue(1);

        horizontalLayout_4->addWidget(pos_harry_y);


        verticalLayout_3->addLayout(horizontalLayout_4);


        verticalLayout->addLayout(verticalLayout_3);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        texto_tamano_4 = new QLabel(infolaberinto);
        texto_tamano_4->setObjectName(QStringLiteral("texto_tamano_4"));

        verticalLayout_2->addWidget(texto_tamano_4);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, 10, -1, -1);
        texto_tamano_6 = new QLabel(infolaberinto);
        texto_tamano_6->setObjectName(QStringLiteral("texto_tamano_6"));

        horizontalLayout_2->addWidget(texto_tamano_6);

        pos_copa_x = new QSpinBox(infolaberinto);
        pos_copa_x->setObjectName(QStringLiteral("pos_copa_x"));
        pos_copa_x->setMinimum(1);
        pos_copa_x->setMaximum(4);
        pos_copa_x->setValue(1);

        horizontalLayout_2->addWidget(pos_copa_x);

        texto_tamano_5 = new QLabel(infolaberinto);
        texto_tamano_5->setObjectName(QStringLiteral("texto_tamano_5"));

        horizontalLayout_2->addWidget(texto_tamano_5);

        pos_copa_y = new QSpinBox(infolaberinto);
        pos_copa_y->setObjectName(QStringLiteral("pos_copa_y"));
        pos_copa_y->setMinimum(1);
        pos_copa_y->setMaximum(4);
        pos_copa_y->setValue(1);

        horizontalLayout_2->addWidget(pos_copa_y);


        verticalLayout_2->addLayout(horizontalLayout_2);


        verticalLayout->addLayout(verticalLayout_2);


        verticalLayout_4->addLayout(verticalLayout);

        boton_ok = new QDialogButtonBox(infolaberinto);
        boton_ok->setObjectName(QStringLiteral("boton_ok"));
        boton_ok->setOrientation(Qt::Horizontal);
        boton_ok->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout_4->addWidget(boton_ok);


        gridLayout->addLayout(verticalLayout_4, 0, 0, 1, 1);


        retranslateUi(infolaberinto);
        QObject::connect(boton_ok, SIGNAL(accepted()), infolaberinto, SLOT(accept()));
        QObject::connect(boton_ok, SIGNAL(rejected()), infolaberinto, SLOT(reject()));

        QMetaObject::connectSlotsByName(infolaberinto);
    } // setupUi

    void retranslateUi(QDialog *infolaberinto)
    {
        infolaberinto->setWindowTitle(QApplication::translate("infolaberinto", "Datos laberinto", 0));
        texto_tamano->setText(QApplication::translate("infolaberinto", "Ingrese el tama\303\261o del mapa", 0));
        texto_tamano_2->setText(QApplication::translate("infolaberinto", "X:", 0));
        texto_tamano_3->setText(QApplication::translate("infolaberinto", "Y:", 0));
        texto_tamano_8->setText(QApplication::translate("infolaberinto", "Ingrese la posici\303\263n de Harry Potter", 0));
        texto_tamano_9->setText(QApplication::translate("infolaberinto", "X:", 0));
        texto_tamano_7->setText(QApplication::translate("infolaberinto", "Y:", 0));
        texto_tamano_4->setText(QApplication::translate("infolaberinto", "Ingrese la posici\303\263n de la Copa de los Tres Magos", 0));
        texto_tamano_6->setText(QApplication::translate("infolaberinto", "X:", 0));
        texto_tamano_5->setText(QApplication::translate("infolaberinto", "Y:", 0));
    } // retranslateUi

};

namespace Ui {
    class infolaberinto: public Ui_infolaberinto {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INFOLABERINTO_H
