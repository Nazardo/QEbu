#include "formattype.h"


/* ------------------------------ ImageFormatType -------------------------- */
QString ImageFormatType::imageFormatId() const
{
    return m_imageFormatId;
}

void ImageFormatType::setImageFormatId(const QString &imageFormatId)
{
    m_imageFormatId=imageFormatId;
}

QString ImageFormatType::imageFormatName() const
{
    return m_imageFormatName;
}

void ImageFormatType::setImageFormatName(const QString &imageFormatName)
{
    m_imageFormatName=imageFormatName;
}

QString ImageFormatType::imageFormatDefinition() const
{
    return m_imageFormatDefinition;
}

void ImageFormatType::setImageFormatDefinition(const QString &imageFormatDefinition)
{
    m_imageFormatDefinition=imageFormatDefinition;
}

unsigned int ImageFormatType::regionDelimX() const
{
    return m_regionDelimX;
}

void ImageFormatType::setRegionDelimX(const unsigned int &regionDelimX)
{
    m_regionDelimX=regionDelimX;
}

unsigned int ImageFormatType::regionDelimY() const
{
    return m_regionDelimY;
}

void ImageFormatType::setRegionDelimY(const unsigned int &regionDelimY)
{
    m_regionDelimY=regionDelimY;
}

LengthType *ImageFormatType::width() const
{
    return m_width;
}

void ImageFormatType::setWidth(LengthType *length)
{
    m_length=length;
}

LengthType *ImageFormatType::height() const
{
    return m_height;
}

void ImageFormatType::setHeight(LengthType *height)
{
    m_height=height;
}

ImageFormatType::Orientation ImageFormatType::orientation() const
{
    return m_orientation;
}

void ImageFormatType::setOrientation(const ImageFormatType::Orientation &orientation)
{
    m_orientation=orientation;
}

QList<TypeGroup *> ImageFormatType::imageEncoding() const
{
    return m_imageEncoding;
}

TechnicalAttributes ImageFormatType::technicalAttributes() const
{
    return m_technicalAttributes;
}

void ImageFormatType::setTechnicalAttributes(const TechnicalAttributes &technicalAttributes)
{
    m_technicalAttributes=technicalAttributes;
}

/* ------------------------------ AspectRatioType -------------------------- */
AspectRatioType::AspectRatioType()
{
}

QString AspectRatioType::note() const
{
    return m_note;
}

void AspectRatioType::setNote(const QString &note)
{
    m_note=note;
}

/* ------------------------------ VideoTrackType -------------------------- */
VideoTrackType::VideoTrackType()
{
}

QString VideoTrackType::trackId() const
{
    return m_trackId;
}

void VideoTrackType::setTrackId(const QString &trackId)
{
    m_trackId=trackId;
}

QString VideoTrackType::trackName() const
{
    return m_trackName;
}

void VideoTrackType::setTrackName(const QString &trackName)
{
    m_trackName=trackName;
}

/* ------------------------------ VideoFormatType -------------------------- */
VideoFormatType::VideoFormatType()
{
}

QString VideoFormatType::videoFormatId() const
{
    return m_videoFormatId;
}

void VideoFormatType::setVideoFormatId(const QString &videoFormatId)
{
    m_videoFormatId=videoFormatId;
}

QString VideoFormatType::videoFormatName() const
{
    return m_videoFormatName;
}

void VideoFormatType::setVideoFormatName(const QString &videoFormatName)
{
    m_videoFormatName=videoFormatName;
}

QString VideoFormatType::videoFormatDefinition() const
{
    return m_videoFormatDefinition;
}

void VideoFormatType::setVideoFormatDefinition(const QString &videoFormatDefinition)
{
    m_videoFormatDefinition=videoFormatDefinition;
}

unsigned int VideoFormatType::regionDelimX() const
{
    return m_regionDelimX;
}

void VideoFormatType::setRegionDelimX(const unsigned int &regionDelimX)
{
    m_regionDelimX=regionDelimX;
}

unsigned int VideoFormatType::regionDelimY() const
{
    return m_regionDelimY;
}

void VideoFormatType::setRegionDelimY(const unsigned int &regionDelimY)
{
    m_regionDelimY=regionDelimY;
}

LengthType *VideoFormatType::width() const
{
    return m_width;
}

void VideoFormatType::setWidth(LengthType *length)
{
    m_length=length;
}

LengthType *VideoFormatType::height() const
{
    return m_height;
}

void VideoFormatType::setHeight(LengthType *height)
{
    m_height=height;
}

AspectRatioType *VideoFormatType::aspectRatio() const
{
    return m_aspectRatio;
}

void VideoFormatType::setAspectRatio(AspectRatioType *aspectRatio)
{
    m_aspectRatio=aspectRatio;
}

QList<TypeGroup *> VideoFormatType::videoEncoding() const
{
    return m_videoEncoding;
}

QList<VideoTrackType *> VideoFormatType::videoTrack() const
{
    return m_videoTrack;
}

TechnicalAttributes *VideoFormatType::technicalAttributes() const
{
    return m_technicalAttributes;
}

void VideoFormatType::setTechnicalAttributes(TechnicalAttributes *technicalAttributes)
{
    m_technicalAttributes=technicalAttributes;
}

/* ------------------------------ AudioTrackType -------------------------- */
AudioTrackType::AudioTrackType()
{
}

QString AudioTrackType::trackLanguage() const
{
    return m_trackLanguage;
}

void AudioTrackType::setTrackLanguage(const QString &trackLanguage)
{
    m_trackLanguage=trackLanguage;
}

QString AudioTrackType::trackId() const
{
    return m_trackId;
}

void AudioTrackType::setTrackId(const QString &trackId)
{
    m_trackId=trackId;
}

QString AudioTrackType::trackName() const
{
    return m_trackName;
}

void AudioTrackType::setTrackName(const QString &trackName)
{
    m_trackName=trackName;
}

/* ------------------------------ AudioFormatType -------------------------- */
AudioFormatType::AudioFormatType()
{
}

QString AudioFormatType::audioFormatId() const
{
    return m_audioFormatId;
}

void AudioFormatType::setAudioFormatId(const QString &audioFormatId)
{
    m_audioFormatId=audioFormatId;
}

QString AudioFormatType::audioFormatName() const
{
    return m_audioFormatName;
}

void AudioFormatType::setAudioFormatName(const QString &audioFormatName)
{
    m_audioFormatName=audioFormatName;
}

QString AudioFormatType::audioFormatDefinition() const
{
    return m_audioFormatDefinition;
}

void AudioFormatType::setAudioFormatDefinition(const QString &audioFormatDefinition)
{
    m_audioFormatDefinition=audioFormatDefinition;
}

QList<TypeGroup *> AudioFormatType::audioEncoding() const
{
    return m_audioEncoding;
}

TypeGroup *AudioFormatType::audioTrackConfiguration() const
{
    return m_audioTrackConfiguration;
}

void AudioFormatType::setAudioTrackConfiguration(TypeGroup *audioTrackConfiguration)
{
    m_audioTrackConfiguration=audioTrackConfiguration;
}

QList<AudioTrackType *> AudioFormatType::audioTrack() const
{
    return m_audioTrack;
}

TechnicalAttributes *AudioFormatType::technicalAttributes() const
{
    return m_technicalAttributes;
}

void AudioFormatType::setTechnicalAttributes(TechnicalAttributes *technicalAttributes)
{
    m_technicalAttributes=technicalAttributes;
}

/* ------------------------------ CaptioningFormatType -------------------------- */
CaptioningFormatType::CaptioningFormatType()
{
}

QString CaptioningFormatType::captioningSourceUri() const
{
    return m_captioningSourceUri;
}

void CaptioningFormatType::setCaptioningSourceUri(const QString &captioningSourceUri)
{
    m_captioningSourceUri=captioningSourceUri;
}

QString CaptioningFormatType::captioningFormatId() const
{
    return m_captioningFormatId;
}

void CaptioningFormatType::setCaptioningFormatId(const QString &captioningFormatId)
{
    m_captioningFormatId=captioningFormatId;
}

QString CaptioningFormatType::captioningFormatName() const
{
    return m_captioningFormatName;
}

void CaptioningFormatType::setCaptioningFormatName(const QString &captioningFormatName)
{
    m_captioningFormatName=captioningFormatName;
}

/* ------------------------------ AncillarityDataFormatType -------------------------- */
AncillarityDataFormatType::AncillarityDataFormatType()
{
}

QString AncillarityDataFormatType::ancillaryDataFormatId() const
{
    return m_ancillaryDataFormatId;
}

void AncillarityDataFormatType::setAncillaryDataFormatId(const QString &ancillaryDataFormatId)
{
    m_ancillaryDataFormatId=ancillaryDataFormatId;
}

QString AncillarityDataFormatType::ancillaryDataFormatName() const
{
    return m_ancillaryDataFormatName;
}

void AncillarityDataFormatType::setAncillaryDataFormatName(const QString &ancillaryDataFormatName)
{
    m_ancillaryDataFormatName=ancillaryDataFormatName;
}

int AncillarityDataFormatType::DID() const
{
    return m_DID;
}

void AncillarityDataFormatType::setDID(const int &DID)
{
    m_DID=DID;
}

int AncillarityDataFormatType::SDID() const
{
    return m_SDID;
}

void AncillarityDataFormatType::setSDID(const int &SDID)
{
    m_SDID=SDID;
}

QList<int *> AncillarityDataFormatType::lineNumber() const
{
    return m_lineNumber;
}

int AncillarityDataFormatType::wrappingType() const
{
    return m_wrappingType;
}

void AncillarityDataFormatType::setWrappingType(const int &wrappingType)
{
    m_wrappingType=wrappingType;
}

/* ------------------------------ DataFormatType -------------------------- */
DataFormatType::DataFormatType()
{
}

QString DataFormatType::dataFormatId() const
{
    return m_dataFormatId;
}

void DataFormatType::setDataFormatId(const QString &dataFormatId)
{
    m_dataFormatId=dataFormatId;
}

QString DataFormatType::dataFormatName() const
{
    return m_dataFormatName;
}

void DataFormatType::setDataFormatName(const QString &dataFormatName)
{
    m_dataFormatName=dataFormatName;
}

QString DataFormatType::dataFormatDefinition() const
{
    return m_dataFormatDefinition;
}

void DataFormatType::setDataFormatDefinition(const QString &dataFormatDefinition)
{
    m_dataFormatDefinition=dataFormatDefinition;
}

QList<CaptioningFormatType *> DataFormatType::captioningFormat() const
{
    return m_captioningFormat;
}

QList<AncillarityDataFormatType *> DataFormatType::ancillarityDataFormat() const
{
    return m_ancillarityDataFormat;
}

TechnicalAttributes *DataFormatType::technicalAttributes() const
{
    return m_technicalAttributes;
}

void DataFormatType::setTechnicalAttributes(TechnicalAttributes *technicalAttributes)
{
    m_technicalAttributes=technicalAttributes;
}

/* ------------------------------ SigningFormatType -------------------------- */
SigningFormatType::SigningFormatType()
{
}

QString SigningFormatType::trackId() const
{
    return m_trackId;
}

void SigningFormatType::setTrackId(const QString &trackId)
{
    m_trackId=trackId;
}

QString SigningFormatType::trackName() const
{
    return m_trackName;
}

void SigningFormatType::setTrackName(const QString &trackName)
{
    m_trackName=trackName;
}

QString SigningFormatType::language() const
{
    return m_language;
}

void SigningFormatType::setLanguage(const QString &language)
{
    m_language=language;
}

QString SigningFormatType::signingSourceUri() const
{
    return m_signingSourceUri;
}

void SigningFormatType::setSigningSourceUri(const QString &signingSourceUri)
{
    m_signingSourceUri=signingSourceUri;
}

QString SigningFormatType::signingFormatId() const
{
    return m_signingFormatId;
}

void SigningFormatType::setSigningFormatId(const QString &signingFormatId)
{
    m_signingFormatId=signingFormatId;
}

QString SigningFormatType::signingFormatName() const
{
    return m_signingFormatName;
}

void SigningFormatType::setSigningFormatName(const QString &signingFormatName)
{
    m_signingFormatName=signingFormatName;
}

QString SigningFormatType::signingFormatDefinition() const
{
    return m_signingFormatDefinition;
}

void SigningFormatType::setSigningFormatDefinition(const QString &signingFormatDefinition)
{
    m_signingFormatDefinition=signingFormatDefinition;
}

/* ------------------------------ DocumentFormatType -------------------------- */
DocumentFormatType::DocumentFormatType()
{
}

QString DocumentFormatType::formatId() const
{
    return m_formatId;
}

void DocumentFormatType::setFormatId(const QString &formatId)
{
    m_formatId=formatId;
}

QString DocumentFormatType::formatName() const
{
    return m_formatName;
}

void DocumentFormatType::setFormatName(const QString &formatName)
{
    m_formatName=formatName;
}

QString DocumentFormatType::formatDefinition() const
{
    return m_formatDefinition;
}

void DocumentFormatType::setFormatDefinition(const QString &formatDefinition)
{
    m_formatDefinition=formatDefinition;
}

unsigned int DocumentFormatType::regionDelimX() const
{
    return m_regionDelimX;
}

void DocumentFormatType::setRegionDelimX(const unsigned int &regionDelimX)
{
    m_regionDelimX=regionDelimX;
}

unsigned int DocumentFormatType::regionDelimY() const
{
    return m_regionDelimY;
}

void DocumentFormatType::setRegionDelimY(const unsigned int &regionDelimY)
{
    m_regionDelimY=regionDelimY;
}

LengthType *DocumentFormatType::width() const
{
    return m_width;
}

void DocumentFormatType::setHeight(LengthType *height)
{
    m_height=height;
}

TechnicalAttributes *DocumentFormatType::technicalAttributes() const
{
    return m_technicalAttributes;
}

void DocumentFormatType::setTechnicalAttributes(TechnicalAttributes *technicalAttributes)
{
    m_technicalAttributes=technicalAttributes;
}

/* ------------------------------ FormatType -------------------------- */
FormatType::FormatType()
{
}

QString FormatType::formatId() const
{
    return m_formatId;
}

void FormatType::setFormatId(const QString &formatId)
{
    m_formatId=formatId;
}

QString FormatType::formatName() const
{
    return m_formatName;
}

void FormatType::setFormatName(const QString &formatName)
{
    m_formatName=formatName;
}

QString FormatType::formatDefinition() const
{
    return m_formatDefinition;
}

void FormatType::setFormatDefinition(const QString &formatDefinition)
{
    m_formatDefinition=formatDefinition;
}

ElementType *FormatType::format() const
{
    return m_format;
}

void FormatType::setFormat(ElementType *format)
{
    m_format=format;
}

unsigned int FormatType::regionDelimX() const
{
    return m_regionDelimX;
}

void FormatType::setRegionDelimX(const unsigned int &regionDelimX)
{
    m_regionDelimX=regionDelimX;
}

unsigned int FormatType::regionDelimY() const
{
    return m_regionDelimY;
}

void FormatType::setRegionDelimY(const unsigned int &regionDelimY)
{
    m_regionDelimY=regionDelimY;
}

LengthType *FormatType::width() const
{
    return m_width;
}

void FormatType::setWidth(LengthType *width)
{
    m_width=width;
}

LengthType *FormatType::height() const
{
    return m_height;
}

void FormatType::setHeight(LengthType *height)
{
    m_height=height;
}

QList<TypeGroup *> FormatType::medium() const
{
    return m_medium;
}

QList<TypeGroup *> FormatType::mimeType() const
{
    return m_mimeType;
}

QList<ImageFormatType *> FormatType::imageFormat() const
{
    return m_imageFormat;
}

QList<VideoFormatType *> FormatType::videoFormat() const
{
    return m_videoFormat;
}

QList<AudioFormatType *> FormatType::audioFormat() const
{
    return m_audioFormat;
}

QList<TypeGroup *> FormatType::containerFormat() const
{
    return m_containerFormat;
}

QList<DataFormatType *> FormatType::dataFormat() const
{
    return m_dataFormat;
}

QList<SigningFormatType *> FormatType::signingFormat() const
{
    return m_signingFormat;
}

TimeType *FormatType::start() const
{
    return m_start;
}

void FormatType::setStart(TimeType *start)
{
    m_start=start;
}

TimeType *FormatType::end() const
{
    return m_end;
}

void FormatType::setEnd(TimeType *end)
{
    m_end=end;
}

DurationType *FormatType::duration() const
{
    return m_duration;
}

void FormatType::setDuration(DurationType *duration)
{
    m_duration=duration;
}

long FormatType::fileSize() const
{
    return m_fileSize;
}

void FormatType::setFileSize(const long &fileSize)
{
    m_fileSize=fileSize;
}

QString FormatType::fileName() const
{
    return m_fileName;
}

void FormatType::setFileName(const QString &fileName)
{
    m_fileName=fileName;
}

TypeGroup *FormatType::locator() const
{
    return m_locator;
}

void FormatType::setLocator(TypeGroup *locator)
{
    m_locator=locator;
}

DocumentFormatType *FormatType::documentFormat() const
{
    return m_documentFormat;
}

void FormatType::setDocumentFormat(DocumentFormatType *documentFormat)
{
    m_documentFormat=documentFormat;
}

TechnicalAttributes *FormatType::technicalAttributes() const
{
    return m_technicalAttributes;
}

void FormatType::setTechnicalAttributes(TechnicalAttributes *technicalAttributes)
{
    m_technicalAttributes=technicalAttributes;
}

DateGroupType *FormatType::dateCreated() const
{
    return m_dateCreated;
}

void FormatType::setDateCreated(DateGroupType *dateCreated)
{
    m_dateCreated=dateCreated;
}

DateGroupType *FormatType::dateModified() const
{
    return m_dateModified;
}

void FormatType::setDateModified(DateGroupType *dateModified)
{
    m_dateModified=dateModified;
}
