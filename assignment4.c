#include<stdio.h>
#include <stdlib.h>
#include <string.h>

   char base_digits[16] =
	 {'0', '1', '2', '3', '4', '5', '6', '7',
	  '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};	//Δομή που χρησιμοποιείτε από την dec2base για την μετατροπή βάσης

int getInputFromKeyboard(){	//(Θέμα Α) Εισαγωγή  βάσης με τεχνική αμυντικού προγραμματισμού 
    int base;
    char trash[1024];  
    while ( 1 ){
      scanf( "%d", &base );
      if (base>=2 && base <= 16) break;
      //assumes 1 entry per line and no line longer than 1023 characters */
      if (NULL == fgets(trash, sizeof(trash), stdin));
      printf("Ο Αριθμός που δώσατε δεν ήταν αποδεκτός.\nΜπορείτε να δώσετε μόνο ακέραιες τιμές μεγαλύτερες από 2 και μικρότερες από 16!\nΠαρακαλώ προσπαθείστε ξανά:"); 
    }
    return base;
}


int validnumber(int b, char *p){	//(Θέμα Β) To validation γίνεται με την χρήση της strtol η οποία επιστρέφει 0 σε περίπτωση μη έγκυρου string ως προς μια βάση
  long int ret;
  char *pEnd;
  ret = strtol (p,&pEnd,b);
  if (ret!=0) ret=1;  
  return ret;
}

unsigned long base2dec(int b, char *p){	// (Θέμα Γ) H base2dec  γίνεται με την χρήση της strtol η οποία επιστρέφει τη δεκαδική αναπαράσταση οποιουδήποτε αριθμού ως προς μια βάση
    long int ret=0;
    char * pEnd;
    ret = strtol(p,&pEnd,b);
    return ret;
}

void dec2base(int b, unsigned  int x){	//(Θέμα Δ) Συνάρτηση μετατροπή βάσης με τη χρήση διαδοχικών modules (%)
  int converted_number[64];
  long int number_to_convert = x;
  int next_digit, base, index=0;  
  
  base =b;

  printf("Για βάση: %d ο αριθμός είναι: = ",b);
  
   while (number_to_convert != 0) {
	 converted_number[index] = number_to_convert % base;
	 number_to_convert = number_to_convert / base;
	 ++index;
   }
   --index;  /* back up to last entry in the array */

   for(  ; index>=0; index--) { /* go backward through array */   
	 printf("%c", base_digits[converted_number[index]]);
   }  
  
  printf("\n");
  
}

main() {
    
    int  base;  
    char *p = malloc(sizeof(char) * 128);
    int isvalid=0;
    int converteddec=0;
    int index=2;
    
    printf("Καλωσήρθατε στο πρόγραμμα μετατροπής βάσης!\n");
    printf("Παρακαλώ επιλέξτε έναν ακέραιο αριθμό από το 2 έως το 16 που θα χρησιμοποιηθεί ως βάση: ");
    base = getInputFromKeyboard();
    printf("Ο Αριθμός που δώσατε ήταν αποδεκτός: %d\n", base);  
    printf("Παρακαλώ επιλέξτε έναν αριθμό (μέχρι 8 χαρακτήρες) που είναι έγκυρος βάσει της επιλεγείσας βάσης (%d):",base);      
    while (isvalid==0){
      scanf( "%126s", p );  
      isvalid = validnumber(base,p);
      if (isvalid==1){
	if (strlen(p)>8) {
	  printf("Υπενθυμίζουμε οτι επιτρέπονται μέχρι 8 χαρακτήρες! Προσπαθείστε ξανά:\n");
	  isvalid=0;
	}
      } printf("Μη έγκυροιχαρακτήρες για την βάση που επιλέξατε! Προσπαθείστε ξανά:\n");
    }
    printf("Εισάγατε τον αριθμό  '%s' του οποίου η εγκυρότητα είναι: %d (0-Όχι, 1-Ναι) \n",p,isvalid);    
    
    if (isvalid==0) {
      printf("Εφόσον εισάγατε λάθος αριθμό δεν έχει νόημα η περαιτέρω εκτέλεση!\n");      
    } else {      
      converteddec=base2dec(base, p);
      printf("Ο αριθμός που δώσατε στο δεκαδικό σύστημα είναι: %d\n",converteddec);
      printf("Ο αριθμός %d (στο δεκαδικό σύστημα) σε όλα τα συστήματα βάσεων είναι:\n",converteddec);
      for (index=2; index<=16; index++) dec2base(index,converteddec);
    }
    
}//main 