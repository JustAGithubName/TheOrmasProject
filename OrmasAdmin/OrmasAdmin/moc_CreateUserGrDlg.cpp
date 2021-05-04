/****************************************************************************
** Meta object code from reading C++ file 'CreateUserGrDlg.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "CreateUserGrDlg.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CreateUserGrDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CreateUserGrDlg_t {
    QByteArrayData data[11];
    char stringdata0[113];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CreateUserGrDlg_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CreateUserGrDlg_t qt_meta_stringdata_CreateUserGrDlg = {
    {
QT_MOC_LITERAL(0, 0, 15), // "CreateUserGrDlg"
QT_MOC_LITERAL(1, 16, 15), // "CreateUserGroup"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 13), // "EditUserGroup"
QT_MOC_LITERAL(4, 47, 15), // "DeleteUserGroup"
QT_MOC_LITERAL(5, 63, 5), // "Close"
QT_MOC_LITERAL(6, 69, 11), // "OpenUserDlg"
QT_MOC_LITERAL(7, 81, 12), // "OpenGroupDlg"
QT_MOC_LITERAL(8, 94, 5), // "SetID"
QT_MOC_LITERAL(9, 100, 2), // "ID"
QT_MOC_LITERAL(10, 103, 9) // "childName"

    },
    "CreateUserGrDlg\0CreateUserGroup\0\0"
    "EditUserGroup\0DeleteUserGroup\0Close\0"
    "OpenUserDlg\0OpenGroupDlg\0SetID\0ID\0"
    "childName"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CreateUserGrDlg[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x08 /* Private */,
       3,    0,   50,    2, 0x08 /* Private */,
       4,    0,   51,    2, 0x08 /* Private */,
       5,    0,   52,    2, 0x08 /* Private */,
       6,    0,   53,    2, 0x08 /* Private */,
       7,    0,   54,    2, 0x08 /* Private */,
       8,    2,   55,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    9,   10,

       0        // eod
};

void CreateUserGrDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CreateUserGrDlg *_t = static_cast<CreateUserGrDlg *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->CreateUserGroup(); break;
        case 1: _t->EditUserGroup(); break;
        case 2: _t->DeleteUserGroup(); break;
        case 3: _t->Close(); break;
        case 4: _t->OpenUserDlg(); break;
        case 5: _t->OpenGroupDlg(); break;
        case 6: _t->SetID((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObject CreateUserGrDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CreateUserGrDlg.data,
      qt_meta_data_CreateUserGrDlg,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CreateUserGrDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CreateUserGrDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CreateUserGrDlg.stringdata0))
        return static_cast<void*>(const_cast< CreateUserGrDlg*>(this));
    if (!strcmp(_clname, "Ui::CreateUserGroup"))
        return static_cast< Ui::CreateUserGroup*>(const_cast< CreateUserGrDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int CreateUserGrDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
