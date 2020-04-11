import serial.rs485
import minimalmodbus

def leia(reg) :
    ser=serial.rs485.RS485("/dev/ttyAMA0",19200)
    ser.rs485_mode = serial.rs485.RS485Settings()
    ser.rs485_mode.rts_level_for_tx=False # True
    ser.rs485_mode.rts_level_for_rx=True # False
    ser.timeout=0.7
    m = minimalmodbus.Instrument(ser.port,1)
    m.serial=ser
    m.debug=False
    try:
        valor=m.read_float(reg,3,2)
        m.serial.close()        
        return(valor)
    except IOError:
        print("# Failed to read from instrument")
        m.serial.close()
        return(0)    

def testa() :
    ser=serial.rs485.RS485("/dev/ttyAMA0",19200)
    ser.rs485_mode = serial.rs485.RS485Settings()
    ser.rs485_mode.rts_level_for_tx=False # True
    ser.rs485_mode.rts_level_for_rx=True # False
    ser.timeout=0.7
    m = minimalmodbus.Instrument(ser.port,1)
    m.serial=ser
    m.debug=False
    try:
        m.read_float(1,3,2)
        m.serial.close()
        return(1)
    except IOError:
        m.serial.close()
        return(0)    
