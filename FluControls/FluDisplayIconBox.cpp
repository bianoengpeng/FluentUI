﻿#include "FluDisplayIconBox.h"

FluDisplayIconBox::FluDisplayIconBox(QWidget* parent /*= nullptr*/) : FluWidget(parent), m_type(FluAwesomeType::None)
{
    setFixedSize(48, 48);
    m_vMainLayout = new QVBoxLayout;
    m_vMainLayout->setSpacing(0);
    m_vMainLayout->setContentsMargins(5, 5, 5, 5);
    setLayout(m_vMainLayout);

    m_iconLabel = new QLabel(this);
    m_iconLabel->setFixedSize(30, 30);
    m_vMainLayout->addWidget(m_iconLabel, 0, Qt::AlignHCenter);

    m_textLable = new QLabel(this);
    m_vMainLayout->addWidget(m_textLable, 0, Qt::AlignHCenter);

    m_iconLabel->setObjectName("iconLabel");
    m_textLable->setObjectName("textLabel");
    onThemeChanged();
}

FluDisplayIconBox::FluDisplayIconBox(FluAwesomeType type, QWidget* parent /*= nullptr*/) : FluDisplayIconBox(parent)
{
    m_type = type;
    QPixmap pixmap = FluIconUtils::getFluentIconPixmap(m_type, FluThemeUtils::getUtils()->getTheme());
    m_iconLabel->setPixmap(pixmap);
    m_textLable->setText(EnumTypeToQString(type));
}

FluDisplayIconBox::FluDisplayIconBox(FluEmoijType type, QWidget* parent) : FluDisplayIconBox(parent)
{
    m_iconLabel->setPixmap(FluEmoijUtils::getSvgPixmap(type));
}

void FluDisplayIconBox::setSelected(bool bSelected)
{
    setProperty("selected", bSelected);
    update();
}

FluAwesomeType FluDisplayIconBox::getAwesomeType()
{
    return m_type;
}

void FluDisplayIconBox::mouseReleaseEvent(QMouseEvent* event)
{
    QWidget::mouseReleaseEvent(event);
    emit clicked();
}

void FluDisplayIconBox::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}

void FluDisplayIconBox::onThemeChanged()
{
    m_iconLabel->setPixmap(FluIconUtils::getFluentIconPixmap(m_type, FluThemeUtils::getUtils()->getTheme()));
    FluStyleSheetUitls::setQssByFileName("FluDisplayIconBox.qss", this, FluThemeUtils::getUtils()->getTheme());
}
