/****************************************************************************
** Meta object code from reading C++ file 'ProgressDlg.h'
**
** Created: Sun Dec 23 21:59:15 2012
**      by: The Qt Meta Object Compiler version 59 (Qt 4.1.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "source/gui/ProgressDlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ProgressDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.1.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_CProgressDlg[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets

       0        // eod
};

static const char qt_meta_stringdata_CProgressDlg[] = {
    "CProgressDlg\0"
};

const QMetaObject CProgressDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CProgressDlg,
      qt_meta_data_CProgressDlg, 0 }
};

const QMetaObject *CProgressDlg::metaObject() const
{
    return &staticMetaObject;
}

void *CProgressDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CProgressDlg))
	return static_cast<void*>(const_cast<CProgressDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int CProgressDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
