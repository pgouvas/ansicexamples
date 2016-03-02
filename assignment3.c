#include<stdio.h>
#include <math.h>

enum {
    SIZEOFMATRIX = 10
};

float DEMAND[SIZEOFMATRIX] = {1400,1100,1500,1500,2000,1800,1600,1300,1900,1900}; //Είναι η global μεταβλητή του πίνακα τη ζήτησης


float getInputFromKeyboard(){	//Η συνάρτηση αυτή διαβάζει από το πληκτρολόγια τον συντελεστή και κάνει ελέγχους αμυντικού προγραμματισμού (Θέμα Α)
    float a;
    char trash[1024];  
    while ( 1 ){
      scanf( "%f", &a );
      if (a>0 && a < 1) break;
      //Υποθέτουμε μια εισαγωγή ανα γραμμή που δεν υπερβαίνει τους 1023 χαρακτήρες */
      if (NULL == fgets(trash, sizeof(trash), stdin));
      printf("Ο Αριθμός που δώσατε δεν ήταν αποδεκτός.\nΜπορείτε να δώσετε τιμές μεγαλύτερες από 0 και μικρότερες από 1!\nΠαρακαλώ προσπαθείστε ξανά:"); 
    }
    return a;
}

void printArray(float f[], int size){  //Η συναρτηση αυτή τυπώνει τα περιεχόμενα ενός array
    int index=0;
    for (index=0; index<size; index++){
      printf("%f ",f[index]);
    }//for
}

float calculateMAE(float error[]){	//Υπολογισμός Μέσου Απόλυτου Σφάλματος
  float ret=0;
  int index=0;
  float cumul=0;
  for ( index=0; index<(SIZEOFMATRIX); index++ ){
    cumul+=error[index];
  }
  ret = cumul / SIZEOFMATRIX;
  return ret;
}

float calculateMSE(float error[]){		//Υπολογισμός Τετραγωνικού Σφάλματος
  float ret=0;
  int index=0;
  float cumul=0;  
  for ( index=0; index<(SIZEOFMATRIX); index++ ){
    cumul+=(error[index]*error[index]);    
  }  
  ret = cumul / SIZEOFMATRIX;  
  return ret;
}

void display_error_analysis(float f[], int size){	//Συνάρτηση Εκτύπωσης (Θέμα Γ)

    int index=0;  
    float error[SIZEOFMATRIX];
    float mae=0;
    float mse=0;
    printf("Αποτέλεσμα Ανάλυσης\n");
    printf(" t  Χρόνος  Ζήτηση   Πρόβλεψη Σφάλμα   Απόλυτο  Τετραγωνικό \n");
    printf("------------------------------------------------------------\n");
  
    for ( index=0; index<(SIZEOFMATRIX); index++ ){
        error[index] = fabs(DEMAND[index] - f[index]);
	printf(" %d  %d  %0.2f   %0.2f    %0.2f  %0.2f  %0.2f\n",(index+1),(2005+index),DEMAND[index],f[index], error[index], fabs(error[index]), fabs(error[index])*fabs(error[index]) );      
    }
    mae = calculateMAE(error);
    mse = calculateMSE(error);    
    printf("ΜΑΕ: %.2f\n",mae);
    printf("ΜΣΕ: %.2f\n",mse);    
    printf("Η πρόβλεψη για τον τελευταίο χρόνο είναι: %.2f \n",f[SIZEOFMATRIX]);    
}

void exponential_smoothing(float f[], int size, float a){	//Υπολογισμός προβλέψεων (Θέμα Β)
    int index=0;
    float provlepsi;
    
    
    for ( index=0; index<(SIZEOFMATRIX+1); index++ ){
        if (index==0) {
	  provlepsi = DEMAND[0];
	} else {
	  provlepsi = f[index-1]+a*(DEMAND[index-1]-f[index-1]);
	}
	//printf("H πρόβλεψη για τον χρόνο %d είναι %f\n",index,provlepsi);
	f[index]=provlepsi;
    }//for
    
    //printArray(f, SIZEOFMATRIX+1 );
    display_error_analysis(f, SIZEOFMATRIX+1);
    
}//

main() {
    
    float  a;  
    float f[SIZEOFMATRIX+1];
    
    printf("Καλωσήρθατε στο πρόγραμμα εκθετικών προβλέψεων!\n");
    printf("Παρακαλώ επιλέξτε τον συντελεστή εξομάλυνσης α:  ");
    a = getInputFromKeyboard();
    printf("Ο Αριθμός που δώσατε ήταν αποδεκτός: %f\n", a);  
    
    exponential_smoothing(f,SIZEOFMATRIX+1,a);
    
} 

