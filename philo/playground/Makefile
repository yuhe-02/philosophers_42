CC := cc
CFLAGS := -Wall

# SRCS
SRCDIR := ./
SRCS += $(SRCDIR)/main.c

#OBJS
OBJDIR := objs
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%$(SUFFIX).o)

# コンパイルオプション
INCDIR := ../includes
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

$(OBJDIR)/%$(SUFFIX).o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDES) $(DEFINES) -o $@ -c $<

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(PJT)
	rm -f $(foreach SUFFIX,$(SUFFIXES),$(NAME))

re: fclean all

.PHONY: all yyamasak clean fclean re