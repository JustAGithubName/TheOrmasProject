/****************************************************************************
** Meta object code from reading C++ file 'CreatePrExDlg.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "CreatePrExDlg.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CreatePrExDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CreatePrExDlg_t {
    QByteArrayData data[15];
    char stringdata0[172];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CreatePrExDlg_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CreatePrExDlg_t qt_meta_stringdata_CreatePrExDlg = {
    {
QT_MOC_LITERAL(0, 0, 13), // "CreatePrExDlg"
QT_MOC_LITERAL(1, 14, 20), // "CreatePriceExtension"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 18), // "EditPriceExtension"
QT_MOC_LITERAL(4, 55, 20), // "DeletePriceExtension"
QT_MOC_LITERAL(5, 76, 5), // "Close"
QT_MOC_LITERAL(6, 82, 10), // "OpenPrdDlg"
QT_MOC_LITERAL(7, 93, 10), // "OpenBrhDlg"
QT_MOC_LITERAL(8, 104, 10), // "OpenLcnDlg"
QT_MOC_LITERAL(9, 115, 10), // "OpenCltDlg"
QT_MOC_LITERAL(10, 126, 10), // "OpenEmpDlg"
QT_MOC_LITERAL(11, 137, 15), // "TextEditChanged"
QT_MOC_LITERAL(12, 153, 5), // "SetID"
QT_MOC_LITERAL(13, 159, 2), // "ID"
QT_MOC_LITERAL(14, 162, 9) // "childName"

    },
    "CreatePrExDlg\0CreatePriceExtension\0\0"
    "EditPriceExtension\0DeletePriceExtension\0"
    "Close\0OpenPrdDlg\0OpenBrhDlg\0OpenLcnDlg\0"
    "OpenCltDlg\0OpenEmpDlg\0TextEditChanged\0"
    "SetID\0ID\0childName"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CreatePrExDlg[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x08 /* Private */,
       3,    0,   70,    2, 0x08 /* Private */,
       4,    0,   71,    2, 0x08 /* Private */,
       5,    0,   72,    2, 0x08 /* Private */,
       6,    0,   73,    2, 0x08 /* Private */,
       7,    0,   74,    2, 0x08 /* Private */,
       8,    0,   75,    2, 0x08 /* Private */,
       9,    0,   76,    2, 0x08 /* Private */,
      10,    0,   77,    2, 0x08 /* Private */,
      11,    0,   78,    2, 0x08 /* Private */,
      12,    2,   79,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,   13,   14,

       0        // eod
};

void CreatePrExDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CreatePrExDlg *_t = static_cast<CreatePrExDlg *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->CreatePriceExtension(); break;
        case 1: _t->EditPriceExtension(); break;
        case 2: _t->DeletePriceExtension(); break;
        case 3: _t->Close(); break;
        case 4: _t->OpenPrdDlg(); break;
        case 5: _t->OpenBrhDlg(); break;
        case 6: _t->OpenLcnDlg(); break;
        case 7: _t->OpenCltDlg(); break;
        case 8: _t->OpenEmpDlg(); break;
        case 9: _t->TextEditChanged(); break;
        case 10: _t->SetID((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObject CreatePrExDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CreatePrExDlg.data,
      qt_meta_data_CreatePrExDlg,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CreatePrExDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CreatePrExDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CreatePrExDlg.stringdata0))
        return static_cast<void*>(const_cast< CreatePrExDlg*>(this));
    if (!strcmp(_clname, "Ui::CreatePriceExtension"))
        return static_cast< Ui::CreatePriceExtension*>(const_cast< CreatePrExDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int CreatePrExDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
