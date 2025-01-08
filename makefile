server:
	@./run_server

client:
	@./run_client

compile: c_client c_server

c_client: basic_client.o pipe_networking.o
	@gcc -o run_client basic_client.o pipe_networking.o

c_server: forking_server.o pipe_networking.o
	@gcc -o run_server forking_server.o pipe_networking.o

# server: persistent_server.o pipe_networking.o
# 	gcc -o server persistent_server.o pipe_networking.o

# server: basic_server.o pipe_networking.o
# 	gcc -o server basic_server.o pipe_networking.o

basic_client.o: basic_client.c pipe_networking.h
	@gcc -c basic_client.c

forking_server.o: forking_server.c pipe_networking.h
	@gcc -c forking_server.c

persistent_server.o: persistent_server.c pipe_networking.h
	@gcc -c persistent_server.c

# basic_server.o: basic_server.c pipe_networking.h
# 	gcc -c basic_server.c

pipe_networking.o: pipe_networking.c pipe_networking.h
	@gcc -c pipe_networking.c

clean:
	rm *.o
	rm *~
