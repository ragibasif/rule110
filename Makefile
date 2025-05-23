# Makefile

GREEN=\033[0;92m
RED=\033[0;91m
MAGENTA=\033[0;95m
RESET=\033[0m

CC := gcc
CFLAGS := -std=c99 -Wall -Wextra -Weverything -O0 -g3 -pedantic -DDEBUG -v
LDFLAGS := -v -lc

EXECUTABLE := rule110

SRCS := $(wildcard *.c)
HDRS := $(wildcard *.h)
OBJS := $(patsubst %.c, %.o, $(SRCS))

.PHONY: all clean help run

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	@echo "🔧 Linking ${MAGENTA}$@${RESET} ..."
	@$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS) && \
		echo "$(GREEN)✅ Build successful: $@$(RESET)" || \
		(echo "$(RED)❌ Linking failed: $@$(RESET)" && exit 1)

%.o: %.c
	@echo "🔧 Compiling ${MAGENTA}$<${RESET} ..."
	@$(CC) $(CFLAGS) -c $< -o $@ && \
		echo "$(GREEN)✅ Compiled: $<$(RESET)" || \
		(echo "$(RED)❌ Compile failed: $<$(RESET)" && exit 1)

clean:
	@echo "${MAGENTA}make clean${RESET} $(RM) -r $(EXECUTABLE) $(OBJS) *~ *.bak *.dSYM *.out"
	@$(RM) -r $(EXECUTABLE) $(OBJS) *~ *.bak *.dSYM *.out .*.un~

run: $(EXECUTABLE)
	@echo "${MAGENTA}make run${RESET}"
	@make clean
	@make all
	@./$(EXECUTABLE)

help:
	@echo "${MAGENTA}make help${RESET}"
	@echo "Makefile for Building ${MAGENTA}${EXECUTABLE}${RESET}."
	@echo "Usage:"
	@echo "  ${MAGENTA}make${RESET}             — debug build"
	@echo "  ${MAGENTA}make DEBUG=1${RESET}     — force debug build"
	@echo "  ${MAGENTA}make RELEASE=1${RESET}   — release build"
	@echo "  ${MAGENTA}make clean${RESET}       — remove build files"
	@echo "  ${MAGENTA}make run${RESET}         — run program"

