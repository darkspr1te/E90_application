/****************************************************************************
** Meta object code from reading C++ file 'SBLabel.h'
**
** Created: Sun Dec 23 21:59:17 2012
**      by: The Qt Meta Object Compiler version 59 (Qt 4.1.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "source/gui/SBLabel.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SBLabel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.1.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_SBLabel[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets

       0        // eod
};

static const char qt_meta_stringdata_SBLabel[] = {
    "SBLabel\0"
};

const QMetaObject SBLabel::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_SBLabel,
      qt_meta_data_SBLabel, 0 }
};

const QMetaObject *SBLabel::metaObject() const
{
    return &staticMetaObject;
}

void *SBLabel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SBLabel))
	return static_cast<void*>(const_cast<SBLabel*>(this));
    return QWidget::qt_metacast(_clname);
}

int SBLabel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
