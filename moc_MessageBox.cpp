/****************************************************************************
** Meta object code from reading C++ file 'MessageBox.h'
**
** Created: Sun Dec 23 21:59:13 2012
**      by: The Qt Meta Object Compiler version 59 (Qt 4.1.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "source/gui/MessageBox.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MessageBox.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.1.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_CMessageBox[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x0a,
      23,   12,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CMessageBox[] = {
    "CMessageBox\0\0OnBtnOK()\0OnBtnESC()\0"
};

const QMetaObject CMessageBox::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CMessageBox,
      qt_meta_data_CMessageBox, 0 }
};

const QMetaObject *CMessageBox::metaObject() const
{
    return &staticMetaObject;
}

void *CMessageBox::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CMessageBox))
	return static_cast<void*>(const_cast<CMessageBox*>(this));
    return QDialog::qt_metacast(_clname);
}

int CMessageBox::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: OnBtnOK(); break;
        case 1: OnBtnESC(); break;
        }
        _id -= 2;
    }
    return _id;
}
