/****************************************************************************
** Copyright (C) 2012 by
**  Mauro Levra  (nazardo)     mauro@nazardo.it
**  Paolo Pasini (cosmos3900)  paolo.pasini@studenti.polito.it
**  Denis Patti  (dextp3)      denis.patti@studenti.polito.it
**  Giovanni Pessiva           giovanni.pessiva@gmail.com
**  Stefano Ricossa            stefano.ricossa@studenti.polito.it
**
** This file is part of QEbu.
** QEbu is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, in the version 3 of the License.
**
** QEbu is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
** See the GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with QEbu.  If not, see <http://www.gnu.org/licenses/>.
****************************************************************************/

#include "timezoneeditbox.h"

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
    timezones <<tr("(local)");
    addItems(timezones);


    setLocal(); //default: local time
    //setCurrentIndex(15);  //default: UTC+1
}

int TimezoneEditBox::getUTCOffset() const
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
    case 34: return 0;
    default: return 0;
    }
}

void TimezoneEditBox::setUTCOffset(int minutes)
{
    switch (minutes/60) {
    case -12: setCurrentIndex(0); break;
    case -11: setCurrentIndex(1); break;
    case -10: setCurrentIndex(2); break;
    case -9: setCurrentIndex(3); break;
    case -8: setCurrentIndex(4); break;
    case -7: setCurrentIndex(5); break;
    case -6: setCurrentIndex(6); break;
    case -5: setCurrentIndex(7); break;
    case -4:
        switch (minutes%60) {
        case -30: setCurrentIndex(8); break;
        case 0: setCurrentIndex(9); break;
        default: break;
        }
        break;
    case -3:
        switch (minutes%60) {
        case -30: setCurrentIndex(10); break;
        case 0: setCurrentIndex(11); break;
        default: break;
        }
        break;
    case -2: setCurrentIndex(12); break;
    case -1: setCurrentIndex(13); break;
    case 0: setCurrentIndex(14); break;
    case 1: setCurrentIndex(15); break;
    case 2: setCurrentIndex(16); break;
    case 3:
        switch (minutes%60) {
        case 0: setCurrentIndex(17); break;
        case 30: setCurrentIndex(18); break;
        default: break;
        }
        break;
    case 4:
        switch (minutes%60) {
        case 0: setCurrentIndex(19); break;
        case 30: setCurrentIndex(20); break;
        default: break;
        }
        break;
    case 5:
        switch (minutes%60) {
        case 0: setCurrentIndex(21); break;
        case 30: setCurrentIndex(22); break;
        case 45: setCurrentIndex(23); break;
        default: break;
        }
        break;
    case 6:
        switch (minutes%60) {
        case 0: setCurrentIndex(24); break;
        case 30: setCurrentIndex(25); break;
        default: break;
        }
        break;
    case 7: setCurrentIndex(26); break;
    case 8: setCurrentIndex(27); break;
    case 9:
        switch (minutes%60) {
        case 0: setCurrentIndex(28); break;
        case 30: setCurrentIndex(29); break;
        default: break;
        }
        break;
    case 10: setCurrentIndex(30); break;
    case 11: setCurrentIndex(31); break;
    case 12: setCurrentIndex(32); break;
    case 13: setCurrentIndex(33); break;
    default: break;
    }
}

bool TimezoneEditBox::isLocal() const
{
    return currentIndex()==34;
}

void TimezoneEditBox::setLocal()
{
    setCurrentIndex(34);
}
