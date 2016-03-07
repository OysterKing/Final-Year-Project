/****************************************************************************
** Meta object code from reading C++ file 'drawmode.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "drawmode.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'drawmode.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_netanim__DrawMode[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      19,   18,   18,   18, 0x08,
      39,   18,   18,   18, 0x08,
      61,   18,   18,   18, 0x08,
      83,   18,   18,   18, 0x08,
     100,   18,   18,   18, 0x08,
     120,   18,   18,   18, 0x08,
     136,   18,   18,   18, 0x08,
     155,   18,   18,   18, 0x08,
     180,   18,   18,   18, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_netanim__DrawMode[] = {
    "netanim::DrawMode\0\0addHostButtonSlot()\0"
    "addRouterButtonSlot()\0addSwitchButtonSlot()\0"
    "saveButtonSlot()\0addLinkButtonSlot()\0"
    "runButtonSlot()\0deleteButtonSlot()\0"
    "runBlankModeButtonSlot()\0"
    "runDhcpModeButtonSlot()\0"
};

void netanim::DrawMode::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        DrawMode *_t = static_cast<DrawMode *>(_o);
        switch (_id) {
        case 0: _t->addHostButtonSlot(); break;
        case 1: _t->addRouterButtonSlot(); break;
        case 2: _t->addSwitchButtonSlot(); break;
        case 3: _t->saveButtonSlot(); break;
        case 4: _t->addLinkButtonSlot(); break;
        case 5: _t->runButtonSlot(); break;
        case 6: _t->deleteButtonSlot(); break;
        case 7: _t->runBlankModeButtonSlot(); break;
        case 8: _t->runDhcpModeButtonSlot(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData netanim::DrawMode::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject netanim::DrawMode::staticMetaObject = {
    { &Mode::staticMetaObject, qt_meta_stringdata_netanim__DrawMode,
      qt_meta_data_netanim__DrawMode, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &netanim::DrawMode::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *netanim::DrawMode::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *netanim::DrawMode::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_netanim__DrawMode))
        return static_cast<void*>(const_cast< DrawMode*>(this));
    return Mode::qt_metacast(_clname);
}

int netanim::DrawMode::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Mode::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
