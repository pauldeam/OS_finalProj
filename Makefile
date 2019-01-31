JSON_C_DIR=/json_c/install
CFLAGS += -I$(JSON_C_DIR)/include/json-c
LDFLAGS+= -L$(JSON_C_DIR)/lib -ljson-c

run : main.c
	gcc main.c -o main $(CFLAGS) $(LDFLAGS)
