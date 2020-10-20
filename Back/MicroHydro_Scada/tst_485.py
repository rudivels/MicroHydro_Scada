import serial.rs485
import minimalmodbus

#def leia(reg) :
ser=serial.rs485.RS485("/dev/ttyAMA0",19200)
ser.rs485_mode = serial.rs485.RS485Settings()
ser.rs485_mode.rts_level_for_tx=True #False # True
ser.rs485_mode.rts_level_for_rx=False #True # False
ser.timeout=0.7
m = minimalmodbus.Instrument(ser.port,1)
m.serial=ser
m.debug=False
i=1;
for i in range (0,1000):
      try:
             valor=m.read_float(1,3,2)
             print(i,'=',valor)
             print(valor);

      except IOError:
             print("#. ",i)

m.serial.close()



