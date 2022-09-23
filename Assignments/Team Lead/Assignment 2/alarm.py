import random

min_temp = 10
max_temp = 50

min_hum = 30
max_hum = 60

overflow = 20

def getRandomVal(min, max, overflow):
    return random.randrange(min - overflow, max + overflow)

outFile = open("alarm_out.txt", "w")

maxLoopCount = 100
for i in range(maxLoopCount):
    temp = getRandomVal(min_temp, max_temp, overflow)
    hum = getRandomVal(min_hum, max_hum, overflow)

    outFile.write("Temperature: " + str(temp) + "  \tHumidity: " + str(hum) + "\t-----")

    if (temp > max_temp or temp < min_temp and hum > max_hum or hum < min_hum):
        outFile.write("\tALARM: Temperature and Humidity not safe!")

    elif (temp > max_temp or temp < min_temp):
        outFile.write("\tALARM: Temp not safe!")
    
    elif (hum > max_hum or hum < min_hum):
        outFile.write("\tALARM: Humidity not safe!")
    
    else:
        outFile.write("\tNo Alarm!")

    outFile.write("\n")