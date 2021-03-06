include_directories (
  ${KDE4_INCLUDES}
  ${QT_INCLUDES}

  ${CMAKE_CURRENT_SOURCE_DIR}/core/
  ${CMAKE_CURRENT_SOURCE_DIR}/itemviews
  ${CMAKE_CURRENT_SOURCE_DIR}/widgets/colorselectors/kdeselector
  ${CMAKE_CURRENT_SOURCE_DIR}/widgets/colorselectors/gtkselector
  ${CMAKE_CURRENT_SOURCE_DIR}/widgets/colorselectors/blenderselector
  ${CMAKE_CURRENT_SOURCE_DIR}/widgets/colorselectors/builderselector
  ${CMAKE_CURRENT_SOURCE_DIR}/widgets/colorselectors
  ${CMAKE_CURRENT_SOURCE_DIR}/widgets/colorinfo
  ${CMAKE_CURRENT_SOURCE_DIR}/widgets
  ${CMAKE_CURRENT_SOURCE_DIR}/dialog
  ${CMAKE_CURRENT_SOURCE_DIR}/app
)

set (
  kcoloredit_SRCS

  core/colorutil.cpp
  core/palette.cpp
  core/palettemodel.cpp
  core/palettedocument.cpp
  itemviews/palettedelegate.cpp
  itemviews/palettedetailview.cpp
  itemviews/palettebriefview.cpp
  widgets/colorselectors/kdeselector/rectanglecolorwidget.cpp
  widgets/colorselectors/kdeselector/kdecolorselector.cpp
  widgets/colorselectors/gtkselector/trianglecolorwidget.cpp
  widgets/colorselectors/gtkselector/gtkcolorselector.cpp
  widgets/colorselectors/blenderselector/blendercolorselector.cpp
  widgets/colorselectors/builderselector/buildercolorselector.cpp
  widgets/colorselectors/colorselector.cpp
  widgets/colortoolwidget.cpp
  widgets/colorinfo/colorinfovisual.cpp
  widgets/colorinfo/colorinfotext.cpp
  widgets/palettedelegateeditors.cpp
  widgets/palettedescriptionwidget.cpp
  widgets/colorwidget.cpp
  widgets/multipagewidget.cpp
  widgets/kcoloreditwidget.cpp
  dialog/palettedialog.cpp
  app/kcoloredit.cpp
  app/main.cpp
)

kde4_add_ui_files (
  kcoloredit_SRCS

  widgets/colorselectors/builderselector/builderwidget.ui
  settings/builderconfiguration.ui
)

kde4_add_kcfg_files ( kcoloredit_SRCS settings/kcoloredit_settings.kcfgc)

kde4_add_executable ( kcoloredit ${kcoloredit_SRCS} )

target_link_libraries ( kcoloredit ${KDE4_KFILE_LIBS} ${X11_LIBRARIES})

install (TARGETS kcoloredit  ${INSTALL_TARGETS_DEFAULT_ARGS} )
