#
# | TME 01 - 2I001 - C avancee
# | labyrinthe.c
# | auteurs: Corentin Ulliac, Axel Viala


SRCDIR = ./srcs
OBJDIR = ./objs
INCDIR = -I./include -I./my_stdext/includes
SRCS = main.c ecosys.c
LIBDIR = ./my_stdext

CFLAGS = -Wall -Wextra -Werror -pedantic -pedantic-errors -std=c99 -Wno-unused-result
LDFLAGS = -L $(LIBDIR) -lmy_stdext -lm

ifeq ($(DEBUG),yes)
	CC = clang
	CFLAGS += -ggdb -g3 -fstack-protector-all -Wshadow -Wunreachable-code \
			  -Wstack-protector -pedantic-errors -O0 -W -Wundef \
			  -Wfatal-errors -Wstrict-prototypes -Wmissing-prototypes \
			  -Wwrite-strings -Wunknown-pragmas \
			  -Wold-style-definition -Wfloat-equal \
			  -Wpointer-arith -Wnested-externs -Wstrict-overflow=5 \
			  -Wno-missing-field-initializers -Wswitch-default -Wswitch-enum \
			  -Wbad-function-cast -Wredundant-decls -fno-omit-frame-pointer
else
	CC = gcc
	CFLAGS += -O3
endif

LD = $(CC)

OBJS = $(SRCS:.c=.o)
OBJS_PREF = $(addprefix $(OBJDIR)/, $(OBJS))
NAME = ecosys

all: objdir build_dep $(NAME)

objdir:
	@mkdir -p objs

$(NAME): $(OBJS_PREF)
	$(LD) -o $@ $^ $(LDFLAGS) $(INCDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -o $@ -c $< $(CFLAGS) $(INCDIR)

build_dep:
	make -C my_stdext

clean:
	rm -f $(OBJS_PREF)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re all

