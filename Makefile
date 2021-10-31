EXTENSION = repeat
MODULE_big = repeat
DATA = repeat--0.0.1.sql
OBJS = repeat.o 
PG_CONFIG = pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)
$(OBJS): CFLAGS += $(PERMIT_DECLARATION_AFTER_STATEMENT)
