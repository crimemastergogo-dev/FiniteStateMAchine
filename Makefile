BINARY_PATH = bin/
HEADER_PATH = inc/
SOURCE_PATH = src/
TARGET:$(BINARY_PATH)contact
	
$(BINARY_PATH)contact:$(SOURCE_PATH)lib_fsm.a $(SOURCE_PATH)lib_string.a $(SOURCE_PATH)message.o
	echo "Building FSM Library"
	gcc $(SOURCE_PATH)message.o -o $(BINARY_PATH)contact -L . $(SOURCE_PATH)lib_fsm.a $(SOURCE_PATH)lib_string.a

$(SOURCE_PATH)lib_fsm.a:$(SOURCE_PATH)event_hndl.o $(SOURCE_PATH)fsm.o
	echo "Building FSM Library"
	ar rs $(SOURCE_PATH)lib_fsm.a $(SOURCE_PATH)event_hndl.o $(SOURCE_PATH)fsm.o
	
$(SOURCE_PATH)lib_string.a: $(SOURCE_PATH)string.o
	echo "Building String Library"
	ar rs $(SOURCE_PATH)lib_string.a $(SOURCE_PATH)string.o

$(SOURCE_PATH)message.o:$(SOURCE_PATH)message.c
	echo "Building Event Driver functions"
	gcc -c -I $(HEADER_PATH) $(SOURCE_PATH)message.c -o $(SOURCE_PATH)message.o

$(SOURCE_PATH)event_hndl.o:$(SOURCE_PATH)event_hndl.c
	echo "Building Event handler"
	gcc -c -I $(HEADER_PATH) $(SOURCE_PATH)event_hndl.c -o $(SOURCE_PATH)event_hndl.o

$(SOURCE_PATH)fsm.o:$(SOURCE_PATH)fsm.c
	echo "Building FSM"
	gcc -Wall -g -c -I$(HEADER_PATH) $(SOURCE_PATH)fsm.c -o $(SOURCE_PATH)fsm.o


$(SOURCE_PATH)string.o:$(SOURCE_PATH)string.c
	echo "Building My string functiuons"
	gcc -c -I $(HEADER_PATH) $(SOURCE_PATH)string.c -o $(SOURCE_PATH)string.o
	
clean:
	rm -rf $(SOURCE_PATH)*.o
	rm -rf $(SOURCE_PATH)*.a
	rm -rf $(BINARY_PATH)contact


