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

#include "formattype.h"
#include <QObject>


/* ------------------------------ ImageFormatType -------------------------- */
ImageFormatType::ImageFormatType()
{
    m_orientation = 0;
    m_width = 0;
    m_height = 0;
    m_technicalAttributes = 0;
    m_regionDelimX = 0;
    m_regionDelimY = 0;
}

ImageFormatType::~ImageFormatType()
{
    delete m_width;
    delete m_height;
    int s = m_imageEncoding.size();
    for (int i=0; i < s; ++i) {
        delete (m_imageEncoding.takeAt(0));
    }
    delete m_regionDelimX;
    delete m_regionDelimY;
    delete m_technicalAttributes;
    delete m_orientation;
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

unsigned int *ImageFormatType::regionDelimX() const
{
    return m_regionDelimX;
}

void ImageFormatType::setRegionDelimX(unsigned int regionDelimX)
{
    delete m_regionDelimX;
    m_regionDelimX = new unsigned int(regionDelimX);
}

void ImageFormatType::clearRegionDelimX()
{
    delete m_regionDelimX;
    m_regionDelimX = 0;
}

unsigned int *ImageFormatType::regionDelimY() const
{
    return m_regionDelimY;
}

void ImageFormatType::setRegionDelimY(unsigned int regionDelimY)
{
    delete m_regionDelimY;
    m_regionDelimY = new unsigned int(regionDelimY);
}

void ImageFormatType::clearRegionDelimY()
{
    delete m_regionDelimY;
    m_regionDelimY = 0;
}

LengthType *ImageFormatType::width() const
{
    return m_width;
}

void ImageFormatType::setWidth(LengthType *width)
{
    if (width != m_width)
        delete m_width;
    m_width = width;
}

LengthType *ImageFormatType::height() const
{
    return m_height;
}

void ImageFormatType::setHeight(LengthType *height)
{
    if (height != m_height)
        delete m_height;
    m_height = height;
}

ImageFormatType::Orientation *ImageFormatType::orientation() const
{
    return m_orientation;
}

void ImageFormatType::setOrientation(const ImageFormatType::Orientation &orientation)
{
    delete m_orientation;
    m_orientation = new Orientation(orientation);
}

void ImageFormatType::clearOrientation()
{
    delete m_orientation;
    m_orientation = 0;
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
    if (technicalAttributes != m_technicalAttributes)
        delete m_technicalAttributes;
    m_technicalAttributes = technicalAttributes;
}

QString ImageFormatType::toString()
{
    if (!imageFormatName().isEmpty())
        return imageFormatName();
    if (!imageFormatId().isEmpty())
        return imageFormatId();
     return QObject::tr("Unnamed image format");
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

QString AspectRatioType::toString() const
{
    if (!formatLabel().isEmpty())
        return formatLabel();
    return "Unspecified Ratio";
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

QString VideoTrackType::toString() const
{
    if (!m_trackName.isEmpty())
        return m_trackName;
    if (!m_trackId.isEmpty())
        return m_trackId;
    return QObject::tr("Unnamed video track");
}

/* ------------------------------ VideoFormatType -------------------------- */
VideoFormatType::VideoFormatType()
{
    m_width = 0;
    m_height = 0;
    m_aspectRatio = 0;
    m_technicalAttributes = 0;
    m_regionDelimX = 0;
    m_regionDelimY = 0;
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
    delete m_regionDelimX;
    delete m_regionDelimY;
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

unsigned int *VideoFormatType::regionDelimX() const
{
    return m_regionDelimX;
}

void VideoFormatType::setRegionDelimX(unsigned int regionDelimX)
{
    delete m_regionDelimX;
    m_regionDelimX = new unsigned int(regionDelimX);
}

void VideoFormatType::clearRegionDelimX()
{
    delete m_regionDelimX;
    m_regionDelimX = 0;
}

unsigned int *VideoFormatType::regionDelimY() const
{
    return m_regionDelimY;
}

void VideoFormatType::setRegionDelimY(unsigned int regionDelimY)
{
    delete m_regionDelimY;
    m_regionDelimY = new unsigned int(regionDelimY);
}

void VideoFormatType::clearRegionDelimY()
{
    delete m_regionDelimX;
    m_regionDelimX = 0;
}

LengthType *VideoFormatType::width() const
{
    return m_width;
}

void VideoFormatType::setWidth(LengthType *width)
{
    if (width != m_width)
        delete m_width;
    m_width = width;
}

LengthType *VideoFormatType::height() const
{
    return m_height;
}

void VideoFormatType::setHeight(LengthType *height)
{
    if (height != m_height)
        delete m_height;
    m_height = height;
}

AspectRatioType *VideoFormatType::aspectRatio() const
{
    return m_aspectRatio;
}

void VideoFormatType::setAspectRatio(AspectRatioType *aspectRatio)
{
    if (aspectRatio != m_aspectRatio)
        delete m_aspectRatio;
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
    if (technicalAttributes != m_technicalAttributes)
        delete m_technicalAttributes;
    m_technicalAttributes = technicalAttributes;
}

QString VideoFormatType::toString() const
{
    if (!m_videoFormatName.isEmpty())
        return m_videoFormatName;
    if (!m_videoFormatId.isEmpty())
        return m_videoFormatId;
    return "Unnamed Video Format";
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

QString AudioTrackType::toString() const
{
    if (!m_trackName.isEmpty())
        return m_trackName;
    if (!m_trackId.isEmpty())
         return m_trackId;
    return QObject::tr("Unnamed audio track");
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
    if (audioTrackConfiguration != m_audioTrackConfiguration)
        delete m_audioTrackConfiguration;
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
    if (technicalAttributes != m_technicalAttributes)
        delete m_technicalAttributes;
    m_technicalAttributes = technicalAttributes;
}

QString AudioFormatType::toString() const
{
    if (!m_audioFormatName.isEmpty())
        return m_audioFormatName;
    if (!m_audioFormatId.isEmpty())
        return m_audioFormatId;
    return "Unnamed Video Format";
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

QString CaptioningFormatType::toString() const
{
    if (!m_captioningFormatName.isEmpty())
        return m_captioningFormatName;
    if (!m_captioningFormatId.isEmpty())
        return m_captioningFormatId;
    return QObject::tr("Unnamed captioning format");
}

/* ------------------------------ AncillaryDataFormatType -------------------------- */
AncillaryDataFormatType::AncillaryDataFormatType()
{
    m_DID = 0;
    m_SDID = 0;
    m_wrappingType = 0;
}

AncillaryDataFormatType::~AncillaryDataFormatType()
{
    delete m_DID;
    delete m_SDID;
    delete m_wrappingType;
}

QString AncillaryDataFormatType::ancillaryDataFormatId() const
{
    return m_ancillaryDataFormatId;
}

void AncillaryDataFormatType::setAncillaryDataFormatId(const QString &ancillaryDataFormatId)
{
    m_ancillaryDataFormatId = ancillaryDataFormatId;
}

QString AncillaryDataFormatType::ancillaryDataFormatName() const
{
    return m_ancillaryDataFormatName;
}

void AncillaryDataFormatType::setAncillaryDataFormatName(const QString &ancillaryDataFormatName)
{
    m_ancillaryDataFormatName = ancillaryDataFormatName;
}

int *AncillaryDataFormatType::DID() const
{
    return m_DID;
}

void AncillaryDataFormatType::setDID(int DID)
{
    delete m_DID;
    m_DID = new int(DID);
}

void AncillaryDataFormatType::clearDID()
{
    delete m_DID;
    m_DID = 0;
}

int *AncillaryDataFormatType::SDID() const
{
    return m_SDID;
}

void AncillaryDataFormatType::setSDID(int SDID)
{
    delete m_SDID;
    m_SDID = new int(SDID);
}

void AncillaryDataFormatType::clearSDID()
{
    delete m_SDID;
    m_SDID = 0;
}

QList<int> &AncillaryDataFormatType::lineNumber()
{
    return m_lineNumber;
}

int *AncillaryDataFormatType::wrappingType() const
{
    return m_wrappingType;
}

void AncillaryDataFormatType::setWrappingType(int wrappingType)
{
    delete m_wrappingType;
    m_wrappingType = new int(wrappingType);
}

void AncillaryDataFormatType::clearWrappingType()
{
    delete m_wrappingType;
    m_wrappingType = 0;
}

QString AncillaryDataFormatType::toString() const
{
    if (!m_ancillaryDataFormatName.isEmpty())
        return m_ancillaryDataFormatName;
    if (!m_ancillaryDataFormatId.isEmpty())
        return m_ancillaryDataFormatId;
    return QObject::tr("Unnamed ancillary data format");
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
    s = m_ancillaryDataFormat.size();
    for (int i=0; i < s; ++i) {
        delete (m_ancillaryDataFormat.takeAt(0));
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

QList<AncillaryDataFormatType *> &DataFormatType::ancillaryDataFormat()
{
    return m_ancillaryDataFormat;
}

TechnicalAttributes *DataFormatType::technicalAttributes() const
{
    return m_technicalAttributes;
}

void DataFormatType::setTechnicalAttributes(TechnicalAttributes *technicalAttributes)
{
    if (technicalAttributes != m_technicalAttributes)
        delete m_technicalAttributes;
    m_technicalAttributes = technicalAttributes;
}

QString DataFormatType::toString() const
{
    if (!m_dataFormatName.isEmpty())
        return m_dataFormatName;
    if (!m_dataFormatId.isEmpty())
        return m_dataFormatId;
    return QObject::tr("Unnamed Data Format");
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

QString SigningFormatType::toString() const
{
    if (!m_signingFormatName.isEmpty())
        return m_signingFormatName;
    if (!m_signingFormatId.isEmpty())
        return m_signingFormatId;
    return QObject::tr("Unnamed signing format");
}

/* ------------------------------ DocumentFormatType -------------------------- */
DocumentFormatType::DocumentFormatType()
{
    m_width = 0;
    m_height = 0;
    m_regionDelimX = 0;
    m_regionDelimY = 0;
    m_wordCount = 0;
    m_technicalAttributes = 0;
}

DocumentFormatType::~DocumentFormatType()
{
    delete m_width;
    delete m_height;
    delete m_regionDelimX;
    delete m_regionDelimY;
    delete m_wordCount;
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

int *DocumentFormatType::wordCount() const
{
    return m_wordCount;
}

void DocumentFormatType::setWordCount(int wordCount)
{
    delete m_wordCount;
    m_wordCount = new int(wordCount);
}

void DocumentFormatType::clearWordCount()
{
    delete m_wordCount;
    m_wordCount = 0;
}

unsigned int *DocumentFormatType::regionDelimX() const
{
    return m_regionDelimX;
}

void DocumentFormatType::setRegionDelimX(unsigned int regionDelimX)
{
    delete m_regionDelimX;
    m_regionDelimX = new unsigned int(regionDelimX);
}

void DocumentFormatType::clearRegionDelimX()
{
    delete m_regionDelimX;
    m_regionDelimX = 0;
}

unsigned int *DocumentFormatType::regionDelimY() const
{
    return m_regionDelimY;
}

void DocumentFormatType::setRegionDelimY(unsigned int regionDelimY)
{
    delete m_regionDelimY;
    m_regionDelimY = new unsigned int(regionDelimY);
}

void DocumentFormatType::clearRegionDelimY()
{
    delete m_regionDelimY;
    m_regionDelimY = 0;
}

LengthType *DocumentFormatType::width() const
{
    return m_width;
}

void DocumentFormatType::setHeight(LengthType *height)
{
    if (height != m_height)
        delete m_height;
    m_height = height;
}

LengthType *DocumentFormatType::height() const
{
    return m_height;
}

void DocumentFormatType::setWidth(LengthType *width)
{
    if (width != m_width)
        delete m_width;
    m_width = width;
}

TechnicalAttributes *DocumentFormatType::technicalAttributes() const
{
    return m_technicalAttributes;
}

void DocumentFormatType::setTechnicalAttributes(TechnicalAttributes *technicalAttributes)
{
    if (technicalAttributes != m_technicalAttributes)
        delete m_technicalAttributes;
    m_technicalAttributes = technicalAttributes;
}

QString DocumentFormatType::toString() const
{
    if (!m_documentFormatName.isEmpty())
        return m_documentFormatName;
    if (!m_documentFormatId.isEmpty())
        return m_documentFormatId;
    return QObject::tr("Unnamed document format");
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
    m_regionDelimX = 0;
    m_regionDelimY = 0;
    m_fileSize = 0;
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
    delete m_regionDelimX;
    delete m_regionDelimY;
    delete m_fileSize;
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
    if (format != m_format)
        delete m_format;
    m_format = format;
}

unsigned int *FormatType::regionDelimX() const
{
    return m_regionDelimX;
}

void FormatType::setRegionDelimX(const unsigned int &regionDelimX)
{
    delete m_regionDelimX;
    m_regionDelimX = new unsigned int(regionDelimX);
}

void FormatType::clearRegionDelimX()
{
    delete m_regionDelimX;
    m_regionDelimY = 0;
}

unsigned int *FormatType::regionDelimY() const
{
    return m_regionDelimY;
}

void FormatType::clearRegionDelimY()
{
    delete m_regionDelimY;
    m_regionDelimY = 0;
}

void FormatType::setRegionDelimY(const unsigned int &regionDelimY)
{
    delete m_regionDelimY;
    m_regionDelimY = new unsigned int(regionDelimY);
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
    if (start != m_start)
        delete m_start;
    m_start = start;
}

TimeType *FormatType::end() const
{
    return m_end;
}

void FormatType::setEnd(TimeType *end)
{
    if (end != m_end)
        delete m_end;
    m_end = end;
}

DurationType *FormatType::duration() const
{
    return m_duration;
}

void FormatType::setDuration(DurationType *duration)
{
    if (duration != m_duration)
        delete m_duration;
    m_duration = duration;
}

long *FormatType::fileSize() const
{
    return m_fileSize;
}

void FormatType::setFileSize(const long &fileSize)
{
    delete m_fileSize;
    m_fileSize = new long(fileSize);
}

void FormatType::clearFileSize()
{
    delete m_fileSize;
    m_fileSize = 0;
}

QString FormatType::fileName() const
{
    return m_fileName;
}

void FormatType::setFileName(const QString &fileName)
{
    m_fileName = fileName;
}

LocatorType *FormatType::locator() const
{
    return m_locator;
}

void FormatType::setLocator(LocatorType *locator)
{
    if (locator != m_locator)
        delete m_locator;
    m_locator = locator;
}

DocumentFormatType *FormatType::documentFormat() const
{
    return m_documentFormat;
}

void FormatType::setDocumentFormat(DocumentFormatType *documentFormat)
{
    if (documentFormat != m_documentFormat)
        delete m_documentFormat;
    m_documentFormat = documentFormat;
}

TechnicalAttributes *FormatType::technicalAttributes() const
{
    return m_technicalAttributes;
}

void FormatType::setTechnicalAttributes(TechnicalAttributes *technicalAttributes)
{
    if (technicalAttributes != m_technicalAttributes)
        delete m_technicalAttributes;
    m_technicalAttributes = technicalAttributes;
}

DateGroup *FormatType::dateCreated() const
{
    return m_dateCreated;
}

void FormatType::setDateCreated(DateGroup *dateCreated)
{
    if (dateCreated != m_dateCreated)
        delete m_dateCreated;
    m_dateCreated = dateCreated;
}

DateGroup *FormatType::dateModified() const
{
    return m_dateModified;
}

void FormatType::setDateModified(DateGroup *dateModified)
{
    if (dateModified != m_dateModified)
        delete m_dateModified;
    m_dateModified = dateModified;
}

QString FormatType::toString() const
{
    if (m_format)
        return m_format->toString();
    if (!m_formatName.isEmpty())
        return m_formatName;
    if (!m_formatId.isEmpty())
        return m_formatId;
    return QObject::tr("Unspecified format");
}


QString LocatorType::locatorValue()
{
    return m_locatorValue;
}

void LocatorType::setLocatorValue(const QString &locatorValue)
{
    m_locatorValue = locatorValue;
}

QString LocatorType::toString()
{
    if (m_locatorValue.isEmpty())
        return TypeGroup::toString();
    return m_locatorValue;
}
