#include "sw_uart.h"
#pragma GCC optimize ("-O3")

void sw_uart_setup(due_sw_uart *uart, int rx, int tx, int stopbits, int databits, int paritybit) {
	uart->pin_tx     = tx;
	uart->pin_rx     = rx;
	uart->stopbits   = stopbits;
	uart->paritybit  = paritybit;
  uart->databits   = databits;
  pinMode(rx, INPUT);
  pinMode(tx, OUTPUT);
  digitalWrite(tx, HIGH);
}

void sw_uart_write_data(due_sw_uart *uart, char* bufferData, int writeN) {
  for(int i = 0; i < writeN; i++) {
    sw_uart_write_byte(uart, bufferData[i]);
  }
}

void sw_uart_write_string(due_sw_uart *uart, char* stringData) {
  sw_uart_write_data(uart, stringData, strlen(stringData));
}


// função para cálculo da paridade ímpar
int calc_even_parity(char data) {
  data = digitalRead(uart->pin_rx)
	int soma = 0;
  	int one = 1;
	for(i = 0; i<sw_uart->databits; i++) {
		soma += ((data>>i) & one);
	}
	if (soma % 2 == 0) {
		return 1;
	}
	else {
		return 0;
	}
  }

// função para recebimento de dados da serial
int sw_uart_receive_byte(due_sw_uart *uart, char* data) {
  data = digitalRead(uart->pin_rx)  
  
  //_sw_uart_wait_half_T(uart)

  // variável para recebimento de dados
  char nchar  = 0;
  
  // variável para cálculo da paridade
  char parity, rx_parity;
  
  // aguarda start bit
  bool cond = false
  while (cond = false){
    if (data == 0){
      _sw_uart_wait_half_T(uart)
      // confirma start BIT
      if (data == 0){
        // checa se bit ainda é 0
        if (data == 0){
          cond = true

        }

      }
    }
  }
  _sw_uart_wait_T(uart)

    
  // recebe dados
  for(int i = 0; i < uart->databits; i++) {
    data<<i
    nchar = data | nchar
    _sw_uart_wait_T(uart)
  }


  // recebe paridade
  parity = calc_even_parity(data)
  _sw_uart_wait_T(uart)

  // recebe stop bit
  int stopbit = digitalRead(uart->pin_rx)
  
  // checa paridade
  if(parity != rx_parity) {
    return SW_UART_ERROR_PARITY;
  }
  
  *data = nchar;
  return SW_UART_SUCCESS;
}

void sw_uart_write_byte(due_sw_uart *uart, char data) {
 
}

// MCK 21MHz
// 1093 para baudrate 9600/2
void _sw_uart_wait_half_T(due_sw_uart *uart) {
  for(int i = 0; i < 1093; i++)
    asm("NOP");
}

void _sw_uart_wait_T(due_sw_uart *uart) {
  _sw_uart_wait_half_T(uart);
  _sw_uart_wait_half_T(uart);
}

