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
    ui/qebumainwindow.h \
    ui/listview.h \
    ui/stackablewidget.h \
    ui/typegroupeditbox.h \
    ui/qvarptr.h \
    ui/ebucoremainform.h \
    ui/entitytypeform.h \
    ui/typegroupform.h \
    ui/elementtypeeditbox.h \
    ui/addresstypeform.h \
    ui/organisationdetailstypeform.h \
    ui/organisationdepartmenttypeform.h \
    ui/detailstypeform.h \
    ui/contactdetailstypeform.h \
    ui/elementtypeform.h \
    ui/formatgroupeditbox.h \
    ui/formatgroupform.h \
    ui/titletypeform.h \
    ui/temporaltypeform.h \
    ui/rightstypeform.h \
    ui/locationtypeform.h \
    ui/coveragetypeform.h \
    ui/coordinatestypeform.h \
    ui/subjecttypeform.h \
    ui/descriptiontypeform.h \
    ui/ratingtypeform.h \
    ui/lengthtypeform.h \
    ui/signingformattypeform.h \
    ui/relationtypeform.h \
    ui/identifiertypeform.h \
    ui/typetypeform.h \
    ui/languagetypeform.h \
    ui/timetypeform.h \
    ui/publicationhistorytypeform.h \
    ui/publicationtypeform.h \
    ui/durationtypeform.h \
    ui/statusgroupeditbox.h \
    ui/dategroupeditbox.h \
    ui/dategroupform.h \
    ui/datetypeform.h \
    ui/alternativetypeform.h \
    ui/stringform.h \
    ui/booleanform.h \
    ui/floatform.h \
    ui/technicalattributeuritypeform.h \
    ui/int8form.h \
    ui/int32form.h \
    ui/int16form.h \
    ui/int64form.h \
    ui/aspectratiotypeform.h \
    ui/videotracktypeform.h \
    ui/captioningformattypeform.h \
    ui/alternativetitletypeform.h \
    ui/technicalattributesform.h \
    ui/technicalattributerationaltypeform.h \
    ui/uint8form.h \
    ui/uint16form.h \
    ui/uint32form.h \
    ui/uint64form.h \
    ui/audiotracktypeform.h \
    ui/ancillarydataformattypeform.h \
    ui/audioformattypeform.h \
    ui/dataformattypeform.h \
    ui/videoformattypeform.h \
    ui/lengthtypeeditbox.h \
    ui/imageformattypeform.h \
    ui/hastrackparttypeform.h \
    ui/timezoneeditbox.h \
    ui/completereditbox.h \
    ui/documentformattypeform.h \
    ui/coremetadatatypeform.h \
    ui/parttypeform.h \
    ui/verticalscrollarea.h \
    ui/formattypeform.h \
    ui/extendedvalidator.h \
    ui/qextendedspinbox.h \
    ui/locatortypeform.h

SOURCES += \
    ui/qebumainwindow.cpp \
    ui/listview.cpp \
    ui/typegroupeditbox.cpp \
    ui/stackablewidget.cpp \
    ui/ebucoremainform.cpp \
    ui/entitytypeform.cpp \
    ui/typegroupform.cpp \
    ui/elementtypeeditbox.cpp \
    ui/addresstypeform.cpp \
    ui/organisationdetailstypeform.cpp \
    ui/organisationdepartmenttypeform.cpp \
    ui/detailstypeform.cpp \
    ui/contactdetailstypeform.cpp \
    ui/elementtypeform.cpp \
    ui/formatgroupeditbox.cpp \
    ui/formatgroupform.cpp \
    ui/titletypeform.cpp \
    ui/temporaltypeform.cpp \
    ui/rightstypeform.cpp \
    ui/locationtypeform.cpp \
    ui/coveragetypeform.cpp \
    ui/coordinatestypeform.cpp \
    ui/subjecttypeform.cpp \
    ui/descriptiontypeform.cpp \
    ui/ratingtypeform.cpp \
    ui/lengthtypeform.cpp \
    ui/signingformattypeform.cpp \
    ui/relationtypeform.cpp \
    ui/identifiertypeform.cpp \
    ui/typetypeform.cpp \
    ui/languagetypeform.cpp \
    ui/timetypeform.cpp \
    ui/publicationhistorytypeform.cpp \
    ui/publicationtypeform.cpp \
    ui/durationtypeform.cpp \
    ui/statusgroupeditbox.cpp \
    ui/dategroupeditbox.cpp \
    ui/dategroupform.cpp \
    ui/datetypeform.cpp \
    ui/alternativetypeform.cpp \
    ui/stringform.cpp \
    ui/booleanform.cpp \
    ui/floatform.cpp \
    ui/technicalattributeuritypeform.cpp \
    ui/int8form.cpp \
    ui/int32form.cpp \
    ui/int16form.cpp \
    ui/int64form.cpp \
    ui/aspectratiotypeform.cpp \
    ui/videotracktypeform.cpp \
    ui/captioningformattypeform.cpp \
    ui/alternativetitletypeform.cpp \
    ui/technicalattributesform.cpp \
    ui/technicalattributerationaltypeform.cpp \
    ui/uint8form.cpp \
    ui/uint16form.cpp \
    ui/uint32form.cpp \
    ui/uint64form.cpp \
    ui/audiotracktypeform.cpp \
    ui/ancillarydataformattypeform.cpp \
    ui/audioformattypeform.cpp \
    ui/dataformattypeform.cpp \
    ui/videoformattypeform.cpp \
    ui/lengthtypeeditbox.cpp \
    ui/imageformattypeform.cpp \
    ui/hastrackparttypeform.cpp \
    ui/timezoneeditbox.cpp \
    ui/completereditbox.cpp \
    ui/documentformattypeform.cpp \
    ui/coremetadatatypeform.cpp \
    ui/parttypeform.cpp \
    ui/verticalscrollarea.cpp \
    ui/formattypeform.cpp \
    ui/locatortypeform.cpp
