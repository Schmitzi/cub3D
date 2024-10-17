NAME	=	libget_next_line.a
CFLAGS	=	-g -Wall -Wextra -Werror -pedantic
CFILES	=	get_next_line_bonus_bonus.c get_next_line_utils_bonus_bonus.c
HEADER	=	get_next_line_bonus_bonus.h
CC	=	cc
CDIR	=	src
ODIR	=	obj
HDIR 	=	include
OBJECTS	=	$(addprefix $(ODIR)/, $(CFILES:.c=.o))
NUM_JOBS	=	$(shell nproc)
MAKEFLAGS	+=	--no-print-directory --jobs=$(NUM_JOBS)

all: $(NAME)

$(NAME): $(OBJECTS) $(HDIR) Makefile
	@ar -rcs $(NAME) $(OBJECTS)
	@ranlib $(NAME)
	@echo "~ GNL   - Archive built successfully"

$(ODIR)/%.o: %.c
	@mkdir -p $(ODIR)
	@$(CC) $(CFLAGS) -I $(HDIR) -c $< -o $@
	@echo "~ GNL   - Compiled $@"

%.o: %.c $(HDIR) Makefile
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "~ GNL   - Compiled $@"

clean:
	@if [ -d $(ODIR) ]; then echo "~ GNL   - Object files deleted"; fi
	@rm -rf $(OBJECTS)
	@rm -rf $(ODIR)

fclean: clean
	@if [ -n $(NAME) ] ; then echo "~ GNL   - Archive deleted"; fi
	@rm -f $(NAME)

re: fclean
	$(MAKE) all

.PHONY: all clean fclean re
