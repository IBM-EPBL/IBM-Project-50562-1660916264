from wiotp.sdk import device
import time

gpsConfig = {
    'identity' : {
        'orgId': 'f336wj',
        'typeId': 'GPS',
        'deviceId': 'GPS123'
    },
    'auth': {
        'token': '12345678'
    }
}

client = device.DeviceClient(gpsConfig)
client.connect()

lat = 13.0827
lon = 80.2707
while lat > 12.5:
    location = { 'name': 'Chennai Express', 'lat': lat, 'lon': lon }
    client.publishEvent(eventId="status", msgFormat="json", data=location, qos=0)
    lat -= 0.01
    lon -= 0.01
    time.sleep(1)
