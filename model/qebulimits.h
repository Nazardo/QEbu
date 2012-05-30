#ifndef QEBULIMITS_H
#define QEBULIMITS_H

#include <limits>

class qEbuLimits
{
public:
    qEbuLimits();

    // Generic types
    static int getMaxShort();
    static int getMinShort();
    static int getMaxInt();
    static int getMinInt();
    static long getMaxLong();
    static long getMinLong();
    static double getMaxDouble();
    static double getMinDouble();

    // qTypes sizes
    static int getMaxInt8();
    static int getMinInt8();
    static int getMaxInt16();
    static int getMinInt16();
    static int getMaxInt32();
    static int getMinInt32();
    static long long getMaxInt64();
    static long long getMinInt64();
    static int getMaxUInt8();
    static int getMinUInt8();
    static int getMaxUInt16();
    static int getMinUInt16();
    static unsigned int getMaxUInt32();
    static unsigned int getMinUInt32();
    static long long unsigned getMaxUInt64();
    static long long unsigned getMinUInt64();
};

#endif // QEBULIMITS_H
