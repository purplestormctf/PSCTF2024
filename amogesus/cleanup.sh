#!/bin/bash

# Restore twentytwenty theme
cp -r /root/backup/twentytwenty /var/www/html/wordpress/wp-content/themes/
chown -R www-data:www-data /var/www/html/wordpress/wp-content/themes/twentytwenty

# Remove temporarily dropper binary
rm /tmp/dropper
