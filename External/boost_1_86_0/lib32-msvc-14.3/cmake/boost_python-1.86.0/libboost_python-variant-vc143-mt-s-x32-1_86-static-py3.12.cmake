# Generated by Boost 1.86.0

# address-model=32

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
  _BOOST_SKIPPED("libboost_python312-vc143-mt-s-x32-1_86.lib" "32 bit, need 64")
  return()
endif()

# python=3.12

if(Boost_PYTHON_VERSION)
  string(REGEX REPLACE "([0-9]+[.][0-9]+)([.].*)?" "\\1" __boost_pyver ${Boost_PYTHON_VERSION})
  if(NOT __boost_pyver VERSION_EQUAL "3.12")
    _BOOST_SKIPPED("libboost_python312-vc143-mt-s-x32-1_86.lib" "3.12, Boost_PYTHON_VERSION=${Boost_PYTHON_VERSION}")
    return()
  endif()
endif()

if(Boost_PYTHON_VERSION_MAJOR)
  if(NOT "3.12" MATCHES "^${Boost_PYTHON_VERSION_MAJOR}[.]")
    _BOOST_SKIPPED("libboost_python312-vc143-mt-s-x32-1_86.lib" "3.12, Boost_PYTHON_VERSION_MAJOR=${Boost_PYTHON_VERSION_MAJOR}")
    return()
  endif()
endif()

# layout=versioned

# toolset=vc143

if(Boost_COMPILER)
  if(NOT "vc143" IN_LIST Boost_COMPILER AND NOT "-vc143" IN_LIST Boost_COMPILER)
    _BOOST_SKIPPED("libboost_python312-vc143-mt-s-x32-1_86.lib" "vc143, Boost_COMPILER=${Boost_COMPILER}")
    return()
  endif()
else()
  if(BOOST_DETECTED_TOOLSET AND NOT BOOST_DETECTED_TOOLSET STREQUAL "vc143")
    _BOOST_SKIPPED("libboost_python312-vc143-mt-s-x32-1_86.lib" "vc143, detected ${BOOST_DETECTED_TOOLSET}, set Boost_COMPILER to override")
    return()
  endif()
endif()

# link=static

if(DEFINED Boost_USE_STATIC_LIBS)
  if(NOT Boost_USE_STATIC_LIBS)
    _BOOST_SKIPPED("libboost_python312-vc143-mt-s-x32-1_86.lib" "static, Boost_USE_STATIC_LIBS=${Boost_USE_STATIC_LIBS}")
    return()
  endif()
else()
  if(NOT WIN32 AND NOT _BOOST_SINGLE_VARIANT)
    _BOOST_SKIPPED("libboost_python312-vc143-mt-s-x32-1_86.lib" "static, default is shared, set Boost_USE_STATIC_LIBS=ON to override")
    return()
  endif()
endif()

# runtime-link=static

if(NOT Boost_USE_STATIC_RUNTIME)
  _BOOST_SKIPPED("libboost_python312-vc143-mt-s-x32-1_86.lib" "static runtime, Boost_USE_STATIC_RUNTIME not ON")
  return()
endif()

# runtime-debugging=off

if(Boost_USE_DEBUG_RUNTIME)
  _BOOST_SKIPPED("libboost_python312-vc143-mt-s-x32-1_86.lib" "release runtime, Boost_USE_DEBUG_RUNTIME=${Boost_USE_DEBUG_RUNTIME}")
  return()
endif()

# threading=multi

if(DEFINED Boost_USE_MULTITHREADED AND NOT Boost_USE_MULTITHREADED)
  _BOOST_SKIPPED("libboost_python312-vc143-mt-s-x32-1_86.lib" "multithreaded, Boost_USE_MULTITHREADED=${Boost_USE_MULTITHREADED}")
  return()
endif()

# variant=release

if(NOT "${Boost_USE_RELEASE_LIBS}" STREQUAL "" AND NOT Boost_USE_RELEASE_LIBS)
  _BOOST_SKIPPED("libboost_python312-vc143-mt-s-x32-1_86.lib" "release, Boost_USE_RELEASE_LIBS=${Boost_USE_RELEASE_LIBS}")
  return()
endif()

if(Boost_VERBOSE OR Boost_DEBUG)
  message(STATUS "  [x] libboost_python312-vc143-mt-s-x32-1_86.lib")
endif()

if(NOT Boost_PYTHON_VERSION)
  if(Boost_DEBUG)
    message(STATUS "  Setting Boost_PYTHON_VERSION to 3.12")
  endif()
  set(Boost_PYTHON_VERSION "3.12")
endif()

# Create imported target Boost::python

if(NOT TARGET Boost::python)
  add_library(Boost::python STATIC IMPORTED)

  set_target_properties(Boost::python PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${_BOOST_INCLUDEDIR}"
    INTERFACE_COMPILE_DEFINITIONS "BOOST_PYTHON_NO_LIB"
  )
endif()

# Target file name: libboost_python312-vc143-mt-s-x32-1_86.lib

get_target_property(__boost_imploc Boost::python IMPORTED_LOCATION_RELEASE)
if(__boost_imploc)
  message(SEND_ERROR "Target Boost::python already has an imported location '${__boost_imploc}', which is being overwritten with '${_BOOST_LIBDIR}/libboost_python312-vc143-mt-s-x32-1_86.lib'")
endif()
unset(__boost_imploc)

set_property(TARGET Boost::python APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)

set_target_properties(Boost::python PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE CXX
  IMPORTED_LOCATION_RELEASE "${_BOOST_LIBDIR}/libboost_python312-vc143-mt-s-x32-1_86.lib"
  )

set_target_properties(Boost::python PROPERTIES
  MAP_IMPORTED_CONFIG_MINSIZEREL Release
  MAP_IMPORTED_CONFIG_RELWITHDEBINFO Release
  )

list(APPEND _BOOST_PYTHON_DEPS headers)
