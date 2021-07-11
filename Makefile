BINARY_PATH = bin/
HEADER_PATH = inc/
SOURCE_PATH = src/
TARGET:$(BINARY_PATH)contact
	
$(BINARY_PATH)contact:$(SOURCE_PATH)lib_fsm.a $(SOURCE_PATH)lib_string.a $(SOURCE_PATH)message.o
	gcc -Wall -g $(SOURCE_PATH)message.o -o $(BINARY_PATH)contact -L . $(SOURCE_PATH)lib_fsm.a $(SOURCE_PATH)lib_string.a

$(SOURCE_PATH)lib_fsm.a:$(SOURCE_PATH)event_hndl.o $(SOURCE_PATH)fsm.o
	ar rs $(SOURCE_PATH)lib_fsm.a $(SOURCE_PATH)event_hndl.o $(SOURCE_PATH)fsm.o
	
$(SOURCE_PATH)lib_string.a: $(SOURCE_PATH)string.o
	ar rs $(SOURCE_PATH)lib_string.a $(SOURCE_PATH)string.o

$(SOURCE_PATH)message.o:$(SOURCE_PATH)message.c
	gcc -Wall -g -c -I $(HEADER_PATH) $(SOURCE_PATH)message.c -o $(SOURCE_PATH)message.o

$(SOURCE_PATH)event_hndl.o:$(SOURCE_PATH)event_hndl.c
	gcc -Wall -g -c -I $(HEADER_PATH) $(SOURCE_PATH)event_hndl.c -o $(SOURCE_PATH)event_hndl.o

$(SOURCE_PATH)fsm.o:$(SOURCE_PATH)fsm.c
	gcc -Wall -g -c -I$(HEADER_PATH) $(SOURCE_PATH)fsm.c -o $(SOURCE_PATH)fsm.o


$(SOURCE_PATH)string.o:$(SOURCE_PATH)string.c
	gcc -Wall -g -c -I $(HEADER_PATH) $(SOURCE_PATH)string.c -o $(SOURCE_PATH)string.o
	
clean:
	rm -rf $(SOURCE_PATH)*.o
	rm -rf $(SOURCE_PATH)*.a
	rm -rf $(BINARY_PATH)contact


