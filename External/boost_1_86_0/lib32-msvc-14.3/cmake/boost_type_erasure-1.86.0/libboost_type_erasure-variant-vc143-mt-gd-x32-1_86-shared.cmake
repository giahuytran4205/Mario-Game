# Generated by Boost 1.86.0

# address-model=32

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
  _BOOST_SKIPPED("boost_type_erasure-vc143-mt-gd-x32-1_86.lib" "32 bit, need 64")
  return()
endif()

# layout=versioned

# toolset=vc143

if(Boost_COMPILER)
  if(NOT "vc143" IN_LIST Boost_COMPILER AND NOT "-vc143" IN_LIST Boost_COMPILER)
    _BOOST_SKIPPED("boost_type_erasure-vc143-mt-gd-x32-1_86.lib" "vc143, Boost_COMPILER=${Boost_COMPILER}")
    return()
  endif()
else()
  if(BOOST_DETECTED_TOOLSET AND NOT BOOST_DETECTED_TOOLSET STREQUAL "vc143")
    _BOOST_SKIPPED("boost_type_erasure-vc143-mt-gd-x32-1_86.lib" "vc143, detected ${BOOST_DETECTED_TOOLSET}, set Boost_COMPILER to override")
    return()
  endif()
endif()

# link=shared

if(DEFINED Boost_USE_STATIC_LIBS)
  if(Boost_USE_STATIC_LIBS)
    _BOOST_SKIPPED("boost_type_erasure-vc143-mt-gd-x32-1_86.lib" "shared, Boost_USE_STATIC_LIBS=${Boost_USE_STATIC_LIBS}")
    return()
  endif()
else()
  if(WIN32 AND NOT _BOOST_SINGLE_VARIANT)
    _BOOST_SKIPPED("boost_type_erasure-vc143-mt-gd-x32-1_86.lib" "shared, default on Windows is static, set Boost_USE_STATIC_LIBS=OFF to override")
    return()
  endif()
endif()

# runtime-link=shared

if(Boost_USE_STATIC_RUNTIME)
  _BOOST_SKIPPED("boost_type_erasure-vc143-mt-gd-x32-1_86.lib" "shared runtime, Boost_USE_STATIC_RUNTIME=${Boost_USE_STATIC_RUNTIME}")
  return()
endif()

# runtime-debugging=on

if(NOT "${Boost_USE_DEBUG_RUNTIME}" STREQUAL "" AND NOT Boost_USE_DEBUG_RUNTIME)
  _BOOST_SKIPPED("boost_type_erasure-vc143-mt-gd-x32-1_86.lib" "debug runtime, Boost_USE_DEBUG_RUNTIME=${Boost_USE_DEBUG_RUNTIME}")
  return()
endif()

# threading=multi

if(DEFINED Boost_USE_MULTITHREADED AND NOT Boost_USE_MULTITHREADED)
  _BOOST_SKIPPED("boost_type_erasure-vc143-mt-gd-x32-1_86.lib" "multithreaded, Boost_USE_MULTITHREADED=${Boost_USE_MULTITHREADED}")
  return()
endif()

# variant=debug

if(NOT "${Boost_USE_DEBUG_LIBS}" STREQUAL "" AND NOT Boost_USE_DEBUG_LIBS)
  _BOOST_SKIPPED("boost_type_erasure-vc143-mt-gd-x32-1_86.lib" "debug, Boost_USE_DEBUG_LIBS=${Boost_USE_DEBUG_LIBS}")
  return()
endif()

if(Boost_VERBOSE OR Boost_DEBUG)
  message(STATUS "  [x] boost_type_erasure-vc143-mt-gd-x32-1_86.lib")
endif()

# Create imported target Boost::type_erasure

if(NOT TARGET Boost::type_erasure)
  add_library(Boost::type_erasure SHARED IMPORTED)

  set_target_properties(Boost::type_erasure PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${_BOOST_INCLUDEDIR}"
    INTERFACE_COMPILE_DEFINITIONS "BOOST_TYPE_ERASURE_NO_LIB"
  )
endif()

# Target file name: boost_type_erasure-vc143-mt-gd-x32-1_86.lib

get_target_property(__boost_imploc Boost::type_erasure IMPORTED_IMPLIB_DEBUG)
if(__boost_imploc)
  message(SEND_ERROR "Target Boost::type_erasure already has an imported location '${__boost_imploc}', which is being overwritten with '${_BOOST_LIBDIR}/boost_type_erasure-vc143-mt-gd-x32-1_86.lib'")
endif()
unset(__boost_imploc)

set_property(TARGET Boost::type_erasure APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)

set_target_properties(Boost::type_erasure PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG CXX
  IMPORTED_IMPLIB_DEBUG "${_BOOST_LIBDIR}/boost_type_erasure-vc143-mt-gd-x32-1_86.lib"
  )

set_target_properties(Boost::type_erasure PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_BOOST_LIBDIR}/boost_type_erasure-vc143-mt-gd-x32-1_86.dll"
  )

set_property(TARGET Boost::type_erasure APPEND
  PROPERTY INTERFACE_COMPILE_DEFINITIONS "BOOST_TYPE_ERASURE_DYN_LINK"
  )

list(APPEND _BOOST_TYPE_ERASURE_DEPS chrono thread headers)
