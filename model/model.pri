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

HEADERS += \
    model/ebucoremaintype.h \
    model/coremetadatatype.h \
    model/entitytype.h \
    model/typegroup.h \
    model/formatgroup.h \
    model/statusgroup.h \
    model/dategroup.h \
    model/organisationdetailstype.h \
    model/elementtype.h \
    model/detailstype.h \
    model/contactdetailstype.h \
    model/technicalattributes.h \
    model/formattype.h \
    model/lengthtype.h \
    model/timetype.h \
    model/typeconverter.h \
    model/duration.h \
    model/durationtype.h \ 
    model/qebulimits.h \
    model/formatupdatelistener.h
	
SOURCES += \
    model/ebucoremaintype.cpp \
    model/coremetadatatype.cpp \
    model/entitytype.cpp \
    model/typegroup.cpp \
    model/formatgroup.cpp \
    model/statusgroup.cpp \
    model/dategroup.cpp \
    model/organisationdetailstype.cpp \
    model/elementtype.cpp \
    model/detailstype.cpp \
    model/contactdetailstype.cpp \
    model/technicalattributes.cpp \
    model/formattype.cpp \
    model/lengthtype.cpp \
    model/timetype.cpp \
    model/typeconverter.cpp \
    model/duration.cpp \
    model/durationtype.cpp \ 
    model/qebulimits.cpp
