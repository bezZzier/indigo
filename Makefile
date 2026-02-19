CC = g++
TARGET = indigo

all: $(TARGET)

$(TARGET): main.cpp
	$(CC) main.cpp -o $(TARGET)

# --- ADD THIS PART BELOW ---
install: $(TARGET)
	sudo install -m 755 $(TARGET) /usr/local/bin

uninstall:
	sudo rm -f /usr/local/bin/$(TARGET)

clean:
	rm -f $(TARGET)