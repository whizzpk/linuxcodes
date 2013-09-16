#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>

int main (void) {
	FILE *SerialPort;
	int n_escr,n_leido;
	unsigned char BufEnvio[11];
	unsigned char BufRecep[11];
	char nom_puerto[20] = "/dev/ttyS1";
	int ChkSum;

	printf("Starting\n");

	SerialPort = fopen("/dev/ttyS1","rb+");

	if (SerialPort == NULL)
	{
		printf("ERROR -1: Error opening port %s\n",nom_puerto);
		return -1;
	}
	printf("Port open (%s)\n",nom_puerto);

	// Data that will be sent over the port
	BufEnvio[0]=0x0F;
	BufEnvio[1]=0x55;
	BufEnvio[2]=0x00;
	BufEnvio[3]=0x55;
	BufEnvio[4]=0xF0;

	n_escr = fwrite(BufEnvio, 1, 5, SerialPort);
	if (n_escr<0)
	{
		printf("ERROR -2: Error writing on port %s\n",nom_puerto);
		fclose(SerialPort);
		return -2;
	}

	n_leido = 0;
	do{
		n_leido = fread(BufRecep, 1, 11, SerialPort);
		if (n_leido<0)
		{
			printf("ERROR -3: Error reading on port %s\n",nom_puerto);
			fclose(SerialPort);
			return -3;
		}
	}while(n_leido<1);

	if((BufRecep[0]==0x0F) && (BufRecep[1]==0x55) && (BufRecep[9]==0x55) && (BufRecep[10]==0xF0))
	{
		ChkSum = BufRecep[2]+BufRecep[3]+BufRecep[4]+BufRecep[5]+BufRecep[6]+BufRecep[7];
		ChkSum = ChkSum % 255;
		if (ChkSum == BufRecep[8])
		{
			// All went fine
                        printf("Everything went fine. Program stops\n");
                        return 0;
		}
		else
		{
			printf("Error -5: ChkSum is wrong --> I have %d and received %d\n",ChkSum,BufRecep[8]);
			return -5;
		}
	}
	else
	{
		printf("ERROR -4: Frame error\n");
		printf("Element  \t value \t\thexadecimal\n");
		for(n_escr=0;n_escr<n_leido;n_escr++)
		{
			printf("   #%d\t\t  %03d\t\t    0x%02x\n", n_escr, BufRecep[n_escr], BufRecep[n_escr]);
		}
		return -4;
	}
}
