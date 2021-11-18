ALL := proc_B proc_A

CC=${CROSS_COMPILE}gcc
CL=${CROSS_COMPILE}clang

CFLAGS=-Wall
CFLAGS_DBG=-g -ggdb -gdwarf-4 -O0 -Wall -Wextra
CFLAGS_DBG_ASAN= -fsanitize=address
CFLAGS_DBG_MSAN= -fsanitize=memory -fPIE -pie
CFLAGS_DBG_UB= -fsanitize=undefined

all: ${ALL}
CB_FILES := *.[ch]

common.o: ../common.c ../common.h
	${CC} ${CFLAGS} -c ../common.c -o common.o
common_dbg.o: ../../common.c ../common.h
	${CC} ${CFLAGS_DBG} -c ../common.c -o common_dbg.o

proc_B: common.o proc_B.o
	${CC} ${CFLAGS} -o proc_B proc_B.c common.o
proc_B_dbg.o: proc_B.c
	${CC} ${CFLAGS_DBG} -c proc_B.c -o proc_B_dbg.o
proc_B_dbg: proc_B_dbg.o common_dbg.o
	${CC} -o proc_B_dbg proc_B_dbg.o common_dbg.o
#	${CL} ${CFLAGS_DBG_ASAN} -o proc_B_asan proc_B_dbg.o common_dbg.o
#	${CL} ${CFLAGS_DBG_UB} -o proc_B_ub proc_B_dbg.o common_dbg.o
#	${CL} ${CFLAGS_DBG_MSAN} -o proc_B_msan proc_B_dbg.o common_dbg.o

proc_A: common.o proc_A.o
	${CC} ${CFLAGS} -o proc_A proc_A.c common.o
proc_A_dbg.o: proc_A.c
	${CC} ${CFLAGS_DBG} -c proc_A.c -o proc_A_dbg.o
proc_A_dbg: proc_A_dbg.o common_dbg.o
	${CC} -o proc_A_dbg proc_A_dbg.o common_dbg.o
#	${CL} ${CFLAGS_DBG_ASAN} -o proc_A_asan proc_A_dbg.o common_dbg.o
#	${CL} ${CFLAGS_DBG_UB} -o proc_A_ub proc_A_dbg.o common_dbg.o
#	${CL} ${CFLAGS_DBG_MSAN} -o proc_A_msan proc_A_dbg.o common_dbg.o

# indent- "beautifies" C code into the "Linux kernel style".
# (cb = C Beautifier :) )
# Note! original source file(s) is overwritten, so we back it up.
cb: ${CB_FILES}
	mkdir bkp 2> /dev/null; cp -f ${CB_FILES} bkp/
	indent -linux ${CB_FILES}

clean:
	rm -vf ${ALL} core* vgcore* *.o *~