/****************************************************************************
** Meta object code from reading C++ file 'MainWindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.0.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "MainWindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MainWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.0.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[28];
    char stringdata[615];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_MainWindow_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10),
QT_MOC_LITERAL(1, 11, 25),
QT_MOC_LITERAL(2, 37, 0),
QT_MOC_LITERAL(3, 38, 23),
QT_MOC_LITERAL(4, 62, 24),
QT_MOC_LITERAL(5, 87, 4),
QT_MOC_LITERAL(6, 92, 27),
QT_MOC_LITERAL(7, 120, 30),
QT_MOC_LITERAL(8, 151, 37),
QT_MOC_LITERAL(9, 189, 30),
QT_MOC_LITERAL(10, 220, 37),
QT_MOC_LITERAL(11, 258, 21),
QT_MOC_LITERAL(12, 280, 21),
QT_MOC_LITERAL(13, 302, 25),
QT_MOC_LITERAL(14, 328, 27),
QT_MOC_LITERAL(15, 356, 29),
QT_MOC_LITERAL(16, 386, 24),
QT_MOC_LITERAL(17, 411, 27),
QT_MOC_LITERAL(18, 439, 34),
QT_MOC_LITERAL(19, 474, 9),
QT_MOC_LITERAL(20, 484, 26),
QT_MOC_LITERAL(21, 511, 28),
QT_MOC_LITERAL(22, 540, 24),
QT_MOC_LITERAL(23, 565, 17),
QT_MOC_LITERAL(24, 583, 8),
QT_MOC_LITERAL(25, 592, 10),
QT_MOC_LITERAL(26, 603, 5),
QT_MOC_LITERAL(27, 609, 4)
    },
    "MainWindow\0onOpenDeviceButtonClicked\0"
    "\0onColorWheelColorChange\0"
    "onMotorControlGotNewLine\0line\0"
    "onSendCommandsButtonClicked\0"
    "onM1StepClockwiseButtonClicked\0"
    "onM1StepCounterclockwiseButtonClicked\0"
    "onM2StepClockwiseButtonClicked\0"
    "onM2StepCounterclockwiseButtonClicked\0"
    "onReleaseMotor1Button\0onReleaseMotor2Button\0"
    "actionColorImageTriggered\0"
    "actionColorStripesTriggered\0"
    "actionLineWorldColorTriggered\0"
    "actionLineWorldTriggered\0"
    "actionPerfectImageTriggered\0"
    "onMotorControlCommandQueueDequeued\0"
    "queueSize\0onFlushCommandsButtonClick\0"
    "onToggleShutterButtonClicked\0"
    "computeGoldenRatioColors\0QVector<QColor*>*\0"
    "startHue\0saturation\0value\0size\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  109,    2, 0x08,
       3,    1,  110,    2, 0x08,
       4,    1,  113,    2, 0x08,
       6,    0,  116,    2, 0x08,
       7,    0,  117,    2, 0x08,
       8,    0,  118,    2, 0x08,
       9,    0,  119,    2, 0x08,
      10,    0,  120,    2, 0x08,
      11,    0,  121,    2, 0x08,
      12,    0,  122,    2, 0x08,
      13,    0,  123,    2, 0x08,
      14,    0,  124,    2, 0x08,
      15,    0,  125,    2, 0x08,
      16,    0,  126,    2, 0x08,
      17,    0,  127,    2, 0x08,
      18,    1,  128,    2, 0x08,
      20,    0,  131,    2, 0x08,
      21,    0,  132,    2, 0x08,
      22,    4,  133,    2, 0x08,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QColor,    2,
    QMetaType::Void, QMetaType::QString,    5,
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
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   19,
    QMetaType::Void,
    QMetaType::Void,
    0x80000000 | 23, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Int,   24,   25,   26,   27,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->onOpenDeviceButtonClicked(); break;
        case 1: _t->onColorWheelColorChange((*reinterpret_cast< QColor(*)>(_a[1]))); break;
        case 2: _t->onMotorControlGotNewLine((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->onSendCommandsButtonClicked(); break;
        case 4: _t->onM1StepClockwiseButtonClicked(); break;
        case 5: _t->onM1StepCounterclockwiseButtonClicked(); break;
        case 6: _t->onM2StepClockwiseButtonClicked(); break;
        case 7: _t->onM2StepCounterclockwiseButtonClicked(); break;
        case 8: _t->onReleaseMotor1Button(); break;
        case 9: _t->onReleaseMotor2Button(); break;
        case 10: _t->actionColorImageTriggered(); break;
        case 11: _t->actionColorStripesTriggered(); break;
        case 12: _t->actionLineWorldColorTriggered(); break;
        case 13: _t->actionLineWorldTriggered(); break;
        case 14: _t->actionPerfectImageTriggered(); break;
        case 15: _t->onMotorControlCommandQueueDequeued((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: _t->onFlushCommandsButtonClick(); break;
        case 17: _t->onToggleShutterButtonClicked(); break;
        case 18: { QVector<QColor*>* _r = _t->computeGoldenRatioColors((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])));
            if (_a[0]) *reinterpret_cast< QVector<QColor*>**>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, 0, 0}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 19)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 19;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
