unsigned int leepeso() {
while (!balanza.is_ready()) {}
    return balanza.read();
}

   