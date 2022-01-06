CLEANFILES = \
	*~

MAINTAINERCLEANFILES = Makefile.in

if pun_ENABLE_PYTHON

bin_SCRIPTS = \
	pun-analysis \
	pun-list-references \
	pun-make-constraint \
	pun-merge-mcmc \
	pun-plot \
	pun-plot-1d \
	pun-plot-2d \
	pun-print-modes \
	pun-print-uncertainty

AM_TESTS_ENVIRONMENT = \
			 export pun_TESTS_CONSTRAINTS="$(top_srcdir)/pun/constraints"; \
			 export pun_TESTS_PARAMETERS="$(top_srcdir)/pun/parameters"; \
			 export PYTHONPATH="$(top_builddir)/python/.libs/:$(top_srcdir)/python"; \
			 export PYTHON="$(PYTHON)"; \
			 export SOURCE_DIR="$(abs_srcdir)";

LOG_COMPILER="/bin/bash"
TESTS = \
	pun-analysis_TEST

endif

EXTRA_DIST = \
	pun-analysis \
	pun-list-references \
	pun-make-constraint \
	pun-merge-mcmc \
	pun-plot \
	pun-plot-1d \
	pun-plot-2d \
	pun-print-modes \
	pun-print-uncertainty \
	pun-analysis_TEST \
	pun-analysis_TEST.d/analysis.yaml
