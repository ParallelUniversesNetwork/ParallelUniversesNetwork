CLEANFILES = \
	*~
MAINTAINERCLEANFILES = Makefile.in

AM_CXXFLAGS = @AM_CXXFLAGS@
AM_LDFLAGS = @AM_LDFLAGS@

lib_LTLIBRARIES = libpunmaths.la
libpunmaths_la_SOURCES = \
	complex.hh \
	derivative.cc derivative.hh \
	gsl-interface.hh \
	integrate.cc integrate.hh integrate-impl.hh \
	integrate-cubature.cc integrate-cubature.hh \
	matrix.hh \
	polylog.cc polylog.hh \
	power-of.hh \
	szego-polynomial.hh

libpunmaths_la_LIBADD = \
	-lgsl -lgslcblas -lm
libpunmaths_la_CXXFLAGS = $(AM_CXXFLAGS) \
	-Dpun_DATADIR='"$(datadir)"' \
	$(GSL_CXXFLAGS)
libpunmaths_la_LDFLAGS = $(AM_LDFLAGS) $(GSL_LDFLAGS)

EXTRA_DIST = \
	polylog_TEST_dilog.bin \
	polylog_TEST_trilog.bin \
	polylog_TEST_z.bin

include_pun_utilsdir = $(includedir)/pun/utils
include_pun_utils_HEADERS = \
	complex.hh \
	derivative.hh \
	gsl-interface.hh \
	integrate.hh \
	integrate-cubature.hh \
	matrix.hh \
	polylog.hh \
	power-of.hh \
	szego-polynomial.hh

AM_TESTS_ENVIRONMENT = \
	export pun_TESTS_PARAMETERS="$(top_srcdir)/pun/parameters";

TESTS = \
	derivative_TEST \
	gsl-interface_TEST \
	integrate_TEST \
	matrix_TEST \
	polylog_TEST \
	power_of_TEST \
	szego-polynomial_TEST
LDADD = \
	$(top_builddir)/test/libpuntest.a \
	libpunmaths.la \
	$(top_builddir)/pun/maths/libpunmaths.la \
	$(top_builddir)/pun/utils/libpunutils.la \
	$(top_builddir)/pun/libpun.la

check_PROGRAMS = $(TESTS)

derivative_TEST_SOURCES = derivative_TEST.cc

gsl_interface_TEST_SOURCES = gsl-interface_TEST.cc

integrate_TEST_SOURCES = integrate_TEST.cc
integrate_TEST_CXXFLAGS = $(AM_CXXFLAGS) $(GSL_CXXFLAGS)
integrate_TEST_LDFLAGS = $(GSL_LDFLAGS)

matrix_TEST_SOURCES = matrix_TEST.cc

polylog_TEST_SOURCES = polylog_TEST.cc

power_of_TEST_SOURCES = power-of_TEST.cc

szego_polynomial_TEST_SOURCES = szego-polynomial_TEST.cc
