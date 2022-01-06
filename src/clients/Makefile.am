CLEANFILES = *~
MAINTAINERCLEANFILES = Makefile.in

AM_CXXFLAGS = -I$(top_srcdir) -std=c++14 -Wall -Wextra -pedantic

noinst_LIBRARIES = libcli.a

libcli_a_SOURCES = \
	cli_dumper.cc cli_dumper.hh \
	cli_error.cc cli_error.hh \
	cli_group.cc cli_group.hh \
	cli_handler.cc cli_handler.hh \
	cli_section.cc cli_section.hh \
	cli_option.cc cli_option.hh \
	cli_visitor.cc cli_visitor.hh

bin_PROGRAMS = \
	pun-evaluate \
	pun-list-constraints \
	pun-list-observables \
	pun-list-parameters \
	pun-list-signal-pdfs \
	pun-print-polynomial

LDADD = \
	$(top_builddir)/pun/statistics/libpunstatistics.la \
	$(top_builddir)/pun/utils/libpunutils.la \
	$(top_builddir)/pun/maths/libpunmaths.la \
	$(top_builddir)/pun/models/libpunmodels.la \
	$(top_builddir)/pun/form-factors/libpunformfactors.la \
	$(top_builddir)/pun/b-decays/libpunbdecays.la \
	$(top_builddir)/pun/rare-b-decays/libpunrarebdecays.la \
	$(top_builddir)/pun/meson-mixing/libpunmesonmixing.la \
	$(top_builddir)/pun/libpun.la \
	libcli.a \
	-lboost_filesystem -lboost_system \
	$(YAMLCPP_LDFLAGS)

pun_evaluate_SOURCES = pun-evaluate.cc

pun_list_constraints_SOURCES = pun-list-constraints.cc
pun_list_constraints_CXXFLAGS = $(AM_CXXFLAGS) $(YAMLCPP_CXXFLAGS)

pun_list_observables_SOURCES = pun-list-observables.cc

pun_list_parameters_SOURCES = pun-list-parameters.cc

pun_list_signal_pdfs_SOURCES = pun-list-signal-pdfs.cc

pun_print_polynomial_SOURCES = pun-print-polynomial.cc