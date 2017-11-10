# Projeto 9 : Serialização/Desserialização

## Introdução

O principal objetivo deste projeto é a serialização e desserialização de dados ao nível de programação mais baixo, a manipulação dos bits individuais. Para manipular a camada física do protocolo da comunicação utilizamos o C++, uma das únicas linguagens de programação capazes de manipular facilmente bits individuais de uma mensagem.

## Comunicação UART

Foi utilizada a comunicação UART (Universal Asynchoronous Receiver-Transmitter), ela não é um protocolo, mas sim um modo de enviar dados, sua principal característica é despensar a utilização de um clock externo para sincronizar o envio e recebimento de dados. Para que isso seja possível é necessário um circuito específico, por esta razão foram utilizados dois Arduinos Due para a comunicação.


## Onda gerada pelo programa
O programa gera uma onda, em teoria quadrada, com picos representando os bits 1 e os bits 0. Um exemplo de onda pode ser observado a seguir.







## Códigos
Existem 3 arquivos principais do projeto. O arquivo .ino é responsável pelo gerenciamento geral dos códigos, ele chama os outros arquivos que realizam as outras tarefas. O arquivo . cpp é  responsável por gerar a onda com a mensagem (em TX) e ler a mensagem (em RX). E o arquivo .h possui a criação de algumas funções que serão usadas em ambos os outros códigos.

### TX
O arquivo .cpp do TX é responsãvel pela geração da onda como citado anteriormente. Ele faz isso através de três principais funções:


**sw_uart_write_string**: Esta função irá receber uma string dada pelo arquivo .ino e irá converter cada char dessa string em bytes usando a função seguinte.

**sw_uart_write_data**: Esta função irá percorrer todos os chars da string inicial e irá gerar a onda a partir da função seguinte.

**sw_uart_write_byte**: Esta função é a que irá manipular diretamente como a onda será formada a partir dos bits recebidos e enviá-la ao pino TX do Arduino conectado. Para isso foi feito um simples protocolo de comunicação, onde por padrão a onda está configurada para o valor 1. Assim, quando o TX envia um sinal 0, este será o começo da mensagem (payload). O payload é enviado utilizando o byte recebido (8 bits contendo um caractere da string inicial) e realizando com ele um loop que realizará a cada iteração um shift para a direita e uma operação AND bit a bit com esse byte, realizamos esse processo todo pois como queremos controlar cada bit da onda, para isso realizamos a operação AND, ela irá "multiplicar" o bit menos significativo do byte e ignorar todos os outros (pois serão multiplicados por 0). Após o envio do payload, é(são) calculado(s) o(s) bit(s) de paridade somando todos os bits do byte e checando se existe resto quando dividido por 2. Após o envio do(s) bit(s) de paridade é(são) enviado(s) o(s) stop bit(s), lembrando que o stop bit será 1, para retornar ao estado natural do sistema.
