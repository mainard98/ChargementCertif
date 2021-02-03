#ifndef VIGIK_UART_MNGT_H_
#define VIGIK_UART_MNGT_H_

#include "stm32l5xx_hal.h"

/* change the size of the buffer */
#define UART_BUFFER_SIZE 3000

typedef struct
{
  unsigned char buffer[UART_BUFFER_SIZE];
  volatile unsigned int head;
  volatile unsigned int tail;
} ring_buffer;

/* Initialize the ring buffer */
void Ringbuf_init(void);

/* To use buffer in extern */
unsigned char* get_rx_buffer();

/* reads the data in the rx_buffer and increment the tail count in rx_buffer */
int Uart_read(void);

/* writes the data to the tx_buffer and increment the head count in tx_buffer */
void Uart_write(int c);

/* function to send data bytes array to the uart */
void Uart_sendDataArray(const uint8_t *data,  int size);

/* Print a number with any base
 * base can be 10, 8 etc*/
void Uart_printbase (long n, uint8_t base);

/* Checks if the data is available to read in the rx_buffer */
int IsDataAvailable(void);

/* Look for a particular string in the given buffer
 * @return 1, if the string is found and -1 if not found
 * @USAGE:: if (Look_for ("some string", buffer)) do something
 */
int Look_for (char *str, char *buffertolookinto);


/* Peek for the data in the Rx Bffer without incrementing the tail count 
* Returns the character
* USAGE: if (Uart_peek () == 'M') do something 
*/
int Uart_peek();


/* Copy the data from the Rx buffer into the bufferr, Upto and including the entered string 
* This copying will take place in the blocking mode, so you won't be able to perform any other operations
* Returns 1 on success and -1 otherwise
* USAGE: while (!(Copy_Upto ("some string", buffer)));
*/
int Copy_upto (char *string, char *buffertocopyinto);


/* Copies the entered number of characters (blocking mode) from the Rx buffer into the buffer, after some particular string is detected
* Returns 1 on success and -1 otherwise
* USAGE: while (!(Get_after ("some string", 6, buffer)));
*/
//int Get_after (char *string, uint8_t numberofchars, char *buffertosave);

int Get_after (char *string, uint8_t numberofchars, uint8_t *buffertosave);

/* Wait until a paricular string is detected in the Rx Buffer
* Return 1 on success and -1 otherwise
* USAGE: while (!(Wait_for("some string")));
*/
int Wait_for (char *string);


/* the ISR for the uart. put it in the IRQ handler */
void Uart_isr (UART_HandleTypeDef *huart);

#endif /* VIGIK_UART_MNGT_H_ */
