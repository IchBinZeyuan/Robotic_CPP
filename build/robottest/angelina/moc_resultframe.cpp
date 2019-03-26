/****************************************************************************
** Meta object code from reading C++ file 'resultframe.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/robottest/angelina/resultframe.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'resultframe.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ResultFrame_t {
    QByteArrayData data[18];
    char stringdata0[230];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ResultFrame_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ResultFrame_t qt_meta_stringdata_ResultFrame = {
    {
QT_MOC_LITERAL(0, 0, 11), // "ResultFrame"
QT_MOC_LITERAL(1, 12, 12), // "readyToStart"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 4), // "done"
QT_MOC_LITERAL(4, 31, 9), // "stopTimer"
QT_MOC_LITERAL(5, 41, 11), // "resumeTimer"
QT_MOC_LITERAL(6, 53, 9), // "addPoints"
QT_MOC_LITERAL(7, 63, 6), // "points"
QT_MOC_LITERAL(8, 70, 13), // "slotSendStart"
QT_MOC_LITERAL(9, 84, 14), // "slotDisqualify"
QT_MOC_LITERAL(10, 99, 23), // "confirmDisqualification"
QT_MOC_LITERAL(11, 123, 16), // "resumeOperations"
QT_MOC_LITERAL(12, 140, 14), // "stopOperations"
QT_MOC_LITERAL(13, 155, 17), // "updateElapsedTime"
QT_MOC_LITERAL(14, 173, 17), // "unsigned long int"
QT_MOC_LITERAL(15, 191, 12), // "sendGameOver"
QT_MOC_LITERAL(16, 204, 8), // "slotRead"
QT_MOC_LITERAL(17, 213, 16) // "slotDisconnected"

    },
    "ResultFrame\0readyToStart\0\0done\0stopTimer\0"
    "resumeTimer\0addPoints\0points\0slotSendStart\0"
    "slotDisqualify\0confirmDisqualification\0"
    "resumeOperations\0stopOperations\0"
    "updateElapsedTime\0unsigned long int\0"
    "sendGameOver\0slotRead\0slotDisconnected"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ResultFrame[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x06 /* Public */,
       3,    0,   85,    2, 0x06 /* Public */,
       4,    0,   86,    2, 0x06 /* Public */,
       5,    0,   87,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   88,    2, 0x0a /* Public */,
       8,    0,   91,    2, 0x0a /* Public */,
       9,    0,   92,    2, 0x0a /* Public */,
      10,    0,   93,    2, 0x0a /* Public */,
      11,    0,   94,    2, 0x0a /* Public */,
      12,    0,   95,    2, 0x0a /* Public */,
      13,    1,   96,    2, 0x0a /* Public */,
      15,    0,   99,    2, 0x0a /* Public */,
      16,    0,  100,    2, 0x08 /* Private */,
      17,    0,  101,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 14,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ResultFrame::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ResultFrame *_t = static_cast<ResultFrame *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->readyToStart(); break;
        case 1: _t->done(); break;
        case 2: _t->stopTimer(); break;
        case 3: _t->resumeTimer(); break;
        case 4: _t->addPoints((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->slotSendStart(); break;
        case 6: _t->slotDisqualify(); break;
        case 7: _t->confirmDisqualification(); break;
        case 8: _t->resumeOperations(); break;
        case 9: _t->stopOperations(); break;
        case 10: _t->updateElapsedTime((*reinterpret_cast< unsigned long int(*)>(_a[1]))); break;
        case 11: _t->sendGameOver(); break;
        case 12: _t->slotRead(); break;
        case 13: _t->slotDisconnected(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ResultFrame::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ResultFrame::readyToStart)) {
                *result = 0;
            }
        }
        {
            typedef void (ResultFrame::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ResultFrame::done)) {
                *result = 1;
            }
        }
        {
            typedef void (ResultFrame::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ResultFrame::stopTimer)) {
                *result = 2;
            }
        }
        {
            typedef void (ResultFrame::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ResultFrame::resumeTimer)) {
                *result = 3;
            }
        }
    }
}

const QMetaObject ResultFrame::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_ResultFrame.data,
      qt_meta_data_ResultFrame,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ResultFrame::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ResultFrame::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ResultFrame.stringdata0))
        return static_cast<void*>(const_cast< ResultFrame*>(this));
    return QFrame::qt_metacast(_clname);
}

int ResultFrame::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void ResultFrame::readyToStart()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void ResultFrame::done()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void ResultFrame::stopTimer()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void ResultFrame::resumeTimer()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
