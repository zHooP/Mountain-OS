## Mountain-OS
When you are bored and decide making an OS

# Compile it yourself
First install the needed dependencies:
```
sudo apt-get install xorriso
sudo -s
wget https://raw.githubusercontent.com/lordmilko/i686-elf-tools/master/i686-elf-tools.sh
chmod +x ./i686-elf-tools.sh
./i686-elf-tools.sh
```
When everything finished run `./comp.sh`. 
After compiling it should say something like this:
```
./comp.sh: line 2: nasm: command not found
./comp.sh: line 3: /root/opt/cross/bin/i686-elf-gcc: No such file or directory
./comp.sh: line 4: /root/opt/cross/bin/i686-elf-gcc: No such file or directory
./comp.sh: line 5: /root/opt/cross/bin/i686-elf-gcc: No such file or directory
./comp.sh: line 6: /root/opt/cross/bin/i686-elf-gcc: No such file or directory
./comp.sh: line 7: /root/opt/cross/bin/i686-elf-gcc: No such file or directory
./comp.sh: line 8: /root/opt/cross/bin/i686-elf-gcc: No such file or directory
./comp.sh: line 9: /root/opt/cross/bin/i686-elf-gcc: No such file or directory
./comp.sh: line 10: /root/opt/cross/bin/i686-elf-gcc: No such file or directory
./comp.sh: line 11: /root/opt/cross/bin/i686-elf-gcc: No such file or directory
./comp.sh: line 12: /root/opt/cross/bin/i686-elf-gcc: No such file or directory
./comp.sh: line 13: /root/opt/cross/bin/i686-elf-gcc: No such file or directory
./comp.sh: line 14: /root/opt/cross/bin/i686-elf-gcc: No such file or directory
./comp.sh: line 15: /root/opt/cross/bin/i686-elf-ld: No such file or directory
cp: cannot stat 'debug/kernel.elf': No such file or directory
```
Don't worry! You now should have a file called `mountainos.iso`. 
Feel free to do whatever you want with it.

## TODO
# Help needed
- move to VGA pixel by pixel drawing (with text fonts and print abilities)
- actual sound instead of beeps

# Time needed
- mouse support

