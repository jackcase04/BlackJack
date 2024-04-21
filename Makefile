CC = g++
# -s removes symbol table information, DO NOT USE if you want to debug
# -pedantic-errors at one point seemed to cause undefined references when passing structs by reference
CFLAGS = -Wall -I include -g -W -pedantic-errors
GTEST_DIR = /usr/lib/x86_64-linux-gnu
GTEST_LIB = $(GTEST_DIR)/libgtest.a
GTEST_INCLUDE = -I$(GTEST_DIR)/include
VALGRIND = valgrind --leak-check=full --track-origins=yes

# only change this part
# add all source files here
SRCS = source/main.cpp source/functions.cpp
OBJS = $(SRCS:.cpp=.o) 
# add all test files here
TST_FILES = source/functions.cpp test/testfunctions.cpp test/testfunctions_isBlackjack.cpp test/testfunctions_generateRandomCard.cpp
TARGET = a.out
TESTS_TARGET = ./tests_$(TARGET)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

tests: $(TESTS_TARGET)
	@echo Executing $@

$(TESTS_TARGET): $(TST_FILES)
	$(CC) $(CFLAGS) $(GTEST_INCLUDE) -pthread -o $(TESTS_TARGET) $(TST_FILES) $(GTEST_LIB)

runtests: $(TESTS_TARGET)
	@echo Executing $@
	$(TESTS_TARGET)

runtestsvalgrind: $(TESTS_TARGET)
	@echo Executing $@
	$(VALGRIND) $(TESTS_TARGET)

cleantests:
	@echo Executing $@
	rm -f $(TESTS_TARGET)

clean:
	@echo Executing $@
	rm -f $(OBJS) $(TARGET) $(TESTS_TARGET)
