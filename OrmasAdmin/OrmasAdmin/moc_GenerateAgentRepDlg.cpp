/****************************************************************************
** Meta object code from reading C++ file 'GenerateAgentRepDlg.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "GenerateAgentRepDlg.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GenerateAgentRepDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_GenerateAgentRep_t {
    QByteArrayData data[9];
    char stringdata0[81];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GenerateAgentRep_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GenerateAgentRep_t qt_meta_stringdata_GenerateAgentRep = {
    {
QT_MOC_LITERAL(0, 0, 16), // "GenerateAgentRep"
QT_MOC_LITERAL(1, 17, 17), // "CloseCreatedForms"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 8), // "Generate"
QT_MOC_LITERAL(4, 45, 5), // "Close"
QT_MOC_LITERAL(5, 51, 10), // "OpenEmpDlg"
QT_MOC_LITERAL(6, 62, 5), // "SetID"
QT_MOC_LITERAL(7, 68, 2), // "ID"
QT_MOC_LITERAL(8, 71, 9) // "childName"

    },
    "GenerateAgentRep\0CloseCreatedForms\0\0"
    "Generate\0Close\0OpenEmpDlg\0SetID\0ID\0"
    "childName"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GenerateAgentRep[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   40,    2, 0x08 /* Private */,
       4,    0,   41,    2, 0x08 /* Private */,
       5,    0,   42,    2, 0x08 /* Private */,
       6,    2,   43,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    7,    8,

       0        // eod
};

void GenerateAgentRep::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GenerateAgentRep *_t = static_cast<GenerateAgentRep *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->CloseCreatedForms(); break;
        case 1: _t->Generate(); break;
        case 2: _t->Close(); break;
        case 3: _t->OpenEmpDlg(); break;
        case 4: _t->SetID((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (GenerateAgentRep::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GenerateAgentRep::CloseCreatedForms)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject GenerateAgentRep::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_GenerateAgentRep.data,
      qt_meta_data_GenerateAgentRep,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *GenerateAgentRep::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GenerateAgentRep::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_GenerateAgentRep.stringdata0))
        return static_cast<void*>(const_cast< GenerateAgentRep*>(this));
    if (!strcmp(_clname, "Ui::GenerateAgentReport"))
        return static_cast< Ui::GenerateAgentReport*>(const_cast< GenerateAgentRep*>(this));
    return QDialog::qt_metacast(_clname);
}

int GenerateAgentRep::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void GenerateAgentRep::CloseCreatedForms()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
