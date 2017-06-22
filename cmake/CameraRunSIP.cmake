SET(INCLUDES)
FILE(GLOB sipfiles RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/sip" "${CMAKE_CURRENT_SOURCE_DIR}/sip/*.sip")
FOREACH(sipfile ${sipfiles})
	SET(INCLUDES 
	"${INCLUDES}
%Include ${sipfile}")
ENDFOREACH()

SET(IMPORTS 
"${IMPORTS}
%Import limacore.sip")

if(SIP_VERSION_STR VERSION_LESS "4.12")
	configure_file(${CMAKE_SOURCE_DIR}/sip/limamodules_before_4_12.sip.in sip/lima${NAME}.sip)
else()
	CONFIGURE_FILE(${CMAKE_SOURCE_DIR}/sip/limamodules.sip.in sip/lima${NAME}.sip)
endif()
SET(SIP_CONCAT_PARTS 1)
SET(SIP_INCLUDES ${SIP_INCLUDES}
    "${CMAKE_SOURCE_DIR}/third-party/Processlib/sip"
    "${CMAKE_BINARY_DIR}/sip/core"
    "${CMAKE_SOURCE_DIR}/third-party/Processlib/tasks/sip"
    "${CMAKE_SOURCE_DIR}/common/sip"
    "${CMAKE_SOURCE_DIR}/hardware/sip"
    "${CMAKE_SOURCE_DIR}/control/sip"
    "${CMAKE_SOURCE_DIR}/control/software_operation/sip"
    "${CMAKE_CURRENT_SOURCE_DIR}/sip")
set(SIP_DISABLE_FEATURES WITH_CONFIG)
set(SIP_CHECK_EXC ON)
ADD_SIP_PYTHON_MODULE(lima${NAME} ${CMAKE_CURRENT_BINARY_DIR}/sip/lima${NAME}.sip)
TARGET_INCLUDE_DIRECTORIES(python_module_lima${NAME} PRIVATE
                          ${PYTHON_INCLUDE_DIRS}
                          "${CMAKE_SOURCE_DIR}/sip"
                          "${CMAKE_SOURCE_DIR}/sip/core")
TARGET_LINK_LIBRARIES(python_module_lima${NAME} lima${NAME})
