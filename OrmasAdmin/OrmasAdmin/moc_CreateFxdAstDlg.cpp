/****************************************************************************
** Meta object code from reading C++ file 'CreateFxdAstDlg.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "CreateFxdAstDlg.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CreateFxdAstDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CreateFxdAstDlg_t {
    QByteArrayData data[17];
    char stringdata0[206];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CreateFxdAstDlg_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CreateFxdAstDlg_t qt_meta_stringdata_CreateFxdAstDlg = {
    {
QT_MOC_LITERAL(0, 0, 15), // "CreateFxdAstDlg"
QT_MOC_LITERAL(1, 16, 17), // "CloseCreatedForms"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 17), // "CreateFixedAssets"
QT_MOC_LITERAL(4, 53, 15), // "EditFixedAssets"
QT_MOC_LITERAL(5, 69, 17), // "DeleteFixedAssets"
QT_MOC_LITERAL(6, 87, 5), // "Close"
QT_MOC_LITERAL(7, 93, 10), // "OpenStsDlg"
QT_MOC_LITERAL(8, 104, 10), // "OpenAccDlg"
QT_MOC_LITERAL(9, 115, 10), // "OpenPurDlg"
QT_MOC_LITERAL(10, 126, 10), // "OpenActDlg"
QT_MOC_LITERAL(11, 137, 11), // "OpenSpecDlg"
QT_MOC_LITERAL(12, 149, 15), // "TextEditChanged"
QT_MOC_LITERAL(13, 165, 21), // "CalculateMonthChanged"
QT_MOC_LITERAL(14, 187, 5), // "SetID"
QT_MOC_LITERAL(15, 193, 2), // "ID"
QT_MOC_LITERAL(16, 196, 9) // "childName"

    },
    "CreateFxdAstDlg\0CloseCreatedForms\0\0"
    "CreateFixedAssets\0EditFixedAssets\0"
    "DeleteFixedAssets\0Close\0OpenStsDlg\0"
    "OpenAccDlg\0OpenPurDlg\0OpenActDlg\0"
    "OpenSpecDlg\0TextEditChanged\0"
    "CalculateMonthChanged\0SetID\0ID\0childName"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CreateFxdAstDlg[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   80,    2, 0x08 /* Private */,
       4,    0,   81,    2, 0x08 /* Private */,
       5,    0,   82,    2, 0x08 /* Private */,
       6,    0,   83,    2, 0x08 /* Private */,
       7,    0,   84,    2, 0x08 /* Private */,
       8,    0,   85,    2, 0x08 /* Private */,
       9,    0,   86,    2, 0x08 /* Private */,
      10,    0,   87,    2, 0x08 /* Private */,
      11,    0,   88,    2, 0x08 /* Private */,
      12,    0,   89,    2, 0x08 /* Private */,
      13,    0,   90,    2, 0x08 /* Private */,
      14,    2,   91,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

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
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,   15,   16,

       0        // eod
};

void CreateFxdAstDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CreateFxdAstDlg *_t = static_cast<CreateFxdAstDlg *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->CloseCreatedForms(); break;
        case 1: _t->CreateFixedAssets(); break;
        case 2: _t->EditFixedAssets(); break;
        case 3: _t->DeleteFixedAssets(); break;
        case 4: _t->Close(); break;
        case 5: _t->OpenStsDlg(); break;
        case 6: _t->OpenAccDlg(); break;
        case 7: _t->OpenPurDlg(); break;
        case 8: _t->OpenActDlg(); break;
        case 9: _t->OpenSpecDlg(); break;
        case 10: _t->TextEditChanged(); break;
        case 11: _t->CalculateMonthChanged(); break;
        case 12: _t->SetID((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CreateFxdAstDlg::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CreateFxdAstDlg::CloseCreatedForms)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject CreateFxdAstDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CreateFxdAstDlg.data,
      qt_meta_data_CreateFxdAstDlg,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CreateFxdAstDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CreateFxdAstDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CreateFxdAstDlg.stringdata0))
        return static_cast<void*>(const_cast< CreateFxdAstDlg*>(this));
    if (!strcmp(_clname, "Ui::CreateFxdAst"))
        return static_cast< Ui::CreateFxdAst*>(const_cast< CreateFxdAstDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int CreateFxdAstDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void CreateFxdAstDlg::CloseCreatedForms()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
