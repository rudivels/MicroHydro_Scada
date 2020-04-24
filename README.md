# Programa para monitorar multimedidor via MQTT
Rudivels@ 30/02/2020

Programa para Raspberry que faça a leitura de valores elétricos um multimedidor com MODBUS-RTU e publica estes dados a cada 10 segundos via internet usando um servidor MQTT públic, além de armazena-los no próprio Raspberry.

## Apresentação
Este programa faz parte de um projeto de um central de monitoramento e comando de uma micro unidade geradora de energia elétrica numa localidade remota. Este central tem que monitorar a geração de energia elétrica e sua qualidade (potência, energia, fator de potência, interrupções de fornecimento, etc), e mandar essas informações via internet para um computador central onde será intergrada num sistema Supervisório Control and Data Aquisition (Scada).

Além disso, o central tem que perimitir a configuração e/ou reprogramação remota de um controlador de carga dessa micro unidade geradora de energia elétrica. O controlador de carga é implementado num microcontrolador Arduino que será documentado em outro repositório no meu github. 

Escolheu-se implementar o hardware do central com o Raspberry rodando raspbian (linux debian para Raspberry). O diagrama de bloco do sistema é mostrada no figura a seguir.  

![Diagrama de blocos](./Diagrama_blocos.jpg)


<img src="diagrama_blocoso.jpg" alt="Diagrama" title="Diagrama" width="450"  height="400" />

Um foto do hardware montado com o Raspberry, Conversor RS485, 4G Dongle e Display a mostrada a seguir.



<img src="foto_quadro.jpg" alt="Quadro" title="Quadro" width="450"  height="400" />



Este respositário detalhará a implementação do protocolo Modbus-RTU no Arduino, e a comunicação via MQTT a computador de monitoramento.
Os detalhes do controlador de carga e interface com display serão registrados em outro repositório git.


## Hardware
- Raspberry Pi com Raspbian
- Multimedior Sentron com interface RS485
- Conversor TTL RS485 half-duplex
- USB 4G Dongle

![Alt text](./conv_cmos_rs485.jpg)



 
## Software
- Rotina em Python para ler os dados do multimedidor
- Rotina em Pyhton para publicar os dados
- Script em bash que temporiza o envio
- Cron para carregar o programa na inicialização

Antes de rodar os programa tem que configurar o Raspberry para que habiliar a porta serial. Isso pode ser feito com o comando:
```
$ raspi-config
```
Outra preocupação é garantir a habilitação para que o módulo serial do Python consegue trabalhar no modo half-duplex. Isso é feito pela instalação do programa do rpirtsrtc disponível no <https://github.com/mholling/rpirtscts> num diretório de trabalho no Raspberry.
```
$ /home/pi/bin/rpirtscts on
```

### Rotina em Python para ler os dados do multimedidor


Nome do arquivo é <modmedidor.py> e implementa o protocolo MODBUS-RTU para fazer a leitura dos valores do medidor.

O nome da porta serial e o endereço do medidor está codificado diretamente na rotina. O nome da porta é "/dev/ttyAMA0" e o endereço é 1.

O parametro de entrada é o endereço da variavel a ser lido no multimedidor e o valor de retorno é o valor da variável.
 
### Rotina para publicar os dados
Nome do arquivo <publish_microhydro_002.py>

O parametros de entrada é o nome do logfile que armazena os dados locais.

A rotina implementa o protocolo cliente MQTT e o endereco do servidor MQTT é  <http://mqtt.eclipse.org> usando a porta 1883 e o topic é  ChapHydro.

Para garantir a integridade dos dados escolheu-se a opção de depois de cada operação de varredura do MODBUS e publicação dos dados com MQTT fechar todas as portas e arquivos.  

### Script para temporizar
Nome do arquivo <loop_publish.sh>

O script em bash foi a opção encontrada para chamar a rotina em Python e temporizar a publicação dos dados.
 
Para permitir a execução deste programa em background dessamarrado de um terminal aberto Raspberry, usa-se a seguinte comando:

```
nohup ./loop_publish.sh  & > /dev/null &
```

### Cron para carregar o programa na inicialização

O programa para configurar o cron é o 
```
$ crontab -e
```
Também pode-se editar o arquivo de configuração do cron diretamente. Nas ultimas linhas do arquivo adiciona os seguintes comandos.
```
@reboot /home/pi/bin/rpirtscts on
@reboot nohup /home/pi/src/MicroHydro_Scada/loop_publish.sh  & > /dev/null &
```

