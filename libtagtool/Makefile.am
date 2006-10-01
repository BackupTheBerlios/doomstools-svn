## library 

lib_LIBRARIES = libtagtool.a
libtagtool_a_SOURCES = lib/libtagtool.c lib/libtagtool-priv.c

## binaries test

bin_PROGRAMS = tag_create \
		tag_init \
		tag_put \
		tag_info \
		tag_list \
		tag_search \
		tag_rename \
		tag_delete \
		tag_remove

commonLDFLAGS = -ltagtool -L.
commonDEPENDENCIES = libtagtool.a
commonLDADD = -L. -ltagtool -lstdtool -lsqlite3
commonCFLAGS = -Ilib/ -Wall

tag_create_LDFLAGS = $(commonLDFLAGS)
tag_create_LDADD = $(commonLDADD)
tag_create_CFLAGS = $(commonCFLAGS)
tag_create_DEPENDENCIES = $(commonDEPENDENCIES)
tag_create_SOURCES = bin/tag_create.c

tag_init_LDFLAGS = $(commonLDFLAGS)
tag_init_LDADD = $(commonLDADD)
tag_init_CFLAGS = $(commonCFLAGS)
tag_init_DEPENDENCIES = $(commonDEPENDENCIES)
tag_init_SOURCES = bin/tag_init.c

tag_put_LDFLAGS = $(commonLDFLAGS)
tag_put_LDADD = $(commonLDADD)
tag_put_CFLAGS = $(commonCFLAGS)
tag_put_DEPENDENCIES = $(commonDEPENDENCIES)
tag_put_SOURCES = bin/tag_put.c

tag_info_LDFLAGS = $(commonLDFLAGS)
tag_info_LDADD = $(commonLDADD)
tag_info_CFLAGS = $(commonCFLAGS)
tag_info_DEPENDENCIES = $(commonDEPENDENCIES)
tag_info_SOURCES = bin/tag_info.c

tag_list_LDFLAGS = $(commonLDFLAGS)
tag_list_LDADD = $(commonLDADD)
tag_list_CFLAGS = $(commonCFLAGS)
tag_list_DEPENDENCIES = $(commonDEPENDENCIES)
tag_list_SOURCES = bin/tag_list.c

tag_rename_LDFLAGS = $(commonLDFLAGS)
tag_rename_LDADD = $(commonLDADD)
tag_rename_CFLAGS = $(commonCFLAGS)
tag_rename_DEPENDENCIES = $(commonDEPENDENCIES)
tag_rename_SOURCES = bin/tag_rename.c

tag_search_LDFLAGS = $(commonLDFLAGS)
tag_search_LDADD = $(commonLDADD)
tag_search_CFLAGS = $(commonCFLAGS)
tag_search_DEPENDENCIES = $(commonDEPENDENCIES)
tag_search_SOURCES = bin/tag_search.c

tag_remove_LDFLAGS = $(commonLDFLAGS)
tag_remove_LDADD = $(commonLDADD)
tag_remove_CFLAGS = $(commonCFLAGS)
tag_remove_DEPENDENCIES = $(commonDEPENDENCIES)
tag_remove_SOURCES = bin/tag_remove.c

tag_delete_LDFLAGS = $(commonLDFLAGS)
tag_delete_LDADD = $(commonLDADD)
tag_delete_CFLAGS = $(commonCFLAGS)
tag_delete_DEPENDENCIES = $(commonDEPENDENCIES)
tag_delete_SOURCES = bin/tag_delete.c
