/****************************************************************************
** Meta object code from reading C++ file 'MainWindow.h'
**
** Created: Sun Dec 23 21:59:12 2012
**      by: The Qt Meta Object Compiler version 59 (Qt 4.1.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "source/gui/MainWindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MainWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.1.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_CMainWindow[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CMainWindow[] = {
    "CMainWindow\0\0OnTimer()\0"
};

const QMetaObject CMainWindow::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CMainWindow,
      qt_meta_data_CMainWindow, 0 }
};

const QMetaObject *CMainWindow::metaObject() const
{
    return &staticMetaObject;
}

void *CMainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CMainWindow))
	return static_cast<void*>(const_cast<CMainWindow*>(this));
    return QWidget::qt_metacast(_clname);
}

int CMainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: OnTimer(); break;
        }
        _id -= 1;
    }
    return _id;
}
static const uint qt_meta_data_CVerify[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets

       0        // eod
};

static const char qt_meta_stringdata_CVerify[] = {
    "CVerify\0"
};

const QMetaObject CVerify::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CVerify,
      qt_meta_data_CVerify, 0 }
};

const QMetaObject *CVerify::metaObject() const
{
    return &staticMetaObject;
}

void *CVerify::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CVerify))
	return static_cast<void*>(const_cast<CVerify*>(this));
    return QDialog::qt_metacast(_clname);
}

int CVerify::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_CBellDlg[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets

       0        // eod
};

static const char qt_meta_stringdata_CBellDlg[] = {
    "CBellDlg\0"
};

const QMetaObject CBellDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CBellDlg,
      qt_meta_data_CBellDlg, 0 }
};

const QMetaObject *CBellDlg::metaObject() const
{
    return &staticMetaObject;
}

void *CBellDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CBellDlg))
	return static_cast<void*>(const_cast<CBellDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int CBellDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
