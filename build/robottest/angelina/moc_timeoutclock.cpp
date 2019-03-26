/****************************************************************************
** Meta object code from reading C++ file 'timeoutclock.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/robottest/angelina/timeoutclock.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'timeoutclock.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TimeoutClock_t {
    QByteArrayData data[6];
    char stringdata0[42];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TimeoutClock_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TimeoutClock_t qt_meta_stringdata_TimeoutClock = {
    {
QT_MOC_LITERAL(0, 0, 12), // "TimeoutClock"
QT_MOC_LITERAL(1, 13, 4), // "ring"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 7), // "newTime"
QT_MOC_LITERAL(4, 27, 5), // "value"
QT_MOC_LITERAL(5, 33, 8) // "slotTick"

    },
    "TimeoutClock\0ring\0\0newTime\0value\0"
    "slotTick"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TimeoutClock[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x06 /* Public */,
       3,    1,   30,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   33,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    4,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void TimeoutClock::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TimeoutClock *_t = static_cast<TimeoutClock *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ring(); break;
        case 1: _t->newTime((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->slotTick(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (TimeoutClock::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TimeoutClock::ring)) {
                *result = 0;
            }
        }
        {
            typedef void (TimeoutClock::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TimeoutClock::newTime)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject TimeoutClock::staticMetaObject = {
    { &QTimer::staticMetaObject, qt_meta_stringdata_TimeoutClock.data,
      qt_meta_data_TimeoutClock,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TimeoutClock::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TimeoutClock::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TimeoutClock.stringdata0))
        return static_cast<void*>(const_cast< TimeoutClock*>(this));
    return QTimer::qt_metacast(_clname);
}

int TimeoutClock::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTimer::qt_metacall(_c, _id, _a);
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
void TimeoutClock::ring()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void TimeoutClock::newTime(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
