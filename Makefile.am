SUBDIRS = data include src

bomberguy_docdir = ${prefix}/share/doc/bomberclone
bomberguy_doc_DATA = \
	README\
	COPYING\
	AUTHORS\
	ChangeLog\
	INSTALL\
	NEWS\
	bomberclone.nsi

EXTRA_DIST = bomberclone.prj $(bomberguy_doc_DATA)

# Copy all the spec files. Of cource, only one is actually used.
dist-hook:
	for specfile in *.spec; do \
		if test -f $$specfile; then \
			cp -p $$specfile $(distdir); \
		fi \
	done
