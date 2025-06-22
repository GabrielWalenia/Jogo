CC = gcc
CFLAGS = -Wall -O2 -g
LDFLAGS = -lallegro -lallegro_font -lallegro_ttf -lallegro_primitives -lallegro_image -lallegro_audio -lallegro_acodec -lallegro_dialog
SRC = main.c ./elementos/personagem.c ./elementos/joystick.c ./elementos/arma.c ./elementos/municao.c ./elementos/inimigo.c ./elementos/background.c
OUT = jogo

all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(OUT) $(LDFLAGS)

clean:
	rm -f $(OUT)