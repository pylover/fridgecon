CC = xc8-cc
CHIP = 12f675
PG = ardpicprog
DIST = ./out
OSCCAL = FF 
CCARGS = \
	-ansi \
	-O2 \
	-fasmfile \
	-mno-osccal \
	-moscval=$(OSCCAL) \
	-mcpu=$(CHIP) 

# -mc90lib \
# -fshort-float \
#SERIALPORT = /dev/ttyUSB0
SERIALPORT = /dev/ttyACM0
PGARGS = --quiet --pic-serial-port $(SERIALPORT)
SRCS = \
	timer.c \
	store.c \
	main.c


all: main.hex


$(DIST):
	mkdir -p $(DIST)


main.hex: $(DIST)
	$(CC) $(CCARGS) -o $(DIST)/main.hex $(SRCS)


.PHONY: clean
clean: 
	rm $(DIST)/*


.PHONY: program
program: main.hex
	$(PG) $(PGARGS) --erase --burn --force-calibration --input-hexfile $(DIST)/main.hex


.PHONY: read
read:
	$(PG) $(PGARGS) --ihx8m --output-hexfile OUTPUT 

