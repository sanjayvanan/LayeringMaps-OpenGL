/****************************************************************************
** Meta object code from reading C++ file 'shapefilerenderer.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../shapefilerenderer.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'shapefilerenderer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.7.2. It"
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
struct qt_meta_stringdata_CLASSShapefileRendererENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSShapefileRendererENDCLASS = QtMocHelpers::stringData(
    "ShapefileRenderer",
    "zoomChanged",
    "",
    "centerChanged",
    "lndareVisibleChanged",
    "availableLayersChanged",
    "selectedLayersChanged",
    "toggleLayer",
    "layerName",
    "zoom",
    "center",
    "lndareVisible",
    "availableLayers",
    "selectedLayers"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSShapefileRendererENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       5,   58, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   50,    2, 0x06,    6 /* Public */,
       3,    0,   51,    2, 0x06,    7 /* Public */,
       4,    0,   52,    2, 0x06,    8 /* Public */,
       5,    0,   53,    2, 0x06,    9 /* Public */,
       6,    0,   54,    2, 0x06,   10 /* Public */,

 // methods: name, argc, parameters, tag, flags, initial metatype offsets
       7,    1,   55,    2, 0x02,   11 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Void, QMetaType::QString,    8,

 // properties: name, type, flags
       9, QMetaType::QReal, 0x00015103, uint(0), 0,
      10, QMetaType::QPointF, 0x00015103, uint(1), 0,
      11, QMetaType::Bool, 0x00015103, uint(2), 0,
      12, QMetaType::QStringList, 0x00015001, uint(3), 0,
      13, QMetaType::QStringList, 0x00015103, uint(4), 0,

       0        // eod
};

Q_CONSTINIT const QMetaObject ShapefileRenderer::staticMetaObject = { {
    QMetaObject::SuperData::link<QQuickItem::staticMetaObject>(),
    qt_meta_stringdata_CLASSShapefileRendererENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSShapefileRendererENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSShapefileRendererENDCLASS_t,
        // property 'zoom'
        QtPrivate::TypeAndForceComplete<qreal, std::true_type>,
        // property 'center'
        QtPrivate::TypeAndForceComplete<QPointF, std::true_type>,
        // property 'lndareVisible'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'availableLayers'
        QtPrivate::TypeAndForceComplete<QStringList, std::true_type>,
        // property 'selectedLayers'
        QtPrivate::TypeAndForceComplete<QStringList, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<ShapefileRenderer, std::true_type>,
        // method 'zoomChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'centerChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'lndareVisibleChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'availableLayersChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'selectedLayersChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'toggleLayer'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>
    >,
    nullptr
} };

void ShapefileRenderer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ShapefileRenderer *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->zoomChanged(); break;
        case 1: _t->centerChanged(); break;
        case 2: _t->lndareVisibleChanged(); break;
        case 3: _t->availableLayersChanged(); break;
        case 4: _t->selectedLayersChanged(); break;
        case 5: _t->toggleLayer((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ShapefileRenderer::*)();
            if (_t _q_method = &ShapefileRenderer::zoomChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ShapefileRenderer::*)();
            if (_t _q_method = &ShapefileRenderer::centerChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ShapefileRenderer::*)();
            if (_t _q_method = &ShapefileRenderer::lndareVisibleChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ShapefileRenderer::*)();
            if (_t _q_method = &ShapefileRenderer::availableLayersChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (ShapefileRenderer::*)();
            if (_t _q_method = &ShapefileRenderer::selectedLayersChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
    } else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<ShapefileRenderer *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< qreal*>(_v) = _t->zoom(); break;
        case 1: *reinterpret_cast< QPointF*>(_v) = _t->center(); break;
        case 2: *reinterpret_cast< bool*>(_v) = _t->lndareVisible(); break;
        case 3: *reinterpret_cast< QStringList*>(_v) = _t->availableLayers(); break;
        case 4: *reinterpret_cast< QStringList*>(_v) = _t->selectedLayers(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<ShapefileRenderer *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setZoom(*reinterpret_cast< qreal*>(_v)); break;
        case 1: _t->setCenter(*reinterpret_cast< QPointF*>(_v)); break;
        case 2: _t->setLndareVisible(*reinterpret_cast< bool*>(_v)); break;
        case 4: _t->setSelectedLayers(*reinterpret_cast< QStringList*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
}

const QMetaObject *ShapefileRenderer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ShapefileRenderer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSShapefileRendererENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QQuickItem::qt_metacast(_clname);
}

int ShapefileRenderer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QQuickItem::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 6;
    }else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void ShapefileRenderer::zoomChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void ShapefileRenderer::centerChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void ShapefileRenderer::lndareVisibleChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void ShapefileRenderer::availableLayersChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void ShapefileRenderer::selectedLayersChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}
QT_WARNING_POP
