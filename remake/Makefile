CC = g++
CFLAGS = -Og -g -I /usr/include/SDL2 -I /usr/include/mariadb -I /usr/include/mariadb/mysql
LFLAGS = -lSDL2 -lSDL2_image -lSDL2_net -lSDL2_ttf -lSDL2_mixer \
	-L /usr/lib/mariadb -lmariadb -lssl -ldl -lm -lpthread
OBJS = afisare.o body.o choose_name.o menu_1.o rankings.o \
	screen.o stage1.o start_all.o status.o stage.o
OUTPUT_NAME = nave

all_minimum: link_all

all_full: link_all prepare_media

link_all: $(OBJS)
	$(CC) $(OBJS) $(LFLAGS) -o $(OUTPUT_NAME)

afisare.o: afisare.cpp
	$(CC) $(CFLAGS) -c afisare.cpp -o afisare.o

body.o: body.cpp
	$(CC) $(CFLAGS) -c body.cpp -o body.o

choose_name.o: choose_name.cpp
	$(CC) $(CFLAGS) -c choose_name.cpp -o choose_name.o

menu_1.o: menu_1.cpp
	$(CC) $(CFLAGS) -c menu_1.cpp -o menu_1.o

nave_net.o: nave_net.cpp
	$(CC) $(CFLAGS) -c nave_net.cpp -o nave_net.o

rankings.o: rankings.cpp
	$(CC) $(CFLAGS) -c rankings.cpp -o rankings.o

screen.o: screen.cpp
	$(CC) $(CFLAGS) -c screen.cpp -o screen.o

stage1.o: stage1.cpp
	$(CC) $(CFLAGS) -c stage1.cpp -o stage1.o

start_all.o: start_all.cpp
	$(CC) $(CFLAGS) -c start_all.cpp -o start_all.o

status.o: status.cpp
	$(CC) $(CFLAGS) -c status.cpp -o status.o

stage.o: stage.cpp
	$(CC) $(CFLAGS) -c stage.cpp -o stage.o

clean:
	rm $(OBJS)
	rm $(OUTPUT_NAME)

clean_obj:
	rm $(OBJS)

prepare_media: muzica media
	cp -r muzica media bin/

small: start_all.cpp stage.cpp stage1.cpp
	$(CC) $(CFLAGS) $(LFLAGS) start_all.cpp stage.cpp stage1.cpp -o mini
