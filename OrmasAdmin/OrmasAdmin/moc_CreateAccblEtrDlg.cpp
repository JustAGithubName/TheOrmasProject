/****************************************************************************
** Meta object code from reading C++ file 'CreateAccblEtrDlg.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "CreateAccblEtrDlg.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CreateAccblEtrDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CreateAccblEtrDlg_t {
    QByteArrayData data[17];
    char stringdata0[214];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CreateAccblEtrDlg_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CreateAccblEtrDlg_t qt_meta_stringdata_CreateAccblEtrDlg = {
    {
QT_MOC_LITERAL(0, 0, 17), // "CreateAccblEtrDlg"
QT_MOC_LITERAL(1, 18, 25), // "IncrementEntryEditChanged"
QT_MOC_LITERAL(2, 44, 0), // ""
QT_MOC_LITERAL(3, 45, 25), // "DecrementEntryEditChanged"
QT_MOC_LITERAL(4, 71, 11), // "CreateEntry"
QT_MOC_LITERAL(5, 83, 11), // "DeleteEntry"
QT_MOC_LITERAL(6, 95, 5), // "Close"
QT_MOC_LITERAL(7, 101, 11), // "OpenDAccDlg"
QT_MOC_LITERAL(8, 113, 11), // "OpenCAccDlg"
QT_MOC_LITERAL(9, 125, 12), // "OpenDSAccDlg"
QT_MOC_LITERAL(10, 138, 12), // "OpenCSAccDlg"
QT_MOC_LITERAL(11, 151, 13), // "DATextChanged"
QT_MOC_LITERAL(12, 165, 13), // "CATextChanged"
QT_MOC_LITERAL(13, 179, 15), // "TextEditChanged"
QT_MOC_LITERAL(14, 195, 5), // "SetID"
QT_MOC_LITERAL(15, 201, 2), // "ID"
QT_MOC_LITERAL(16, 204, 9) // "childName"

    },
    "CreateAccblEtrDlg\0IncrementEntryEditChanged\0"
    "\0DecrementEntryEditChanged\0CreateEntry\0"
    "DeleteEntry\0Close\0OpenDAccDlg\0OpenCAccDlg\0"
    "OpenDSAccDlg\0OpenCSAccDlg\0DATextChanged\0"
    "CATextChanged\0TextEditChanged\0SetID\0"
    "ID\0childName"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CreateAccblEtrDlg[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   79,    2, 0x06 /* Public */,
       3,    1,   82,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   85,    2, 0x08 /* Private */,
       5,    0,   86,    2, 0x08 /* Private */,
       6,    0,   87,    2, 0x08 /* Private */,
       7,    0,   88,    2, 0x08 /* Private */,
       8,    0,   89,    2, 0x08 /* Private */,
       9,    0,   90,    2, 0x08 /* Private */,
      10,    0,   91,    2, 0x08 /* Private */,
      11,    0,   92,    2, 0x08 /* Private */,
      12,    0,   93,    2, 0x08 /* Private */,
      13,    0,   94,    2, 0x08 /* Private */,
      14,    2,   95,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,

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
    QMetaType::Void, QMetaType::Int, QMetaType::QString,   15,   16,

       0        // eod
};

void CreateAccblEtrDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CreateAccblEtrDlg *_t = static_cast<CreateAccblEtrDlg *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->IncrementEntryEditChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 1: _t->DecrementEntryEditChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 2: _t->CreateEntry(); break;
        case 3: _t->DeleteEntry(); break;
        case 4: _t->Close(); break;
        case 5: _t->OpenDAccDlg(); break;
        case 6: _t->OpenCAccDlg(); break;
        case 7: _t->OpenDSAccDlg(); break;
        case 8: _t->OpenCSAccDlg(); break;
        case 9: _t->DATextChanged(); break;
        case 10: _t->CATextChanged(); break;
        case 11: _t->TextEditChanged(); break;
        case 12: _t->SetID((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CreateAccblEtrDlg::*_t)(double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CreateAccblEtrDlg::IncrementEntryEditChanged)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (CreateAccblEtrDlg::*_t)(double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CreateAccblEtrDlg::DecrementEntryEditChanged)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject CreateAccblEtrDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CreateAccblEtrDlg.data,
      qt_meta_data_CreateAccblEtrDlg,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CreateAccblEtrDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CreateAccblEtrDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CreateAccblEtrDlg.stringdata0))
        return static_cast<void*>(const_cast< CreateAccblEtrDlg*>(this));
    if (!strcmp(_clname, "Ui::CreateAccblEntry"))
        return static_cast< Ui::CreateAccblEntry*>(const_cast< CreateAccblEtrDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int CreateAccblEtrDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void CreateAccblEtrDlg::IncrementEntryEditChanged(double _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CreateAccblEtrDlg::DecrementEntryEditChanged(double _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
