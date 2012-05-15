#include "formattype.h"


/* ------------------------------ ImageFormatType -------------------------- */
ImageFormatType::ImageFormatType()
{
    m_width = 0;
    m_height = 0;
    m_technicalAttributes = 0;
}

ImageFormatType::~ImageFormatType()
{
    delete m_width;
    delete m_height;
    int s = m_imageEncoding.size();
    for (int i=0; i < s; ++i) {
        delete (m_imageEncoding.takeAt(0));
    }
    delete m_technicalAttributes;
}

QString ImageFormatType::imageFormatId() const
{
    return m_imageFormatId;
}

void ImageFormatType::setImageFormatId(const QString &imageFormatId)
{
    m_imageFormatId = imageFormatId;
}

QString ImageFormatType::imageFormatName() const
{
    return m_imageFormatName;
}

void ImageFormatType::setImageFormatName(const QString &imageFormatName)
{
    m_imageFormatName = imageFormatName;
}

QString ImageFormatType::imageFormatDefinition() const
{
    return m_imageFormatDefinition;
}

void ImageFormatType::setImageFormatDefinition(const QString &imageFormatDefinition)
{
    m_imageFormatDefinition = imageFormatDefinition;
}

unsigned int ImageFormatType::regionDelimX() const
{
    return m_regionDelimX;
}

void ImageFormatType::setRegionDelimX(const unsigned int &regionDelimX)
{
    m_regionDelimX = regionDelimX;
}

unsigned int ImageFormatType::regionDelimY() const
{
    return m_regionDelimY;
}

void ImageFormatType::setRegionDelimY(const unsigned int &regionDelimY)
{
    m_regionDelimY = regionDelimY;
}

LengthType *ImageFormatType::width() const
{
    return m_width;
}

void ImageFormatType::setWidth(LengthType *width)
{
    m_width = width;
}

LengthType *ImageFormatType::height() const
{
    return m_height;
}

void ImageFormatType::setHeight(LengthType *height)
{
    m_height = height;
}

ImageFormatType::Orientation ImageFormatType::orientation() const
{
    return m_orientation;
}

void ImageFormatType::setOrientation(const ImageFormatType::Orientation &orientation)
{
    m_orientation = orientation;
}

QList<TypeGroup *> &ImageFormatType::imageEncoding()
{
    return m_imageEncoding;
}

TechnicalAttributes *ImageFormatType::technicalAttributes() const
{
    return m_technicalAttributes;
}

void ImageFormatType::setTechnicalAttributes(TechnicalAttributes *technicalAttributes)
{
    m_technicalAttributes = technicalAttributes;
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
    m_note = note;
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
    m_trackId = trackId;
}

QString VideoTrackType::trackName() const
{
    return m_trackName;
}

void VideoTrackType::setTrackName(const QString &trackName)
{
    m_trackName = trackName;
}

/* ------------------------------ VideoFormatType -------------------------- */
VideoFormatType::VideoFormatType()
{
    m_width = 0;
    m_height = 0;
    m_aspectRatio = 0;
    m_technicalAttributes = 0;
}

VideoFormatType::~VideoFormatType()
{
    delete m_width;
    delete m_height;
    delete m_aspectRatio;
    int s = m_videoEncoding.size();
    for (int i=0; i < s; ++i) {
        delete (m_videoEncoding.takeAt(0));
    }
    s = m_videoTrack.size();
    for (int i=0; i < s; ++i) {
        delete (m_videoTrack.takeAt(0));
    }
    delete m_technicalAttributes;
}

QString VideoFormatType::videoFormatId() const
{
    return m_videoFormatId;
}

void VideoFormatType::setVideoFormatId(const QString &videoFormatId)
{
    m_videoFormatId = videoFormatId;
}

QString VideoFormatType::videoFormatName() const
{
    return m_videoFormatName;
}

void VideoFormatType::setVideoFormatName(const QString &videoFormatName)
{
    m_videoFormatName = videoFormatName;
}

QString VideoFormatType::videoFormatDefinition() const
{
    return m_videoFormatDefinition;
}

void VideoFormatType::setVideoFormatDefinition(const QString &videoFormatDefinition)
{
    m_videoFormatDefinition = videoFormatDefinition;
}

unsigned int VideoFormatType::regionDelimX() const
{
    return m_regionDelimX;
}

void VideoFormatType::setRegionDelimX(const unsigned int &regionDelimX)
{
    m_regionDelimX = regionDelimX;
}

unsigned int VideoFormatType::regionDelimY() const
{
    return m_regionDelimY;
}

void VideoFormatType::setRegionDelimY(const unsigned int &regionDelimY)
{
    m_regionDelimY = regionDelimY;
}

LengthType *VideoFormatType::width() const
{
    return m_width;
}

void VideoFormatType::setWidth(LengthType *width)
{
    m_width = width;
}

LengthType *VideoFormatType::height() const
{
    return m_height;
}

void VideoFormatType::setHeight(LengthType *height)
{
    m_height = height;
}

AspectRatioType *VideoFormatType::aspectRatio() const
{
    return m_aspectRatio;
}

void VideoFormatType::setAspectRatio(AspectRatioType *aspectRatio)
{
    m_aspectRatio = aspectRatio;
}

QList<TypeGroup *> &VideoFormatType::videoEncoding()
{
    return m_videoEncoding;
}

QList<VideoTrackType *> &VideoFormatType::videoTrack()
{
    return m_videoTrack;
}

TechnicalAttributes *VideoFormatType::technicalAttributes() const
{
    return m_technicalAttributes;
}

void VideoFormatType::setTechnicalAttributes(TechnicalAttributes *technicalAttributes)
{
    m_technicalAttributes = technicalAttributes;
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
    m_trackLanguage = trackLanguage;
}

QString AudioTrackType::trackId() const
{
    return m_trackId;
}

void AudioTrackType::setTrackId(const QString &trackId)
{
    m_trackId = trackId;
}

QString AudioTrackType::trackName() const
{
    return m_trackName;
}

void AudioTrackType::setTrackName(const QString &trackName)
{
    m_trackName = trackName;
}

/* ------------------------------ AudioFormatType -------------------------- */
AudioFormatType::AudioFormatType()
{
    m_audioTrackConfiguration = 0;
    m_technicalAttributes = 0;
}

AudioFormatType::~AudioFormatType()
{
    int s = m_audioEncoding.size();
    for (int i=0; i < s; ++i) {
        delete (m_audioEncoding.takeAt(0));
    }
    delete m_audioTrackConfiguration;
    s = m_audioTrack.size();
    for (int i=0; i < s; ++i) {
        delete (m_audioTrack.takeAt(0));
    }
    delete m_technicalAttributes;
}

QString AudioFormatType::audioFormatId() const
{
    return m_audioFormatId;
}

void AudioFormatType::setAudioFormatId(const QString &audioFormatId)
{
    m_audioFormatId = audioFormatId;
}

QString AudioFormatType::audioFormatName() const
{
    return m_audioFormatName;
}

void AudioFormatType::setAudioFormatName(const QString &audioFormatName)
{
    m_audioFormatName = audioFormatName;
}

QString AudioFormatType::audioFormatDefinition() const
{
    return m_audioFormatDefinition;
}

void AudioFormatType::setAudioFormatDefinition(const QString &audioFormatDefinition)
{
    m_audioFormatDefinition = audioFormatDefinition;
}

QList<TypeGroup *> &AudioFormatType::audioEncoding()
{
    return m_audioEncoding;
}

TypeGroup *AudioFormatType::audioTrackConfiguration() const
{
    return m_audioTrackConfiguration;
}

void AudioFormatType::setAudioTrackConfiguration(TypeGroup *audioTrackConfiguration)
{
    m_audioTrackConfiguration = audioTrackConfiguration;
}

QList<AudioTrackType *> &AudioFormatType::audioTrack()
{
    return m_audioTrack;
}

TechnicalAttributes *AudioFormatType::technicalAttributes() const
{
    return m_technicalAttributes;
}

void AudioFormatType::setTechnicalAttributes(TechnicalAttributes *technicalAttributes)
{
    m_technicalAttributes = technicalAttributes;
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
    m_captioningSourceUri = captioningSourceUri;
}

QString CaptioningFormatType::captioningFormatId() const
{
    return m_captioningFormatId;
}

void CaptioningFormatType::setCaptioningFormatId(const QString &captioningFormatId)
{
    m_captioningFormatId = captioningFormatId;
}

QString CaptioningFormatType::captioningFormatName() const
{
    return m_captioningFormatName;
}

void CaptioningFormatType::setCaptioningFormatName(const QString &captioningFormatName)
{
    m_captioningFormatName = captioningFormatName;
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
    m_ancillaryDataFormatId = ancillaryDataFormatId;
}

QString AncillarityDataFormatType::ancillaryDataFormatName() const
{
    return m_ancillaryDataFormatName;
}

void AncillarityDataFormatType::setAncillaryDataFormatName(const QString &ancillaryDataFormatName)
{
    m_ancillaryDataFormatName = ancillaryDataFormatName;
}

int AncillarityDataFormatType::DID() const
{
    return m_DID;
}

void AncillarityDataFormatType::setDID(const int &DID)
{
    m_DID = DID;
}

int AncillarityDataFormatType::SDID() const
{
    return m_SDID;
}

void AncillarityDataFormatType::setSDID(const int &SDID)
{
    m_SDID = SDID;
}

QList<int> &AncillarityDataFormatType::lineNumber()
{
    return m_lineNumber;
}

int AncillarityDataFormatType::wrappingType() const
{
    return m_wrappingType;
}

void AncillarityDataFormatType::setWrappingType(const int &wrappingType)
{
    m_wrappingType = wrappingType;
}

/* ------------------------------ DataFormatType -------------------------- */
DataFormatType::DataFormatType()
{
    m_technicalAttributes = 0;
}

DataFormatType::~DataFormatType()
{
    int s = m_captioningFormat.size();
    for (int i=0; i < s; ++i) {
        delete (m_captioningFormat.takeAt(0));
    }
    s = m_ancillarityDataFormat.size();
    for (int i=0; i < s; ++i) {
        delete (m_ancillarityDataFormat.takeAt(0));
    }
    delete m_technicalAttributes;
}

QString DataFormatType::dataFormatId() const
{
    return m_dataFormatId;
}

void DataFormatType::setDataFormatId(const QString &dataFormatId)
{
    m_dataFormatId = dataFormatId;
}

QString DataFormatType::dataFormatName() const
{
    return m_dataFormatName;
}

void DataFormatType::setDataFormatName(const QString &dataFormatName)
{
    m_dataFormatName = dataFormatName;
}

QString DataFormatType::dataFormatDefinition() const
{
    return m_dataFormatDefinition;
}

void DataFormatType::setDataFormatDefinition(const QString &dataFormatDefinition)
{
    m_dataFormatDefinition = dataFormatDefinition;
}

QList<CaptioningFormatType *> &DataFormatType::captioningFormat()
{
    return m_captioningFormat;
}

QList<AncillarityDataFormatType *> &DataFormatType::ancillarityDataFormat()
{
    return m_ancillarityDataFormat;
}

TechnicalAttributes *DataFormatType::technicalAttributes() const
{
    return m_technicalAttributes;
}

void DataFormatType::setTechnicalAttributes(TechnicalAttributes *technicalAttributes)
{
    m_technicalAttributes = technicalAttributes;
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
    m_trackId = trackId;
}

QString SigningFormatType::trackName() const
{
    return m_trackName;
}

void SigningFormatType::setTrackName(const QString &trackName)
{
    m_trackName = trackName;
}

QString SigningFormatType::language() const
{
    return m_language;
}

void SigningFormatType::setLanguage(const QString &language)
{
    m_language = language;
}

QString SigningFormatType::signingSourceUri() const
{
    return m_signingSourceUri;
}

void SigningFormatType::setSigningSourceUri(const QString &signingSourceUri)
{
    m_signingSourceUri = signingSourceUri;
}

QString SigningFormatType::signingFormatId() const
{
    return m_signingFormatId;
}

void SigningFormatType::setSigningFormatId(const QString &signingFormatId)
{
    m_signingFormatId = signingFormatId;
}

QString SigningFormatType::signingFormatName() const
{
    return m_signingFormatName;
}

void SigningFormatType::setSigningFormatName(const QString &signingFormatName)
{
    m_signingFormatName = signingFormatName;
}

QString SigningFormatType::signingFormatDefinition() const
{
    return m_signingFormatDefinition;
}

void SigningFormatType::setSigningFormatDefinition(const QString &signingFormatDefinition)
{
    m_signingFormatDefinition = signingFormatDefinition;
}

/* ------------------------------ DocumentFormatType -------------------------- */
DocumentFormatType::DocumentFormatType()
{
    m_width = 0;
    m_height = 0;
    m_technicalAttributes = 0;
}

DocumentFormatType::~DocumentFormatType()
{
    delete m_width;
    delete m_height;
    delete m_technicalAttributes;
}

QString DocumentFormatType::documentFormatId() const
{
    return m_documentFormatId;
}

void DocumentFormatType::setDocumentFormatId(const QString &formatId)
{
    m_documentFormatId = formatId;
}

QString DocumentFormatType::documentFormatName() const
{
    return m_documentFormatName;
}

void DocumentFormatType::setDocumentFormatName(const QString &formatName)
{
    m_documentFormatName = formatName;
}

QString DocumentFormatType::documentFormatDefinition() const
{
    return m_documentFormatDefinition;
}

void DocumentFormatType::setDocumentFormatDefinition(const QString &formatDefinition)
{
    m_documentFormatDefinition = formatDefinition;
}

int DocumentFormatType::wordCount() const
{
    return m_wordCount;
}

void DocumentFormatType::setWordCount(const int &wordCount)
{
    m_wordCount = wordCount;
}

unsigned int DocumentFormatType::regionDelimX() const
{
    return m_regionDelimX;
}

void DocumentFormatType::setRegionDelimX(const unsigned int &regionDelimX)
{
    m_regionDelimX = regionDelimX;
}

unsigned int DocumentFormatType::regionDelimY() const
{
    return m_regionDelimY;
}

void DocumentFormatType::setRegionDelimY(const unsigned int &regionDelimY)
{
    m_regionDelimY = regionDelimY;
}

LengthType *DocumentFormatType::width() const
{
    return m_width;
}

void DocumentFormatType::setHeight(LengthType *height)
{
    m_height = height;
}

LengthType *DocumentFormatType::height() const
{
    return m_height;
}

void DocumentFormatType::setWidth(LengthType *width)
{
    m_width = width;
}

TechnicalAttributes *DocumentFormatType::technicalAttributes() const
{
    return m_technicalAttributes;
}

void DocumentFormatType::setTechnicalAttributes(TechnicalAttributes *technicalAttributes)
{
    m_technicalAttributes = technicalAttributes;
}

/* ------------------------------ FormatType -------------------------- */
FormatType::FormatType()
{
    m_format = 0;
    m_width = 0;
    m_height = 0;
    m_start = 0;
    m_end = 0;
    m_duration = 0;
    m_locator = 0;
    m_documentFormat = 0;
    m_technicalAttributes = 0;
    m_dateCreated = 0;
    m_dateModified = 0;
}

FormatType::~FormatType()
{
    delete m_format;
    delete m_width;
    delete m_height;
    int s = m_medium.size();
    for (int i=0; i < s; ++i) {
            delete (m_medium.takeAt(0));
    }
    s = m_mimeType.size();
    for (int i=0; i < s; ++i) {
            delete (m_mimeType.takeAt(0));
    }
    s = m_imageFormat.size();
    for (int i=0; i < s; ++i) {
            delete (m_imageFormat.takeAt(0));
    }
    s = m_videoFormat.size();
    for (int i=0; i < s; ++i) {
            delete (m_videoFormat.takeAt(0));
    }
    s = m_audioFormat.size();
    for (int i=0; i < s; ++i) {
            delete (m_audioFormat.takeAt(0));
    }
    s = m_containerFormat.size();
    for (int i=0; i < s; ++i) {
            delete (m_containerFormat.takeAt(0));
    }
    s = m_dataFormat.size();
    for (int i=0; i < s; ++i) {
            delete (m_dataFormat.takeAt(0));
    }
    s = m_signingFormat.size();
    for (int i=0; i < s; ++i) {
            delete (m_signingFormat.takeAt(0));
    }
    delete m_start;
    delete m_end;
    delete m_duration;
    delete m_locator;
    delete m_documentFormat;
    delete m_technicalAttributes;
    delete m_dateCreated;
    delete m_dateModified;
}

QString FormatType::formatId() const
{
    return m_formatId;
}

void FormatType::setFormatId(const QString &formatId)
{
    m_formatId = formatId;
}

QString FormatType::formatName() const
{
    return m_formatName;
}

void FormatType::setFormatName(const QString &formatName)
{
    m_formatName = formatName;
}

QString FormatType::formatDefinition() const
{
    return m_formatDefinition;
}

void FormatType::setFormatDefinition(const QString &formatDefinition)
{
    m_formatDefinition = formatDefinition;
}

ElementType *FormatType::format() const
{
    return m_format;
}

void FormatType::setFormat(ElementType *format)
{
    m_format = format;
}

unsigned int FormatType::regionDelimX() const
{
    return m_regionDelimX;
}

void FormatType::setRegionDelimX(const unsigned int &regionDelimX)
{
    m_regionDelimX = regionDelimX;
}

unsigned int FormatType::regionDelimY() const
{
    return m_regionDelimY;
}

void FormatType::setRegionDelimY(const unsigned int &regionDelimY)
{
    m_regionDelimY = regionDelimY;
}

LengthType *FormatType::width() const
{
    return m_width;
}

void FormatType::setWidth(LengthType *width)
{
    m_width = width;
}

LengthType *FormatType::height() const
{
    return m_height;
}

void FormatType::setHeight(LengthType *height)
{
    m_height = height;
}

QList<TypeGroup *> &FormatType::medium()
{
    return m_medium;
}

QList<TypeGroup *> &FormatType::mimeType()
{
    return m_mimeType;
}

QList<ImageFormatType *> &FormatType::imageFormat()
{
    return m_imageFormat;
}

QList<VideoFormatType *> &FormatType::videoFormat()
{
    return m_videoFormat;
}

QList<AudioFormatType *> &FormatType::audioFormat()
{
    return m_audioFormat;
}

QList<FormatGroup *> &FormatType::containerFormat()
{
    return m_containerFormat;
}

QList<DataFormatType *> &FormatType::dataFormat()
{
    return m_dataFormat;
}

QList<SigningFormatType *> &FormatType::signingFormat()
{
    return m_signingFormat;
}

TimeType *FormatType::start() const
{
    return m_start;
}

void FormatType::setStart(TimeType *start)
{
    m_start = start;
}

TimeType *FormatType::end() const
{
    return m_end;
}

void FormatType::setEnd(TimeType *end)
{
    m_end = end;
}

DurationType *FormatType::duration() const
{
    return m_duration;
}

void FormatType::setDuration(DurationType *duration)
{
    m_duration = duration;
}

long FormatType::fileSize() const
{
    return m_fileSize;
}

void FormatType::setFileSize(const long &fileSize)
{
    m_fileSize = fileSize;
}

QString FormatType::fileName() const
{
    return m_fileName;
}

void FormatType::setFileName(const QString &fileName)
{
    m_fileName = fileName;
}

TypeGroup *FormatType::locator() const
{
    return m_locator;
}

void FormatType::setLocator(TypeGroup *locator)
{
    m_locator = locator;
}

DocumentFormatType *FormatType::documentFormat() const
{
    return m_documentFormat;
}

void FormatType::setDocumentFormat(DocumentFormatType *documentFormat)
{
    m_documentFormat = documentFormat;
}

TechnicalAttributes *FormatType::technicalAttributes() const
{
    return m_technicalAttributes;
}

void FormatType::setTechnicalAttributes(TechnicalAttributes *technicalAttributes)
{
    m_technicalAttributes = technicalAttributes;
}

DateGroup *FormatType::dateCreated() const
{
    return m_dateCreated;
}

void FormatType::setDateCreated(DateGroup *dateCreated)
{
    m_dateCreated = dateCreated;
}

DateGroup *FormatType::dateModified() const
{
    return m_dateModified;
}

void FormatType::setDateModified(DateGroup *dateModified)
{
    m_dateModified = dateModified;
}
