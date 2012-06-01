#include "timezoneeditbox.h"
#include <QDebug>

TimezoneEditBox::TimezoneEditBox(QWidget *parent) :
    QComboBox(parent)
{
    QStringList timezones;
    timezones <<tr("(UTC -12:00) Linea cambiamento data internazionale (occidentale)");
    timezones <<tr("(UTC -11:00) Isole Midway, Samoa");
    timezones <<tr("(UTC -10:00) Hawaii");
    timezones <<tr("(UTC -09:00) Alaska");
    timezones <<tr("(UTC -08:00) Pacific standard time (US & Canada), Tijuana");
    timezones <<tr("(UTC -07:00) Mountain standard time (US & Canada)");
    timezones <<tr("(UTC -06:00) Central standard time (US & Canada)");
    timezones <<tr("(UTC -05:00) Eastern standard time (US & Canada)");
    timezones <<tr("(UTC -04:30) Caracas");
    timezones <<tr("(UTC -04:00) Atlantic standard time (Canada)");
    timezones <<tr("(UTC -03:30) Newfoundland standard time (Canada)");
    timezones <<tr("(UTC -03:00) Buenos Aires, Georgetown");
    timezones <<tr("(UTC -02:00) Medio Atlantico");
    timezones <<tr("(UTC -01:00) Isola di Capo Verde");
    timezones <<tr("(UTC  00:00) Dublino, Edinburgo, Lisbona, Londra");
    timezones <<tr("(UTC +01:00) Amsterdam, Berlino, Berna, Roma, Parigi, Stoccolma, Vienna");
    timezones <<tr("(UTC +02:00) Atene, Bucharest, Istanbul, Minsk");
    timezones <<tr("(UTC +03:00) Mosca, S. Pietroburgo, Volgograd");
    timezones <<tr("(UTC +03:30) Tehran");
    timezones <<tr("(UTC +04:00) Abu Dhabi, Muscat");
    timezones <<tr("(UTC +04:30) Kabul");
    timezones <<tr("(UTC +05:00) Islamabad, Karachi, Tashkent");
    timezones <<tr("(UTC +05:30) Calcutta, Chennai, Mumbai, Nuova Delhi");
    timezones <<tr("(UTC +05:45) Kathmandu");
    timezones <<tr("(UTC +06:00) Astana, Almaty, Dhaka, Novosibirsk");
    timezones <<tr("(UTC +06:30) Rangoon (Yangon, Burma)");
    timezones <<tr("(UTC +07:00) Bangkok, Hanoi, Jakarta");
    timezones <<tr("(UTC +08:00) Beijing, Chongqing, Hong Kong, Urumqi");
    timezones <<tr("(UTC +09:00) Osaka, Sapporo, Tokyo");
    timezones <<tr("(UTC +09:30) Adelaide, Darwin");
    timezones <<tr("(UTC +10:00) Canberra, Melbourne, Sydney, Vladvostok");
    timezones <<tr("(UTC +11:00) Magadan, Isole Solomon, Nuova Caledonia");
    timezones <<tr("(UTC +12:00) Auckland, Fiji, Kamchatka, Isole Marshall");
    timezones <<tr("(UTC +13:00) Nuku'alofa");
    addItems(timezones);
    setCurrentIndex(15);

    QObject::connect(this, SIGNAL(currentIndexChanged(int)),
                     this, SLOT(timezoneSelected(int)));
}

int TimezoneEditBox::getUTCOffset()
{
    switch(currentIndex()){
    case 0: return -12 * 60;
    case 1: return -11 * 60;
    case 2: return -10 * 60;
    case 3: return -9 * 60;
    case 4: return -8 * 60;
    case 5: return -7 * 60;
    case 6: return -6 * 60;
    case 7: return -5 * 60;
    case 8: return -4 * 60 - 30;
    case 9: return -4 * 60;
    case 10: return -3 * 60 - 30;
    case 11: return -3 * 60;
    case 12: return -2 * 60;
    case 13: return -1 * 60;
    case 14: return 0;
    case 15: return 1 * 60;
    case 16: return 2 * 60;
    case 17: return 3 * 60;
    case 18: return 3 * 60 + 30;
    case 19: return 4 * 60;
    case 20: return 4 * 60 + 30;
    case 21: return 5 * 60;
    case 22: return 5 * 60 + 30;
    case 23: return 5 * 60 + 45;
    case 24: return 6 * 60;
    case 25: return 6 * 60 + 30;
    case 26: return 7 * 60;
    case 27: return 8 * 60;
    case 28: return 9 * 60;
    case 29: return 9 * 60 + 30;
    case 30: return 10 * 60;
    case 31: return 11 * 60;
    case 32: return 12 * 60;
    case 33: return 13 * 60;
    default: qDebug() <<"Error in TimezoneEditBox: unexpected code: "+currentIndex();
    }
    return 0;
}

void TimezoneEditBox::timezoneSelected(int index)
{
    Q_UNUSED(index)
    qDebug() <<"Timezone selected: UTC" <<(int)getUTCOffset()/60 <<":" <<getUTCOffset()%60;
}

