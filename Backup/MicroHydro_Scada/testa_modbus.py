# Hardware Raspberry PI, placa serial TTL - RS485, Multimedidor Sentron PAC3100
# Rudi van Els @ 29/02/2020
# Programa que implementa Protocolo Modbus e MQTT 

# Programa para ler Multi-Medidor Sentron PAC3100
# Hardware Raspberry Pi com SN75176 e optoisoladores

# Comversor RS485 - Placa WP 

# Para habilitar a porta no modo RS485 tem que rodar o programa 
# /home/pi/bin/rpirtscts on

# Interacao com KST-plot
# versao 03/03/2020 reduzindo espacos no publish
#                   versao testado no crontab <ok> com amostragem de a cada minuto
#                   inciar versao para gravar local em disco logfile
#                   renomeado para publish_microhydro_002.py
#                   tirando prints para nao sobrecarregar nohup.out
# Colocar um flag de debug para facilitar a depuracao e tirar os prints
#
# versao 08/03/2020 Preparando leitura de corrente e potencia
#                   Falta checar se a leitura do modbus foi bem sucedida
# versao 23/05/2020 Deixar um flag para sinalizar no dislay lcd que o modbus estah ok
#                   Quando o modbus nao funcionar nao gravar no logdisc...  para nao preencher espaco
#                   importante eh quando faltou comunicacao e quando voltou. 
# 
import mod_medidor
from datetime import datetime
from random import random 
import paho.mqtt.publish as publish
import time
import sys

if (len(sys.argv))==2 :
	# print ("# logfile  = ", sys.argv[1])
	logfile=True
else :
    logfile=False 

t=str(datetime.now())
agora=t[:19]

####
##   rotina para reduzir o string
##   s = str(agora) 
##   2020-03-03 01:38:36.519665
##   s[:21]
##   2020-03-03 01:38:36.5
##   2020-03-03 01:38:36
####

# Testa comunicacao modbus
# Se for ok continua .. se nao finalize com sys.exit(0) 
# e escreve mensagem no log..

#for i in (1,1000):


#mod_medidor.testa() 

if mod_medidor.testa()==0 :
    print("# " + str(agora) + "; Sem modbus ")
    if (logfile == True) :
        f = open(sys.argv[1],"a")
        f.write("# " + str(agora) + "; Sem modbus ")
        f.write("\n")
        f.close()
    sys.exit(0)

#------------------------------------------------------
# leia frequencia , tensao , corrente, fatorpotencia
frequencia = round(mod_medidor.leia(39),1)  # frequencia
tensao_A =   round(mod_medidor.leia(1),1)   # tensao 1
tensao_B =   round(mod_medidor.leia(3),1)   # tensao 2
tensao_C =   round(mod_medidor.leia(5),1)   # tensao 2

corrente_A  =   round(mod_medidor.leia(13),1)   # tensao 2
corrente_B  =   round(mod_medidor.leia(15),1)   # tensao 2
corrente_C  =   round(mod_medidor.leia(17),1)   # tensao 2

pot_ativa_A =   round(mod_medidor.leia(25),1)   # tensao 2
pot_ativa_B =   round(mod_medidor.leia(27),1)   # tensao 2
pot_ativa_C =   round(mod_medidor.leia(29),1)   # tensao 2

fator_pot   =   round(mod_medidor.leia(53),1)   # tensao 2

s = str(agora)+";"+str(frequencia)+";"+ str(tensao_A)+";"+str(tensao_B)+";"+str(corrente_A)+";"+str(corrente_B)+";"+str(corrente_C)+";"+str(pot_ativa_A)+";"+str(pot_ativa_B)+";"+str(pot_ativa_B)+";"+str(fator_pot)
# print("Data hora; Frequencia ; Tensao A ; Tensao B ")
# print(s)

#frequencia = round(60*random(),1) 
#tensao_A =   round(10*random(),1) 
#tensao_B =   round(100*random(),1) 
#------------------------------------------------------

#s = str(agora)+";"+str(frequencia)+";"+ str(tensao_A)+";"+str(tensao_B)
# publish.single("ChapHydro", s ,hostname="mqtt.eclipse.org")

print(s)
if (logfile == True) :
    f = open(sys.argv[1],"a")
    f.write(s)
    f.write("\n")
    f.close()
#
# print("Publicou dados ")
