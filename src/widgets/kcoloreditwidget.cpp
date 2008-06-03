/*********************************************************************************
*  Copyright (C) 2008 by Percy Camilo Triveño Aucahuasi <orgyforever@gmail.com>  *
*                                                                                *
*  This program is free software; you can redistribute it and/or modify          *
*  it under the terms of the GNU General Public License as published by          *
*  the Free Software Foundation; either version 2 of the License, or             *
*  (at your option) any later version.                                           *
*                                                                                *
*  This program is distributed in the hope that it will be useful,               *
*  but WITHOUT ANY WARRANTY; without even the implied warranty of                *
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                 *
*  GNU General Public License for more details.                                  *
*                                                                                *
*  You should have received a copy of the GNU General Public License             *
*  along with this program; if not, write to the                                 *
*  Free Software Foundation, Inc.,                                               *
*  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.                 *
*********************************************************************************/

#include "kcoloreditwidget.h"

#include <QtGui/QHBoxLayout>
#include <QtGui/QVBoxLayout>

#include <KLocalizedString>

#include "multipagewidget.h"
#include "kdecolorselector.h"
#include "gtkcolorselector.h"
#include "blendercolorselector.h"
#include "colorwidget.h"
#include "colorinfovisual.h"
#include "colorinfotext.h"

KColorEditWidget::KColorEditWidget(QWidget * parent)
    : QWidget(parent)
{
    MultiPageWidget * colorSelectors = new MultiPageWidget(this);
    colorSelectors->setPrevToolTip(i18n("Prev selector"));
    colorSelectors->setNextToolTip(i18n("Next selector"));

    m_kdeColorSelector = new KdeColorSelector(colorSelectors);

    m_gtkColorSelector = new GtkColorSelector(colorSelectors);

    m_blenderColorSelector = new BlenderColorSelector(colorSelectors);

    colorSelectors->addPage(m_kdeColorSelector, KIcon("kde"), i18n("KDE Style"));
    colorSelectors->addPage(m_gtkColorSelector, KIcon("fill-color"), i18n("GTK Style"));
    colorSelectors->addPage(m_blenderColorSelector, KIcon("fill-color"), i18n("Mix Colors"));

    MultiPageWidget* colorInfoVisuals = new MultiPageWidget(this);
    colorInfoVisuals->setMaximumHeight(128); // NOTE default value here;
    colorInfoVisuals->setPrevToolTip(i18n("Prev visual style"));
    colorInfoVisuals->setNextToolTip(i18n("Next visual style"));

    m_colorDispatcher = new ColorWidget(this);

    ColorInfoVisualComplement * colorInfoVisualComplement = new ColorInfoVisualComplement(colorInfoVisuals);

    colorInfoVisuals->addPage(colorInfoVisualComplement, KIcon(), i18n("Complementary color"));

    MultiPageWidget * colorInfoTexts = new MultiPageWidget(this);
    colorInfoTexts->setMaximumHeight(100); // NOTE default value here;
    colorInfoTexts->setPrevToolTip(i18n("Prev text style"));
    colorInfoTexts->setNextToolTip(i18n("Next text style"));

    ColorInfoTextRGB * infoTextRGB = new ColorInfoTextRGB(colorInfoTexts);
    infoTextRGB->setColor(Qt::red); // default color

    ColorInfoTextHSV * infoTextHSV = new ColorInfoTextHSV(colorInfoTexts);
    infoTextHSV->setColor(Qt::red); // default color

    ColorInfoTextCMY * infoTextCMY = new ColorInfoTextCMY(colorInfoTexts);
    infoTextCMY->setColor(Qt::red); // default color

    ColorInfoTextHTML * infoTextHTML = new ColorInfoTextHTML(colorInfoTexts);
    infoTextHTML->setColor(Qt::red); // default color

    colorInfoTexts->addPage(infoTextRGB, KIcon(), i18n("RGB Model"));
    colorInfoTexts->addPage(infoTextHSV, KIcon(), i18n("HSV Model"));
    colorInfoTexts->addPage(infoTextCMY, KIcon(), i18n("CMY Model"));
    colorInfoTexts->addPage(infoTextHTML, KIcon(), i18n("Other"));

    QVBoxLayout * mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(colorSelectors);
    mainLayout->addWidget(m_colorDispatcher);
    mainLayout->addWidget(colorInfoTexts);
    mainLayout->addWidget(colorInfoVisuals);

    for (int i = 0; i < colorSelectors->count(); i++)
        connect(colorSelectors->page(i), SIGNAL( colorSelected(QColor) ), m_colorDispatcher, SLOT( setColor(QColor) ));

    for (int k = 0; k < colorInfoTexts->count(); k++)
        connect(m_colorDispatcher, SIGNAL( colorChanged(QColor) ), colorInfoTexts->page(k), SLOT( setColor(QColor) ));

    for (int j = 0; j < colorInfoVisuals->count(); j++)
        connect(m_colorDispatcher, SIGNAL( colorChanged(QColor) ), colorInfoVisuals->page(j), SLOT( setColor(QColor) ));
}

QColor KColorEditWidget::selectedColor() const
{
    return m_colorDispatcher->color();
}

void KColorEditWidget::setColor(const QColor & color)
{
    m_kdeColorSelector->setColor(color);
    m_gtkColorSelector->setColor(color);
    m_blenderColorSelector->setColor(color);
}

#include "kcoloreditwidget.moc"
