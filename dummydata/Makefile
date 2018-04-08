SQL = sqlite3
TARGET = dummy.db

all: $(TARGET)

dummy.db: dummy.sql
	$(SQL) $@ < $<

install:
	cp $(TARGET) ../crispy_chainsaw/
