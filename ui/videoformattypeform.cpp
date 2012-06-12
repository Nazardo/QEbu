#include "videoformattypeform.h"
#include "../model/formattype.h"
#include "listview.h"
#include "qvarptr.h"
#include "listview.h"
#include "typegroupform.h"
#include "videotracktypeform.h"
#include "technicalattributesform.h"
#include "aspectratiotypeform.h"
#include "lengthtypeeditbox.h"
#include "../model/qebulimits.h"
#include <QPushButton>
#include <QButtonGroup>
#include <QLineEdit>
#include <QTextEdit>
#include <QCheckBox>
#include <QFormLayout>
#include "qextendedspinbox.h"
#include <QEvent>

VideoFormatTypeForm::VideoFormatTypeForm(VideoFormatType *videoFormat,
                                         QEbuMainWindow *mainWindow,
                                         QWidget *parent) :
    StackableWidget(mainWindow, parent)
{
    m_op = (videoFormat) ? Edit : Add;
    if (!videoFormat)
        m_videoFormat = new VideoFormatType;
    else
        m_videoFormat = videoFormat;
    //Layout
    QHBoxLayout *mainHLayout = new QHBoxLayout;
    QVBoxLayout *vl = new QVBoxLayout;
    {
        QFormLayout *fl = new QFormLayout;
        m_editVideoFormatId = new QLineEdit;
        fl->addRow(tr("Video Format Id"), m_editVideoFormatId);
        m_editVideoFormatName = new QLineEdit;
        fl->addRow(tr("Video Format Name"), m_editVideoFormatName);
        m_editVideoFormatDefinition = new QLineEdit;
        fl->addRow(tr("Video Format Definition"), m_editVideoFormatDefinition);
        vl->addLayout(fl);
    }
    {
        QGridLayout *gl = new QGridLayout;

        m_spinRegionDelimX = new QUnsignedSpinBox;
        m_spinRegionDelimX->setRange(qEbuLimits::getMinUInt(), qEbuLimits::getMaxUInt());
        m_checkRegionDelimX = new QCheckBox(tr("Region Delim X"));
        gl->addWidget(m_checkRegionDelimX, 0, 0);
        gl->addWidget(m_spinRegionDelimX, 0, 1);
        QObject::connect(m_spinRegionDelimX, SIGNAL(valueChanged()),
                         this, SLOT(regionDelimXChanged()));

        m_spinRegionDelimY = new QUnsignedSpinBox;
        m_spinRegionDelimY->setRange(qEbuLimits::getMinUInt(), qEbuLimits::getMaxUInt());
        m_checkRegionDelimY = new QCheckBox(tr("Region Delim Y"));
        gl->addWidget(m_checkRegionDelimY, 1, 0);
        gl->addWidget(m_spinRegionDelimY, 1, 1);
        QObject::connect(m_spinRegionDelimY, SIGNAL(valueChanged()),
                         this, SLOT(regionDelimYChanged()));

        m_editWidth = new LengthTypeEditBox(m_videoFormat->width());
        m_editWidth->setLabel(tr("Width"));
        gl->addWidget(m_editWidth, 2, 0, 1, 2);

        m_editHeight = new LengthTypeEditBox(m_videoFormat->height());
        m_editHeight->setLabel(tr("Heigth"));
        gl->addWidget(m_editHeight, 3, 0, 1, 2);

        vl->addLayout(gl);
    }
    {
        QFormLayout *fl = new QFormLayout;

        m_buttonAspectRatio = new QPushButton(">>");
        fl->addRow(tr("Aspect Ratio"), m_buttonAspectRatio);
        QObject::connect(m_buttonAspectRatio, SIGNAL(toggled(bool)),
                         this, SLOT(aspectRatioChecked(bool)));
        m_buttonVideoEncoding = new QPushButton(">>");
        fl->addRow(tr("Video Encoding"), m_buttonVideoEncoding);
        QObject::connect(m_buttonVideoEncoding, SIGNAL(toggled(bool)),
                         this, SLOT(videoEncodingChecked(bool)));
        m_buttonVideoTrack = new QPushButton(">>");
        fl->addRow(tr("Video Track"), m_buttonVideoTrack);
        QObject::connect(m_buttonVideoTrack, SIGNAL(toggled(bool)),
                         this, SLOT(videoTrackTypeChecked(bool)));
        m_buttonTechnicalAttributes = new QPushButton(">>");
        fl->addRow(tr("Technical Attributes"), m_buttonTechnicalAttributes);
        QObject::connect(m_buttonTechnicalAttributes, SIGNAL(toggled(bool)),
                         this, SLOT(technicalAttributesChecked(bool)));
        vl->addLayout(fl);
        QButtonGroup *group = new QButtonGroup(this);
        m_buttonAspectRatio->setCheckable(true);
        group->addButton(m_buttonAspectRatio);
        m_buttonVideoEncoding->setCheckable(true);
        group->addButton(m_buttonVideoEncoding);
        m_buttonVideoTrack->setCheckable(true);
        group->addButton(m_buttonVideoTrack);
        m_buttonTechnicalAttributes->setCheckable(true);
        group->addButton(m_buttonTechnicalAttributes);
    }
    mainHLayout->addLayout(vl);
    // Add list view on the right
    m_listView = new ListView();
    QObject::connect(m_listView->buttonAdd(), SIGNAL(clicked()),
                     this, SLOT(addClicked()));
    QObject::connect(m_listView->buttonEdit(), SIGNAL(clicked()),
                     this, SLOT(editClicked()));
    QObject::connect(m_listView->buttonRemove(), SIGNAL(clicked()),
                     this, SLOT(removeClicked()));
    mainHLayout->addWidget(m_listView);
    this->setLayout(mainHLayout);

    //Event filter
    m_textDocumentation->setText(tr("A description of video characteristics of the resource to provide technical information such as colour, greyscale or black and white colour schemes, frame rate, sampling rate, scanning format, encoding, track configuration."));
    m_editVideoFormatId->installEventFilter(this);
    m_editVideoFormatDefinition->installEventFilter(this);
    m_editVideoFormatName->installEventFilter(this);
    m_spinRegionDelimX->installEventFilter(this);
    m_spinRegionDelimY->installEventFilter(this);
    m_editWidth->editValue()->installEventFilter(this);
    m_editWidth->editUnit()->installEventFilter(this);
    m_editHeight->editValue()->installEventFilter(this);
    m_editHeight->editUnit()->installEventFilter(this);
    m_buttonAspectRatio->installEventFilter(this);
    m_buttonVideoEncoding->installEventFilter(this);
    m_buttonVideoTrack->installEventFilter(this);
    m_buttonTechnicalAttributes->installEventFilter(this);

    //Set data fields...
    m_editVideoFormatId->setText(m_videoFormat->videoFormatId());
    m_editVideoFormatName->setText(m_videoFormat->videoFormatName());
    m_editVideoFormatDefinition->setText(m_videoFormat->videoFormatDefinition());
    if (m_videoFormat->regionDelimX()) {
        m_spinRegionDelimX->setValue(*(m_videoFormat->regionDelimX()));
        m_checkRegionDelimX->setChecked(true);
    }
    if (m_videoFormat->regionDelimY()) {
        m_spinRegionDelimY->setValue(*(m_videoFormat->regionDelimY()));
        m_checkRegionDelimY->setChecked(true);
    }
    m_buttonAspectRatio->setChecked(true);
}

QString VideoFormatTypeForm::toString()
{
    return QString(tr("Video Format"));
}

void VideoFormatTypeForm::cancelClicked()
{
    if (m_op == Add) {
        delete m_videoFormat;
        m_videoFormat = 0;
    }
    emit closed(m_op, QVarPtr<VideoFormatType>::asQVariant(m_videoFormat));
}

void VideoFormatTypeForm::applyClicked()
{
    m_videoFormat->setVideoFormatId(m_editVideoFormatId->text());
    m_videoFormat->setVideoFormatName(m_editVideoFormatName->text());
    m_videoFormat->setVideoFormatDefinition(m_editVideoFormatDefinition->text());
    if (m_checkRegionDelimX->isChecked())
        m_videoFormat->setRegionDelimX(m_spinRegionDelimX->value());
    else
        m_videoFormat->clearRegionDelimX();
    if (m_checkRegionDelimY->isChecked())
        m_videoFormat->setRegionDelimY(m_spinRegionDelimY->value());
    else
        m_videoFormat->clearRegionDelimY();
    m_videoFormat->setWidth(m_editWidth->lengthType());
    m_videoFormat->setHeight(m_editHeight->lengthType());
    emit closed(m_op, QVarPtr<VideoFormatType>::asQVariant(m_videoFormat));
}

void VideoFormatTypeForm::regionDelimXChanged()
{
    m_checkRegionDelimX->setChecked(true);
}

void VideoFormatTypeForm::regionDelimYChanged()
{
    m_checkRegionDelimY->setChecked(true);
}

void VideoFormatTypeForm::addClicked()
{
    switch (m_currentEditMode) {
    case AspectRatio:
    {
        AspectRatioTypeForm *aspectRatioForm = new AspectRatioTypeForm(0, this->mainWindow());
        aspectRatioForm->addLinksMap(this->mainWindow()->getMap("ebu_VisualAspectRatioCS")); //Autocompletion values
        QObject::connect(aspectRatioForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(aspectRatioFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(aspectRatioForm);
    }
        break;
    case VideoEncoding:
    {
        TypeGroupForm *videoEncodingForm = new TypeGroupForm(0, this->mainWindow());
        videoEncodingForm->addLinksMap(this->mainWindow()->getMap("ebu_VideoCompressionCodeCS")); //Autocompletion values
        videoEncodingForm->setTitle(tr("Video Encoding"));
        QObject::connect(videoEncodingForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(videoEncodingFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(videoEncodingForm);
    }
        break;
    case VideoTrack:
    {
        VideoTrackTypeForm *videoTrackForm = new VideoTrackTypeForm(0, this->mainWindow());
        QObject::connect(videoTrackForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(videoTrackFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(videoTrackForm);
    }
        break;
    case TechnicalAttributesMode:
    {
        TechnicalAttributesForm *technicalAttributesForm = new TechnicalAttributesForm(0, this->mainWindow());
        QObject::connect(technicalAttributesForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(technicalAttributesFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(technicalAttributesForm);
    }
        break;
    }
}

void VideoFormatTypeForm::editClicked()
{
    int index = m_listView->selected();
    if (index < 0)
        return;
    switch (m_currentEditMode) {
    case AspectRatio:
    {
        AspectRatioTypeForm *aspectRatioForm = new AspectRatioTypeForm(
                    m_videoFormat->aspectRatio(), this->mainWindow());
        aspectRatioForm->addLinksMap(this->mainWindow()->getMap("ebu_VisualAspectRatioCS")); //Autocompletion values
        QObject::connect(aspectRatioForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(aspectRatioFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(aspectRatioForm);
    }
        break;
    case VideoEncoding:
    {
        TypeGroupForm *videoEncodingForm = new TypeGroupForm(
                    m_videoFormat->videoEncoding().at(index), this->mainWindow());
        videoEncodingForm->addLinksMap(this->mainWindow()->getMap("ebu_VideoCompressionCodeCS")); //Autocompletion values
        videoEncodingForm->setTitle(tr("Video Encoding"));
        QObject::connect(videoEncodingForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(videoEncodingFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(videoEncodingForm);
    }
        break;
    case VideoTrack:
    {
        VideoTrackTypeForm *videoTrackForm = new VideoTrackTypeForm(
                    m_videoFormat->videoTrack().at(index), this->mainWindow());
        QObject::connect(videoTrackForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(videoTrackFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(videoTrackForm);
    }
        break;
    case TechnicalAttributesMode:
    {
        TechnicalAttributesForm *technicalAttributesForm = new TechnicalAttributesForm(
                    m_videoFormat->technicalAttributes(), this->mainWindow());
        QObject::connect(technicalAttributesForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(organisationDetailsFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(technicalAttributesForm);
    }
        break;
    }
}

void VideoFormatTypeForm::removeClicked()
{
    int row = m_listView->selected();
    if (row < 0)
        return;
    m_listView->removeAt(row);
    switch (m_currentEditMode) {
    case AspectRatio:
    {
        m_videoFormat->setAspectRatio(0);
        m_listView->buttonAdd()->setEnabled(true);
    }
    case VideoEncoding:
    {
        delete(m_videoFormat->videoEncoding().takeAt(row));
    }
        break;
    case VideoTrack:
    {
        delete(m_videoFormat->videoTrack().takeAt(row));
    }
        break;
    case TechnicalAttributesMode:
    {
        m_videoFormat->setTechnicalAttributes(0);
        m_listView->buttonAdd()->setEnabled(true);
    }
        break;
    }
}

void VideoFormatTypeForm::aspectRatioChecked(bool checked)
{
    if (!checked)
        return;
    m_currentEditMode = AspectRatio;
    updateListAndButtons();
    AspectRatioType *art = m_videoFormat->aspectRatio();
    if (art) {
        m_listView->addItem(art->toString());
        m_listView->enableAdd(false);
    }
}

void VideoFormatTypeForm::videoEncodingChecked(bool checked)
{
    if (!checked)
        return;
    m_currentEditMode = VideoEncoding;
    updateListAndButtons();
    int s = m_videoFormat->videoEncoding().size();
    for (int i=0; i < s; ++i) {
        TypeGroup *tg = m_videoFormat->videoEncoding().at(i);
        if (!tg)
            continue;
        m_listView->addItem(tg->toString());
    }
}

void VideoFormatTypeForm::videoTrackTypeChecked(bool checked)
{
    if (!checked)
        return;
    m_currentEditMode = VideoTrack;
    updateListAndButtons();
    int s = m_videoFormat->videoTrack().size();
    for (int i=0; i < s; ++i) {
        VideoTrackType *vtt = m_videoFormat->videoTrack().at(i);
        if (!vtt)
            continue;
        m_listView->addItem(vtt->toString());
    }
}

void VideoFormatTypeForm::technicalAttributesChecked(bool checked)
{
    if (!checked)
        return;
    m_currentEditMode = TechnicalAttributesMode;
    updateListAndButtons();
    TechnicalAttributes *ta = m_videoFormat->technicalAttributes();
    if (ta) {
        m_listView->addItem(ta->toString());
        m_listView->enableAdd(false);
    }
}

void VideoFormatTypeForm::aspectRatioFormClosed(StackableWidget::Operation op, QVariant value)
{
    AspectRatioType *aspectRatio = QVarPtr<AspectRatioType>::asPointer(value);
    if(!aspectRatio)
        return;
    if(op == Add) {
        m_listView->addItem(aspectRatio->toString());
        m_videoFormat->setAspectRatio(aspectRatio);
        m_listView->enableAdd(false);
    } else if(op == Edit) {
        int row = 0;
        m_listView->setItem(row, aspectRatio->toString());
    }
}

void VideoFormatTypeForm::videoEncodingFormClosed(StackableWidget::Operation op, QVariant value)
{
    TypeGroup *videoEncoding = QVarPtr<TypeGroup>::asPointer(value);
    if(!videoEncoding)
        return;
    if(op == Add) {
        m_listView->addItem(videoEncoding->toString());
        m_videoFormat->videoEncoding().append(videoEncoding);
    } else if(op == Edit) {
        int row = m_videoFormat->videoEncoding().indexOf(videoEncoding);
        m_listView->setItem(row, videoEncoding->toString());
    }
}

void VideoFormatTypeForm::videoTrackFormClosed(Operation op, QVariant value)
{
    VideoTrackType *videoTrack = QVarPtr<VideoTrackType>::asPointer(value);
    if (!videoTrack)
        return;
    if (op == Add) {
        m_listView->addItem(videoTrack->toString());
        m_videoFormat->videoTrack().append(videoTrack);
    } else if (op == Edit) {
        int row = m_videoFormat->videoTrack().indexOf(videoTrack);
        m_listView->setItem(row, videoTrack->toString());
    }
}

void VideoFormatTypeForm::technicalAttributesFormClosed(StackableWidget::Operation op, QVariant value)
{
    TechnicalAttributes *technicalAttributes = QVarPtr<TechnicalAttributes>::asPointer(value);
    if(!technicalAttributes)
        return;
    if(op == Add) {
        m_listView->addItem(technicalAttributes->toString());
        m_videoFormat->setTechnicalAttributes(technicalAttributes);
        m_listView->enableAdd(false);
    } else if(op == Edit) {
        int row = 0;
        m_listView->setItem(row, technicalAttributes->toString());
    }
}

void VideoFormatTypeForm::updateListAndButtons()
{
    QString title;
    if (m_currentEditMode == AspectRatio)
        title = tr("Aspect Ratio");
    else if (m_currentEditMode == VideoEncoding)
        title = tr("Video Encoding");
    else if (m_currentEditMode == VideoTrack)
        title = tr("Video Track");
    else if (m_currentEditMode == TechnicalAttributesMode)
        title = tr("Technical Attributes");
    m_listView->setTitle(title);
    m_listView->clear();
}

bool VideoFormatTypeForm::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::FocusIn) {
        if (obj == (QObject*) m_editVideoFormatId)
            m_textDocumentation->setText(tr("An Identifier to identify a specific format in which the resource is available or has been published."));
        else if ( obj ==(QObject*) m_editVideoFormatDefinition)
            m_textDocumentation->setText(tr("A definition of the format information being provided either technical or editorial in nature."));
        else if ( obj == (QObject*) m_editVideoFormatName)
            m_textDocumentation->setText(tr("A name attributed to a particular format."));
        else if (obj == (QObject*) m_spinRegionDelimX)
            m_textDocumentation->setText(tr("The identification of a region in a document, an image or a video is done by defining the coordinates of the bottom left corner of the region. The region is defined from this point of reference using the width and height properties. regionDelimX uses the same unit as width."));
        else if ( obj ==(QObject*) m_spinRegionDelimY)
            m_textDocumentation->setText(tr("The identification of a region in a document, an image or a video is done by defining the coordinates of the bottom left corner of the region. The region is defined from this point of reference using the width and height properties. regionDelimY uses the same unit as height."));
        else if  (obj == (QObject*) m_editWidth->editValue())
            m_textDocumentation->setText(tr("To define the width of a video image."));
        else if  (obj == (QObject*) m_editWidth->editUnit())
            m_textDocumentation->setText(tr("An attribute to specify the unit in which the width is expressed."));
        else if  (obj == (QObject*) m_editHeight->editValue())
            m_textDocumentation->setText(tr("To define the height of a video image."));
        else if  (obj == (QObject*) m_editHeight->editUnit())
            m_textDocumentation->setText(tr("An attribute to specify the unit in which the height is expressed."));
        else if ( obj == (QObject*) m_buttonAspectRatio)
            m_textDocumentation->setText(tr("A string to define e.g. the ratio of the picture (the width by the height), for instance '4:3' or '16 9' (rational). The format of the aspect ratio is precised in the format attributes."));
        else if ( obj == (QObject*) m_buttonVideoEncoding)
            m_textDocumentation->setText(tr("Used to express the encoding parameters of the resource e.g. H264 for a video channel."));
        else if ( obj == (QObject*) m_buttonVideoTrack)
            m_textDocumentation->setText(tr("To describe the main features of video tracks such as in multiview systems."));
        else if ( obj == (QObject*) m_buttonTechnicalAttributes)
            m_textDocumentation->setText(tr("An extension element to allow users and implementers defining their own technical attributes."));
    }
    return QObject::eventFilter(obj, event);
}
