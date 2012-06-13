#############################################################################
# Copyright (C) 2012 by                                                     #
#  Mauro Levra  (nazardo)     mauro@nazardo.it                              #
#  Paolo Pasini (cosmos3900)  paolo.pasini@studenti.polito.it               #
#  Denis Patti  (dextp3)      denis.patti@studenti.polito.it                #
#  Giovanni Pessiva           giovanni.pessiva@gmail.com                    #
#  Stefano Ricossa            stefano.ricossa@studenti.polito.it            #
#                                                                           #
# This file is part of QEbu.                                                #
# QEbu is free software: you can redistribute it and/or modify              #
# it under the terms of the GNU General Public License as published by      #
# the Free Software Foundation, in the version 3 of the License.            #
#                                                                           #
# QEbu is distributed in the hope that it will be useful,                   #
# but WITHOUT ANY WARRANTY; without even the implied warranty of            #
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                      #
# See the GNU General Public License for more details.                      #
#                                                                           #
# You should have received a copy of the GNU General Public License         #
# along with QEbu.  If not, see <http://www.gnu.org/licenses/>.             #
#############################################################################

include(model/model.pri)
include(fileproc/fileproc.pri)
include(ui/ui.pri)

QT       += core gui xml

TARGET = QEbu
TEMPLATE = app


SOURCES += main.cpp

HEADERS  +=

OTHER_FILES += \
    images/watermark.png \
    images/page3.png \
    images/page2.png \
    images/page1.png \
    images/page0.png \
    images/banner.png \
    images/qebu-icon_256.png \
    images/qebu-icon_128.png \
    images/qebu-icon_64.png \
    images/qebu-icon_32.png \
    images/qebu-icon_16.png \
    icon.rc \
    icon.ico

RESOURCES += \
    qResources.qrc

RC_FILE = icon.rc
