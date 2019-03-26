/****************************************************************************
** Meta object code from reading C++ file 'SONG.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/robottest/include/robottest/SONG.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SONG.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SONG_t {
    QByteArrayData data[17];
    char stringdata0[189];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SONG_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SONG_t qt_meta_stringdata_SONG = {
    {
QT_MOC_LITERAL(0, 0, 4), // "SONG"
QT_MOC_LITERAL(1, 5, 12), // "slotTellback"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 11), // "slotTellPos"
QT_MOC_LITERAL(4, 31, 13), // "slotSendAlive"
QT_MOC_LITERAL(5, 45, 13), // "slotconnected"
QT_MOC_LITERAL(6, 59, 16), // "slotdisconnected"
QT_MOC_LITERAL(7, 76, 18), // "slotdetectionStart"
QT_MOC_LITERAL(8, 95, 13), // "slotgameStart"
QT_MOC_LITERAL(9, 109, 16), // "slotgetTruecolor"
QT_MOC_LITERAL(10, 126, 9), // "TeamColor"
QT_MOC_LITERAL(11, 136, 5), // "color"
QT_MOC_LITERAL(12, 142, 12), // "slotgameOver"
QT_MOC_LITERAL(13, 155, 16), // "slotstopMovement"
QT_MOC_LITERAL(14, 172, 12), // "slotabValues"
QT_MOC_LITERAL(15, 185, 1), // "a"
QT_MOC_LITERAL(16, 187, 1) // "b"

    },
    "SONG\0slotTellback\0\0slotTellPos\0"
    "slotSendAlive\0slotconnected\0"
    "slotdisconnected\0slotdetectionStart\0"
    "slotgameStart\0slotgetTruecolor\0TeamColor\0"
    "color\0slotgameOver\0slotstopMovement\0"
    "slotabValues\0a\0b"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SONG[] = {

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
       1,    0,   69,    2, 0x0a /* Public */,
       3,    0,   70,    2, 0x0a /* Public */,
       4,    0,   71,    2, 0x0a /* Public */,
       5,    0,   72,    2, 0x0a /* Public */,
       6,    0,   73,    2, 0x0a /* Public */,
       7,    0,   74,    2, 0x0a /* Public */,
       8,    0,   75,    2, 0x0a /* Public */,
       9,    1,   76,    2, 0x0a /* Public */,
      12,    0,   79,    2, 0x0a /* Public */,
      13,    0,   80,    2, 0x0a /* Public */,
      14,    2,   81,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Int,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double, QMetaType::Double,   15,   16,

       0        // eod
};

void SONG::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SONG *_t = static_cast<SONG *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { int _r = _t->slotTellback();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 1: _t->slotTellPos(); break;
        case 2: _t->slotSendAlive(); break;
        case 3: _t->slotconnected(); break;
        case 4: _t->slotdisconnected(); break;
        case 5: _t->slotdetectionStart(); break;
        case 6: _t->slotgameStart(); break;
        case 7: _t->slotgetTruecolor((*reinterpret_cast< TeamColor(*)>(_a[1]))); break;
        case 8: _t->slotgameOver(); break;
        case 9: _t->slotstopMovement(); break;
        case 10: _t->slotabValues((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObject SONG::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_SONG.data,
      qt_meta_data_SONG,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *SONG::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SONG::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_SONG.stringdata0))
        return static_cast<void*>(const_cast< SONG*>(this));
    return QObject::qt_metacast(_clname);
}

int SONG::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
