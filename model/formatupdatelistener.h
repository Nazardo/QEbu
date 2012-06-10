#ifndef FORMATUPDATELISTENER_H
#define FORMATUPDATELISTENER_H

class FormatUpdateListener {
public:
    virtual void onFormatDelete(const QString &formatId) = 0;
};

#endif // FORMATUPDATELISTENER_H
