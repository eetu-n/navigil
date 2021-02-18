
OBJS = led_and_button_controller.o light_wrapper.o logger.o external.o
CFLAGS = -Wall -g
CC = gcc
INCLUDE =
LDLIBS = -pthread -lcheck_pic -pthread -lrt -lm -lsubunit

all:lightlib.a

led_and_button_controller.o: led_and_button_controller.c
	${CC} ${CFLAGS} ${INCLUDE} -c $^ -o $@ ${LDLIBS}

light_wrapper.o: light_wrapper.c
	${CC} ${CFLAGS} ${INCLUDE} -c $^ -o $@ ${LDLIBS}

logger.o: logger.c
	${CC} ${CFLAGS} ${INCLUDE} -c $^ -o $@ ${LDLIBS}

external.o: external.c
	${CC} ${CFLAGS} ${INCLUDE} -c $^ -o $@ ${LDLIBS}

lightlib.a: ${OBJS}
	ar ruv lightlib.a ${OBJS}

clean:
	rm -f *.o *.a tests

check: tests
	chmod +x tests
	./tests

tests: external.c led_and_button_controller.c light_wrapper.c logger.c tests.c
	${CC} ${CFLAGS} ${INCLUDE} $^ -o $@ ${LDLIBS}
