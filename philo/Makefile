CC := cc
# CFLAGS := -Wall -Werror -Wextra
CFLAGS := -g -fsanitize=thread
# CFLAGS := -g -fsanitize=address
# CFLAGS := 

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
# SRCS += $(SRCDIR)/${UTILS}/ft_shows.c
SRCS += $(SRCDIR)/${UTILS}/ft_itoa.c
SRCS += $(SRCDIR)/${UTILS}/ft_strlen.c
SRCS += $(SRCDIR)/${UTILS}/ft_strncmp.c
SRCS += $(SRCDIR)/${UTILS}/ft_timeofday.c
SRCS += $(SRCDIR)/${UTILS}/ft_dead_check.c
SRCS += $(SRCDIR)/${UTILS}/ft_print_act.c

#OBJS
OBJDIR := objs
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%$(SUFFIX).o)

# コンパイルオプション
INCDIR := includes
INCLUDES := -I$(SRCDIR) -I$(INCDIR) -lpthread

# 実行ファイル名
NAME = $(PJT)$(SUFFIX)

# プロジェクト名
PJT := philo

# SUFFIX一覧
SUFFIXES := _yyamasak

# デバッグの場合分け
ifdef YYAMASAK_DEBUG
	DEFINES := -D YYAMASAK_DEBUG
	SUFFIX := $(word 1, $(SUFFIXES))
else
	DEFINES :=
	SUFFIX :=
endif

# ターゲット
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LIB)

yyamasak:
	make YYAMASAK_DEBUG=1

$(OBJDIR):
	@mkdir -p $(OBJDIR)
	@mkdir -p $(OBJDIR)/$(UTILS)

$(OBJDIR)/%$(SUFFIX).o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDES) $(DEFINES) -o $@ -c $<

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(PJT)
	rm -f $(foreach SUFFIX,$(SUFFIXES),$(NAME))

re: fclean all

.PHONY: all yyamasak clean fclean re
