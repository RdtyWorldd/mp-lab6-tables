set(target ${PROJECT_LIB})

set(headers Table.h ArrayTable.h ScanTable.h SortTable.h HashTable.h ArrayHashTable.h)

add_library(${target} STATIC ${headers})
set_target_properties(${target} PROPERTIES LINKER_LANGUAGE CXX)