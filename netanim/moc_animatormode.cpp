/****************************************************************************
** Meta object code from reading C++ file 'animatormode.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "animatormode.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'animatormode.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_netanim__AnimatorMode[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      30,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      23,   22,   22,   22, 0x08,
      48,   22,   22,   22, 0x08,
      65,   22,   22,   22, 0x08,
      83,   22,   22,   22, 0x08,
     102,   22,   22,   22, 0x08,
     119,   22,   22,   22, 0x08,
     135,   22,   22,   22, 0x08,
     171,  165,   22,   22, 0x08,
     195,   22,   22,   22, 0x08,
     216,   22,   22,   22, 0x08,
     240,  165,   22,   22, 0x08,
     265,  165,   22,   22, 0x08,
     293,   22,   22,   22, 0x08,
     319,   22,   22,   22, 0x08,
     339,   22,   22,   22, 0x08,
     356,   22,   22,   22, 0x08,
     376,   22,   22,   22, 0x08,
     391,   22,   22,   22, 0x08,
     408,   22,   22,   22, 0x08,
     434,   22,   22,   22, 0x08,
     456,   22,   22,   22, 0x08,
     484,   22,   22,   22, 0x08,
     497,   22,   22,   22, 0x08,
     511,   22,   22,   22, 0x08,
     531,   22,   22,   22, 0x08,
     557,   22,   22,   22, 0x08,
     592,   22,   22,   22, 0x08,
     613,   22,   22,   22, 0x08,
     631,   22,   22,   22, 0x08,
     642,   22,   22,   22, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_netanim__AnimatorMode[] = {
    "netanim::AnimatorMode\0\0clickTraceFileOpenSlot()\0"
    "reloadFileSlot()\0clickZoomInSlot()\0"
    "clickZoomOutSlot()\0clickResetSlot()\0"
    "clickPlaySlot()\0simulationSliderPressedSlot()\0"
    "value\0updateTimelineSlot(int)\0"
    "updateTimelineSlot()\0updateRateTimeoutSlot()\0"
    "updateGridLinesSlot(int)\0"
    "updateNodeSizeSlot(QString)\0"
    "updateUpdateRateSlot(int)\0showGridLinesSlot()\0"
    "showNodeIdSlot()\0showNodeSysIdSlot()\0"
    "showMetaSlot()\0showPacketSlot()\0"
    "showWirelessCirclesSlot()\0"
    "showPacketStatsSlot()\0showNodePositionStatsSlot()\0"
    "showIpSlot()\0showMacSlot()\0"
    "showRoutePathSlot()\0showBatteryCapacitySlot()\0"
    "buttonAnimationGroupFinishedSlot()\0"
    "showPropertiesSlot()\0pauseAtTimeSlot()\0"
    "stepSlot()\0enableMousePositionSlot()\0"
};

void netanim::AnimatorMode::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        AnimatorMode *_t = static_cast<AnimatorMode *>(_o);
        switch (_id) {
        case 0: _t->clickTraceFileOpenSlot(); break;
        case 1: _t->reloadFileSlot(); break;
        case 2: _t->clickZoomInSlot(); break;
        case 3: _t->clickZoomOutSlot(); break;
        case 4: _t->clickResetSlot(); break;
        case 5: _t->clickPlaySlot(); break;
        case 6: _t->simulationSliderPressedSlot(); break;
        case 7: _t->updateTimelineSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->updateTimelineSlot(); break;
        case 9: _t->updateRateTimeoutSlot(); break;
        case 10: _t->updateGridLinesSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->updateNodeSizeSlot((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 12: _t->updateUpdateRateSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->showGridLinesSlot(); break;
        case 14: _t->showNodeIdSlot(); break;
        case 15: _t->showNodeSysIdSlot(); break;
        case 16: _t->showMetaSlot(); break;
        case 17: _t->showPacketSlot(); break;
        case 18: _t->showWirelessCirclesSlot(); break;
        case 19: _t->showPacketStatsSlot(); break;
        case 20: _t->showNodePositionStatsSlot(); break;
        case 21: _t->showIpSlot(); break;
        case 22: _t->showMacSlot(); break;
        case 23: _t->showRoutePathSlot(); break;
        case 24: _t->showBatteryCapacitySlot(); break;
        case 25: _t->buttonAnimationGroupFinishedSlot(); break;
        case 26: _t->showPropertiesSlot(); break;
        case 27: _t->pauseAtTimeSlot(); break;
        case 28: _t->stepSlot(); break;
        case 29: _t->enableMousePositionSlot(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData netanim::AnimatorMode::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject netanim::AnimatorMode::staticMetaObject = {
    { &Mode::staticMetaObject, qt_meta_stringdata_netanim__AnimatorMode,
      qt_meta_data_netanim__AnimatorMode, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &netanim::AnimatorMode::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *netanim::AnimatorMode::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *netanim::AnimatorMode::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_netanim__AnimatorMode))
        return static_cast<void*>(const_cast< AnimatorMode*>(this));
    return Mode::qt_metacast(_clname);
}

int netanim::AnimatorMode::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Mode::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 30)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 30;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
