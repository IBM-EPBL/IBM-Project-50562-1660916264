import random

def getTemp():
    return random.randint(-10, 70)

def getHumidity():
    return random.randint(10, 90)

def Temp(temperature):
    return temperature > 10 and temperature < 50

def Hum(humidity):
    return humidity > 30 and humidity < 60


with open("output.txt", "w") as out_file:
    for _ in range(25):
        temperature = getTemp()
        humidity = getHumidity()

        safe_temp_value = Temp(temperature)
        safe_hum_value= Hum(humidity)

        out_file.write(f"Temperature: {temperature}, Humidity: {humidity}\t-----\t")
        
        if not safe_temp_value and not safe_hum_value:
            out_file.write("Temperature and Humidity Not Safe!\n")
        elif not safe_temp_value:
            out_file.write("Temperature Not Safe!\n")
        elif not safe_temp_value:
            out_file.write("Humidity Not Safe!\n")
        else:
            out_file.write("All is well!\n")
