/****************************************************************************
** Meta object code from reading C++ file 'dialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../EX10-gerinne-qt/dialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Dialog_t {
    QByteArrayData data[15];
    char stringdata0[416];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Dialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Dialog_t qt_meta_stringdata_Dialog = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Dialog"
QT_MOC_LITERAL(1, 7, 23), // "on_pushButtonIC_clicked"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 23), // "on_pushButtonBC_clicked"
QT_MOC_LITERAL(4, 56, 24), // "on_pushButtonMAT_clicked"
QT_MOC_LITERAL(5, 81, 24), // "on_pushButtonRUN_clicked"
QT_MOC_LITERAL(6, 106, 24), // "on_pushButtonALL_clicked"
QT_MOC_LITERAL(7, 131, 14), // "RUN_NewtonStep"
QT_MOC_LITERAL(8, 146, 29), // "on_pushButtonICChange_clicked"
QT_MOC_LITERAL(9, 176, 29), // "on_pushButtonBCChange_clicked"
QT_MOC_LITERAL(10, 206, 36), // "on_pushButtonDischargeChange_..."
QT_MOC_LITERAL(11, 243, 46), // "on_pushButtonFrictionLawExpon..."
QT_MOC_LITERAL(12, 290, 46), // "on_pushButtonFrictionCoeffici..."
QT_MOC_LITERAL(13, 337, 35), // "on_pushButtonBedSlopeChange_c..."
QT_MOC_LITERAL(14, 373, 42) // "on_pushButtonNewtonToleranceC..."

    },
    "Dialog\0on_pushButtonIC_clicked\0\0"
    "on_pushButtonBC_clicked\0"
    "on_pushButtonMAT_clicked\0"
    "on_pushButtonRUN_clicked\0"
    "on_pushButtonALL_clicked\0RUN_NewtonStep\0"
    "on_pushButtonICChange_clicked\0"
    "on_pushButtonBCChange_clicked\0"
    "on_pushButtonDischargeChange_clicked\0"
    "on_pushButtonFrictionLawExponentChange_clicked\0"
    "on_pushButtonFrictionCoefficientChange_clicked\0"
    "on_pushButtonBedSlopeChange_clicked\0"
    "on_pushButtonNewtonToleranceChange_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Dialog[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x08 /* Private */,
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
      14,    0,   91,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Double,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Dialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Dialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_pushButtonIC_clicked(); break;
        case 1: _t->on_pushButtonBC_clicked(); break;
        case 2: _t->on_pushButtonMAT_clicked(); break;
        case 3: _t->on_pushButtonRUN_clicked(); break;
        case 4: _t->on_pushButtonALL_clicked(); break;
        case 5: { double _r = _t->RUN_NewtonStep();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = std::move(_r); }  break;
        case 6: _t->on_pushButtonICChange_clicked(); break;
        case 7: _t->on_pushButtonBCChange_clicked(); break;
        case 8: _t->on_pushButtonDischargeChange_clicked(); break;
        case 9: _t->on_pushButtonFrictionLawExponentChange_clicked(); break;
        case 10: _t->on_pushButtonFrictionCoefficientChange_clicked(); break;
        case 11: _t->on_pushButtonBedSlopeChange_clicked(); break;
        case 12: _t->on_pushButtonNewtonToleranceChange_clicked(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Dialog::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_Dialog.data,
    qt_meta_data_Dialog,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Dialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Dialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Dialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int Dialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
