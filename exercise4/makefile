.SILENT:

do: compile run labels

compile:
	gcc -O3 -Wall -ansi defis4.c

run: compile
	./a.out

labels:
	python find_labels.py