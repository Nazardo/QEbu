#include "videoformattypeform.h"
#include "../model/formattype.h"
#include "listview.h"
#include "qvarptr.h"
#include "listview.h"
#include "typegroupform.h"
#include "videotracktypeform.h"
#include "technicalattributesform.h"
#include "aspectratiotypeform.h"
#include "lengthtypeform.h"
#include "../model/qebulimits.h"
#include <QPushButton>
#include <QButtonGroup>
#include <QLineEdit>
#include <QSpinBox>
#include <QCheckBox>
#include <QFormLayout>

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
        fl->addRow(tr("Video format ID"), m_editVideoFormatId);
        m_editVideoFormatName = new QLineEdit;
        fl->addRow(tr("Video format name"), m_editVideoFormatName);
        m_editVideoFormatDefinition = new QLineEdit;
        fl->addRow(tr("Video format definition"), m_editVideoFormatDefinition);
        vl->addLayout(fl);
    }
    {
        QGridLayout *gl = new QGridLayout;

        m_spinRegionDelimX = new QSpinBox;
        m_spinRegionDelimX->setRange(0, qEbuLimits::getMaxInt());
        m_checkRegionDelimX = new QCheckBox(tr("Region delim X"));
        gl->addWidget(m_checkRegionDelimX, 0, 0);
        gl->addWidget(m_spinRegionDelimX, 0, 1);
        QObject::connect(m_spinRegionDelimX, SIGNAL(valueChanged(int)),
                         this, SLOT(regionDelimXChanged()));

        m_spinRegionDelimY = new QSpinBox;
        m_spinRegionDelimY->setRange(0, qEbuLimits::getMaxInt());
        m_checkRegionDelimY = new QCheckBox(tr("Region delim Y"));
        gl->addWidget(m_checkRegionDelimY, 1, 0);
        gl->addWidget(m_spinRegionDelimY, 1, 1);
        QObject::connect(m_spinRegionDelimY, SIGNAL(valueChanged(int)),
                         this, SLOT(regionDelimYChanged()));

        vl->addLayout(gl);
    }
    {
        QFormLayout *fl = new QFormLayout;
        m_buttonWidth = new QPushButton(">>");
        fl->addRow(tr("Width"), m_buttonWidth);
        QObject::connect(m_buttonWidth, SIGNAL(toggled(bool)),
                         this, SLOT(widthChecked(bool)));
        m_buttonHeight = new QPushButton(">>");
        fl->addRow(tr("Heigth"), m_buttonHeight);
        QObject::connect(m_buttonHeight, SIGNAL(toggled(bool)),
                         this, SLOT(heightChecked(bool)));
        m_buttonAspectRatio = new QPushButton(">>");
        fl->addRow(tr("Aspect ratio"), m_buttonAspectRatio);
        QObject::connect(m_buttonAspectRatio, SIGNAL(toggled(bool)),
                         this, SLOT(aspectRatioChecked(bool)));
        m_buttonVideoEncoding = new QPushButton(">>");
        fl->addRow(tr("Video encoding"), m_buttonVideoEncoding);
        QObject::connect(m_buttonVideoEncoding, SIGNAL(toggled(bool)),
                         this, SLOT(videoEncodingChecked(bool)));
        m_buttonVideoTrack = new QPushButton(">>");
        fl->addRow(tr("Video track"), m_buttonVideoTrack);
        QObject::connect(m_buttonVideoTrack, SIGNAL(toggled(bool)),
                         this, SLOT(videoTrackTypeChecked(bool)));
        m_buttonTechnicalAttributes = new QPushButton(">>");
        fl->addRow(tr("Technical attributes"), m_buttonTechnicalAttributes);
        QObject::connect(m_buttonTechnicalAttributes, SIGNAL(toggled(bool)),
                         this, SLOT(technicalAttributesChecked(bool)));
        vl->addLayout(fl);
        QButtonGroup *group = new QButtonGroup(this);
        m_buttonAspectRatio->setCheckable(true);
        group->addButton(m_buttonAspectRatio);
        m_buttonWidth->setCheckable(true);
        group->addButton(m_buttonWidth);
        m_buttonHeight->setCheckable(true);
        group->addButton(m_buttonHeight);
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
    m_buttonWidth->setChecked(true);
}

QString VideoFormatTypeForm::toString()
{
    return QString("Video Format Type");
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
    if (m_checkRegionDelimY->isChecked())
        m_videoFormat->setRegionDelimY(m_spinRegionDelimY->value());
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
        QObject::connect(aspectRatioForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(aspectRatioFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(aspectRatioForm);
    }
        break;
    case Width:
    {
        LengthTypeForm *widthForm = new LengthTypeForm(0, this->mainWindow());
        QObject::connect(widthForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(widthFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(widthForm);
    }
        break;
    case Height:
    {
        LengthTypeForm *heightForm = new LengthTypeForm(0, this->mainWindow());
        QObject::connect(heightForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(heightFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(heightForm);
    }
        break;
    case VideoEncoding:
    {
        TypeGroupForm *videoEncodingForm = new TypeGroupForm(0, this->mainWindow());
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
        QObject::connect(aspectRatioForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(aspectRatioFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(aspectRatioForm);
    }
        break;
    case Width:
    {
        LengthTypeForm *widthForm = new LengthTypeForm(
                    m_videoFormat->width(), this->mainWindow());
        QObject::connect(widthForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(widthFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(widthForm);
    }
        break;
    case Height:
    {
        LengthTypeForm *heightForm = new LengthTypeForm(
                    m_videoFormat->height(), this->mainWindow());
        QObject::connect(heightForm, SIGNAL(closed(Operation,QVariant)),
                         this, SLOT(heightFormClosed(Operation,QVariant)));
        this->mainWindow()->pushWidget(heightForm);
    }
        break;
    case VideoEncoding:
    {
        TypeGroupForm *videoEncodingForm = new TypeGroupForm(
                    m_videoFormat->videoEncoding().at(index), this->mainWindow());
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
    case Width:
    {
        m_videoFormat->setWidth(0);
        m_listView->buttonAdd()->setEnabled(true);
    }
    case Height:
    {
        m_videoFormat->setHeight(0);
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

void VideoFormatTypeForm::widthChecked(bool checked)
{
    if (!checked)
        return;
    m_currentEditMode = Width;
    updateListAndButtons();
    LengthType *lt = m_videoFormat->width();
    if (lt) {
        m_listView->addItem(lt->toString());
        m_listView->enableAdd(false);
    }
}

void VideoFormatTypeForm::heightChecked(bool checked)
{
    if (!checked)
        return;
    m_currentEditMode = Height;
    updateListAndButtons();
    LengthType *lt = m_videoFormat->height();
    if (lt) {
        m_listView->addItem(lt->toString());
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

void VideoFormatTypeForm::widthFormClosed(StackableWidget::Operation op, QVariant value)
{
    LengthType *width = QVarPtr<LengthType>::asPointer(value);
    if(!width)
        return;
    if(op == Add) {
        m_listView->addItem(width->toString());
        m_videoFormat->setWidth(width);
        m_listView->enableAdd(false);
    } else if(op == Edit) {
        int row = 0;
        m_listView->setItem(row, width->toString());
    }
}

void VideoFormatTypeForm::heightFormClosed(StackableWidget::Operation op, QVariant value)
{
    LengthType *height = QVarPtr<LengthType>::asPointer(value);
    if(!height)
        return;
    if(op == Add) {
        m_listView->addItem(height->toString());
        m_videoFormat->setHeight(height);
        m_listView->enableAdd(false);
    } else if(op == Edit) {
        int row = 0;
        m_listView->setItem(row, height->toString());
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
        title = tr("Aspect ratio");
    else if (m_currentEditMode == Width)
        title = tr("Width");
    else if (m_currentEditMode == Height)
        title = tr("Height");
    else if (m_currentEditMode == VideoEncoding)
        title = tr("Video encoding");
    else if (m_currentEditMode == VideoTrack)
        title = tr("Video track");
    else if (m_currentEditMode == TechnicalAttributesMode)
        title = tr("Technical attributes");
    m_listView->setTitle(title);
    m_listView->clear();
}
