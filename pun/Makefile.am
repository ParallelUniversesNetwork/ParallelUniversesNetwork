CLEANFILES = \
	*~ \
	references_TEST
MAINTAINERCLEANFILES = Makefile.in

SUBDIRS = \
	constraints \
	parameters \
	utils \
	maths \
	models \
	statistics \
	form-factors \
	rare-b-decays \
	b-decays \
	meson-mixing \
	.

AM_CXXFLAGS = @AM_CXXFLAGS@
AM_LDFLAGS = @AM_LDFLAGS@

lib_LTLIBRARIES = libpun.la
libpun_la_SOURCES = \
	constraint.cc constraint.hh \
	observable.cc observable.hh observable-fwd.hh observable-impl.hh \
	reference.cc reference.hh \
	signal-pdf.cc signal-pdf.hh
libpun_la_CXXFLAGS = $(AM_CXXFLAGS) \
	-Dpun_DATADIR='"$(datadir)"' \
	$(GSL_CXXFLAGS) \
	$(YAMLCPP_CXXFLAGS)
libpun_la_LDFLAGS = $(AM_LDFLAGS) $(GSL_LDFLAGS) $(YAMLCPP_LDFLAGS)
libpun_la_LIBADD = \
	$(top_builddir)/pun/utils/libpunutils.la \
	$(top_builddir)/pun/statistics/libpunstatistics.la \
	$(top_builddir)/pun/form-factors/libpunformfactors.la \
	$(top_builddir)/pun/b-decays/libpunbdecays.la \
	$(top_builddir)/pun/rare-b-decays/libpunrarebdecays.la \
	$(top_builddir)/pun/meson-mixing/libpunmesonmixing.la

include_pundir = $(includedir)/pun
include_pun_HEADERS = \
	constraint.hh \
	observable.hh \
	reference.hh \
	signal-pdf.hh

AM_TESTS_ENVIRONMENT = \
	export pun_TESTS_CONSTRAINTS="$(top_srcdir)/pun/constraints"; \
	export pun_TESTS_PARAMETERS="$(top_srcdir)/pun/parameters"; \
	export pun_TESTS_REFERENCES="$(top_srcdir)/pun/";

TESTS = \
	constraint_TEST \
	observable_TEST \
	reference_TEST

LDADD = \
	$(top_builddir)/test/libpuntest.a \
	$(top_builddir)/pun/utils/libpunutils.la \
	$(top_builddir)/pun/b-decays/libpunbdecays.la \
	$(top_builddir)/pun/form-factors/libpunformfactors.la \
	$(top_builddir)/pun/rare-b-decays/libpunrarebdecays.la \
	$(top_builddir)/pun/statistics/libpunstatistics.la \
	$(top_builddir)/pun/libpun.la

check_PROGRAMS = \
	constraint_TEST \
	observable_TEST \
	reference_TEST

constraint_TEST_SOURCES = constraint_TEST.cc
constraint_TEST_CXXFLAGS = $(AM_CXXFLAGS) $(GSL_CXXFLAGS)
constraint_TEST_LDADD = $(LDADD) -lyaml-cpp

observable_TEST_SOURCES = observable_TEST.cc
observable_TEST_CXXFLAGS = $(AM_CXXFLAGS) $(GSL_CXXFLAGS)
observable_TEST_LDADD = $(LDADD) -lyaml-cpp

reference_TEST_SOURCES = reference_TEST.cc
reference_TEST_CXXFLAGS = $(AM_CXXFLAGS) $(GSL_CXXFLAGS)
reference_TEST_LDADD = $(LDADD) -lyaml-cpp

pkgdata_DATA = references.yaml
EXTRA_DIST = \
	references.yaml
