# File generated by kdevelop's qmake manager. 
# ------------------------------------------- 
# Subdir relative project main directory: ./libraries/yade-lib-gui-qt
# Target is a library:  QtGUI

FORMS += YadeQtGeneratedMainWindow.ui \
         QtFileGeneratorController.ui \
         QtGeneratedSimulationController.ui \
         QtGeneratedMessageDialog.ui \
         QtGeneratedEngineEditor.ui \
         QtGeneratedCodeGenerator.ui 
HEADERS += QtGUI.hpp \
           GLViewer.hpp \
           YadeQtMainWindow.hpp \
           QtFileGenerator.hpp \
           SimulationController.hpp \
           QGLThread.hpp \
           SimulationControllerUpdater.hpp \
           MessageDialog.hpp \
           FileDialog.hpp \
           QtEngineEditor.hpp \
           GLEngineEditor.hpp \
           QtCodeGenerator.hpp 
SOURCES += QtGUI.cpp \
           GLViewer.cpp \
           YadeQtMainWindow.cpp \
           QtFileGenerator.cpp \
           SimulationController.cpp \
           QGLThread.cpp \
           SimulationControllerUpdater.cpp \
           MessageDialog.cpp \
           FileDialog.cpp \
           QtEngineEditor.cpp \
           GLEngineEditor.cpp \
           QtCodeGenerator.cpp 
QtGeneratedSimulationController.ui.target = QtGeneratedSimulationController.ui
QtGeneratedFrontEnd.ui.target = QtGeneratedFrontEnd.ui
QtGUISignalCatcher.ui.target = QtGUISignalCatcher.ui
QtFileGeneratorController.ui.target = QtFileGeneratorController.ui
LIBS += -lyade-lib-wm3-math \
-lyade-lib-multimethods \
-lyade-lib-factory \
-lyade-lib-opengl \
-lyade-lib-threads \
-lXMLManager \
-lyade-lib-serialization \
-lyade-lib-serialization-qt \
-lyade-lib-computational-geometry \
-lQGLViewer \
-lboost_date_time \
-lboost_filesystem \
-rdynamic
INCLUDEPATH += $(YADEINCLUDEPATH)
MOC_DIR = $(YADECOMPILATIONPATH)
UI_DIR = $(YADECOMPILATIONPATH)
OBJECTS_DIR = $(YADECOMPILATIONPATH)
QMAKE_LIBDIR = ../../libraries/yade-lib-wm3-math/$(YADEDYNLIBPATH) \
../../libraries/yade-lib-multimethods/$(YADEDYNLIBPATH) \
../../libraries/yade-lib-factory/$(YADEDYNLIBPATH) \
../../libraries/yade-lib-opengl/$(YADEDYNLIBPATH) \
../../libraries/yade-lib-threads/$(YADEDYNLIBPATH) \
../../libraries/yade-lib-serialization-xml/$(YADEDYNLIBPATH) \
../../libraries/yade-lib-serialization/$(YADEDYNLIBPATH) \
../../libraries/yade-lib-serialization-qt/$(YADEDYNLIBPATH) \
../../libraries/yade-lib-computational-geometry/$(YADEDYNLIBPATH) \
$(YADEDYNLIBPATH)
QMAKE_CXXFLAGS_RELEASE += -lpthread \
-pthread
QMAKE_CXXFLAGS_DEBUG += -lpthread \
-pthread
TARGET = QtGUI
DESTDIR = $(YADEDYNLIBPATH)
CONFIG += debug \
warn_on \
qt \
dll
TEMPLATE = lib
