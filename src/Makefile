.PHONY: all clean

CC=gcc
FLAGS=-Wall -Wextra -Werror -std=c11 -fsanitize=address
LDFLAGS=$(shell pkg-config --cflags --libs check)


GCOVFLAGS=-fprofile-arcs -ftest-coverage


SRCS=$(wildcard backend/*.c)
GCOVNAME=coverage

all: clean debug

debug: clean
	$(CC) $(FLAGS) -g $(SRCS)
	./a.out

test: clean
	$(CC) $(LDFLAGS) $(SRCS) backend/tests/test.c -o test
	./test

gcov_report: add_coverage_flag
	$(CC) $(LDFLAGS) $(GCOVFLAGS) $(SRCS) backend/tests/test.c -o gcov_main
	./gcov_main
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory gcov_report
	open gcov_report/index.html
	
install: uninstall
	cd SmartCalc && cmake -B build . && cd build && make
	@open SmartCalc/build/SmartCalc.app

uninstall: clean
	rm -rf build* SmartCalc/build

dist: clean
	mkdir Archive_SmartCalc_v1.0
	cp Makefile backend/*.c backend/headers/*.h SmartCalc/*.cpp SmartCalc/*.h SmartCalc/*.h SmartCalc/*.qrc SmartCalc/*.css SmartCalc/*.ui Archive_SmartCalc_v1.0/
	tar cvzf Archive_SmartCalc_v1.0.tgz Archive_SmartCalc_v1.0/

clean:
	rm -rf *.o backend/*.o *.html *.gcda *.gcno *.css *.a *.gcov *.info *.out *.cfg *.txt gcov_main test rm -rf *.dSYM
	rm -rf test_build gcov_report Archive* *.log *.dvi

style_check:
	clang-format --style=Google -n $(SRCS) *.c *.h backend/tests/*.c *.h backend/headers/*.h SmartCalc/*.cpp *.h
	
style:
	clang-format --style=Google -i $(SRCS) *.c *.h backend/tests/*.c *.h backend/headers/*.h SmartCalc/*.cpp *.h 

linter:
	python3 ../cpplint.py --extensions=c *.c *.h tests/*.c tests/*.h

dvi:
	texi2dvi --shell-escape doc.texi 


add_coverage_flag:
	$(eval FLAGS += --coverage)