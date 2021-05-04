/****************************************************************************
** Meta object code from reading C++ file 'GenerateWrRepDlg.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "GenerateWrRepDlg.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GenerateWrRepDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_GenerateWrRep_t {
    QByteArrayData data[5];
    char stringdata0[48];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GenerateWrRep_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GenerateWrRep_t qt_meta_stringdata_GenerateWrRep = {
    {
QT_MOC_LITERAL(0, 0, 13), // "GenerateWrRep"
QT_MOC_LITERAL(1, 14, 17), // "CloseCreatedForms"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 8), // "Generate"
QT_MOC_LITERAL(4, 42, 5) // "Close"

    },
    "GenerateWrRep\0CloseCreatedForms\0\0"
    "Generate\0Close"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GenerateWrRep[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   30,    2, 0x08 /* Private */,
       4,    0,   31,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void GenerateWrRep::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GenerateWrRep *_t = static_cast<GenerateWrRep *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->CloseCreatedForms(); break;
        case 1: _t->Generate(); break;
        case 2: _t->Close(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (GenerateWrRep::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GenerateWrRep::CloseCreatedForms)) {
                *result = 0;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject GenerateWrRep::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_GenerateWrRep.data,
      qt_meta_data_GenerateWrRep,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *GenerateWrRep::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GenerateWrRep::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_GenerateWrRep.stringdata0))
        return static_cast<void*>(const_cast< GenerateWrRep*>(this));
    if (!strcmp(_clname, "Ui::GenerateWarehouseReport"))
        return static_cast< Ui::GenerateWarehouseReport*>(const_cast< GenerateWrRep*>(this));
    return QDialog::qt_metacast(_clname);
}

int GenerateWrRep::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void GenerateWrRep::CloseCreatedForms()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
