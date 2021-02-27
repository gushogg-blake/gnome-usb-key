#include <stdio.h>
#include <gnome-keyring.h>

int main() {
	GnomeKeyringResult res = gnome_keyring_lock_all_sync();
	
	if (res == GNOME_KEYRING_RESULT_OK) {
		printf("Keyrings locked\n");
		
		return 0;
	} else {
		printf("Error locking keyrings: %d\n", res);
		
		return 1;
	}
}
