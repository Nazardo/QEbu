#ifndef QVARPTR_H
#define QVARPTR_H

template <class T> class QVarPtr
{
public:
    static T* asPointer(QVariant v) {
        return (T*)v.value<void*>();
    }

    static QVariant asQVariant(T* ptr) {
        return qVariantFromValue((void*) ptr);
    }
};

#endif // QVARPTR_H
