/****************************************************************************
** Meta object code from reading C++ file 'sourceanalyzergui.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "src/sourceanalyzergui.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sourceanalyzergui.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SourceAnalyzerGUI_t {
    QByteArrayData data[11];
    char stringdata[225];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_SourceAnalyzerGUI_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_SourceAnalyzerGUI_t qt_meta_stringdata_SourceAnalyzerGUI = {
    {
QT_MOC_LITERAL(0, 0, 17),
QT_MOC_LITERAL(1, 18, 22),
QT_MOC_LITERAL(2, 41, 0),
QT_MOC_LITERAL(3, 42, 5),
QT_MOC_LITERAL(4, 48, 21),
QT_MOC_LITERAL(5, 70, 28),
QT_MOC_LITERAL(6, 99, 30),
QT_MOC_LITERAL(7, 130, 29),
QT_MOC_LITERAL(8, 160, 28),
QT_MOC_LITERAL(9, 189, 22),
QT_MOC_LITERAL(10, 212, 11)
    },
    "SourceAnalyzerGUI\0on_source_list_pressed\0"
    "\0index\0on_pushButton_clicked\0"
    "on_start_file_button_clicked\0"
    "on_start_device_button_clicked\0"
    "on_output_device_list_pressed\0"
    "on_input_device_list_pressed\0"
    "on_stop_button_clicked\0errorString\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SourceAnalyzerGUI[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x08,
       4,    0,   57,    2, 0x08,
       5,    0,   58,    2, 0x08,
       6,    0,   59,    2, 0x08,
       7,    1,   60,    2, 0x08,
       8,    1,   63,    2, 0x08,
       9,    0,   66,    2, 0x08,
      10,    1,   67,    2, 0x08,

 // slots: parameters
    QMetaType::Void, QMetaType::QModelIndex,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex,    3,
    QMetaType::Void, QMetaType::QModelIndex,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,

       0        // eod
};

void SourceAnalyzerGUI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SourceAnalyzerGUI *_t = static_cast<SourceAnalyzerGUI *>(_o);
        switch (_id) {
        case 0: _t->on_source_list_pressed((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 1: _t->on_pushButton_clicked(); break;
        case 2: _t->on_start_file_button_clicked(); break;
        case 3: _t->on_start_device_button_clicked(); break;
        case 4: _t->on_output_device_list_pressed((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 5: _t->on_input_device_list_pressed((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 6: _t->on_stop_button_clicked(); break;
        case 7: _t->errorString((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject SourceAnalyzerGUI::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_SourceAnalyzerGUI.data,
      qt_meta_data_SourceAnalyzerGUI,  qt_static_metacall, 0, 0}
};


const QMetaObject *SourceAnalyzerGUI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SourceAnalyzerGUI::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SourceAnalyzerGUI.stringdata))
        return static_cast<void*>(const_cast< SourceAnalyzerGUI*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int SourceAnalyzerGUI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
