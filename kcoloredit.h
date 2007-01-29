/***************************************************************************
                          kcoloredit.h  -  description
                             -------------------
    begin                : Sat Jul  8 09:57:28 CEST 2000
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

#ifndef KCOLOREDIT_H
#define KCOLOREDIT_H


#include <config.h>

// include files for Qt
#include <qevent.h>
#include <qstringlist.h>
//Added by qt3to4:
#include <QMouseEvent>

// include files for KDE
#include <kapplication.h>
#include <kmainwindow.h>
#include <kaction.h>
#include <kconfig.h>
#include <ktoggleaction.h>
#include <krecentfilesaction.h>
// application specific includes
#include "color.h"

class KColorEditDoc;
class KColorEditView;

/**
  * The base class for KColorEdit application windows. It sets up the main
  * window and reads the config file as well as providing a menubar, toolbar
  * and statusbar. An instance of KColorEditView creates your center view, which is connected
  * to the window's Doc object.
  * KColorEditApp reimplements the methods that KMainWindow provides for main window handling and supports
  * full session management as well as keyboard accelerator configuration by using KAccel.
  * @see KMainWindow
  * @see KApplication
  * @see KConfig
  * @see KAccel
  *
  * @author Source Framework Automatically Generated by KDevelop, (c) The KDevelop Team.
  * @version KDevelop version 0.4 code generation
  */
class KColorEditApp : public KMainWindow
{
  Q_OBJECT

  friend class KColorEditView;

  public:
    /** construtor of KColorEditApp, calls all init functions to create the application.
     * @see initMenuBar initToolBar
     */
    KColorEditApp();
    ~KColorEditApp();

    /** opens a file specified by commandline option
     */
    void openDocumentFile(const char *_cmdl=0);
    /** returns a pointer to the current document connected to the KMainWindow instance and is used by
     * the View class to access the document object's methods
     */
    KColorEditDoc *document() const;

  protected:
    /** save general Options like all bar positions and status as well as the geometry and the recent file list to the configuration
     * file
     */
    void saveOptions();
    /** read general Options again and initialize all variables like the recent file list
     */
    void readOptions();

    void initActions();

    /** initMenuBar creates the menubar and inserts the menupopups as well as creating the helpMenu.
     * @see KApplication#getHelpMenu
     */
    void initStatusBar();
    /** initializes the document object of the main window that is connected to the view in initView().
     * @see initView();
     */
    void initDocument();
    /** creates the centerwidget of the KMainWindow instance and sets it as the view
     */
    void initView();
    /** queryClose is called by KMainWindow on each closeEvent of a window. Against the
     * default implementation (only returns true), this calles saveModified() on the document object to ask if the document shall
     * be saved if Modified; on cancel the closeEvent is rejected.
     * @see KMainWindow#queryClose
     * @see KMainWindow#closeEvent
     */
    virtual bool queryClose();
    /** queryExit is called by KMainWindow when the last window of the application is going to be closed during the closeEvent().
     * Against the default implementation that just returns true, this calls saveOptions() to save the settings of the last window's
     * properties.
     * @see KMainWindow#queryExit
     * @see KMainWindow#closeEvent
     */
    virtual bool queryExit();

	void mouseReleaseEvent(QMouseEvent* event);

  public slots:

    void slotFileNewWindow();
    /** clears the document in the actual view to reuse it as the new document */
    void slotFileNew();
    /** open a file and load it into the document*/
    void slotFileOpen();
    /** opens a file from the recent files menu */
    void slotFileOpenRecent( const KUrl & );
    /** save a document */
    void slotFileSave();
    /** save a document by a new filename
     *  @return whether the file has been saved
     */
    bool slotFileSaveAs();
    /** asks for saving if the file is modified, then closes the actual file and window*/
    void slotClose();
    /** print the actual file */
    void slotFilePrint();
    /** closes all open windows by calling close() on each memberList item until the list is empty, then quits the application.
     * If queryClose() returns false because the user canceled the saveModified() dialog, the closing breaks.
     */
    void slotQuit();
    /** put the marked text/object into the clipboard and remove
     *	it from the document
     */
    void slotEditCut();
    /** put the marked text/object into the clipboard
     */
    void slotEditCopy();
    /** paste the clipboard into the document
     */
    void slotEditPaste();
    /** get a color from palette
     */
    void slotColorFromPalette();
    /** get a color from screen
     */
    void slotColorFromScreen();
    /** copies a color to clipboard
     */
    void slotViewColorNames();
    /** changes the statusbar contents for the standard label permanently, used to indicate current actions.
     * @param text the text that is displayed in the statusbar
     */

    void slotSelectionChanged( int, int );
    void slotClipboardChanged();
    void slotModified( bool );
    void slotPaletteAvailable( bool );

  private:

    /** the configuration object of the application */
    KSharedConfigPtr config;

    QAction *m_actSave, *m_actCut, *m_actCopy, *m_actPaste, *m_actPalette;
    KToggleAction *m_actNames;
    KRecentFilesAction *m_actRecent;

    /** view is the main widget which represents your working area. The View
     * class should handle all events of the view widget.  It is kept empty so
     * you can create your view according to your application's needs by
     * changing the view class.
     */
    KColorEditView *view;
    /** doc represents your actual document and is created only once. It keeps
     * information such as filename and does the serialization of your files.
     */
    KColorEditDoc *doc;
	/** Whether in getting a color from screen */
	bool gettingColorFromScreen;
	/** A color taken from screen */
	Color color;
	/** Whether to view color names */
	bool viewColorNames;
};

#endif // KCOLOREDIT_H
