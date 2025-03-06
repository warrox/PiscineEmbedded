# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: whamdi <whamdi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/03 10:11:51 by whamdi            #+#    #+#              #
#    Updated: 2025/03/05 08:59:23 by whamdi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC         := avr-gcc
OBJCOPY    := avr-objcopy #converti en un format specifique pour le microcontrolleur
AVRDUDE    := avrdude #flash le microcontrolleur
MCU        := atmega328p # type du microcontrolleur
F_CPU      ?= 16000000UL # frequence du processeur ici 16 Mhz sois 16 Millions d'operations par seconde 🫨
CFLAGS     := -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os -Wall -Wextra -MMD -MP
SRC_DIR    := src
BUILD_DIR  := .build
SRC        := $(wildcard $(SRC_DIR)/*.c)
OBJ        := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC))

all: hex flash

hex: main.hex

main.hex: main.bin
	$(OBJCOPY) -j .text -j .data -O ihex $< $@

main.bin: $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

flash: main.hex
	$(AVRDUDE) -v -p $(MCU) -c arduino -P /dev/ttyUSB0 -b 115200 -D -U flash:w:$<:i

clean:
	rm -f main.hex main.bin

fclean: clean
	rm -rf $(BUILD_DIR)

re: fclean all

-include $(OBJ:.o=.d)
