# entropist
Generate random numbers from mouse moves and keystrokes

## Install and run

### Linux

```
sudo apt install libcrypto++-dev
git clone https://github.com/ola-ct/entropist.git
cd entropist
mkdir Release
cd Release
cmake -DCMAKE_BUILD_TYPE=Release ..
make
sudo ./entropist -v --hex
```

Move mouse around for a while. Hexadecimally coded random numbers should appear.
