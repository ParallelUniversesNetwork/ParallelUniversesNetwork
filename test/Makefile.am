CLEANFILES = *~
MAINTAINERCLEANFILES = Makefile.in

AM_CXXFLAGS = -I$(top_srcdir) -std=c++0x -Wall -Wextra -pedantic

noinst_LIBRARIES = libpuntest.a

libpuntest_a_SOURCES = \
	test.cc test.hh

TESTS = \
	test_TEST
LDADD = libpuntest.a \
	$(top_builddir)/pun/utils/libpunutils.la \
	$(top_builddir)/pun/libpun.la

check_PROGRAMS = $(TESTS)

test_TEST_SOURCES = test_TEST.cc
