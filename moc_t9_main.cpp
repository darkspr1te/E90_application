/****************************************************************************
** Meta object code from reading C++ file 't9_main.h'
**
** Created: Sun Dec 23 21:59:18 2012
**      by: The Qt Meta Object Compiler version 59 (Qt 4.1.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "source/t9/t9_main.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 't9_main.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.1.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_CT9Window[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets

       0        // eod
};

static const char qt_meta_stringdata_CT9Window[] = {
    "CT9Window\0"
};

const QMetaObject CT9Window::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CT9Window,
      qt_meta_data_CT9Window, 0 }
};

const QMetaObject *CT9Window::metaObject() const
{
    return &staticMetaObject;
}

void *CT9Window::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CT9Window))
	return static_cast<void*>(const_cast<CT9Window*>(this));
    return QDialog::qt_metacast(_clname);
}

int CT9Window::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
