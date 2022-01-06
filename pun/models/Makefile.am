CLEANFILES = \
	*~
MAINTAINERCLEANFILES = Makefile.in

AM_CXXFLAGS = @AM_CXXFLAGS@
AM_LDFLAGS = @AM_LDFLAGS@

lib_LTLIBRARIES = libpunmodels.la
libpunmodels_la_SOURCES = \
	ckm.cc ckm.hh \
	model.cc model.hh \
	standard-model.cc standard-model.hh \
	top-loops.cc top-loops.hh \
	wet.cc wet.hh \
	wilson-coefficients.cc wilson-coefficients.hh

libpunmodels_la_LIBADD = \
	-lgsl -lgslcblas -lm
libpunmodels_la_CXXFLAGS = $(AM_CXXFLAGS) \
	-Dpun_DATADIR='"$(datadir)"' \
	$(GSL_CXXFLAGS)
libpunmodels_la_LDFLAGS = $(AM_LDFLAGS) $(GSL_LDFLAGS)

include_pun_modelsdir = $(includedir)/pun/models
include_pun_models_HEADERS = \
	ckm.hh \
	model.hh \
	standard-model.hh \
	wet.hh \
	wilson-coefficients.hh

AM_TESTS_ENVIRONMENT = \
	export pun_TESTS_PARAMETERS="$(top_srcdir)/pun/parameters";

TESTS = \
	ckm_TEST \
	standard_model_TEST \
	top-loops_TEST \
	wet_TEST \
	wilson-coefficients_TEST
LDADD = \
	$(top_builddir)/test/libpuntest.a \
	libpunmodels.la \
	$(top_builddir)/pun/utils/libpunutils.la \
	$(top_builddir)/pun/libpun.la

check_PROGRAMS = $(TESTS)

ckm_TEST_SOURCES = ckm_TEST.cc

standard_model_TEST_SOURCES = standard-model_TEST.cc

top_loops_TEST_SOURCES = top-loops_TEST.cc

wet_TEST_SOURCES = wet_TEST.cc

wilson_coefficients_TEST_SOURCES = wilson-coefficients_TEST.cc
wilson_coefficients_TEST_CXXFLAGS = $(AM_CXXFLAGS) $(GSL_CXXFLAGS)
wilson_coefficients_TEST_LDFLAGS = $(GSL_LDFLAGS)

