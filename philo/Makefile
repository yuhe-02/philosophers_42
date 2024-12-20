CC := cc
CFLAGS := -Wall -Werror -Wextra -g -fsanitize=thread

# SRCS
SRCDIR := srcs
SRCS += $(SRCDIR)/main.c
SRCS += $(SRCDIR)/init.c
SRCS += $(SRCDIR)/only_die.c
SRCS += $(SRCDIR)/launch.c
SRCS += $(SRCDIR)/philo_thread.c
SRCS += $(SRCDIR)/owner_thread.c

UTILS := utils
SRCS += $(SRCDIR)/${UTILS}/ft_atoi.c
SRCS += $(SRCDIR)/${UTILS}/ft_timeofday.c
SRCS += $(SRCDIR)/${UTILS}/ft_dead_check.c
SRCS += $(SRCDIR)/${UTILS}/ft_print_act.c

#OBJS
OBJDIR := objs
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%$(SUFFIX).o)

INCDIR := includes
INCLUDES := -I$(INCDIR) 

NAME = $(PJT)$(SUFFIX)

PJT := philo


SUFFIXES := _yyamasak

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LIB) -lpthread


$(OBJDIR):
	@mkdir -p $(OBJDIR)
	@mkdir -p $(OBJDIR)/$(UTILS)

$(OBJDIR)/%$(SUFFIX).o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDES) $(DEFINES) -o $@ -c $<

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(PJT)

re: fclean all

.PHONY: all clean fclean re
