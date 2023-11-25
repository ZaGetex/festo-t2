project(src)

set(SOURCE_FILES
        Motor.cpp
        Motor.h
        FSM.cpp
        FSM.h
        ## Dummy-Dateien können gelöscht werden, sobald neue Datien hier hinzugefügt wurden
)

add_library(src STATIC ${SOURCE_FILES}
        ../main.cpp)