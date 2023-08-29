OS=$(shell uname)
CXX=g++ -std=c++17
SUBDIRS = s21_array s21_list s21_queue s21_stack s21_vector
ifeq ($(OS), Linux)
	CXXFLAGS=-lgtest -g -lpthread 
	LEAKS = valgrind --leak-check=full
else
	CXXFLAGS =-lgtest -lcheck -pthread -g -std=c++17 -lstdc++ 
	LEAKS = CK_FORK=no leaks --atExit -- 
endif

all: check

test: clean s21_containers.a s21_containersplus.a
	$(CXX) -lstdc++ s21_containers.h s21_containers_tests.cpp -o s21_containers_tests.out $(CXXFLAGS)
	./s21_containers_tests.out
	$(CXX) -lstdc++ s21_containersplus.h s21_containersplus_test.cpp -o s21_containersplus_test.out $(CXXFLAGS)
	./s21_containersplus_test.out

s21_containers.a:
	$(CXX) -c s21_containers.cpp -o s21_containers.o
	ar rc s21_containers.a s21_containers.o

s21_containersplus.a:
	$(CXX) -c s21_containersplus.cpp -o s21_containersplus.o
	ar rc s21_containersplus.a s21_containersplus.o

leaks:
	$(CXX) --coverage -O0 -C s21_containers_tests.cpp -o s21_containers_tests_for_leaks.out $(CXXFLAGS)
	$(LEAKS) ./s21_containers_tests_for_leaks.out --gtest_filter=s21_*_test.*
	# $(CXX) --coverage -O0 -C s21_containersplus_test.cpp -o s21_containersplus_test_for_leaks.out $(CXXFLAGS)
	# $(LEAKS) ./s21_containersplus_test_for_leaks.out --gtest_filter=s21_*_test.*

gcov_report_basic:
	g++ -std=c++17 --coverage -fkeep-inline-functions s21_containers.cpp s21_containers_tests.cpp -o s21_containers_tests -lgtest -lgtest_main -pthread
	./s21_containers_tests
	gcov s21_containers
	gcov -f s21_containers.gcda
	lcov --no-external --capture --directory . --output-file main_coverage.info
	genhtml main_coverage.info --output-directory lcov_report
	open lcov_report/index.html

gcov_report_plus:
	g++ -std=c++17 --coverage -fkeep-inline-functions s21_containersplus.cpp s21_containersplus_test.cpp -o s21_containersplus_test -lgtest -lgtest_main -pthread
	./s21_containersplus_test
	gcov s21_containersplus
	gcov -f s21_containersplus.gcda
	lcov --no-external --capture --directory . --output-file main_coverageplus.info
	genhtml main_coverageplus.info --output-directory lcov_reportplus
	open lcov_reportplus/index.html

clean:
	rm -rf *.0 *.a *.gcno *.gcda *.info *.out report *.dSYM *.gch small_report
	# rm -rf *.o *.out *_test .vscode .DS_Store tests all_report *.gcov lcov_report lcov_reportplus
	rm -rf *.o *.out *_test .vscode .DS_Store tests all_report *.gcov lcov_report

style:
	cp ../materials/linters/.clang-format ./
# brew install clang-format
	clang-format -i *.inl *.h
	clang-format -n *.h *.inl
	rm -rf .clang-format

check:
	cppcheck --std=c++17 --language=c++ --suppress=missingIncludeSystem s21_*.inl s21_*.h	
 
.PHONY:  check clean_gcov gcov_report tests $(SUBDIRS) test
