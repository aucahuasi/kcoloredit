/***************************************************************************
                          loadpalettedlg.cpp  -  description
                             -------------------
    begin                : Sat Jul 8 2000
    copyright            : (C) 2000 by Artur Rataj
    email                : art@zeus.polsl.gliwice.pl
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "loadpalettedlg.h"

#include <string.h>

#include <qlayout.h>
#include <qlabel.h>
#include <qstring.h>
#include <qstringlist.h>
#include <qpushbutton.h>
//Added by qt3to4:
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <klocale.h>
#include <kstandarddirs.h>
#include <kfiledialog.h>
#include <kdialog.h>
#include "main.h"
#include "palette.h"

LoadPaletteDlg::LoadPaletteDlg(QWidget *parent, const char *name)
        : KDialog(parent) {
    setCaption( i18n( "Load Palette" ) );
    setButtons( Ok|Cancel );
    setDefaultButton( Ok );
    setModal( true );
    fileName = "";
    QWidget *mainWidget = new QWidget( this );
    setMainWidget( mainWidget );
    QVBoxLayout* topLayout = new QVBoxLayout(mainWidget);
    topLayout->setSpacing(spacingHint());
    topLayout->setMargin(0);

    QLabel* label = new QLabel(i18n( "Select a palette:" ), mainWidget);
    topLayout->addWidget(label);

    paletteBox = new QComboBox(mainWidget);
    paletteBox->setEditable( false );
    browseFileNameInserted = false;
    QStringList palettesList = Palette::kdePalettes();
    for(QStringList::Iterator palette = palettesList.begin();
        palette != palettesList.end(); ++palette) {
        bool prepend = (*palette).contains( "colors/Custom_Colors" );
        QString fileName = KStandardDirs::locate("config", (*palette));
        if(prepend) {
            palettesFileNames.prepend(fileName);
            setFileName(&fileName);
        }	else {
            palettesFileNames.append(fileName);
            if(palette == palettesList.begin())
                setFileName(&fileName);
        }
        QString paletteName = (*palette).mid(palettesDir.length() + 1);
        if(paletteName == "Custom_Colors")
            paletteName = i18n("Custom Colors");
        else if(paletteName == "Recent_Colors")
            paletteName = i18n("Recent Colors");
        if(prepend)
            paletteBox->insertItem(0, paletteName);
        else
            paletteBox->addItem(paletteName);
    }
    connect(paletteBox, SIGNAL( activated(int) ), SLOT( setFileName(int) ));
    topLayout->addWidget(paletteBox);
    QHBoxLayout* browseLayout = new QHBoxLayout;
    QPushButton* browseButton = new QPushButton(i18n( "Browse..." ), mainWidget);
    connect(browseButton, SIGNAL( clicked() ), SLOT( browseFileNames() ));
    browseLayout->addWidget(browseButton);
    browseLayout->addStretch(10);
    topLayout->addLayout(browseLayout);
    topLayout->addStretch(10);
    resize(300, 155);
}
LoadPaletteDlg::~LoadPaletteDlg() {
}

void LoadPaletteDlg::setFileName(QString* fileName) {
	this->fileName = *fileName;
}

void LoadPaletteDlg::setFileName(int index) {
	setFileName(&palettesFileNames[index]);
}

void LoadPaletteDlg::browseFileNames() {
	QString fileToOpen = KFileDialog::getOpenFileName(lastOpenPaletteFileDir,
		i18n("*|All Files"), this, i18n("Open File"));
	if(!fileToOpen.isEmpty()) {
		fileName = fileToOpen;
		if(browseFileNameInserted) {
			paletteBox->removeItem(0);
			palettesFileNames.removeAt(0);
		}
		paletteBox->insertItem(0, fileName);
		paletteBox->setCurrentIndex(0);
		palettesFileNames.prepend(fileName);
		browseFileNameInserted = true;
		lastOpenPaletteFileDir = fileName;
	}
}

QString LoadPaletteDlg::getFileName() {
	return fileName;
}
#include "loadpalettedlg.moc"
