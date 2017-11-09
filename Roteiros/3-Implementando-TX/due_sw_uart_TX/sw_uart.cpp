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

// Funcao para calcular paridade impar
// retorna paridade
int calc_even_parity(due_sw_uart *uart, char data) {
	int soma = 0;
  int one = 0x01;
	for(int i = 0; i<uart->databits; i++) {
		soma += ((data>>i) & one);
	}
  int resultado = soma % 2;
	if (resultado == 0) {
		return 1;
	}
	else {
		return 0;
	}
}

// Funcao para enviar um char (data 8 bits) via uart
void sw_uart_write_byte(due_sw_uart *uart, char data) {
  
  // variável para armazenar paridade
  int parity = 0;

  // atualiza valor da paridade
  if(uart->paritybit == SW_UART_EVEN_PARITY) {
     parity = calc_even_parity(uart, data);
  } else if(uart->paritybit == SW_UART_ODD_PARITY) {
     parity = !calc_even_parity(uart, data);
  }
  
  // envia start bit
  digitalWrite(uart->pin_tx, LOW);
  _sw_uart_wait_T(uart);

  // envia payload
  int one = 0x01;
  for(int i = 0; i<uart->databits; i++) {
    int resultado = (data>>i) & one;
    digitalWrite(uart->pin_tx, resultado);
    _sw_uart_wait_T(uart);
  }

  // envia paridade, se existir
  if(uart->paritybit != SW_UART_NO_PARITY) {
  	digitalWrite(uart->pin_tx, parity);
    _sw_uart_wait_T(uart);
  }
  
  // envia stop bit, se existir
  digitalWrite(uart->stopbits, HIGH); //verificar se realmente é pin_tx ou stopbits
  for(int i = 0; i < uart->stopbits; i++) { //verificar se realmente é pin_tx ou stopbits
    digitalWrite(uart->stopbits, HIGH); //verificar se realmente é pin_tx ou stopbits
    _sw_uart_wait_T(uart);    
  }
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

