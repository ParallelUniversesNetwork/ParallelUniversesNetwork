CLEANFILES = *~
MAINTAINERCLEANFILES = Makefile.in

AM_CXXFLAGS = @AM_CXXFLAGS@

lib_LTLIBRARIES = libpunmesonmixing.la
libpunmesonmixing_la_SOURCES = \
    bq-mixing.cc bq-mixing.hh \
	observables.cc observables.hh
libpunmesonmixing_la_CXXFLAGS = $(AM_CXXFLAGS) $(GSL_CXXFLAGS)
libpunmesonmixing_la_LDFLAGS = $(GSL_LDFLAGS)
libpunmesonmixing_la_LIBADD = \
	$(top_builddir)/pun/utils/libpunutils.la \
	$(top_builddir)/pun/maths/libpunmaths.la \
	$(top_builddir)/pun/models/libpunmodels.la \
	-lgslcblas \
	-lgsl

include_pun_mesonmixingdir = $(includedir)/pun/meson-mixing
include_pun_mesonmixing_HEADERS = \
	bq-mixing.hh \
	observables.hh

EXTRA_DIST =

AM_TESTS_ENVIRONMENT = \
	export pun_TESTS_PARAMETERS="$(top_srcdir)/pun/parameters";

TESTS = \
    bq-mixing_TEST

LDADD = \
	$(top_builddir)/test/libpuntest.a \
	libpunmesonmixing.la \
	$(top_builddir)/pun/utils/libpunutils.la \
	$(top_builddir)/pun/libpun.la

check_PROGRAMS = $(TESTS)
bq_mixing_TEST_SOURCES = bq-mixing_TEST.cc