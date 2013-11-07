  // set and reset bits
    #include <stdio.h>
    int powi(int number, int exponent)
{
	int i, product = 1;
	for (i = 0; i < exponent; i++)
		product *= number;

	return product;
}
    int main()
    {
        int y=0;
        printf("y=%x \n", y);
        y = y | 1;        // set bit 0
        printf("y=%x \n", y);
        y = y | 8;       // set bit 3
        printf("y=%x \n", y);
     
        int x=0x0b00110011;
        printf("x=%x \n", x);
        x = x | 2; //set bit 1
        printf("x=%x \n", x);
        
        x = x | 64; //set bit 6
        printf("x=%x \n", x);
        
        x = x & ~2;        // clear bit 1
        printf("x=%x \n", x);
        x = x & ~16;       // clear bit 4
        printf("x=%x \n", x);
        
        //stroing bit 2 and 5 ;
        int m=4;
        m= (x & m);//bit 2 stored
        printf("m=%x \n", m);
        
        int n=32;
        n= (x & n);//bit 5 stored
        printf("n=%x \n", n);
        
        //swap int
        int z = 12;        
        z = ((z >> 16) & 0xFFFF) + ((z << 16) &0xFFFF0000);
        printf("z=%x \n", z);
        
        //reversing
        z=92;
        printf("z=%x \n", z);
        int tempz=0;
        //tempz=z;
        int i = 31;
        int a=0;
        int power;
       /* for(i=31;i>=0;i--){
      
   
        if(i-a>0)
        tempz= (((z & (power^i))>>(i-a))   | tempz) ;
        else if (i-a<0)
        tempz= (((z & (power^i))<<(a-i))   | tempz) ;
        else
        tempz= (((z & (power^i)))   | tempz) ;
        
        a++;
        
        
        }*/
        tempz=0;
        for(i=0;i<=31;i++){
     
       if( (powi(2,i) & z) == powi(2,i) )  tempz=tempz+ powi(2,(31-i));
        
        
        }
        z=tempz;
         printf("z=%x \n", z);
        
     return 0;
    } 
     

