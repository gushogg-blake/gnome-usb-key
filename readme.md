gnome-usb-key
===

Unlock your GNOME keyring with a physical key.  `./unlock-keyring` performs the unlocking, accepting a password on `stdin`.

Calling it when the USB key is inserted can be done using `inotifywait`, which writes to `stdout` on filesystem events.  Storing the password on the key is a security vulnerability, but a fun way to give it some security-by-obscurity is to [store it in an image](https://en.wikipedia.org/wiki/Steganography):

steg (`$ steg orig-image.png image-with-password.png`):

```bash
#!/bin/bash

origImg=$1
newImg=$2

file=/tmp/steg/file

mkdir -p `dirname $file`

read line

echo -n $line > $file

# replace PASSWORD with a password to encrypt the zip file

zip -PPASSWORD -j - $file | cat $origImg - > $newImg

rm $file

rmdir `dirname $file`
```

unsteg (`$ unsteg image-with-password.png # outputs password`):

```bash
#!/bin/bash

img=$1

unzip -PPASSWORD -p $img file 2>/dev/null
```

Example startup script:

```bash
#!/bin/bash

file="/media/user/USB/image-with-password.png"

function check {
	test -f $file && unsteg $file | unlock-keyring login && return 0
	
	return 1
}

function check-burst {
	for i in {1..5}; do
		check && return 0
		
		sleep 0.5
	done
}

check-burst

inotifywait -m /media/user -e create | while read; do
	check-burst
done
```
