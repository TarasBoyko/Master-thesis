
#-------------------------------------------------
#
# Project created by QtCreator 2016-02-01T10:32:05
#
#-------------------------------------------------

QT       += multimedia
QT       += core gui
CONFIG   += c++11
QMAKE_CXXFLAGS_RELEASE *= -O3

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Framework
TEMPLATE = app


SOURCES += main.cpp\
    BaseButton/BaseButton.cpp \
    BaseButton/EditSizeFrame/B_Square.cpp \
    BaseButton/EditSizeFrame/L_Square.cpp \
    BaseButton/EditSizeFrame/LB_Square.cpp \
    BaseButton/EditSizeFrame/LT_Square.cpp \
    BaseButton/EditSizeFrame/R_Square.cpp \
    BaseButton/EditSizeFrame/RB_Square.cpp \
    BaseButton/EditSizeFrame/RT_Square.cpp \
    BaseButton/EditSizeFrame/Square.cpp \
    BaseButton/EditSizeFrame/T_Square.cpp \
    Function/t_FunctionSticker.cpp \
    Function/t_FunctionStickerScrollArea.cpp \
    Navigation/AreaButton.cpp \
    GreenButton.cpp \
    SearchForm.cpp \
    Navigation/t_Navigator.cpp \
    BaseButton/EditingName.cpp \
    BaseButton/EditSizeFrame/EditSizeFrame.cpp \
    InfoStore.cpp \
    InteractiveButton.cpp \
    t_AppState.cpp \
    Function/FunctionForm.cpp \
    BackupNoteForm.cpp \
    FunctionalityForm/AbstractFunctionalityForm.cpp \
    FunctionalityForm/BaseFunctionalityForm.cpp \
    Navigation/AbstractAreaButton.cpp \
    Navigation/AreaButtonForm.cpp \
    Function/TextShortDescription.cpp \
    CustomWidgets/CustomErrorMsgBox.cpp \
    CustomWidgets/CustomWarringMsgBox.cpp

HEADERS  += \
    header.h \
    BaseButton/BaseButton.h \
    BaseButton/EditSizeFrame/B_Square.h \
    BaseButton/EditSizeFrame/L_Square.h \
    BaseButton/EditSizeFrame/LB_Square.h \
    BaseButton/EditSizeFrame/LT_Square.h \
    BaseButton/EditSizeFrame/R_Square.h \
    BaseButton/EditSizeFrame/RB_Square.h \
    BaseButton/EditSizeFrame/RT_Square.h \
    BaseButton/EditSizeFrame/Square.h \
    BaseButton/EditSizeFrame/T_Square.h \
    Function/t_FunctionSticker.h \
    Function/t_FunctionStickerScrollArea.h \
    Navigation/AreaButton.h \
    GreenButton.h \
    SearchForm.h \
    Navigation/t_Navigator.h \
    BaseButton/EditingName.h \
    BaseButton/EditSizeFrame/EditSizeFrame.h \
    InfoStore.h \
    InteractiveButton.h \
    t_AppState.h \
    Function/FunctionForm.h \
    BackupNoteForm.h \
    FunctionalityForm/AbstractFunctionalityForm.h \
    FunctionalityForm/BaseFunctionalityForm.h \
    Navigation/AbstractAreaButton.h \
    Navigation/AreaButtonForm.h \
    Function/TextShortDescription.h \
    CustomWidgets/CustomErrorMsgBox.h \
    CustomWidgets/CustomWarringMsgBox.h

FORMS    += \
    Function/t_FunctionSticker.ui \
    Function/t_FunctionStickerScrollArea.ui \
    SearchForm.ui \
    Function/FunctionForm.ui \
    BackupNoteForm.ui \
    FunctionalityForm/AbstractFunctionalityForm.ui \
    FunctionalityForm/BaseFunctionalityForm.ui \
    Navigation/AreaButtonForm.ui
