/****************************************************************************
** Meta object code from reading C++ file 'CreateNcCoeffDlg.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "CreateNcCoeffDlg.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CreateNcCoeffDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CreateNcCoeffDlg_t {
    QByteArrayData data[10];
    char stringdata0[127];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CreateNcCoeffDlg_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CreateNcCoeffDlg_t qt_meta_stringdata_CreateNcCoeffDlg = {
    {
QT_MOC_LITERAL(0, 0, 16), // "CreateNcCoeffDlg"
QT_MOC_LITERAL(1, 17, 24), // "CreateNetCostCoefficient"
QT_MOC_LITERAL(2, 42, 0), // ""
QT_MOC_LITERAL(3, 43, 22), // "EditNetCostCoefficient"
QT_MOC_LITERAL(4, 66, 24), // "DeleteNetCostCoefficient"
QT_MOC_LITERAL(5, 91, 5), // "Close"
QT_MOC_LITERAL(6, 97, 10), // "OpenPrdDlg"
QT_MOC_LITERAL(7, 108, 5), // "SetID"
QT_MOC_LITERAL(8, 114, 2), // "ID"
QT_MOC_LITERAL(9, 117, 9) // "childName"

    },
    "CreateNcCoeffDlg\0CreateNetCostCoefficient\0"
    "\0EditNetCostCoefficient\0"
    "DeleteNetCostCoefficient\0Close\0"
    "OpenPrdDlg\0SetID\0ID\0childName"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CreateNcCoeffDlg[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x08 /* Private */,
       3,    0,   45,    2, 0x08 /* Private */,
       4,    0,   46,    2, 0x08 /* Private */,
       5,    0,   47,    2, 0x08 /* Private */,
       6,    0,   48,    2, 0x08 /* Private */,
       7,    2,   49,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    8,    9,

       0        // eod
};

void CreateNcCoeffDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CreateNcCoeffDlg *_t = static_cast<CreateNcCoeffDlg *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->CreateNetCostCoefficient(); break;
        case 1: _t->EditNetCostCoefficient(); break;
        case 2: _t->DeleteNetCostCoefficient(); break;
        case 3: _t->Close(); break;
        case 4: _t->OpenPrdDlg(); break;
        case 5: _t->SetID((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObject CreateNcCoeffDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CreateNcCoeffDlg.data,
      qt_meta_data_CreateNcCoeffDlg,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CreateNcCoeffDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CreateNcCoeffDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CreateNcCoeffDlg.stringdata0))
        return static_cast<void*>(const_cast< CreateNcCoeffDlg*>(this));
    if (!strcmp(_clname, "Ui::CreateNetCostCoefficient"))
        return static_cast< Ui::CreateNetCostCoefficient*>(const_cast< CreateNcCoeffDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int CreateNcCoeffDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
