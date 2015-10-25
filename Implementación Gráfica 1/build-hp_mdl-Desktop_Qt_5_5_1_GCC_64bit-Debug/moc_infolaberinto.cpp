/****************************************************************************
** Meta object code from reading C++ file 'infolaberinto.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../hp_mdl/infolaberinto.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'infolaberinto.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_infolaberinto_t {
    QByteArrayData data[7];
    char stringdata0[106];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_infolaberinto_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_infolaberinto_t qt_meta_stringdata_infolaberinto = {
    {
QT_MOC_LITERAL(0, 0, 13), // "infolaberinto"
QT_MOC_LITERAL(1, 14, 10), // "ok_clicked"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 20), // "on_boton_ok_accepted"
QT_MOC_LITERAL(4, 47, 26), // "on_tam_mapa_x_valueChanged"
QT_MOC_LITERAL(5, 74, 4), // "arg1"
QT_MOC_LITERAL(6, 79, 26) // "on_tam_mapa_y_valueChanged"

    },
    "infolaberinto\0ok_clicked\0\0"
    "on_boton_ok_accepted\0on_tam_mapa_x_valueChanged\0"
    "arg1\0on_tam_mapa_y_valueChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_infolaberinto[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   35,    2, 0x0a /* Public */,
       4,    1,   36,    2, 0x08 /* Private */,
       6,    1,   39,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    5,

       0        // eod
};

void infolaberinto::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        infolaberinto *_t = static_cast<infolaberinto *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ok_clicked(); break;
        case 1: _t->on_boton_ok_accepted(); break;
        case 2: _t->on_tam_mapa_x_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->on_tam_mapa_y_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (infolaberinto::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&infolaberinto::ok_clicked)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject infolaberinto::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_infolaberinto.data,
      qt_meta_data_infolaberinto,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *infolaberinto::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *infolaberinto::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_infolaberinto.stringdata0))
        return static_cast<void*>(const_cast< infolaberinto*>(this));
    return QDialog::qt_metacast(_clname);
}

int infolaberinto::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void infolaberinto::ok_clicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
