/****************************************************************************
** Meta object code from reading C++ file 'demowritemode.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "demowritemode.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'demowritemode.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_netanim__DemoWriteMode[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      24,   23,   23,   23, 0x08,
      41,   23,   23,   23, 0x08,
      62,   23,   23,   23, 0x08,
      73,   23,   23,   23, 0x08,
      89,   23,   23,   23, 0x08,
     102,   23,   23,   23, 0x08,
     113,   23,   23,   23, 0x08,
     133,  126,   23,   23, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_netanim__DemoWriteMode[] = {
    "netanim::DemoWriteMode\0\0saveButtonSlot()\0"
    "addImageButtonSlot()\0textBold()\0"
    "textUnderline()\0textItalic()\0textSize()\0"
    "textColour()\0format\0"
    "currentCharFormatChanged(QTextCharFormat)\0"
};

void netanim::DemoWriteMode::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        DemoWriteMode *_t = static_cast<DemoWriteMode *>(_o);
        switch (_id) {
        case 0: _t->saveButtonSlot(); break;
        case 1: _t->addImageButtonSlot(); break;
        case 2: _t->textBold(); break;
        case 3: _t->textUnderline(); break;
        case 4: _t->textItalic(); break;
        case 5: _t->textSize(); break;
        case 6: _t->textColour(); break;
        case 7: _t->currentCharFormatChanged((*reinterpret_cast< const QTextCharFormat(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData netanim::DemoWriteMode::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject netanim::DemoWriteMode::staticMetaObject = {
    { &Mode::staticMetaObject, qt_meta_stringdata_netanim__DemoWriteMode,
      qt_meta_data_netanim__DemoWriteMode, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &netanim::DemoWriteMode::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *netanim::DemoWriteMode::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *netanim::DemoWriteMode::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_netanim__DemoWriteMode))
        return static_cast<void*>(const_cast< DemoWriteMode*>(this));
    return Mode::qt_metacast(_clname);
}

int netanim::DemoWriteMode::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Mode::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
