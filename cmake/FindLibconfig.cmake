find_library(LIBCONFIG_LIBRARIES libconfig++)
find_path(LIBCONFIG_INCLUDE_DIRS libconfig.h++)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(config DEFAULT_MSG LIBCONFIG_LIBRARIES LIBCONFIG_INCLUDE_DIRS)
