/****************************************************************************
** Meta object code from reading C++ file 'canteen_manager.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../canteen_manager.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'canteen_manager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASScanteen_managerENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASScanteen_managerENDCLASS = QtMocHelpers::stringData(
    "canteen_manager",
    "on_loginButton_clicked",
    "",
    "on_exitButton_clicked",
    "on_userManageButton_clicked",
    "on_canteenManageButton_clicked",
    "on_menuManageButton_clicked",
    "on_newsManageButton_clicked",
    "on_logoutButton_clicked",
    "on_actionLogout_triggered",
    "on_actionExit_triggered",
    "on_canteenSearchEdit_textChanged",
    "text",
    "on_dishSearchEdit_textChanged",
    "on_dishTableView_clicked",
    "QModelIndex",
    "index",
    "on_dishManageTableView_clicked",
    "on_addCanteenButton_clicked",
    "on_editCanteenButton_clicked",
    "on_deleteCanteenButton_clicked",
    "on_addDishButton_clicked",
    "on_editDishButton_clicked",
    "on_deleteDishButton_clicked",
    "on_addAnnouncementButton_clicked",
    "on_editAnnouncementButton_clicked",
    "on_deleteAnnouncementButton_clicked",
    "on_announcementManageSearchEdit_textChanged",
    "on_addUserButton_clicked",
    "on_editUserButton_clicked",
    "on_deleteUserButton_clicked",
    "on_resetPasswordButton_clicked",
    "on_userManageSearchEdit_textChanged"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASScanteen_managerENDCLASS_t {
    uint offsetsAndSizes[66];
    char stringdata0[16];
    char stringdata1[23];
    char stringdata2[1];
    char stringdata3[22];
    char stringdata4[28];
    char stringdata5[31];
    char stringdata6[28];
    char stringdata7[28];
    char stringdata8[24];
    char stringdata9[26];
    char stringdata10[24];
    char stringdata11[33];
    char stringdata12[5];
    char stringdata13[30];
    char stringdata14[25];
    char stringdata15[12];
    char stringdata16[6];
    char stringdata17[31];
    char stringdata18[28];
    char stringdata19[29];
    char stringdata20[31];
    char stringdata21[25];
    char stringdata22[26];
    char stringdata23[28];
    char stringdata24[33];
    char stringdata25[34];
    char stringdata26[36];
    char stringdata27[44];
    char stringdata28[25];
    char stringdata29[26];
    char stringdata30[28];
    char stringdata31[31];
    char stringdata32[36];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASScanteen_managerENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASScanteen_managerENDCLASS_t qt_meta_stringdata_CLASScanteen_managerENDCLASS = {
    {
        QT_MOC_LITERAL(0, 15),  // "canteen_manager"
        QT_MOC_LITERAL(16, 22),  // "on_loginButton_clicked"
        QT_MOC_LITERAL(39, 0),  // ""
        QT_MOC_LITERAL(40, 21),  // "on_exitButton_clicked"
        QT_MOC_LITERAL(62, 27),  // "on_userManageButton_clicked"
        QT_MOC_LITERAL(90, 30),  // "on_canteenManageButton_clicked"
        QT_MOC_LITERAL(121, 27),  // "on_menuManageButton_clicked"
        QT_MOC_LITERAL(149, 27),  // "on_newsManageButton_clicked"
        QT_MOC_LITERAL(177, 23),  // "on_logoutButton_clicked"
        QT_MOC_LITERAL(201, 25),  // "on_actionLogout_triggered"
        QT_MOC_LITERAL(227, 23),  // "on_actionExit_triggered"
        QT_MOC_LITERAL(251, 32),  // "on_canteenSearchEdit_textChanged"
        QT_MOC_LITERAL(284, 4),  // "text"
        QT_MOC_LITERAL(289, 29),  // "on_dishSearchEdit_textChanged"
        QT_MOC_LITERAL(319, 24),  // "on_dishTableView_clicked"
        QT_MOC_LITERAL(344, 11),  // "QModelIndex"
        QT_MOC_LITERAL(356, 5),  // "index"
        QT_MOC_LITERAL(362, 30),  // "on_dishManageTableView_clicked"
        QT_MOC_LITERAL(393, 27),  // "on_addCanteenButton_clicked"
        QT_MOC_LITERAL(421, 28),  // "on_editCanteenButton_clicked"
        QT_MOC_LITERAL(450, 30),  // "on_deleteCanteenButton_clicked"
        QT_MOC_LITERAL(481, 24),  // "on_addDishButton_clicked"
        QT_MOC_LITERAL(506, 25),  // "on_editDishButton_clicked"
        QT_MOC_LITERAL(532, 27),  // "on_deleteDishButton_clicked"
        QT_MOC_LITERAL(560, 32),  // "on_addAnnouncementButton_clicked"
        QT_MOC_LITERAL(593, 33),  // "on_editAnnouncementButton_cli..."
        QT_MOC_LITERAL(627, 35),  // "on_deleteAnnouncementButton_c..."
        QT_MOC_LITERAL(663, 43),  // "on_announcementManageSearchEd..."
        QT_MOC_LITERAL(707, 24),  // "on_addUserButton_clicked"
        QT_MOC_LITERAL(732, 25),  // "on_editUserButton_clicked"
        QT_MOC_LITERAL(758, 27),  // "on_deleteUserButton_clicked"
        QT_MOC_LITERAL(786, 30),  // "on_resetPasswordButton_clicked"
        QT_MOC_LITERAL(817, 35)   // "on_userManageSearchEdit_textC..."
    },
    "canteen_manager",
    "on_loginButton_clicked",
    "",
    "on_exitButton_clicked",
    "on_userManageButton_clicked",
    "on_canteenManageButton_clicked",
    "on_menuManageButton_clicked",
    "on_newsManageButton_clicked",
    "on_logoutButton_clicked",
    "on_actionLogout_triggered",
    "on_actionExit_triggered",
    "on_canteenSearchEdit_textChanged",
    "text",
    "on_dishSearchEdit_textChanged",
    "on_dishTableView_clicked",
    "QModelIndex",
    "index",
    "on_dishManageTableView_clicked",
    "on_addCanteenButton_clicked",
    "on_editCanteenButton_clicked",
    "on_deleteCanteenButton_clicked",
    "on_addDishButton_clicked",
    "on_editDishButton_clicked",
    "on_deleteDishButton_clicked",
    "on_addAnnouncementButton_clicked",
    "on_editAnnouncementButton_clicked",
    "on_deleteAnnouncementButton_clicked",
    "on_announcementManageSearchEdit_textChanged",
    "on_addUserButton_clicked",
    "on_editUserButton_clicked",
    "on_deleteUserButton_clicked",
    "on_resetPasswordButton_clicked",
    "on_userManageSearchEdit_textChanged"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASScanteen_managerENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
      28,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  182,    2, 0x08,    1 /* Private */,
       3,    0,  183,    2, 0x08,    2 /* Private */,
       4,    0,  184,    2, 0x08,    3 /* Private */,
       5,    0,  185,    2, 0x08,    4 /* Private */,
       6,    0,  186,    2, 0x08,    5 /* Private */,
       7,    0,  187,    2, 0x08,    6 /* Private */,
       8,    0,  188,    2, 0x08,    7 /* Private */,
       9,    0,  189,    2, 0x08,    8 /* Private */,
      10,    0,  190,    2, 0x08,    9 /* Private */,
      11,    1,  191,    2, 0x08,   10 /* Private */,
      13,    1,  194,    2, 0x08,   12 /* Private */,
      14,    1,  197,    2, 0x08,   14 /* Private */,
      17,    1,  200,    2, 0x08,   16 /* Private */,
      18,    0,  203,    2, 0x08,   18 /* Private */,
      19,    0,  204,    2, 0x08,   19 /* Private */,
      20,    0,  205,    2, 0x08,   20 /* Private */,
      21,    0,  206,    2, 0x08,   21 /* Private */,
      22,    0,  207,    2, 0x08,   22 /* Private */,
      23,    0,  208,    2, 0x08,   23 /* Private */,
      24,    0,  209,    2, 0x08,   24 /* Private */,
      25,    0,  210,    2, 0x08,   25 /* Private */,
      26,    0,  211,    2, 0x08,   26 /* Private */,
      27,    1,  212,    2, 0x08,   27 /* Private */,
      28,    0,  215,    2, 0x08,   29 /* Private */,
      29,    0,  216,    2, 0x08,   30 /* Private */,
      30,    0,  217,    2, 0x08,   31 /* Private */,
      31,    0,  218,    2, 0x08,   32 /* Private */,
      32,    1,  219,    2, 0x08,   33 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   12,
    QMetaType::Void, QMetaType::QString,   12,
    QMetaType::Void, 0x80000000 | 15,   16,
    QMetaType::Void, 0x80000000 | 15,   16,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   12,

       0        // eod
};

Q_CONSTINIT const QMetaObject canteen_manager::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CLASScanteen_managerENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASScanteen_managerENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASScanteen_managerENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<canteen_manager, std::true_type>,
        // method 'on_loginButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_exitButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_userManageButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_canteenManageButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_menuManageButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_newsManageButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_logoutButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_actionLogout_triggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_actionExit_triggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_canteenSearchEdit_textChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'on_dishSearchEdit_textChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'on_dishTableView_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QModelIndex &, std::false_type>,
        // method 'on_dishManageTableView_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QModelIndex &, std::false_type>,
        // method 'on_addCanteenButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_editCanteenButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_deleteCanteenButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_addDishButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_editDishButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_deleteDishButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_addAnnouncementButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_editAnnouncementButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_deleteAnnouncementButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_announcementManageSearchEdit_textChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'on_addUserButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_editUserButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_deleteUserButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_resetPasswordButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_userManageSearchEdit_textChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>
    >,
    nullptr
} };

void canteen_manager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<canteen_manager *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_loginButton_clicked(); break;
        case 1: _t->on_exitButton_clicked(); break;
        case 2: _t->on_userManageButton_clicked(); break;
        case 3: _t->on_canteenManageButton_clicked(); break;
        case 4: _t->on_menuManageButton_clicked(); break;
        case 5: _t->on_newsManageButton_clicked(); break;
        case 6: _t->on_logoutButton_clicked(); break;
        case 7: _t->on_actionLogout_triggered(); break;
        case 8: _t->on_actionExit_triggered(); break;
        case 9: _t->on_canteenSearchEdit_textChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 10: _t->on_dishSearchEdit_textChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 11: _t->on_dishTableView_clicked((*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[1]))); break;
        case 12: _t->on_dishManageTableView_clicked((*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[1]))); break;
        case 13: _t->on_addCanteenButton_clicked(); break;
        case 14: _t->on_editCanteenButton_clicked(); break;
        case 15: _t->on_deleteCanteenButton_clicked(); break;
        case 16: _t->on_addDishButton_clicked(); break;
        case 17: _t->on_editDishButton_clicked(); break;
        case 18: _t->on_deleteDishButton_clicked(); break;
        case 19: _t->on_addAnnouncementButton_clicked(); break;
        case 20: _t->on_editAnnouncementButton_clicked(); break;
        case 21: _t->on_deleteAnnouncementButton_clicked(); break;
        case 22: _t->on_announcementManageSearchEdit_textChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 23: _t->on_addUserButton_clicked(); break;
        case 24: _t->on_editUserButton_clicked(); break;
        case 25: _t->on_deleteUserButton_clicked(); break;
        case 26: _t->on_resetPasswordButton_clicked(); break;
        case 27: _t->on_userManageSearchEdit_textChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject *canteen_manager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *canteen_manager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASScanteen_managerENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int canteen_manager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 28)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 28;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 28)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 28;
    }
    return _id;
}
QT_WARNING_POP
