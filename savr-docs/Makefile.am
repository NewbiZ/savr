SPHINXOPTS    = -q
SPHINXBUILD   = sphinx-build
PAPER         =
BUILDDIR      = $(top_builddir)/savr-docs/build
SOURCEDIR     = $(top_srcdir)/savr-docs/source

PAPEROPT_a4     = -D latex_paper_size=a4
PAPEROPT_letter = -D latex_paper_size=letter
ALLSPHINXOPTS   = -d $(BUILDDIR)/doctrees $(PAPEROPT_$(PAPER)) $(SPHINXOPTS) $(SOURCEDIR)
I18NSPHINXOPTS  = $(PAPEROPT_$(PAPER)) $(SPHINXOPTS) $(SOURCEDIR)

.PHONY: help clean html pdf text man changes linkcheck gettext

if HAVE_SPHINX
all: html
else
all:
endif

clean:
	-rm -rf $(BUILDDIR)/*

html:
	$(AM_V_GEN)$(SPHINXBUILD) -b html $(ALLSPHINXOPTS) $(BUILDDIR)/html

pdf:
	$(AM_V_GEN)$(SPHINXBUILD) -b latex $(ALLSPHINXOPTS) $(BUILDDIR)/latex
	$(AM_V_GEN)$(MAKE) -C $(BUILDDIR)/latex all-pdf

text:
	$(AM_V_GEN)$(SPHINXBUILD) -b text $(ALLSPHINXOPTS) $(BUILDDIR)/text

man:
	$(AM_V_GEN)$(SPHINXBUILD) -b man $(ALLSPHINXOPTS) $(BUILDDIR)/man

texinfo:
	$(SPHINXBUILD) -b texinfo $(ALLSPHINXOPTS) $(BUILDDIR)/texinfo

info:
	$(SPHINXBUILD) -b texinfo $(ALLSPHINXOPTS) $(BUILDDIR)/texinfo

gettext:
	$(SPHINXBUILD) -b gettext $(I18NSPHINXOPTS) $(BUILDDIR)/locale

changes:
	$(SPHINXBUILD) -b changes $(ALLSPHINXOPTS) $(BUILDDIR)/changes

linkcheck:
	$(SPHINXBUILD) -b linkcheck $(ALLSPHINXOPTS) $(BUILDDIR)/linkcheck
