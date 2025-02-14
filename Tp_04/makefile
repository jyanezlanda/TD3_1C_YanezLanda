# Compilador y opciones
CC = arm-linux-gnueabihf-gcc
AS = arm-linux-gnueabihf-as
LD = arm-linux-gnueabihf-ld
OBD = arm-linux-gnueabihf-objdump
OBC = arm-linux-gnueabihf-objcopy
VM = qemu-system-arm
CFLAGS = -g -c -marm
ASFLAGS =
BOARD=realview-pb-a8
VMFLGS= -M $(BOARD)  -no-reboot -nographic -monitor telnet:127.0.0.1:1234,server,nowait

# Directorios
SRC_DIR = src
INC_DIR = inc
OBJ_DIR = obj
LST_DIR = lst
BIN_DIR = bin

# Archivos fuentes y objetos
ASM_SOURCES = tables.s handler.s startup.s reset.s
C_SOURCES = irq_handler.c timer.c gic.c board_init.c tareas.c scheduler.c

ASM_OBJECTS = $(patsubst %.s,$(OBJ_DIR)/%.o,$(ASM_SOURCES))
C_OBJECTS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(C_SOURCES))

# Nombre del ejecutable
BIOS = bios
TARGET = $(BIN_DIR)/$(BIOS).bin $(OBJ_DIR)/$(BIOS).elf 

# Reglas de compilación
all: $(TARGET)

$(BIN_DIR)/$(BIOS).bin: $(OBJ_DIR)/$(BIOS).elf
	$(OBC) -O binary $< $@

$(OBJ_DIR)/$(BIOS).elf: $(ASM_OBJECTS) $(C_OBJECTS)
	@echo "Linkeando..."
	$(LD) -T memmap.ld $(OBJ_DIR)/*.o -o $(OBJ_DIR)/$(BIOS).elf -Map $(LST_DIR)/$(BIOS).map
	@echo "Linkeo finalizado!"
	@echo "Generando archivos de información: mapa de memoria y símbolos"
	readelf -a $(OBJ_DIR)/$(BIOS).elf >>$(LST_DIR)/$(BIOS)_elf.txt
	$(OBD) -D $(OBJ_DIR)/$(BIOS).elf >>$(LST_DIR)/$(BIOS).lst
	@echo "Listo!"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.s
	@echo ""
	mkdir -p $(BIN_DIR)
	mkdir -p $(OBJ_DIR)
	mkdir -p $(LST_DIR) 
	@echo "Compilando $<..."
	$(AS) $(ASFLAGS) -o $@ $<
	@echo "Listo!"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "Compilando $<..."
	$(CC) $(CFLAGS) $< -o $@
	@echo "Listo!"

# Regla para correr el programa
run:
	$(VM) $(VMFLGS) -kernel $(BIN_DIR)/$(BIOS).bin -S -gdb tcp::2159


# Regla para limpiar archivos generados
clean:
	rm -rf $(OBJ_DIR)/* $(LST_DIR)/* $(BIN_DIR)/*

.PHONY: clean
