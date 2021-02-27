#include <stdio.h>
#include <gnome-keyring.h>

int main(int argc, char** argv) {
	char* keyring = argv[1];
	
	char password[128];
	
	gets(password);
	
	GnomeKeyringResult res = gnome_keyring_unlock_sync(keyring, password);
	
	if (res == GNOME_KEYRING_RESULT_OK) {
		return 0;
	} else {
		printf("Error unlocking keyring: %d\n", res);
		
		return 1;
	}
}
