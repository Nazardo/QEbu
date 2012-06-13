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

#ifndef FORMATTYPE_H
#define FORMATTYPE_H

#include <QList>
#include <QString>
#include "timetype.h"
#include "durationtype.h"
#include "entitytype.h"
#include "lengthtype.h"
#include "dategroup.h"
#include "formatgroup.h"
#include "typegroup.h"
#include "technicalattributes.h"

class TimeType;
class DurationType;

class ImageFormatType
{
public:
    ImageFormatType();
    ~ImageFormatType();
    enum Orientation { Landscape, Portrait };

    // Attributes
    QString imageFormatId() const;
    void setImageFormatId(const QString &imageFormatId);
    QString imageFormatName() const;
    void setImageFormatName(const QString &imageFormatName);
    QString imageFormatDefinition() const;
    void setImageFormatDefinition(const QString &imageFormatDefinition);
    // Elements
    unsigned int *regionDelimX() const;
    void setRegionDelimX(unsigned int regionDelimX);
    void clearRegionDelimX();
    unsigned int *regionDelimY() const;
    void setRegionDelimY(unsigned int regionDelimY);
    void clearRegionDelimY();
    LengthType *width() const;
    void setWidth(LengthType *length);
    LengthType *height() const;
    void setHeight(LengthType *height);
    Orientation *orientation() const;
    void setOrientation(const enum Orientation &orientation);
    void clearOrientation();
    QList<TypeGroup*> &imageEncoding();
    TechnicalAttributes *technicalAttributes() const;
    void setTechnicalAttributes(TechnicalAttributes *technicalAttributes);

    QString toString();
private:
    // Attributes
    QString m_imageFormatId;
    QString m_imageFormatName;
    QString m_imageFormatDefinition;
    // Elements (all optional)
    unsigned int *m_regionDelimX;    //nonNegativeInteger
    unsigned int *m_regionDelimY;    //nonNegativeInteger
    LengthType *m_width;
    LengthType *m_height;
    Orientation *m_orientation;
    QList<TypeGroup*> m_imageEncoding;
    TechnicalAttributes *m_technicalAttributes;
};

class AspectRatioType : public FormatGroup
{
public:
    AspectRatioType();
    // Attributes
    QString note() const;
    void setNote(const QString &note);
    QString toString() const;
private:
    // Attributes
    QString m_note;
};

class VideoTrackType : public TypeGroup
{
public:
    VideoTrackType();
    // Attributes
    QString trackId() const;
    void setTrackId(const QString &trackId);
    QString trackName() const;
    void setTrackName(const QString &trackName);
    QString toString() const;
private:
    // Attributes
    QString m_trackId;
    QString m_trackName;
};

class VideoFormatType
{
public:
    VideoFormatType();
    ~VideoFormatType();
    // Attributes
    QString videoFormatId() const;
    void setVideoFormatId(const QString &videoFormatId);
    QString videoFormatName() const;
    void setVideoFormatName(const QString &videoFormatName);
    QString videoFormatDefinition() const;
    void setVideoFormatDefinition(const QString &videoFormatDefinition);
    // Elements
    unsigned int *regionDelimX() const;
    void setRegionDelimX(unsigned int regionDelimX);
    void clearRegionDelimX();
    unsigned int *regionDelimY() const;
    void setRegionDelimY(unsigned int regionDelimY);
    void clearRegionDelimY();
    LengthType *width() const;
    void setWidth(LengthType *width);
    LengthType *height() const;
    void setHeight(LengthType *height);
    AspectRatioType *aspectRatio() const;
    void setAspectRatio(AspectRatioType *aspectRatio);
    QList<TypeGroup*> &videoEncoding();
    QList<VideoTrackType*> &videoTrack();
    TechnicalAttributes *technicalAttributes() const;
    void setTechnicalAttributes(TechnicalAttributes *technicalAttributes);
    QString toString() const;
private:
    // Attributes
    QString m_videoFormatId;
    QString m_videoFormatName;
    QString m_videoFormatDefinition;
    // Elements (all optional)
    unsigned int *m_regionDelimX;    //nonNegativeInteger
    unsigned int *m_regionDelimY;    //nonNegativeInteger
    LengthType *m_width;
    LengthType *m_height;
    AspectRatioType *m_aspectRatio;
    QList<TypeGroup*> m_videoEncoding;
    QList<VideoTrackType*> m_videoTrack;
    TechnicalAttributes *m_technicalAttributes;
};

class AudioTrackType : public TypeGroup
{
public:
    AudioTrackType();
    // Attributes
    QString trackLanguage() const;
    void setTrackLanguage(const QString &trackLanguage);
    QString trackId() const;
    void setTrackId(const QString &trackId);
    QString trackName() const;
    void setTrackName(const QString &trackName);
    QString toString() const;
private:
    // Attributes
    QString m_trackLanguage;
    QString m_trackId;
    QString m_trackName;
};

class AudioFormatType
{
public:
    AudioFormatType();
    ~AudioFormatType();
    // Attributes
    QString audioFormatId() const;
    void setAudioFormatId(const QString &audioFormatId);
    QString audioFormatName() const;
    void setAudioFormatName(const QString &audioFormatName);
    QString audioFormatDefinition() const;
    void setAudioFormatDefinition(const QString &audioFormatDefinition);
    // Elements
    QList<TypeGroup*> &audioEncoding();
    TypeGroup *audioTrackConfiguration() const;
    void setAudioTrackConfiguration(TypeGroup *audioTrackConfiguration);
    QList<AudioTrackType*> &audioTrack();
    TechnicalAttributes *technicalAttributes() const;
    void setTechnicalAttributes(TechnicalAttributes *technicalAttributes);
    QString toString() const;
private:
    // Attributes
    QString m_audioFormatId;
    QString m_audioFormatName;
    QString m_audioFormatDefinition;
    // Elements (all optional)
    QList<TypeGroup*> m_audioEncoding;
    TypeGroup *m_audioTrackConfiguration;
    QList<AudioTrackType*> m_audioTrack;
    TechnicalAttributes *m_technicalAttributes;
};

class CaptioningFormatType : public AudioTrackType, public FormatGroup
{
public:
    CaptioningFormatType();
    // Attributes
    QString captioningSourceUri() const;
    void setCaptioningSourceUri(const QString &captioningSourceUri);
    QString captioningFormatId() const;
    void setCaptioningFormatId(const QString &captioningFormatId);
    QString captioningFormatName() const;
    void setCaptioningFormatName(const QString &captioningFormatName);
    QString toString() const;
private:
    // Attributes
    QString m_captioningSourceUri;
    QString m_captioningFormatId;
    QString m_captioningFormatName;
};

class AncillaryDataFormatType
{
public:
    AncillaryDataFormatType();
    ~AncillaryDataFormatType();
    // Attributes
    QString ancillaryDataFormatId() const;
    void setAncillaryDataFormatId(const QString &ancillaryDataFormatId);
    QString ancillaryDataFormatName() const;
    void setAncillaryDataFormatName(const QString &ancillaryDataFormatName);
    // Elements (all optional)
    int *DID() const;
    void setDID(int DID);
    void clearDID();
    int *SDID() const;
    void setSDID(int SDID);
    void clearSDID();
    QList<int> &lineNumber();
    int *wrappingType() const;
    void setWrappingType(int wrappingType);
    void clearWrappingType();
    QString toString() const;
private:
    // Attributes
    QString m_ancillaryDataFormatId;
    QString m_ancillaryDataFormatName;
    // Elements (all optional)
    int *m_DID;
    int *m_SDID;
    QList<int> m_lineNumber;
    int *m_wrappingType;
};


class DataFormatType
{
public:
    DataFormatType();
    ~DataFormatType();
    // Attributes
    QString dataFormatId() const;
    void setDataFormatId(const QString &dataFormatId);
    QString dataFormatName() const;
    void setDataFormatName(const QString &dataFormatName);
    QString dataFormatDefinition() const;
    void setDataFormatDefinition(const QString &dataFormatDefinition);
    // Elements
    QList<CaptioningFormatType*> &captioningFormat();
    QList<AncillaryDataFormatType*> &ancillaryDataFormat();
    TechnicalAttributes *technicalAttributes() const;
    void setTechnicalAttributes(TechnicalAttributes *technicalAttributes);
    QString toString() const;
private:
    // Attributes
    QString m_dataFormatId;
    QString m_dataFormatName;
    QString m_dataFormatDefinition;
    // Elements (all optional)
    QList<CaptioningFormatType*> m_captioningFormat;
    QList<AncillaryDataFormatType*> m_ancillaryDataFormat;
    TechnicalAttributes *m_technicalAttributes;
};

class SigningFormatType : public TypeGroup, public FormatGroup
{
public:
    SigningFormatType();
    // Attributes
    QString trackId() const;
    void setTrackId(const QString &trackId);
    QString trackName() const;
    void setTrackName(const QString &trackName);
    QString language() const;
    void setLanguage(const QString &language);
    QString signingSourceUri() const;
    void setSigningSourceUri(const QString &signingSourceUri);
    QString signingFormatId() const;
    void setSigningFormatId(const QString &signingFormatId);
    QString signingFormatName() const;
    void setSigningFormatName(const QString &signingFormatName);
    QString signingFormatDefinition() const;
    void setSigningFormatDefinition(const QString &signingFormatDefinition);
    QString toString() const;
private:
    // Attributes
    QString m_trackId;
    QString m_trackName;
    QString m_language;
    QString m_signingSourceUri;
    QString m_signingFormatId;
    QString m_signingFormatName;
    QString m_signingFormatDefinition;
};

class DocumentFormatType : public TypeGroup, public FormatGroup
{
public:
    DocumentFormatType();
    ~DocumentFormatType();
    // Attributes
    QString documentFormatId() const;
    void setDocumentFormatId(const QString &formatId);
    QString documentFormatName() const;
    void setDocumentFormatName(const QString &documentFormatName);
    QString documentFormatDefinition() const;
    void setDocumentFormatDefinition(const QString &documentFormatDefinition);
    // Elements
    int *wordCount() const;
    void setWordCount(int wordCount);
    void clearWordCount();
    unsigned int *regionDelimX() const;
    void setRegionDelimX(unsigned int regionDelimX);
    void clearRegionDelimX();
    unsigned int *regionDelimY() const;
    void setRegionDelimY(unsigned int regionDelimY);
    void clearRegionDelimY();
    LengthType *width() const;
    void setWidth(LengthType *length);
    LengthType *height() const;
    void setHeight(LengthType *height);
    TechnicalAttributes *technicalAttributes() const;
    void setTechnicalAttributes(TechnicalAttributes *technicalAttributes);
    QString toString() const;
private:
    // Attributes
    QString m_documentFormatId;
    QString m_documentFormatName;
    QString m_documentFormatDefinition;
    // Elements (all optional)
    unsigned int *m_regionDelimX;    //nonNegativeInteger
    unsigned int *m_regionDelimY;    //nonNegativeInteger
    int *m_wordCount;
    LengthType *m_width;
    LengthType *m_height;
    TechnicalAttributes *m_technicalAttributes;
};

class LocatorType;

class FormatType
{
public:
    FormatType();
    ~FormatType();
    // Attributes
    QString formatId() const;
    void setFormatId(const QString &formatId);
    QString formatName() const;
    void setFormatName(const QString &formatName);
    QString formatDefinition() const;
    void setFormatDefinition(const QString &formatDefinition);
    // Elements
    ElementType *format() const;
    void setFormat(ElementType *format);
    unsigned int *regionDelimX() const;
    void setRegionDelimX(const unsigned int &regionDelimX);
    void clearRegionDelimX();
    unsigned int *regionDelimY() const;
    void clearRegionDelimY();
    void setRegionDelimY(const unsigned int &regionDelimY);
    LengthType *width() const;
    void setWidth(LengthType *width);
    LengthType *height() const;
    void setHeight(LengthType *height);
    QList<TypeGroup*> &medium();
    QList<TypeGroup*> &mimeType();
    QList<ImageFormatType*> &imageFormat();
    QList<VideoFormatType*> &videoFormat();
    QList<AudioFormatType*> &audioFormat();
    QList<FormatGroup*> &containerFormat();
    QList<DataFormatType*> &dataFormat();
    QList<SigningFormatType*> &signingFormat();
    TimeType *start() const;
    void setStart(TimeType *start);
    TimeType *end() const;
    void setEnd(TimeType *end);
    DurationType *duration() const;
    void setDuration(DurationType *duration);
    long *fileSize() const;
    void setFileSize(const long &fileSize);
    void clearFileSize();
    QString fileName() const;
    void setFileName(const QString &fileName);
    LocatorType *locator() const;
    void setLocator(LocatorType *locator);
    DocumentFormatType *documentFormat() const;
    void setDocumentFormat(DocumentFormatType *documentFormat);
    TechnicalAttributes *technicalAttributes() const;
    void setTechnicalAttributes(TechnicalAttributes *technicalAttributes);
    DateGroup *dateCreated() const;
    void setDateCreated(DateGroup *dateCreated);
    DateGroup *dateModified() const;
    void setDateModified(DateGroup *dateModified);
    QString toString() const;
private:
    // Attributes
    QString m_formatId;
    QString m_formatName;
    QString m_formatDefinition;
    // Elements (all optional)
    ElementType *m_format;
    unsigned int *m_regionDelimX;    //nonNegativeInteger
    unsigned int *m_regionDelimY;    //nonNegativeInteger
    LengthType *m_width;
    LengthType *m_height;
    QList<TypeGroup*> m_medium;
    QList<TypeGroup*> m_mimeType;
    QList<ImageFormatType*> m_imageFormat;
    QList<VideoFormatType*> m_videoFormat;
    QList<AudioFormatType*> m_audioFormat;
    QList<FormatGroup*> m_containerFormat;
    QList<DataFormatType*> m_dataFormat;
    QList<SigningFormatType*> m_signingFormat;
    TimeType *m_start;
    TimeType *m_end;
    DurationType *m_duration;
    long *m_fileSize;
    QString m_fileName;
    LocatorType *m_locator;
    DocumentFormatType *m_documentFormat;
    TechnicalAttributes *m_technicalAttributes;
    DateGroup *m_dateCreated;
    DateGroup *m_dateModified;
};

class LocatorType : public TypeGroup
{
public:
    QString locatorValue();
    void setLocatorValue(const QString &locatorValue);
    QString toString();
private:
    QString m_locatorValue;
};

#endif // FORMATTYPE_H
