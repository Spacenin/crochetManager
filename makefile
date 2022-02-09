CFLAGS = -g -o crochetManager
COMP = gcc

all: crochetManager

run: crochetManager
	./crochetManager

crochetManager: src/crochetManager.c src/menu.c
	$(COMP) $? $(CFLAGS)
	$(move)

clean:
	rm crochetManager
	