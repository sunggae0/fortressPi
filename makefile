CC := gcc

SRCDIR := src
INCDIR := include
OBJDIR := obj
BINDIR := bin
TARGET := fortressPi

CFLAGS := -Wall -Wextra -O2 -std=c11 -I$(INCDIR) -MMD -MP
LDFLAGS := -lbcm2835 -lm -lpthread

SOURCES := $(wildcard $(SRCDIR)/*.c)
OBJECTS := $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SOURCES))
DEPS := $(OBJECTS:.o=.d)

.PHONY: all clean dirs

all: dirs $(BINDIR)/$(TARGET)

dirs:
	@mkdir -p $(OBJDIR) $(BINDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BINDIR)/$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

-include $(DEPS)

clean:
	@rm -rf $(OBJDIR) $(BINDIR)
