#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#ifdef YYAMASAK_DEBUG
# define YYAMASAK(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
# define YYAMASAK(fmt, ...)
#endif

#endif