find_path(NXS_INCLUDE_DIRS nexuscpp/nexuscpp.h)
find_library(NXS_LIBRARIES nexuscpp)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(NXS DEFAULT_MSG NXS_LIBRARIES NXS_INCLUDE_DIRS)