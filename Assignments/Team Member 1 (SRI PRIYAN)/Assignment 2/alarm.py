import random

def getTemperature():
    return random.randint(-10, 60)

def getHumidity():
    return random.randint(10, 70)

def isTemperatureSafe(temperature: int):
    return temperature > 10 and temperature < 40

def isHumiditySafe(humidity: int):
    return humidity > 30 and humidity < 50


with open("output.txt", "w") as outfile:
    for _ in range(50):
        temperature = getTemperature()
        humidity = getHumidity()

        safeTemperature = isTemperatureSafe(temperature)
        safeHumidity = isHumiditySafe(humidity)

        outfile.write(f"Temperature: {temperature}, Humidity: {humidity}\t-->\t")
        
        if not safeTemperature and not safeHumidity:
            outfile.write("ALARM: Temperature and Humidity Not Safe!\n")
        elif not safeTemperature:
            outfile.write("ALARM: Temperature Not Safe!\n")
        elif not safeHumidity:
            outfile.write("ALARM: Humidity Not Safe!\n")
        else:
            outfile.write("Everything's Fine!\n")
            