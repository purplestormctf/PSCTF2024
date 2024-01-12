# hurricane

## Set Timezone

```c
root@hurricane:~# timedatectl set-timezone Europe/Berlin
```

## Update Server OS

```c
root@hurricane:~# apt-get update && apt-get upgrade && apt-get dist-upgrade && apt-get autoremove && apt-get autoclean
```

## Packages

```c
root@hurricane:~# apt-get install apt-transport-https curl gcc git ncat nmap tmux vim
```

## User Configuration

```c
root@hurricane:~# useradd -m <USER>
...
root@hurricane:~# passwd <USER>
...
root@hurricane:~# usermod -aG sudo <USER>
...
root@hurricane:~# ln /dev/null ~/.bash_history -sf
```