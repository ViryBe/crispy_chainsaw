SQL = sqlite3
TARGET = dummy.db

all: $(TARGET)

dummy.db: dummy.sql
	$(SQL) $@ < $<
