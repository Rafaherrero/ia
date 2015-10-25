/****************************************************************************
** Meta object code from reading C++ file 'ventanaprincipal.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../hp_mdl/ventanaprincipal.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ventanaprincipal.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_VentanaPrincipal_t {
    QByteArrayData data[15];
    char stringdata0[238];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VentanaPrincipal_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VentanaPrincipal_t qt_meta_stringdata_VentanaPrincipal = {
    {
QT_MOC_LITERAL(0, 0, 16), // "VentanaPrincipal"
QT_MOC_LITERAL(1, 17, 24), // "on_boton_generar_clicked"
QT_MOC_LITERAL(2, 42, 0), // ""
QT_MOC_LITERAL(3, 43, 7), // "gen_lab"
QT_MOC_LITERAL(4, 51, 14), // "gen_lab_visual"
QT_MOC_LITERAL(5, 66, 13), // "gen_lab_setos"
QT_MOC_LITERAL(6, 80, 10), // "porcentaje"
QT_MOC_LITERAL(7, 91, 19), // "on_play_lab_clicked"
QT_MOC_LITERAL(8, 111, 18), // "sliderValueChanged"
QT_MOC_LITERAL(9, 130, 5), // "value"
QT_MOC_LITERAL(10, 136, 26), // "on_boton_aleatorio_clicked"
QT_MOC_LITERAL(11, 163, 26), // "on_boton_modificar_clicked"
QT_MOC_LITERAL(12, 190, 6), // "prueba"
QT_MOC_LITERAL(13, 197, 34), // "on_lista_temas_currentIndexCh..."
QT_MOC_LITERAL(14, 232, 5) // "index"

    },
    "VentanaPrincipal\0on_boton_generar_clicked\0"
    "\0gen_lab\0gen_lab_visual\0gen_lab_setos\0"
    "porcentaje\0on_play_lab_clicked\0"
    "sliderValueChanged\0value\0"
    "on_boton_aleatorio_clicked\0"
    "on_boton_modificar_clicked\0prueba\0"
    "on_lista_temas_currentIndexChanged\0"
    "index"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VentanaPrincipal[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x08 /* Private */,
       3,    0,   65,    2, 0x08 /* Private */,
       4,    0,   66,    2, 0x08 /* Private */,
       5,    1,   67,    2, 0x08 /* Private */,
       7,    0,   70,    2, 0x08 /* Private */,
       8,    1,   71,    2, 0x08 /* Private */,
      10,    0,   74,    2, 0x08 /* Private */,
      11,    0,   75,    2, 0x08 /* Private */,
      12,    0,   76,    2, 0x08 /* Private */,
      13,    1,   77,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::UInt,    6,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   14,

       0        // eod
};

void VentanaPrincipal::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        VentanaPrincipal *_t = static_cast<VentanaPrincipal *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_boton_generar_clicked(); break;
        case 1: _t->gen_lab(); break;
        case 2: _t->gen_lab_visual(); break;
        case 3: _t->gen_lab_setos((*reinterpret_cast< uint(*)>(_a[1]))); break;
        case 4: _t->on_play_lab_clicked(); break;
        case 5: _t->sliderValueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->on_boton_aleatorio_clicked(); break;
        case 7: _t->on_boton_modificar_clicked(); break;
        case 8: _t->prueba(); break;
        case 9: _t->on_lista_temas_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject VentanaPrincipal::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_VentanaPrincipal.data,
      qt_meta_data_VentanaPrincipal,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *VentanaPrincipal::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VentanaPrincipal::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_VentanaPrincipal.stringdata0))
        return static_cast<void*>(const_cast< VentanaPrincipal*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int VentanaPrincipal::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
