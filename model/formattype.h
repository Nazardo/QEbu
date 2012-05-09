#ifndef FORMATTYPE_H
#define FORMATTYPE_H

#include <QList>
#include <QString>
#include "entitytype.h"
#include "lengthtype.h"
#include "dategroup.h"
#include "formatgroup.h"
#include "typegroup.h"
#include "timetype.h"
#include "technicalattributes.h"
#include "dategroup.h"

class TimeType;

class ImageFormatType
{
public:
    ImageFormatType();
    enum Orientation {landscape, portrait};

    // Attributes
    QString imageFormatId() const;
    void setImageFormatId(const QString &imageFormatId);
    QString imageFormatName() const;
    void setImageFormatName(const QString &imageFormatName);
    QString imageFormatDefinition() const;
    void setImageFormatDefinition(const QString &imageFormatDefinition);
    // Elements
    unsigned int regionDelimX() const;
    void setRegionDelimX(const unsigned int &regionDelimX);
    unsigned int regionDelimY() const;
    void setRegionDelimY(const unsigned int &width);
    LengthType *width() const;
    void setWidth(LengthType *length);
    LengthType *height() const;
    void setHeight(LengthType *height);
    enum Orientation orientation() const;
    void setOrientation(const enum Orientation &orientation);
    QList<TypeGroup*> &imageEncoding();
    TechnicalAttributes *technicalAttributes() const;
    void setTechnicalAttributes(TechnicalAttributes *technicalAttributes);

private:
    // Attributes
    QString m_imageFormatId;
    QString m_imageFormatName;
    QString m_imageFormatDefinition;
    // Elements (all optional)
    unsigned int m_regionDelimX;    //nonNegativeInteger
    unsigned int m_regionDelimY;    //nonNegativeInteger
    LengthType *m_width;
    LengthType *m_height;
    enum Orientation m_orientation;
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
private:
    // Attributes
    QString m_trackId;
    QString m_trackName;
};

class VideoFormatType
{
public:
    VideoFormatType();
    // Attributes
    QString videoFormatId() const;
    void setVideoFormatId(const QString &videoFormatId);
    QString videoFormatName() const;
    void setVideoFormatName(const QString &videoFormatName);
    QString videoFormatDefinition() const;
    void setVideoFormatDefinition(const QString &videoFormatDefinition);
    // Elements
    unsigned int regionDelimX() const;
    void setRegionDelimX(const unsigned int &regionDelimX);
    unsigned int regionDelimY() const;
    void setRegionDelimY(const unsigned int &regionDelimY);
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

private:
    // Attributes
    QString m_videoFormatId;
    QString m_videoFormatName;
    QString m_videoFormatDefinition;
    // Elements (all optional)
    unsigned int m_regionDelimX;    //nonNegativeInteger
    unsigned int m_regionDelimY;    //nonNegativeInteger
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

private:
    // Attributes
    QString m_captioningSourceUri;
    QString m_captioningFormatId;
    QString m_captioningFormatName;
};

class AncillarityDataFormatType
{
public:
    AncillarityDataFormatType();
    // Attributes
    QString ancillaryDataFormatId() const;
    void setAncillaryDataFormatId(const QString &ancillaryDataFormatId);
    QString ancillaryDataFormatName() const;
    void setAncillaryDataFormatName(const QString &ancillaryDataFormatName);
    // Elements (all optional)
    int DID() const;
    void setDID(const int &DID);
    int SDID() const;
    void setSDID(const int &SDID);
    QList<int> &lineNumber();
    int wrappingType() const;
    void setWrappingType(const int &wrappingType);

private:
    // Attributes
    QString m_ancillaryDataFormatId;
    QString m_ancillaryDataFormatName;
    // Elements (all optional)
    int m_DID;
    int m_SDID;
    QList<int> m_lineNumber;
    int m_wrappingType;
};


class DataFormatType
{
public:
    DataFormatType();
    // Attributes
    QString dataFormatId() const;
    void setDataFormatId(const QString &dataFormatId);
    QString dataFormatName() const;
    void setDataFormatName(const QString &dataFormatName);
    QString dataFormatDefinition() const;
    void setDataFormatDefinition(const QString &dataFormatDefinition);
    // Elements
    QList<CaptioningFormatType*> &captioningFormat();
    QList<AncillarityDataFormatType*> &ancillarityDataFormat();
    TechnicalAttributes *technicalAttributes() const;
    void setTechnicalAttributes(TechnicalAttributes *technicalAttributes);

private:
    // Attributes
    QString m_dataFormatId;
    QString m_dataFormatName;
    QString m_dataFormatDefinition;
    // Elements (all optional)
    QList<CaptioningFormatType*> m_captioningFormat;
    QList<AncillarityDataFormatType*> m_ancillarityDataFormat;
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
    // Attributes
    QString formatId() const;
    void setFormatId(const QString &formatId);
    QString formatName() const;
    void setFormatName(const QString &formatName);
    QString formatDefinition() const;
    void setFormatDefinition(const QString &formatDefinition);
    // Elements
    unsigned int regionDelimX() const;
    void setRegionDelimX(const unsigned int &regionDelimX);
    unsigned int regionDelimY() const;
    void setRegionDelimY(const unsigned int &regionDelimY);
    LengthType *width() const;
    void setWidth(LengthType *length);
    LengthType *height() const;
    void setHeight(LengthType *height);
    TechnicalAttributes *technicalAttributes() const;
    void setTechnicalAttributes(TechnicalAttributes *technicalAttributes);

private:
    // Attributes
    QString m_formatId;
    QString m_formatName;
    QString m_formatDefinition;
    // Elements (all optional)
    unsigned int m_regionDelimX;    //nonNegativeInteger
    unsigned int m_regionDelimY;    //nonNegativeInteger
    LengthType *m_width;
    LengthType *m_height;
    TechnicalAttributes *m_technicalAttributes;
};


class FormatType
{
public:
    FormatType();
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
    unsigned int regionDelimX() const;
    void setRegionDelimX(const unsigned int &regionDelimX);
    unsigned int regionDelimY() const;
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
    TimeType *duration() const;
    void setDuration(TimeType *duration);
    long fileSize() const;
    void setFileSize(const long &fileSize);
    QString fileName() const;
    void setFileName(const QString &fileName);
    TypeGroup *locator() const;
    void setLocator(TypeGroup *locator);
    DocumentFormatType *documentFormat() const;
    void setDocumentFormat(DocumentFormatType *documentFormat);
    TechnicalAttributes *technicalAttributes() const;
    void setTechnicalAttributes(TechnicalAttributes *technicalAttributes);
    DateGroup *dateCreated() const;
    void setDateCreated(DateGroup *dateCreated);
    DateGroup *dateModified() const;
    void setDateModified(DateGroup *dateModified);

private:
    // Attributes
    QString m_formatId;
    QString m_formatName;
    QString m_formatDefinition;
    // Elements (all optional)
    ElementType *m_format;
    unsigned int m_regionDelimX;    //nonNegativeInteger
    unsigned int m_regionDelimY;    //nonNegativeInteger
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
    TimeType *m_duration;
    long m_fileSize;
    QString m_fileName;
    TypeGroup *m_locator;
    DocumentFormatType *m_documentFormat;
    TechnicalAttributes *m_technicalAttributes;
    DateGroup *m_dateCreated;
    DateGroup *m_dateModified;
};

#endif // FORMATTYPE_H
