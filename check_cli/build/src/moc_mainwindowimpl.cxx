/****************************************************************************
** Meta object code from reading C++ file 'mainwindowimpl.h'
**
** Created: Mon Apr 1 12:56:36 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/mainwindowimpl.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindowimpl.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindowImpl[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x0a,
      30,   15,   15,   15, 0x08,
      47,   15,   15,   15, 0x08,
      57,   15,   15,   15, 0x08,
      70,   15,   15,   15, 0x08,
      84,   15,   15,   15, 0x08,
     101,   15,   15,   15, 0x08,
     113,   15,   15,   15, 0x08,
     127,   15,   15,   15, 0x08,
     141,   15,   15,   15, 0x08,
     160,   15,   15,   15, 0x08,
     169,   15,   15,   15, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindowImpl[] = {
    "MainWindowImpl\0\0toCheckFace()\0"
    "takingPictures()\0checkIn()\0searchInfo()\0"
    "readShowImg()\0takingPicAgain()\0"
    "submitPic()\0clearUIFace()\0toAddNewEmp()\0"
    "toCheckRightFace()\0signIn()\0cancelSignIn()\0"
};

void MainWindowImpl::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindowImpl *_t = static_cast<MainWindowImpl *>(_o);
        switch (_id) {
        case 0: _t->toCheckFace(); break;
        case 1: _t->takingPictures(); break;
        case 2: _t->checkIn(); break;
        case 3: _t->searchInfo(); break;
        case 4: _t->readShowImg(); break;
        case 5: _t->takingPicAgain(); break;
        case 6: _t->submitPic(); break;
        case 7: _t->clearUIFace(); break;
        case 8: _t->toAddNewEmp(); break;
        case 9: _t->toCheckRightFace(); break;
        case 10: _t->signIn(); break;
        case 11: _t->cancelSignIn(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData MainWindowImpl::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWindowImpl::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindowImpl,
      qt_meta_data_MainWindowImpl, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindowImpl::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindowImpl::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindowImpl::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindowImpl))
        return static_cast<void*>(const_cast< MainWindowImpl*>(this));
    if (!strcmp(_clname, "Ui::MainWindow"))
        return static_cast< Ui::MainWindow*>(const_cast< MainWindowImpl*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindowImpl::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
