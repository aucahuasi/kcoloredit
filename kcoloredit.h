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
 

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

// include files for Qt
#include <qevent.h>
#include <qstrlist.h>

// include files for KDE 
#include <kapp.h>
#include <kmainwindow.h>
#include <kaccel.h>

// application specific includes
#include "color.h"

class KColorEditDoc;
class KColorEditView;

/**
  * The base class for KColorEdit application windows. It sets up the main
  * window and reads the config file as well as providing a menubar, toolbar
  * and statusbar. An instance of KColorEditView creates your center view, which is connected
  * to the window's Doc object.
  * KColorEditApp reimplements the methods that KTMainWindow provides for main window handling and supports
  * full session management as well as keyboard accelerator configuration by using KAccel.
  * @see KTMainWindow
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
    /** enables menuentries/toolbar items
     */
    void enableCommand(int id_);
    /** disables menuentries/toolbar items
     */
    void disableCommand(int id_);
    /** add a opened file to the recent file list and update recent_file_menu
     */
    void addRecentFile(const QString &file);
    /** opens a file specified by commandline option
     */
    void openDocumentFile(const char *_cmdl=0);
    /** returns a pointer to the current document connected to the KTMainWindow instance and is used by
     * the View class to access the document object's methods
     */	
    KColorEditDoc *getDocument() const; 	

  protected:
    /** save general Options like all bar positions and status as well as the geometry and the recent file list to the configuration
     * file
     */ 	
    void saveOptions();
    /** read general Options again and initialize all variables like the recent file list
     */
    void readOptions();
    /** initKeyAccel creates the keyboard accelerator items for the available slots and changes the menu accelerators.
     * @see KAccel
     */
    void initKeyAccel();
    /** initMenuBar creates the menubar and inserts the menupopups as well as creating the helpMenu.
     * @see KApplication#getHelpMenu
     */
    void initMenuBar();
    /** this creates the toolbars.
     */
    void initToolBar();
    /** sets up the statusbar for the main window by initialzing a statuslabel.
     */
    void initStatusBar();
    /** initializes the document object of the main window that is connected to the view in initView().
     * @see initView();
     */
    void initDocument();
    /** creates the centerwidget of the KTMainWindow instance and sets it as the view
     */
    void initView();
    /** queryClose is called by KTMainWindow on each closeEvent of a window. Against the
     * default implementation (only returns true), this calles saveModified() on the document object to ask if the document shall
     * be saved if Modified; on cancel the closeEvent is rejected.
     * @see KTMainWindow#queryClose
     * @see KTMainWindow#closeEvent
     */
    virtual bool queryClose();
    /** queryExit is called by KTMainWindow when the last window of the application is going to be closed during the closeEvent().
     * Against the default implementation that just returns true, this calls saveOptions() to save the settings of the last window's	
     * properties.
     * @see KTMainWindow#queryExit
     * @see KTMainWindow#closeEvent
     */
    virtual bool queryExit();
    /** saves the window properties for each open window during session end to the session config file, including saving the currently
     * opened file by a temporary filename provided by KApplication.
     * @see KTMainWindow#saveProperties
     */
    virtual void saveProperties(KConfig *_cfg);
    /** reads the session config file and restores the application's state including the last opened files and documents by reading the
     * temporary files saved by saveProperties()
     * @see KTMainWindow#readProperties
     */
    virtual void readProperties(KConfig *_cfg);
    /** Updates the recent files menu */
	void updateRecentFilesMenu();
	void mouseReleaseEvent(QMouseEvent* event);

  public slots:
    /** switch argument for slot selection by menu or toolbar ID */
    void commandCallback(int id_);
    /** switch argument for Statusbar help entries on slot selection. Add your ID's help here for toolbars and menubar entries. */
    void statusCallback(int id_);
    /** open a new application window by creating a new instance of KColorEditApp */
    void slotFileNewWindow();
    /** clears the document in the actual view to reuse it as the new document */
    void slotFileNew();
    /** open a file and load it into the document*/
    void slotFileOpen();
    /** opens a file from the recent files menu */
    void slotFileOpenRecent(int id_);
    /** save a document */
    void slotFileSave();
    /** save a document by a new filename
     *  @return whether the file has been saved
     */
    bool slotFileSaveAs();
    /** asks for saving if the file is modified, then closes the actual file and window*/
    void slotFileClose();
    /** print the actual file */
    void slotFilePrint();
    /** closes all open windows by calling close() on each memberList item until the list is empty, then quits the application.
     * If queryClose() returns false because the user canceled the saveModified() dialog, the closing breaks.
     */
    void slotFileQuit();
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
    void slotColorCopy();
    /** pastes a color from clipboard
     */
    void slotColorPaste();
    /** toggles the color names view
     */
    void slotViewColorNames();
    /** toggles the toolbar
     */
    void slotViewToolBar();
    /** toggles the statusbar
     */
    void slotViewStatusBar();
    /** changes the statusbar contents for the standard label permanently, used to indicate current actions.
     * @param text the text that is displayed in the statusbar
     */
    void slotStatusMsg(const QString &text);
    /** changes the status message of the whole statusbar for two seconds, then restores the last status. This is used to display
     * statusbar messages that give information about actions for toolbar icons and menuentries.
     * @param text the text that is displayed in the statusbar
     */
    void slotStatusHelpMsg(const QString &text);

  private:
    /** contains the recently used filenames */
    QStrList recentFiles;

    /** the configuration object of the application */
    KConfig *config;
    /** the key accelerator container */
    KAccel *keyAccel;
    /** file_menu contains all items of the menubar entry "File" */
    QPopupMenu *fileMenu;
    /** the recent file menu containing the last five opened files */
    QPopupMenu *recentFilesMenu;
    /** edit_menu contains all items of the menubar entry "Edit" */
    QPopupMenu *editMenu;
    /** Color menu contains all items of the menu bar entry "Color" */
    QPopupMenu *colorMenu;
    /** view_menu contains all items of the menubar entry "View" */
    QPopupMenu *viewMenu;
    /** help_menu contains all items of the menubar entry "Help" */
    QPopupMenu *helpMenu_;
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
