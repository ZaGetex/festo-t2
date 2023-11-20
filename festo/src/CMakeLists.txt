project(src)

set(SOURCE_FILES
        dummy.cpp dummy.h
## Dummy-Dateien können gelöscht werden, sobald neue Datien hier hinzugefügt wurden
)

add_library(src STATIC ${SOURCE_FILES})