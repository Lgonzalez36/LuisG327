CC=gcc

CFLAGS_DBG=-g -ggdb -gdwarf-4 -O0 -Wall -Wextra
CFLAGS=-c -Wall -Wextra

all: prog2
common.o: ../common.c ../common.h
	${CC} ${CFLAGS} -c ../common.c -o common.o
common_dbg.o: ../common.c ../common.h
	${CC} ${CFLAGS_DBG} -c ../common.c -o common_dbg.o

 #--- Sanitizers (use clang): common_dbg_*
common_dbg_asan.o: ../common.c ../common.h
	${CL} ${CFLAGS_DBG_ASAN} -c ../common.c -o common_dbg_asan.o
common_dbg_ub.o: ../common.c ../common.h
	${CL} ${CFLAGS_DBG_UB} -c ../common.c -o common_dbg_ub.o
common_dbg_msan.o: ../common.c ../common.h
	${CL} ${CFLAGS_DBG_MSAN} -c ../common.c -o common_dbg_msan.o

exec_env.o: exec_env.c
	${CC} ${CFLAGS} -c exec_env.c -o exec_env.o
exec_env: common.o exec_env.o
	${CC} -o exec_env exec_env.o common.o 

execd_pgm.o: execd_pgm.c
	${CC} ${CFLAGS} -c execd_pgm.c -o execd_pgm.o
execd_pgm: common.o execd_pgm.o
	${CC} -o execd_pgm execd_pgm.o common.o 

clean:
	rm -rf *o prog2